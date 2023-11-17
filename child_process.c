#include "shell.h"

/**
 * child_process - forks a process
 * @tokens: array of strings storing the commands
 * @absolute_path: the absolute path of command executable
 * @shell: name of the program
 * @env: environment variables of the process
 *
 * Return: Nothing.
 */

int child_process(char **tokens, char *absolute_path, char *shell, char **env)
{
	pid_t pid, wait_status;
	int status, exit_status;
	struct stat file_status;

	if (stat(tokens[0], &file_status) == 0 ||
			stat(absolute_path, &file_status) == 0)
	{
		pid = fork();

		if (pid < 0)
		{
			free_memory(tokens);
			free(absolute_path);
			perror("Error: (fork)");
			exit(errno);
		}
		else if (pid == 0)
		{
			exec_cmd(tokens, absolute_path, shell, env);
			free(absolute_path);
			free_memory(tokens);
			return (2);
		}
		else
		{
			wait_status = wait(&status);
			if (wait_status == -1)
			{
				free_memory(tokens);
				free(absolute_path);
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			free(absolute_path);
			free_memory(tokens);
		}
	}
	return (exit_status);
}
