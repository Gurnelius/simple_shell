#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char* args[MAX_COMMAND_LENGTH];
	int i = 0;
	pid_t pid;

	while (1)
	{
		printf(":) ");

		fgets(command, MAX_COMMAND_LENGTH, stdin);

		command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
		break;

		args[i] = strtok(command, " ");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}
		args[i] = NULL;

		pid = fork();
		if (pid == -1) {
			printf("Error: Failed to fork process\n");
        	}
		else if (pid == 0)
		{
			execvp(args[0], args);
			printf("Error: Failed to execute command '%s'\n", args[0]);
			exit(1);
		}
		else
			wait(NULL);
	}

	return 0;
}
