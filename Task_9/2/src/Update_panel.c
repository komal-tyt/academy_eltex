#include "../include/panel.h"

void Update_panel(struct Panel* panel){
	if (panel -> namelist){
		for (int i = 0; i < panel->files_count; i++){
			free(panel -> namelist[i]);
		}
		free(panel -> namelist);
		panel -> namelist = NULL;
	}

	panel->files_count = scandir(panel->path, &panel->namelist, NULL, alphasort);
	refresh();
}
