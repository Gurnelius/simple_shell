#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
* main - read user commands and
* executes.
*
* @argc: arguments count
* @argv: pointer to argument vectors
*
* Return: 0- success, 1 - fail.
*/
int main(int argc, char **argv)
{
	pid_t pid;
	char *command = NULL;
	size_t command_size = 0;
	char *args[2];
	ssize_t bytes_read; 

	while (1)
	{
		printf("#cisfun: ");
		bytes_read = getline(&command, &command_size, stdin);

		if (bytes_read == -1)
		{
			printf("\n");
			free(command);
			break;
		}

		command[bytes_read - 1] = '\0';

		pid = fork();

		if (pid < 0)
		{
			perror("Unkown error occurred.");
		}
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;

			execve(command, args, NULL);

			if (argc > 0)
				printf("%s : No such file or directory\n", argv[0]);
			return (1);
		}
		else
		{
		waitpid(pid, NULL, 0);
		}
	}
	return (0);
}
