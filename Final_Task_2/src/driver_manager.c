#include "../include/common.h"
#include "../include/driver_manager.h"
#include "../include/driver.h"

void create_driver(Driver *drivers, int *drivers_count){
	if(*drivers_count >= MAX_DRIVERS){
		printf("Error! many drivers!");
		exit(EXIT_FAILURE);
	}

	int to_driver[2];
	int from_driver[2];

	if (pipe(to_driver) == -1){
		perror("pipe to_driver");
		exit(EXIT_FAILURE);
	}

	if (pipe(from_driver) == -1){
		perror("pipe from_driver");
		close(to_driver[0]);
		close(to_driver[1]);
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if(pid == -1){
		perror("fork");
		close(to_driver[0]);
		close(to_driver[1]);
		close(from_driver[0]);
		close(from_driver[1]);
		exit(EXIT_FAILURE);
	}

	if (pid == 0){
		close(to_driver[1]);
		close(from_driver[0]);

		run_driver(to_driver[0], from_driver[1]);
	} else {
  		close(to_driver[0]);
        close(from_driver[1]);

        drivers[*drivers_count].pid = pid;
        drivers[*drivers_count].write_fd = to_driver[1];
        drivers[*drivers_count].read_fd = from_driver[0];
        drivers[*drivers_count].status = AVAILABLE;
        (*drivers_count)++;
	}
}

void send_task(Driver *drivers, int drivers_count, pid_t pid, int timer){
	int id = -1;
 	for (int i = 0; i < drivers_count; i++) {
        if (drivers[i].pid == pid) {
            id = i;
            break;
        }
    }

  	if (id == -1){
   		perror("Driver not found");
     	return;
   	}

	char request[SIZE];
    snprintf(request, sizeof(request), "task %d", timer);
    write(drivers[id].write_fd, request, strlen(request));

    char response[SIZE];
    memset(response, 0, sizeof(response));
    int n = read(drivers[id].read_fd, response, sizeof(response) - 1);
    if (n == -1){
   		perror("read");
    	exit(EXIT_FAILURE);
    }

    printf("%s\n", response);

}

void get_status(Driver *drivers, int drivers_count, pid_t pid){
	int id = -1;
    for (int i = 0; i < drivers_count; i++) {
        if (drivers[i].pid == pid) {
            id = i;
            break;
        }
    }
	if (id == -1){
		perror("Driver not found");
	  return;
	}


    write(drivers[id].write_fd, "status", 6);

    char response[SIZE];
    memset(response, 0, sizeof(response));
    int n = read(drivers[id].read_fd, response, sizeof(response) - 1);

    if (n == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", response);
}

void get_drivers(Driver* drivers, int drivers_count){
 	if (drivers_count == 0) {
        printf("Drivers is empty\n");
        return;
    }

  	for (int i = 0; i < drivers_count; i++) {
   		write(drivers[i].write_fd, "status", 6);
    	char response[SIZE];
        memset(response, 0, sizeof(response));
        int n = read(drivers[i].read_fd, response, sizeof(response) - 1);
        if (n > 0) {
            response[n] = '\0';
            printf("PID %d: %s\n", drivers[i].pid, response);
        } else {
          	perror("read");
           	exit(EXIT_FAILURE);
        }
   	}
}
