#include "../../include/bash.h"

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
		printf("\nEnter the command -> ");
		fgets(buffer, sizeof(buffer), stdin);

		// debug_print(buffer);

		remove_space(buffer);

		// printf("\n");

		// debug_print(buffer);

		split(buffer, args);

		// printf("\n");

		pid_t proc = fork();

		if (proc > 0){
			int status = 0;
			pid_t finished_proc = wait(&status);
			if (finished_proc == -1){
				perror("Error! Wait failed!");
			}
		} else if (proc == 0){
			printf("\n");
			execvp(args[0], args);
			perror("execvp error!");
			exit(23);
		} else{
			perror("Error!fork failed!");
		}

	}
}
