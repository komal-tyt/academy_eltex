#include <bits/types/siginfo_t.h>
#include <complex.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler(){
	printf("Signal SIGUSR1\n");
}

int main(){
	struct sigaction act = {0};

	pid_t pid = getpid();
	printf("My pid: %d\n", pid);

	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &act, NULL) == -1){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	while(1);
}
