#include "../../include/bash.h"
#include <stdlib.h>

// void debug_print(char *str){
//     int i = 0;
//     while(1){
//         if(str[i] == '\0'){
//             printf("[NULL]");
//             i++;
//         } else if(str[i] == '\n'){
//             printf("[NEWLINE]");
//             break;
//         } else if(str[i] == ' '){
//             printf("[SPACE]");
//             i++;
//         } else {
//             printf("%c", str[i]);
//             i++;
//         }
//     }
// }

int main(){

	while(1){
		char buffer[1024];
		char *args[64];
		char *args1[64];
		int pipefd[2];
		printf("\nEnter the command -> ");
		fgets(buffer, sizeof(buffer), stdin);


		split_pipe(buffer, args, args1);

		printf("\n");

		if (args1[0] != NULL) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid_t proc1 = fork();
            if (proc1 == (pid_t)-1){
            	perror("fork");
            	exit(EXIT_FAILURE);
            }

            if (proc1 == 0) {
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1){
                	perror("dup2");
                 	exit(EXIT_FAILURE);
                }
                close(pipefd[1]);
                if (execvp(args[0], args) == -1){
	               	perror("execvp");
	                exit(EXIT_FAILURE);
                }
            }

            pid_t proc2 = fork();
            if (proc2 == (pid_t)-1){
            	perror("fork");
            	exit(EXIT_FAILURE);
            }

            if (proc2 == 0) {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                execvp(args1[0], args1);
                if (execvp(args[0], args) == -1){
	               	perror("execvp");
	                exit(EXIT_FAILURE);
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        } else {
            pid_t proc = fork();
            if (proc == (pid_t)-1){
            	perror("fork");
            	exit(EXIT_FAILURE);
            }

            if (proc == 0) {
                execvp(args[0], args);
                if (execvp(args[0], args) == -1){
	               	perror("execvp");
	                exit(EXIT_FAILURE);
                }
            }
            wait(NULL);
        }

	}
}
