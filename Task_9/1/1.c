#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd;
	ssize_t fd_write;
	int len;

	char text[] = "String from file";

	fd = open("output.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1){
		perror("Error! File dont created");
		return 1;
	}


	fd_write = write(fd, text, sizeof(text) - 1);
	if (fd_write == -1){
		perror("Error! Dont writed");
		return 1;
	}

	len = lseek(fd, 0, SEEK_CUR);

	for(int i = len - 1; i>=0; i--){
		lseek(fd, i, SEEK_SET);

		char temp;
		read(fd, &temp, 1);
		printf("%c", temp);
	}
	close(fd);

}
