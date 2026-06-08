#ifndef CLIENT_UI_H
#define CLIENT_UI_H

#include <stdio.h>
#include <ncurses.h>
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "main.h"


#define MQ_NAME "/myqueue"

typedef struct{
	WINDOW *win;
	int nlines;
	int ncols;
	int begin_y;
	int begin_x;
} Window;

extern Window name_users;

void init_ncurses();
Window create_window(int nlines, int ncols, int begin_y, int begin_x);
void delete_window(Window *win);
void draw_window(Window *win);
void update_users_window(UserList *user_list);

#endif
