/**
  * --------------------------PROJECT ASSIGNMENT 2---------------------------
  * @author Sneha Dipankar Roy (sr0069@uah.edu)
  * @class CS590-01 Summer 2016
  * @date 19th July 2016
  * @desc Command line processor which is capable of running other programs
  * -------------------------------------------------------------------------
  */

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	// Variable declaration
	char command[500];
	char *argv[30];
	char *token;
	int i = 0, j, k;
	pid_t pid;
	int status;
	strcpy(command, "echo");
	do {
		printf("CS590-sh> ");	// Shell's prompt name
		scanf("%[^\n]s",command);	// Takes command from user
		getchar();
		fflush(stdin);		// Flushes the stdin buffer
		// String tokenizer to parse input
		token = strtok(command, " ");
		while (token != NULL) {
			argv[i] = token;
			// Reads argument in double quotes from command
			for(j = 0; j < strlen(argv[i]); j++) {
				if (argv[i][j] == '\"')
					for(k = j; k < strlen(argv[i]); k++) 
						argv[i][k] = argv[i][k+1];
			}
			i++;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		// Exits loop when command is 'exit'
		if (strcmp(argv[0], "exit") == 0) {
			exit(0);
		}
		pid = fork();	// Creates child process
		// Prints error message and exits loop if fork() fails
		if (pid < 0) {
			printf("Fork error.\n");
			exit(1);
		}
		/*-------------------------Child Process-------------------------*/
		else if (pid == 0) {
			// Executes program file as per command
			if (execvp(argv[0], argv) < 0) {
				printf("%s: command not found\n", command);
			}
			exit(0);
		}
		/*-------------------------Parent Process-------------------------*/
		else if (pid > 0) {
			wait(&status);
			strcpy(command, "echo");
			i = 0;
		}
	} while (strcmp(command, "exit") != 0);
	return 0;
}
