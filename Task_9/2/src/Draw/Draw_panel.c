#include "../../include/panel.h"

long get_file_size(char *path) {
    FILE *file = fopen(path, "rb");
    if (!file){
    	return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

void Draw_header_panel(struct Panel* panel){
	wattron(panel->window, COLOR_PAIR(5));
	mvwprintw(panel->window, 1, 1, "/n");
	mvwprintw(panel->window, 1, 17, "Name");
	mvwprintw(panel->window, 1, 53, "Size");
	wattroff(panel->window, COLOR_PAIR(5));
}

void Draw_panel(struct Panel* panel){

	if (panel->files_count < 0){
		mvprintw(30, 0, "Error!Error reading directory!");
		refresh();
		napms(800);
		mvprintw(30, 0, "                              ");
		refresh();
	} else{
		int max_display = LINES - 4;
		for(int i = 0; i < panel->files_count && i < max_display; i++){
			char size_str[20];

			if (panel->namelist[i]->d_type == DT_DIR) {
                snprintf(size_str, sizeof(size_str), "<DIR>");
            } else {
	           	char full_path[2048];
	            snprintf(full_path, sizeof(full_path), "%s/%s", panel->path, panel->namelist[i]->d_name);
	            long size = get_file_size(full_path);

                if (size < 0) {
                    snprintf(size_str, sizeof(size_str), "?");
                } else if (size < 1024) {
                    snprintf(size_str, sizeof(size_str), "%ld B", size);
                } else if (size < 1024 * 1024) {
                    snprintf(size_str, sizeof(size_str), "%.1f KB", size / 1024.0);
                } else {
                    snprintf(size_str, sizeof(size_str), "%.1f MB", size / (1024.0 * 1024.0));
                }
            }

			if (panel->active == 1 && i == panel->current_str){
				wattron(panel->window, COLOR_PAIR(4));
            	mvwprintw(panel->window, i + 2, 1, "%s", panel->namelist[i]->d_name);
             	mvwprintw(panel->window, i + 2, 53, "%s", size_str);
               	wattroff(panel->window, COLOR_PAIR(4));
			} else{
				mvwprintw(panel->window, i + 2, 1, "%s", panel->namelist[i]->d_name);
				mvwprintw(panel->window, i + 2, 53, "%s", size_str);
			}
		}
	}

}
