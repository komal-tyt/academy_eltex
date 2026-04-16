#include "../include/panel.h"

void Switch_active_panel(struct Panel* left, struct Panel* right){
	left->active = !left->active;
	right->active = !right->active;
}

void move_up(struct Panel* panel){
	if (panel->current_str > 0) panel->current_str--;
}

void move_down(struct Panel* panel){
	if (panel->current_str < panel->files_count - 1) panel->current_str++;
}

int string_equal(char* a, char* b){
	int i = 0;
	while(a[i] != '\0' && b[i] != '\0'){
		if (a[i] != b[i]) return 0;
		i++;
	}
	return (a[i] == b[i]);
}


void move_in_directory(struct Panel* panel){
	if (panel->files_count <= 0) return;

	char *name_str = panel->namelist[panel->current_str]->d_name;

	if (string_equal(name_str, ".")) return;

	char new_path[1024];

	if (string_equal(name_str, "..")){
		int i = 0;
		while(panel->path[i] != '\0'){
			new_path[i] = panel->path[i];
			i++;
		}

		int j = i - 1;
		while(j>=0 && new_path[j] != '/'){
			j--;
		}
		if (j > 0){
			new_path[j] = '\0';
		}else{
			new_path[0] = '/';
			new_path[1] = '\0';
		}
	} else {
		int i = 0;
		while(panel->path[i] != '\0'){
			new_path[i] = panel->path[i];
			i++;
		}
		new_path[i] = '/';
		i++;
        int j = 0;
        while (name_str[j] != '\0') {
            new_path[i + j] = name_str[j];
            j++;
        }
        new_path[i + j] = '\0';
	}

 char old_path[1024];
    int k = 0;
    while (panel->path[k] != '\0') {
        old_path[k] = panel->path[k];
        k++;
    }
    old_path[k] = '\0';

    int i = 0;
    while (new_path[i] != '\0') {
        panel->path[i] = new_path[i];
        i++;
    }
    panel->path[i] = '\0';

    Update_panel(panel);

    if (panel->files_count >= 0) {
        panel->current_str = 0;
    } else {
        int j = 0;
        while (old_path[j] != '\0') {
            panel->path[j] = old_path[j];
            j++;
        }
        panel->path[j] = '\0';

        Update_panel(panel);

        mvprintw(30, 0, "Cannot open directory!");
        refresh();
        napms(800);
        mvprintw(30, 0, "                      ");
        refresh();
        return;
    }
}
