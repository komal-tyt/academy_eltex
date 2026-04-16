#include "../../include/panel.h"

void Draw_panel_box(struct Panel* panel){

	if (panel->active){
		wattron(panel->window, COLOR_PAIR(2));
		box(panel->window, '|', '-');
		wattroff(panel->window, COLOR_PAIR(2));

        } else {
		wattron(panel->window, COLOR_PAIR(3));
		box(panel->window, '|', '-');
		wattroff(panel->window, COLOR_PAIR(3));
	}
}
