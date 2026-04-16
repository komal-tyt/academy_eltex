#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t proc1 = fork();

	if (proc1 > 0){
		printf("\nThis Parent(proc1 and proc2)\nPID: %d\nPPID: %d\n", getpid(), getppid());

		pid_t proc2 = fork();

		if (proc2 > 0){
			int status_proc1 = 0;
			int status_proc2 = 0;

			pid_t finished_proc1 = wait(&status_proc1);
			if(finished_proc1 == -1){
				perror("\nError! Wait proc1 failed!\n");
			}else{
				printf("\nWait proc1 success!\nStatus proc1: %d\n", WEXITSTATUS(status_proc1));
			}

			pid_t finished_proc2 = wait(&status_proc2);
			if(finished_proc2 == -1){
				perror("\nError! Wait proc2 failed!\n");
			}else{
				printf("\nWait proc2 success!\nStatus proc2: %d\n", WEXITSTATUS(status_proc2));
			}


		}else if(proc2 == 0){
			printf("\nThis Proc2(parent proc5)\nPID: %d\nPPID: %d\n", getpid(), getppid());

			pid_t proc5 = fork();

			if(proc5 > 0){
				int status_proc5 = 0;
				pid_t finished_proc5 = wait(&status_proc5);
				if(finished_proc5 == -1){
					perror("\nError! Wait proc5 failed!\n");
				}else{
					printf("\nWait proc5 success!\nStatus proc5: %d\n", WEXITSTATUS(status_proc5));
				}

			}else if (proc5 == 0){
				printf("\nThis Proc5\nPID: %d\nPPID: %d\n", getpid(), getppid());
				exit(105);
			}else{
				perror("\nError! fork(proc5) failed!\n");
			}

			exit(102);
		} else{
			perror("\nError! fork(proc2) failed!\n");
		}

	} else if(proc1 == 0){
		printf("\nThis Proc1(parent proc3 and proc4)\nPID: %d\nPPID: %d\n", getpid(), getppid());

		pid_t proc3 = fork();

		if (proc3 > 0){

			pid_t proc4 = fork();

			if(proc4 > 0){
				int status_proc3 = 0;
				int status_proc4 = 0;

				pid_t finished_proc3 = wait(&status_proc3);

				if(finished_proc3 == -1){
					perror("\nError! Wait proc3 failed!\n");
				}else{
					printf("\nWait proc3 success!\nStatus proc3: %d\n", WEXITSTATUS(status_proc3));
				}

				pid_t finished_proc4 = wait(&status_proc4);

				if(finished_proc4 == -1){
					perror("\nError! Wait proc4 failed!\n");
				}else{
					printf("\nWait proc4 success!\nStatus proc4: %d\n", WEXITSTATUS(status_proc4));
				}


			} else if(proc4 == 0){
				printf("\nThis Proc4\nPID: %d\nPPID: %d\n", getpid(), getppid());
				exit(104);
			} else {
				perror("\nError! fork(proc4) failed!\n");
			}

		} else if (proc3 == 0){
			printf("\nThis Proc3\nPID: %d\nPPID: %d\n", getpid(), getppid());
			exit(103);
		}else{
			perror("\nError! fork(proc3) failed!\n");
		}

		exit(101);
	} else{
		perror("\nError! fork(proc1) failed!\n");
	}
}
