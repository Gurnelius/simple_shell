#include <stddef.h>
#include <string.h>

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
