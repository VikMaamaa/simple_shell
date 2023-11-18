#include "shell.h"

/**
 * getPath - get the paths to the command executables
 * @env: the environment variables
 *
 * Return: an array to the paths in PATH variable
 */

char **getPath(char **env)
{
	char **dir = NULL, *var = NULL, *val = NULL, *var_dup = NULL;
	size_t i = 0;

	var_dup = _strdup(env[i]);
	var = strtok(var_dup, "=");
	while (var_dup != NULL)
	{
		i++;
		if (strcmp(var, "PATH") == 0)
		{
			val = strtok(NULL, "\n");
			dir = _strtok(val, ":");
			free(var_dup);
			return (dir);
		}
		free(var_dup);
		var_dup = _strdup(env[i]);
		var = strtok(var_dup, "=");
	}
	return (NULL);
}

/**
 * get_full_cmd - get the full path to the executable
 * @path: the directory to use in PATH environment variable
 * @command: the command to be run
 *
 * Return: the full path to the command executable
 */

char *get_full_cmd(char *path, char *command)
{
	char *full_path = NULL;

	full_path = malloc(_strlen(path) + _strlen(command) + 2);

	if (full_path != NULL)
	{
		_strcpy(full_path, path);
		_strcat(full_path, command);
		if (access(full_path, X_OK) == 0 || access(command, X_OK) == 0)
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

/**
 * exec_cmd - executes the command (first string in tokens)
 * @tokens: array of strings that stores the commands
 * @shell: name of the shell
 * @absolute_path: the full path of command executable
 * @env: the environment variables of the process
 *
 * Return: Nothing.
 */

int exec_cmd(char **tokens, char *absolute_path, char *shell, char **env)
{
	struct stat file_status;

	if (stat(tokens[0], &file_status) == 0)
	{
		if (execve(tokens[0], tokens, env) == -1)
		{
			free_memory(tokens);
			perror(shell);

			return (2);
		}
	}
	else if (stat(absolute_path, &file_status) == 0)
	{
		if (execve(absolute_path, tokens, env) == -1)
		{
			free_memory(tokens);
			free(absolute_path);
			perror(shell);

			return (2);
		}
	}
	return (0);
}

/**
 * error_message - prints error message
 * @tokens: array of strings storing the command and its
 * arguments
 * @full_path: the absolute path to the command executable
 * @shell: name of the shell program
 * @count: count of commands run in shell
 *
 * Return: Nothing.
 */

void error_message(char **tokens, char *full_path, char *shell, size_t count)
{
	char count_char = count + '0';

	if (full_path == NULL)
	{
		write(STDOUT_FILENO, shell, _strlen(shell));
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, &count_char, 1);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, tokens[0], _strlen(tokens[0]));
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, "not found\n", 10);
		free_memory(tokens);
	}
}
