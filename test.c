#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PATH_LENGTH 1000
#define MAX_COMMAND_LENGTH 100

char *fetch_path(char *command, char *env) {
    char *path = NULL;
    char *path_var = strtok(env, "="); // Splitting PATH environment variable
    if (strcmp(path_var, "PATH") == 0) {
        path = strtok(NULL, "=");
    }

    return path;
}

int main(int argc, char **argv, char **env) {
    char *command = NULL;
    size_t buffer_size = 0;
    ssize_t chars_count;

    while (1) {
        printf("#cisfun: ");
        chars_count = getline(&command, &buffer_size, stdin);

        if (chars_count == -1) {
            free(command);
            break;
        }

        command[strcspn(command, "\n")] = 0; // Remove newline

        char *path = fetch_path("PATH", *env);
        char *dir = strtok(path, ":");

        int found = 0;

        while (dir != NULL) {
            char path_command[MAX_PATH_LENGTH];
            snprintf(path_command, sizeof(path_command), "%s/%s", dir, command);

            FILE *fp = fopen(path_command, "r");
            if (fp != NULL) {
                found = 1;
                fclose(fp);
                pid_t pid = fork();

                if (pid < 0) {
                    perror("Fork error");
                } else if (pid == 0) {
                    char *args[] = {path_command, NULL};
                    execve(path_command, args, env); // Execute the command in the child process
                    perror("Execution error");
                    exit(EXIT_FAILURE);
                } else {
                    wait(NULL); // Wait for the child process to finish
                    break; // Command found and executed, break from loop
                }
            }

            dir = strtok(NULL, ":");
        }

        if (!found) {
            printf("Command not found\n");
        }
    }

    return 0;
}

