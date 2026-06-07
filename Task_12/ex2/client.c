#include <complex.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
	char buffer[100];

	const char* fifo_path = "my_fifo";

	int fd = open(fifo_path, O_RDONLY);
	if (fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	if (read(fd, buffer, sizeof(buffer)) == -1){
		perror("read");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", buffer);

	close(fd);

}
