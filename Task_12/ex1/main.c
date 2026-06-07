#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pipefd[2];
	char buffer[100];
	pid_t cpid;

	if (pipe(pipefd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == (pid_t)-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer));
		printf("%s\n", buffer);
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	}else{
		close(pipefd[0]);
		write(pipefd[1], "Hi!", 3);
		close(pipefd[1]);
		wait(NULL);
	}


}
