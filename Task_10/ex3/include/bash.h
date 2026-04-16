#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void remove_space(char *str);
void split(char *str, char **args);

#endif
