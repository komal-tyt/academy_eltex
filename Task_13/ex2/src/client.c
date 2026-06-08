#include "../include/client_ui.h"
#include "../include/client_logic.h"
#include "../include/main.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
mqd_t my_mq;
mqd_t server_mq;
char my_name[NAME_SIZE];
char my_mq_name[NAME_SIZE];
Window name_users;

int main(){
	init_ncurses();
	echo();
	curs_set(0);

	server_mq = mq_open(SERVER_MQ, O_WRONLY);
	if(server_mq == (mqd_t)-1){
		perror("mq_open");
		exit(EXIT_FAILURE);
	}


	Window reg_win = create_window(42, 190, 0, 0);
	mvwprintw(reg_win.win, 15, 87, "Enter you name");
	draw_window(&reg_win);
	mvwgetnstr(reg_win.win, 17, 87, my_name, sizeof(my_name) - 1);
	noecho();
	delwin(reg_win.win);
	refresh();

	Message reg_msg;
	reg_msg.type = MSG_LOGIN;
	strcpy(reg_msg.name, my_name);
	snprintf(my_mq_name, NAME_SIZE, "/user_mq_%.*s", NAME_SIZE - 10, my_name);
	my_mq = mq_open(my_mq_name, O_CREAT | O_RDONLY, 0666, &attr);
    if (my_mq == (mqd_t)-1) {
    	perror("mq_open");
     	exit(EXIT_FAILURE);
    }

    strcpy(reg_msg.user_mq, my_mq_name);

	if (mq_send(server_mq, (char*)&reg_msg, sizeof(Message), 1) == -1){
		perror("mq_send");
		exit(EXIT_FAILURE);
	}

	Window msg_users = create_window(32, 140, 0, 0);
	name_users = create_window(32, 49, 0, 141);
	Window input_msg = create_window(9, 190, 32, 0);

	mvwprintw(name_users.win, 2, 1, "%s", reg_msg.name);
	mvwprintw(msg_users.win, 1, 65, "Message users");
	mvwprintw(name_users.win, 1, 20, "Name users");
	mvwprintw(input_msg.win, 1, 1, "Enter you text");


	pthread_t thread;
	int *status = 0;
	pthread_create(&thread, NULL, &thread_input_text, &msg_users);

	echo();
	Message msg_to_server;
	msg_to_server.type = MSG_INPUT;
	strcpy(msg_to_server.name, my_name);

	int running = 1;

	while(running){

		draw_window(&input_msg);
		draw_window(&msg_users);
		draw_window(&name_users);

		mvwgetnstr(input_msg.win, 3, 1, msg_to_server.data, sizeof(msg_to_server.data) - 1);

		if (mq_send(server_mq, (char*)&msg_to_server, sizeof(Message), 1) == -1){
			perror("mq_send");
			exit(EXIT_FAILURE);
		}

		mvwprintw(input_msg.win, 3, 1, "%-179s", " ");
		wrefresh(input_msg.win);
	}

	pthread_join(thread, (void **)status);
 	mq_close(my_mq);
    mq_close(server_mq);
    mq_unlink(my_mq_name);
    endwin();
}
