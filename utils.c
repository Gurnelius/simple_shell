#include "main.h"

/**
 * tokenize - tokenize a string
 *
 * @command: pointer to the string to tokenize
 * @args: pointer to pointer to tokens
 *
 * Returns: Nothing
 */
void tokenize(char *command, char **args)
{
	char *token = NULL;
	int a = 0;

	token = strtok(command, " \n");

	while (token)
	{
		args[a] = token;
		token = strtok(NULL, " \n");
		a++;
	}
	args[a] = NULL;
}

/**
 * get_file_path - get the path of a file
 *
 * @path: path string
 * @command: the file to find
 *
 * Return: file path
 */
char *get_file_path(char *path, char *command)
{
	char *dir = NULL;
	FILE *fp = NULL;
	char *file_path = NULL;
	size_t file_path_size = 0;

	if (path == NULL || command == NULL)
		return (NULL);

	file_path_size = strlen(path) + strlen(command) + 2;
	file_path = malloc(file_path_size);

	if (file_path == NULL)
		return (NULL);
	dir = strtok(path, ":");

	while (dir != NULL)
	{
		snprintf(file_path, file_path_size, "%s/%s", dir, command);
		fp = fopen(file_path, "r");

		if (fp != NULL)
			break;
		dir = strtok(NULL, ":");
	}
	if (fp)
	{
		fclose(fp);
		return (file_path);
	}
	else
	{
		free(file_path);
		return (NULL);
	}
}
