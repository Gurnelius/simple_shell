#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
char *_get_path(char *command, char *env) 
{
    char *path = NULL;
    char *path_var = strtok(env, "=");
    if (strcmp(path_var, "PATH") == 0) {
        path = strtok(NULL, "=");
    }

    return path;
    }
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
	{
        	perror("Memory allocation error");
E
		return (NULL);
	}

	dir = strtok(path, ":");
	
	while(dir != NULL)
	{
		snprintf(file_path, file_path_size, "%s/%s", dir, command);
		fp = fopen(file_path, "r");

		if(fp != NULL)
		{
			break;
		}

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
