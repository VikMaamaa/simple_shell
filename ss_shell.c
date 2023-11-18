#include "shell.h"

/**
 * prompt - print prompt to screen
 *
 * Return: Nothing
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * signal_handler - handle CTRL+C signal
 * @signum: signal that triggered the hanler
 *
 * Return: Nothing.
 */

void signal_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
	prompt();
}

/**
 * main - entry point, runs the shell program
 * @argc: number of arguments passed to the program
 * @argv: array of strings holding the arguments passed
 * to program
 * @env: the environment variables of process
 *
 * Return: Nothing
 */

int main(int argc, char *argv[], char **env)
{
	char *buf = NULL, **tokens = NULL, *absolute_path = NULL, **path = NULL;
	size_t n = 0, count = 0;
	ssize_t no_bytes;
	int exit_status = 0;

	(void) argc;
	while (1)
	{
		size_t i = 0;

		signal(SIGINT, signal_handler);
		prompt(), count++;
		no_bytes = getline(&buf, &n, stdin);
		if (no_bytes == EOF)
			_EOF(buf);
		tokens = _strtok(buf, " \n");
		if (tokens == NULL)
			continue;
		free(buf);
		if (_strcmp(tokens[0], "exit") == 0)
			exit_shell(tokens, argv[0], count, exit_status);
		else if (_strcmp(tokens[0], "cd") == 0)
			change_dir(tokens[1]), free_memory(tokens);
		else if (_strcmp(tokens[0], "env") == 0)
			print_env(), free_memory(tokens);
		else
		{
			path = getPath(env);
			do {
				absolute_path = get_full_cmd(path[i], tokens[0]);
				if (absolute_path)
					exit_status = child_process(tokens, absolute_path, argv[0], env);
				i++;
			} while (path[i] != NULL && absolute_path == NULL);
			free_memory(path);
			error_message(tokens, absolute_path, argv[0], count);
		}
		buf = NULL;
	}
	return (2);
}
