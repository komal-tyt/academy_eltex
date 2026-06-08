#include "../include/server_logic.h"

User users[USER_MAX];
int user_count = 0;
History history[HISTORY_SIZE];
int history_count = 0;

void add_to_history(char* name, char* message) {
    if (history_count < HISTORY_SIZE) {
        strcpy(history[history_count].name, name);
        strcpy(history[history_count].message, message);
        history_count++;
    } else {
        for (int i = 1; i < HISTORY_SIZE; i++) {
            history[i-1] = history[i];
        }
        strcpy(history[HISTORY_SIZE-1].name, name);
        strcpy(history[HISTORY_SIZE-1].message, message);
    }
}

void send_history(mqd_t user_mq) {
    Message history_msg;
    history_msg.type = MSG_HISTORY;

    for (int i = 0; i < history_count; i++) {
        strcpy(history_msg.name, history[i].name);
        strcpy(history_msg.data, history[i].message);

        if (mq_send(user_mq, (char*)&history_msg, sizeof(Message), 1) == -1) {
            perror("mq_send history");
            exit(EXIT_FAILURE);
        }
    }
}

void send_user_list(mqd_t user_mq){
	Message list_msg;
    list_msg.type = MSG_USER_LIST;
    list_msg.user_list.count = 0;

    for (int i = 0; i < user_count; i++){
    	strcpy(list_msg.user_list.names[list_msg.user_list.count], users[i].name);
     	list_msg.user_list.count++;
    }

    for (int i = 0; i < user_count; i++) {
        if (mq_send(users[i].mq, (char*)&list_msg, sizeof(Message), 1) == -1) {
            perror("mq_send broadcast list");
            exit(EXIT_FAILURE);
        }
    }
}

void send_to_users(Message* msg){
 	for (int i = 0; i < user_count; i++) {
  		if (mq_send(users[i].mq, (char*)msg, sizeof(Message), 1) == -1) {
        	perror("mq_send");
            exit(EXIT_FAILURE);
        }

    }
}

void add_user(char* name, char* mq_name, mqd_t user_mq){
	if (user_count < USER_MAX){
		strcpy(users[user_count].name, name);
		strcpy(users[user_count].mq_name, mq_name);
		users[user_count].mq = user_mq;
		user_count++;

		send_history(user_mq);

		send_user_list(user_mq);

		Message login_msg;
        login_msg.type = MSG_LOGIN;
        strcpy(login_msg.name, name);
        strcpy(login_msg.data, "joined the chat");
        send_to_users(&login_msg);
	}
}
