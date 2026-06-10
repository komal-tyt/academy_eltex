#include <bits/types/siginfo_t.h>
#include <bits/types/sigset_t.h>
#include <complex.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	if (sigprocmask(SIG_BLOCK, &set, NULL) == -1){
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}

	pid_t pid = getpid();
	printf("My pid: %d\n", pid);

	while(1);
}
