#include <complex.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	const char* fifo_path = "my_fifo";

	if (mkfifo(fifo_path, 0666) == -1){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	int fd = open(fifo_path, O_WRONLY);
	if (fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	char* messange = "Hi!";

	if (write(fd, messange, 3) == -1){
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(fd);
	unlink(fifo_path);
}
