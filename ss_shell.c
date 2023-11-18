#include "shell.h"
#include <csignal>

/**
 * prompt_new - print prompt to screen
 *
 * Return: Nothing
 */

void prompt_new(void) {
  if (isatty(STDIN_FILENO)) {
    printf("$> ");
  }
}

/**
 * sig_handler - handle CTRL+C signal
 * @signum: signal that triggered the hanler
 *
 * Return: Nothing.
 */

void sig_handler(int sig) {
  (void) sig; // Suppress unused parameter warning

  // Print a newline character to indicate the interruption
  write(STDOUT_FILENO, "\n", 1);

  // Display the prompt to continue interacting with the shell
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

int main(int argc, char *argv[], char **env) {
  char *buf = NULL, **tokens = NULL, *absolute_path = NULL, **path = NULL;
  size_t n = 0, count = 0;
  ssize_t bytes_read;
  int exit_status = 0;

  (void)argc; // Unused parameter

  while (1) {
    size_t i = 0;

    // Handle signals for interrupting the shell
    signal(SIGINT, signal_handler);

    // Display the prompt and increment the command count
    prompt();
    count++;

    // Read the input line using getline
    bytes_read = getline(&buf, &n, stdin);

    // Check for EOF
    if (bytes_read == EOF) {
      _EOF(buf); // Handle EOF error
    }

    // Tokenize the input line using _strtok
    tokens = _strtok(buf, " \n");

    // Check for empty commands
    if (tokens == NULL) {
      continue;
    }

    // Free the buffer allocated by getline
    free(buf);

    // Handle built-in commands
    if (strcmp(tokens[0], "exit") == 0) {
      exit_shell(tokens, argv[0], count, exit_status);
    } else if (strcmp(tokens[0], "cd") == 0) {
      change_dir(tokens[1]);
      free_memory(tokens);
    } else if (strcmp(tokens[0], "env") == 0) {
      print_env();
      free_memory(tokens);
    } else {
      // Search for the executable command in the PATH environment variable
      path = getPath(env);

      do {
        absolute_path = get_full_cmd(path[i], tokens[0]);

        if (absolute_path) {
          // Execute the command using child_process
          exit_status = child_process(tokens, absolute_path, argv[0], env);
          break;
        }

        i++;
      } while (path[i] != NULL && absolute_path == NULL);

      // Free the PATH array
      free_memory(path);

      // Display an error message if the command was not found
      if (absolute_path == NULL) {
        error_message(tokens, absolute_path, argv[0], count);
      }
    }

    // Reset the buffer pointer
    buf = NULL;
  }

  return (2);
}
