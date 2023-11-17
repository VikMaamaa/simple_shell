#include "shell.h"

/**
 * _isdigit - function that checks if input is a number
 * @num: the input to check
 *
 * Return: 1 if num is a number, 0 otherwise
 */
int _isdigit(char *num)
{
	int i;

	if (num == NULL)
		return (0);

	for (i = 0; num[i] < '0' || num[i] > '9'; i++)
		return (0);
	return (1);
}

/**
 * _atoi - function that converts a string to an integer
 * @s: the string to convert
 * Return: the resulting integer
 */

int _atoi(char *s)
{
	int i, sign = 1;
	unsigned int num = 0;

	/**
	 * check for characters outside the range of 0 - 9
	 * to see if any equals '-' character
	 */
	for (i = 0; (s[i] < '0' || s[i] > '9') && s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;
	}

	/**
	 * check for characters within 0 - 9 range
	 * and covert them to int to give overall number
	 */
	for (i = 0; (s[i] >= 48 && s[i] <= 57) && s[i] != '\0'; i++)
		num = (num * 10) + (s[i] - '0');

	return (num * sign);
}

/**
 * exit_shell - function that exits the shell
 * @args: pointer to tokenized command
 * @shell: the name of the shell program
 * @count: number of times commands are run in the shell
 * @exit_status: exit status
 *
 * Return: void (Nothing)
 */
void exit_shell(char **args, char *shell, size_t count, int exit_status)
{
	int status = 0;
	char count_char = count + '0';

	if (args[1] == NULL)
	{
		free_memory(args);
		exit(exit_status);
	}

	if (_isdigit(args[1]))
	{
		status = _atoi(args[1]);
		if (status > 255) /* MAX EXIT STATUS VALUE */
			status = status % 256;
		if (status < 0)
		{
			write(STDOUT_FILENO, shell, _strlen(shell));
			write(STDOUT_FILENO, ": ", 2), write(STDOUT_FILENO, &count_char, 1);
			write(STDOUT_FILENO, ": ", 2);
			write(STDOUT_FILENO, args[0], _strlen(args[0]));
			write(STDOUT_FILENO, ": ", 2), write(STDOUT_FILENO, "Illegal number", 14);
			write(STDOUT_FILENO, ": ", 2);
			write(STDOUT_FILENO, args[1], _strlen(args[1]));
			write(STDOUT_FILENO, "\n", 1), status = 2;
		}
	}
	else
	{
		write(STDOUT_FILENO, shell, _strlen(shell));
		write(STDOUT_FILENO, ": ", 2), write(STDOUT_FILENO, &count_char, 1);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, args[0], _strlen(args[0]));
		write(STDOUT_FILENO, ": ", 2), write(STDOUT_FILENO, "Illegal number", 14);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, args[1], _strlen(args[1]));
		write(STDOUT_FILENO, "\n", 1);
		status = 2;
	}
	free_memory(args);
	exit(status);
}

/**
 * _EOF - function that handles "end of file" condition
 * @buf: the input
 *
 * Return: void (nothing)
 */
void _EOF(char *buf)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buf);
	exit(EXIT_SUCCESS);
}
