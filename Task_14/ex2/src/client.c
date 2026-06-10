#include "../include/client_ui.h"
#include "../include/client_logic.h"

char my_name[NAME_SIZE];
int my_id = 0;
int i = 2;

Window msg_users;
Window name_users;

int main(){
	initscr();
	echo();
	curs_set(0);

	int fd = shm_open(SHM_NAME, O_RDWR, 0666);
	if (fd == -1){
		perror("shm_open");
		return 1;
	}

	SharedMemory *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	Window reg_win = create_window(42, 190, 0, 0);
	draw_window(&reg_win);
	mvwprintw(reg_win.win, 15, 87, "Enter you name");
	mvwgetnstr(reg_win.win, 17, 87, my_name, sizeof(my_name) - 1);
	curs_set(0);
	delwin(reg_win.win);
	refresh();

	sem_wait(&shm_ptr->mutex);
    shm_ptr->msg.type = MSG_LOGIN;
	strcpy(shm_ptr->msg.name, my_name);
    sem_post(&shm_ptr->mutex);
	sem_post(&shm_ptr->sem_client);

	sleep(1);

	sem_wait(&shm_ptr->mutex);
    my_id = shm_ptr->msg.data[0];
    sem_post(&shm_ptr->mutex);

	msg_users = create_window(32, 140, 0, 0);
	name_users = create_window(32, 49, 0, 141);
	Window input_msg = create_window(9, 190, 32, 0);

	mvwprintw(msg_users.win, 1, 65, "Message users");
	mvwprintw(name_users.win, 1, 20, "Name users");
	mvwprintw(input_msg.win, 1, 1, "Enter you text");

	draw_window(&input_msg);
	draw_window(&msg_users);
	draw_window(&name_users);

	pthread_t thread;
	pthread_create(&thread, NULL, response_for_server, shm_ptr);

  	sem_wait(&shm_ptr->mutex);
    shm_ptr->msg.type = MSG_REG;
	strcpy(shm_ptr->msg.name, my_name);
	strcpy(shm_ptr->msg.data, "joined the chat");
	if(strcmp(shm_ptr->history[0].message, "") != 0){
		mvwprintw(msg_users.win, i++, 1, "HISTORY");
	}

	for (int j = 0; j < shm_ptr->history_count && j < HISTORY_SIZE; j++) {
		mvwprintw(msg_users.win, i++, 1, "[%s]->%s",shm_ptr->history[j].name, shm_ptr->history[j].message);
		wrefresh(msg_users.win);
	}
    sem_post(&shm_ptr->mutex);

    sem_post(&shm_ptr->sem_client);


	char input_buffer[MSG_SIZE] = {0};


	while(1){
		mvwprintw(input_msg.win, 3, 1, "%-179s", " ");
		wrefresh(input_msg.win);
		mvwgetnstr(input_msg.win, 3, 1, input_buffer, sizeof(input_buffer) - 1);
		shm_ptr->msg.type = MSG_INPUT;
       	strcpy(shm_ptr->msg.name, my_name);
       	strcpy(shm_ptr->msg.data, input_buffer);

		sem_post(&shm_ptr->sem_client);

	}



}
