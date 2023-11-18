#include "shell.h"

/**
 * _strlen - function that returns the length of a string
 * @s: the string whose length is evaluated
 *
 * Return: the length/count of the string
 */
int _strlen( char *s) {
    int length = 0;

    while (*s != '\0') {
        length++;
        s++;
    }

    return length;
}


/**
 * _strcpy - function that copies the string pointed to by src
 * including the terminating null byte (\0), to the buffer pointed to by dest
 *
 * @dest: the destination
 * @src: the source
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest,  char *src) {
    if (!dest || !src) {
        return NULL;
    }

    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}


/**
 * _strcat - function that concatenates two strings
 *
 * @dest: destination string
 * @src: source string
 *
 * Return: a pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src) {
    if (!dest || !src) {
        return NULL;
    }

    int destLength = 0;
    while (dest[destLength] != '\0') {
        destLength++;
    }

    // Append a path separator if the destination string doesn't already end with one
    if (dest[destLength - 1] != '/') {
        dest[destLength++] = '/';
    }

    int i = 0;
    while (src[i] != '\0') {
        dest[destLength + i] = src[i];
        i++;
    }

    dest[destLength + i] = '\0';
    return dest;
}

/**
 * _strcmp - function that compares two strings
 *
 * @s1: the first string
 * @s2: the seond string
 *
 * Return: 0, if s1 and s2 are equal, a -ve value if s1 < s2
 * or +ve value if s1 > s2
 */
int _strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 < *s2) {
            return (*s1 - *s2);
        } else if (*s1 > *s2) {
            return (*s1 - *s2);
        }

        s1++;
        s2++;
    }

    // Handle the case where both strings reached the null terminator
    return (*s1 - *s2);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: duplicated string
 */

char *_strdup(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t strLen = strlen(str);
    char *dupStr = malloc(strLen + 1);
    if (!dupStr) {
        return NULL;
    }

    memcpy(dupStr, str, strLen);
    dupStr[strLen] = '\0';

    return dupStr;
}
