#include "shell.h"

/**
 * free_memory - function that frees allocated memory
 * @buffer: The pointer allocated memory that will be freed
 *
 * Return: void (Nothing)
 */

void lose_memory(char **buffer) {
  if (buffer == NULL) {
    return;
  }

  for (size_t j = 0; buffer[j] != NULL; j++) {
    free(buffer[j]);
  }

  free(buffer);
}


