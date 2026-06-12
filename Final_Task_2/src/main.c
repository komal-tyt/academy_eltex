#include "../include/common.h"
#include "../include/driver_manager.h"

void menu(){
	printf("---TAXI MANAGER---\n");
	printf("create_driver\n");
	printf("send_task <pid> <task_timer>\n");
	printf("get_status <pid>\n");
	printf("get_drivers\n");
	printf("\n");
}

int main(){
	menu();
	Driver drivers[MAX_DRIVERS];
	int drivers_count = 0;
	char input[INPUT_SIZE];

	while(1){
		printf("\n~");

		if (fgets(input, sizeof(input), stdin) == NULL){
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "create_driver") == 0){
			create_driver(drivers, &drivers_count);
		}else if (strncmp(input, "send_task", 9) == 0){
			pid_t pid;
			int timer;
			if (sscanf(input, "%*s %d %d", &pid, &timer) == 2){
				send_task(drivers, drivers_count, pid, timer);
			} else {
				printf("Please enter send_task <pid> <task_timer>");
			}
		} else if (strncmp(input, "get_status", 10) == 0){
			pid_t pid;
   			if (sscanf(input, "%*s %d", &pid) == 1){
                get_status(drivers, drivers_count, pid);
            } else {
                printf("Usage: get_status <pid>\n");
            }
		}else if (strcmp(input, "get_drivers") == 0){
            get_drivers(drivers, drivers_count);
        }

	}

}
