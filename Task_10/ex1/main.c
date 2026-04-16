#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t proc = fork();

	if (proc > 0){
		int status = 0;
		printf("This Parent\nPID: %d\nPPID: %d\n", getpid(), getppid());
		pid_t finished_proc = wait(&status);
		if (finished_proc == -1){
			perror("Error! Wait failed!");
		} else {
			printf("\nWait success!\nStatus: %d", WEXITSTATUS(status));
		}
	} else if(proc == 0){
		printf("\nThis Child\nPID: %d\nPPID: %d\n", getpid(), getppid());
		exit(23);
	} else{
		perror("\nError! fork failed!\n");
	}
}
