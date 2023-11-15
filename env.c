#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

char *_get_path(char *command, char *env) 
{
    char *path = NULL;
    char *path_var = strtok(env, "=");
    if (strcmp(path_var, "PATH") == 0) {
        path = strtok(NULL, "=");
    }

    return path;
}

char *get_path(char *command, char *env)
{
	return getenv("PATH");
}

char *get_file_path(char *path, char *command)
{
	char *dir = NULL;
	FILE *fp = NULL;
	char *file_path = NULL;
	size_t file_path_size = 0;


	file_path_size = strlen(path) + strlen(command) + 2; 
	file_path = malloc(file_path_size);

	if (file_path == NULL) 
	{
        	perror("Memory allocation error");
		exit(EXIT_FAILURE);
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
	return (file_path);
}

int main(int argc, char **argv, char **env)
{
	char *path = NULL;
	char *file_path = NULL;
	char *command = "ls";

	path = get_path(command, *env);
	file_path = get_file_path(path, command);

	if (file_path)
	{
		printf("Found: %s", file_path);
	}
	else
		printf("File not found");
		
	free(file_path);
}
