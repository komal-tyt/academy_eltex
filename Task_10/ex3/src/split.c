#include "../include/bash.h"

void split(char *str, char **args){
	int i = 0;
	int j = 0;
	args[j] = &str[i];
	while(1){
		if (str[i] == '\0'){
			i++;
			if (str[i]!='\n'){
				j++;
				args[j] = &str[i];
			}
		} else if (str[i] == '\n'){
			args[j+1] = NULL;
			break;
		}else{
			i++;
		}

	}
}
