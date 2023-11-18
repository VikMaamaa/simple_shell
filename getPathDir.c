#include "shell.h"

/**
 * getNewPath - get the paths to the command executables
 * @env: the environment variables
 *
 * Return: an array to the paths in PATH variable
 */

char **getNewPath(char **env) {
    char **dirs = NULL;
    char *var = NULL, *val = NULL, *var_dup = NULL;
    size_t i = 0;

    while (env[i] != NULL) {
        var_dup = _strdup(env[i]);
        var = strtok(var_dup, "=");
        while (var_dup != NULL) {
            i++;
            if (strcmp(var, "PATH") == 0) {
                val = strtok(NULL, "\n");
                dirs = _strtok(val, ":");
                free(var_dup);
                return dirs;
            }
            free(var_dup);
            var_dup = _strdup(env[i]);
            var = strtok(var_dup, "=");
        }
    }
    return NULL;
}

/**
 * get_cmd - get the full path to the executable
 * @path: the directory to use in PATH environment variable
 * @command: the command to be run
 *
 * Return: the full path to the command executable
 */

char *get_cmd(char *path, char *command) {
    char *full_path = NULL;

    // Allocate memory for the full path including the null terminator.
    full_path = malloc(strlen(path) + strlen(command) + 2);

    if (full_path != NULL) {
        // Copy the path to the full path buffer.
        strcpy(full_path, path);

        // Append the command to the full path.
        strcat(full_path, "/");
        strcat(full_path, command);

        // Check if the full path or the command is executable.
        if (access(full_path, X_OK) == 0 || access(command, X_OK) == 0) {
            return full_path;
        }
    }

    // Free the allocated memory if necessary.
    free(full_path);

    // Return NULL if no executable path was found.
    return NULL;
}

/**
 * execute_cmd - executes the command (first string in tokens)
 * @tokens: array of strings that stores the commands
 * @shell: name of the shell
 * @absolute_path: the full path of command executable
 * @env: the environment variables of the process
 *
 * Return: Nothing.
 */

int execute_cmd(char **tokens, char *absolute_path, char *shell, char **env) {
  struct stat file_status;

  // Check if the first token exists as a file
  if (stat(tokens[0], &file_status) == 0) {
    // If the first token is a file, execute it directly
    if (execve(tokens[0], tokens, env) == -1) {
      free_memory(tokens);
      perror(shell);
      return 2;
    }
  } else {
    // Check if the absolute path exists as a file
    if (stat(absolute_path, &file_status) == 0) {
      // If the absolute path exists, execute the command using the absolute path
      if (execve(absolute_path, tokens, env) == -1) {
        free_memory(tokens);
        free(absolute_path);
        perror(shell);
        return 2;
      }
    }
  }

  // If the command was not found, fork a child process and execute the shell
  pid_t child_pid = fork();
  if (child_pid == 0) {
    // Child process
    if (execve(shell, tokens, env) == -1) {
      free_memory(tokens);
      perror(shell);
      exit(2);
    }
  } else if (child_pid > 0) {
    // Parent process
    int status;
    wait(&status);

    // Check the exit status of the child process
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
      return WEXITSTATUS(status);
    }
  } else {
    // Fork failed
    perror("fork");
    return 1;
  }

  return 0;
}

/**
 * err_message - prints error message
 * @tokens: array of strings storing the command and its
 * arguments
 * @full_path: the absolute path to the command executable
 * @shell: name of the shell program
 * @count: count of commands run in shell
 *
 * Return: Nothing.
 */

void err_message(char **tokens, char *full_path, char *shell, size_t count) {
  char count_char = count + '0';

  if (full_path == NULL) {
    printf("%s: %zu: %s: not found\n", shell, count, tokens[0]);
    free_memory(tokens);
  }
}
