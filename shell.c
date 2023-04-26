#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100
/**
* read_input - capture user input
* Return: pointer to char input
*/
char *read_input()
{
	char *input = (char *) malloc(MAX_INPUT_SIZE);

	fgets(input, MAX_INPUT_SIZE, stdin);
	if (feof(stdin))
		exit(0);
	return (input);
}
/**
* parse_input - Function to parse the user input
* The tokens and token count will be accessed by main.
* @input: pointer to input
* @tokens: pointer to tokens
* @token_count: number of tokens
* Return: nothing
*/
void parse_input(char *input, char **tokens, int *token_count)
{
	char *token;

	*token_count = 0;
	token = strtok(input, " \n");

	while (token != NULL && *token_count < MAX_TOKENS)
	{
		tokens[(*token_count)++] = token;
		token = strtok(NULL, " \n");
	}
	tokens[*token_count] = NULL;
}
/**
* main - Entry point.
* @argc: number of arguments
* @argv: pointer to arguments
* Return: 0 Always
*/
int main(int argc, char *argv[])
{
	char *tokens[MAX_TOKENS];
	int token_count;
	char *input;
	char *prompt = "#cisfun$ ";

	pid_t pid;

	while (1)
	{
		printf("%s", prompt);
		input = read_input();
		parse_input(input, tokens, &token_count);

		if (token_count > 0)
		{
			pid = fork();

			if (pid == 0)
			{
				execvp(tokens[0], tokens);
				if (argc > 0)
					perror(argv[0]);
				exit(1);
			}
			else if (pid < 0)
				perror(argv[0]);
			else
				wait(NULL);
		}

		free(input);
	}

	return (0);
}
