#include "../include/client_ui.h"
#include "../include/client_logic.h"

void init_ncurses(){
	initscr();
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

void delete_window(Window *win){
	delwin(win->win);
}

void draw_window(Window *win){
	pthread_mutex_lock(&mutex);
	box(win->win, 0, 0);
	wrefresh(win->win);
	pthread_mutex_unlock(&mutex);
}

void update_users_window(UserList *user_list){
	for (int k = 2; k < user_list->count; k++){
		mvwprintw(name_users.win, k, 1, "%-48%s", " ");
		wrefresh(name_users.win);
	}

	int line = 2;
	for (int i = 0; i < user_list->count; i++){
		mvwprintw(name_users.win, line++, 1, "%s", user_list->names[i]);
		wrefresh(name_users.win);
	}

}
