#include "../include/panel.h"

void Clean_panel(struct Panel* panel){
 	if (panel->namelist) {
        for (int i = 0; i < panel->files_count; i++) {
            if (panel->namelist[i]){
	            free(panel->namelist[i]);
	            panel->namelist[i] = NULL;
            }
        }
        free(panel->namelist);
        panel->namelist = NULL;
        panel->files_count = 0;
    }

    if (panel->window) {
        delwin(panel->window);
        panel->window = NULL;
    }

    free(panel);
}
