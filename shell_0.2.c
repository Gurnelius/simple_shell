#include "main.h"
#include "utils.h"

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
	size_t buffer_size = 0;
	char **args = NULL;
	ssize_t chars_count;

	(void)argc;

	while (1)
	{
		printf("#cisfun: ");
		chars_count = getline(&command, &buffer_size, stdin);
		if (chars_count == -1)
		{
			free(command);
			break;
		}

		args = (char **)malloc(sizeof(char *) * (int) chars_count);

		pid = fork();
		if (pid < 0)
		{
			printf("Unkown error occurred.");
		}
		else if (pid == 0)
		{
			tokenize(command, args);
			execve(args[0], args, env);
			free(args);
			printf("%s : No such file or directory\n", argv[0]);
			return (1);
		}
		else
			waitpid(pid, NULL, 0);
	}
	return (0);
}
