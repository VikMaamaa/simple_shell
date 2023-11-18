#include "shell.h"

/**
 * print_env - print environment variables and values
 *
 * Return: Nothing.
 */

void print_env(void)
{
	size_t i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i])); /* use _strlen() */
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
