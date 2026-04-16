#include "include/panel.h"

int main(){
	initscr();
	start_color();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	int run = 1;

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);

	struct Panel* left_panel = Create_panel(1, 2, 1);

	struct Panel* right_panel = Create_panel(1, COLS + 5, 0);

	Update_panel(left_panel);
	Update_panel(right_panel);

	refresh();

	while (run){

		werase(left_panel->window);
		werase(right_panel->window);

		Draw_path_panel(left_panel, 0, 2);
		Draw_path_panel(right_panel, 0, 85);

		Draw_panel(left_panel);
		Draw_panel(right_panel);

		Draw_panel_box(left_panel);
		Draw_panel_box(right_panel);

		Draw_header_panel(left_panel);
		Draw_header_panel(right_panel);

		wrefresh(left_panel->window);
		wrefresh(right_panel->window);

		refresh();

		int ch = getch();
		switch(ch){
			case 'q':
				run = 0;
				break;
			case '\t':
			    Switch_active_panel(left_panel, right_panel);
				break;
			case KEY_UP:
			    if (left_panel->active) {
					move_up(left_panel);
				} else {
					move_up(right_panel);
				}
			    break;
			case KEY_DOWN:
			    if (left_panel->active){
					move_down(left_panel);
				} else{
					move_down(right_panel);
				}
			    break;
			case KEY_ENTER:
			case 10:
				if (left_panel->active){
					move_in_directory(left_panel);
				}else{
					move_in_directory(right_panel);
				}
			    break;
			default:
				mvprintw(30, 0, "Error! Invalid Syntax!");
				refresh();
				napms(800);
				mvprintw(30, 0, "                      ");
				refresh();
				break;
		}
	}

	Clean_panel(left_panel);
	Clean_panel(right_panel);

	endwin();
	return 0;
}
