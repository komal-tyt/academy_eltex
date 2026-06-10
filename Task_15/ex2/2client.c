#include <bits/types/siginfo_t.h>
#include <complex.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* args[]){
	if (argc != 2){
		perror("I dont see pid!!");
		exit(EXIT_FAILURE);
	}

	pid_t pid = atoi(args[1]);

	if (kill(pid, SIGINT) == -1){
		perror("kill");
		exit(EXIT_FAILURE);
	}
}
