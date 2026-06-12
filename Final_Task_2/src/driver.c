#include "../include/common.h"
#include "../include/driver.h"

void run_driver(int read_fd, int write_fd){
    DriverStatus status = AVAILABLE;
    time_t end_time = 0;
    char buffer[INPUT_SIZE];

    printf("[Driver %d] started\n", getpid());

    while(1){
        fd_set read_fds;

        if (status == BUSY && time(NULL) >= end_time) {
            status = AVAILABLE;
            end_time = 0;
        }

        FD_ZERO(&read_fds);
        FD_SET(read_fd, &read_fds);

        int wait = select(read_fd + 1, &read_fds, NULL, NULL, NULL);
        if (wait == -1){
        	perror("select");
         	exit(EXIT_FAILURE);
        }

        if (FD_ISSET(read_fd, &read_fds)){
            memset(buffer, 0, INPUT_SIZE);
            int n = read(read_fd, buffer, INPUT_SIZE - 1);
            if (n == -1){
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (strncmp(buffer, "task", 4) == 0) {
                int seconds;
                sscanf(buffer, "task %d", &seconds);

                if (status == BUSY) {
                    int remaining = end_time - time(NULL);
                    if (remaining < 0) remaining = 0;

                    char response[SIZE];
                    snprintf(response, sizeof(response), "[Driver %d] Busy %d", getpid(), remaining);
                    write(write_fd, response, strlen(response));
                } else {
                    status = BUSY;
                    end_time = time(NULL) + seconds;

                    char response[SIZE];
                    snprintf(response, sizeof(response), "[Driver %d] received task for %d sec", getpid(), seconds);
                    write(write_fd, response, strlen(response));
                }
            }
            else if (strcmp(buffer, "status") == 0) {
                char response[SIZE];
                if (status == AVAILABLE) {
                    snprintf(response, sizeof(response), "[Driver %d] Available", getpid());
                } else {
                    int remaining = end_time - time(NULL);
                    if (remaining < 0) remaining = 0;
                    snprintf(response, sizeof(response), "[Driver %d] Busy %d", getpid(), remaining);
                }
                write(write_fd, response, strlen(response));
            }
        }
    }
}
