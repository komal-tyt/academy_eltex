#ifndef PANEL_H
#define PANEL_H

#include <ncurses.h>
#include <dirent.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

#define LINES 20
#define COLS 80

struct Panel{
	WINDOW *window;
	int active;
	int current_str;
	char path[1024];
	int files_count;
	struct dirent **namelist;
};

struct Panel* Create_panel(int y, int x, int active);
void Update_panel(struct Panel* panel);
void Draw_panel_box(struct Panel* panel);
void Draw_path_panel(struct Panel* panel, int y, int x);
void Draw_header_panel(struct Panel* panel);
void Draw_panel(struct Panel* panel);
void Switch_active_panel(struct Panel* left, struct Panel* right);
void move_up(struct Panel* panel);
void move_down(struct Panel* panel);
int string_equal(char* a, char* b);
void move_in_directory(struct Panel* panel);
void Clean_panel(struct Panel* panel);
long get_file_size(char *path);
void get_file_time(char *path, char *time_str, int size);



#endif
