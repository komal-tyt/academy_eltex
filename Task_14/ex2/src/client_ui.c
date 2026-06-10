#include "../include/client_ui.h"

extern Window msg_users;
extern Window name_users;
extern int i;

void update_users_window(SharedMemory *shm_ptr){
		for (int k = 2; k<31; k++) {
			mvwprintw(name_users.win, k, 1, "%-47s", " ");
			wrefresh(name_users.win);
		}

		int line = 2;
		for (int i = 0; i < shm_ptr->msg.user_list.count; i++){
			mvwprintw(name_users.win, line++, 1, "%s", shm_ptr->msg.user_list.names[i]);
			wrefresh(name_users.win);
		}

}

Window create_window(int nlines, int ncols, int begin_y, int begin_x){
	Window new_win;
	new_win.win = newwin(nlines, ncols, begin_y, begin_x);
	new_win.nlines = nlines;
	new_win.ncols = ncols;
	new_win.begin_y = begin_y;
	new_win.begin_x = begin_x;


	return new_win;
}

void draw_window(Window *win){
	box(win->win, 0, 0);
	wrefresh(win->win);
}
