#include "main.h"
#include "utils.h"
#include "utils2.h"

/**
* main - read user commands and
* executes.
*
* @argc: arguments count
* @argv: pointer to argument vectors
* @env: environment variables
*
* Return: 0- success, 1 - fail.
*/

int main(int argc, char **argv, char **env)
{
	pid_t pid;
	char *command = NULL;
	size_t command_size = 0;
	char *args[2];
	ssize_t bytes_read;
	(void) argc;

	while (1)
	{
		if (isatty(0))
			printf("#cisfun: ");
		bytes_read = getline(&command, &command_size, stdin);
		if (bytes_read == -1)
		{
			return (EXIT_FAILURE);
		}

		command[bytes_read - 1] = '\0';
		pid = fork();
		if (pid < 0)
		{
			_puts("Unkown error occurred.\n");
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;
			execve(command, args, env);
			printf("%s: No such file or directory\n", argv[0]);
			return (EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	free(command);
	return (EXIT_SUCCESS);
}
