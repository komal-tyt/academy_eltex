#include "../include/client_logic.h"

void* thread_input_text(void *arg){
	Window *msg_win = arg;

	Message msg_from_server;
	unsigned int prio;

	int i = 2;

	while(1){

		if(mq_receive(my_mq, (char*)&msg_from_server, sizeof(Message), &prio) > 0){

			pthread_mutex_lock(&mutex);
			if(msg_from_server.type == MSG_LOGIN){
				mvwprintw(msg_win->win, i++, 1, "%s %s", msg_from_server.name, msg_from_server.data);
				wrefresh(msg_win->win);
			} else if (msg_from_server.type == MSG_INPUT){
				mvwprintw(msg_win->win, i++, 1, "[%s]->%s", msg_from_server.name, msg_from_server.data);
				wrefresh(msg_win->win);
				if (i > 30){
					for(int j = 2; j< 31; j++){
						mvwprintw(msg_win->win, j, 1, "%-138s", " ");
					}
					i = 2;
				}
			}else if (msg_from_server.type == MSG_USER_LIST){
				update_users_window(&msg_from_server.user_list);
			}else if (msg_from_server.type == MSG_HISTORY){
				mvwprintw(msg_win->win, 3, 1, "HISTORY");
				mvwprintw(msg_win->win, i++, 1, "[%s]->%s", msg_from_server.name, msg_from_server.data);
			}
			pthread_mutex_unlock(&mutex);
		} else {
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}

	}
}
