#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

char* read_input() {
  char* input = (char*) malloc(MAX_INPUT_SIZE);
  fgets(input, MAX_INPUT_SIZE, stdin);
  if (feof(stdin)) {
    exit(0);
  }
  return input;
}

void parse_input(char* input, char** tokens, int* token_count) {
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

int main() {
  char *tokens[MAX_TOKENS];
  int token_count;
  char* input;
  char *prompt = "#cisfun$ ";

  while (1) {
    printf("%s", prompt);
    input = read_input();
    parse_input(input, tokens, &token_count);

    if (token_count > 0) {
      pid_t pid = fork();
      if (pid == 0) {
        execvp(tokens[0], tokens);
        perror("./shell");
        exit(1);
      } else if (pid < 0) {
        perror("./shell");
      } else {
        wait(NULL);
      }
    }

    free(input);
  }

  return 0;
}

