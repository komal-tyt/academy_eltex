#include "../include/bash.h"

void remove_space(char *str){
	int i = 0;
	while(str[i] != '\0'){
		if(str[i] == ' '){
			str[i] = '\0';
		}else if (str[i] == '\n'){
			str[i] = '\0';
			break;
		}
		i++;
	}
}
