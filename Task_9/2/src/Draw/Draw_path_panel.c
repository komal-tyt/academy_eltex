#include "../../include/panel.h"

void Draw_path_panel(struct Panel* panel, int y, int x){
	mvprintw(y, x, "%-80s", panel->path);
}
