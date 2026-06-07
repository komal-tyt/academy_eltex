#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


void remove_space(char *str);
void split(char *str, char **args);
void split_pipe(char *str, char **args, char**args1);

#endif
