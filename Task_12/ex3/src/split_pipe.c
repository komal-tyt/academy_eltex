#include "../include/bash.h"

void split_pipe(char *str, char **args_left, char **args_right) {
    char *pipe_pos = strchr(str, '|');
    if (pipe_pos != NULL) {
        *pipe_pos = '\0';
        char *left = str;
        char *right = pipe_pos + 1;

        char *end = left + strlen(left) - 1;
        while(end > left && (*end == ' ' || *end == '\t')) {
            *end = '\0';
            end--;
        }

        while(*right == ' ' || *right == '\t') {
            right++;
        }

        left[strcspn(left, "\n")] = '\0';
        right[strcspn(right, "\n")] = '\0';

        split(left, args_left);
        split(right, args_right);
    } else {
        str[strcspn(str, "\n")] = '\0';
        split(str, args_left);
        args_right[0] = NULL;
    }
}
