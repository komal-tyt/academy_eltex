#include "../include/bash.h"

void split(char *str, char **args) {
    int j = 0;
    char *token = strtok(str, " \t\n");
    while(token != NULL && j < 63) {
        args[j++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[j] = NULL;
}
