#ifndef CLIENT_UI_H
#define CLIENT_UI_H

#include "main.h"

typedef struct{
	WINDOW *win;
	int nlines;
	int ncols;
	int begin_y;
	int begin_x;
} Window;

extern Window msg_users;
extern Window name_users;

Window create_window(int nlines, int ncols, int begin_y, int begin_x);
void draw_window(Window *win);
void update_users_window(SharedMemory *shm_ptr);

#endif
