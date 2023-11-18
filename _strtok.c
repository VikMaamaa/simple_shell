#include "shell.h"

/**
 * _strtok - tokenizes a string and stores each token
 * in an array of strings
 * @str: string to tokenize
 * @delim: the delimeter by which strin is tokenized
 *
 * Return: array of strings storing tokens.
 */

char **_strtok(char *str, char *delim)
{
	char *token = NULL;
	size_t i = 0, len = 0;
	char **tokenArr = NULL;

	while (str[i] != '\0')
	{
		len++;
		i++;
	}
	i = 0;

	tokenArr = malloc((sizeof(char *) * len) + 1);
	token = strtok(str, delim);
	if (token == NULL)
	{
		free(tokenArr);
		return (NULL);
	}
	while (token)
	{
		tokenArr[i] = malloc(sizeof(char) * strlen(token) + 1);
		_strcpy(tokenArr[i], token);
		i++;
		token = strtok(NULL, delim);
	}

	tokenArr[i] = NULL;

	return (tokenArr);
}
