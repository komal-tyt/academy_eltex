#include "../include/client_logic.h"
#include "../include/client_ui.h"

extern Window msg_users;
extern Window name_users;
extern int i;
extern int my_id;

void* response_for_server(void* arg){
		SharedMemory *shm_ptr = arg;
		while(1){
			sem_wait(&shm_ptr->sem_server[my_id]);
			sem_wait(&shm_ptr->mutex);

			update_users_window(shm_ptr);

			if(shm_ptr->msg.type == MSG_LOGIN){
				wrefresh(msg_users.win);
			}else if (shm_ptr->msg.type == MSG_INPUT){
				mvwprintw(msg_users.win, i++, 1, "[%s]->%s", shm_ptr->msg.name, shm_ptr->msg.data);
				wrefresh(msg_users.win);
			}else if (shm_ptr->msg.type == MSG_REG){
		        mvwprintw(msg_users.win, i++, 1, "%s %s", shm_ptr->msg.name, shm_ptr->msg.data);
		        wrefresh(msg_users.win);
			}
			if (i > 30){
				for(int j = 2; j< 31; j++){
					mvwprintw(msg_users.win, j, 1, "%-138s", " ");
				}
				i = 2;
			}

 			sem_post(&shm_ptr->mutex);
		}
	}
