#include "../include/panel.h"

struct Panel* Create_panel(int y, int x, int active){
	struct Panel* new_panel = (struct Panel*)malloc(sizeof(struct Panel));

	if (new_panel == 0){
		mvprintw(30, 0, "Error! new_panel malloc!");
		return NULL;
	}

	new_panel -> window = newwin(LINES, COLS, y, x);
	new_panel -> active = active;
	new_panel -> current_str = 0;
	new_panel -> files_count = 0;
	new_panel -> namelist = NULL;
	getcwd(new_panel -> path, sizeof(new_panel -> path));

	wbkgd(new_panel -> window, COLOR_PAIR(1));

	return new_panel;
}
