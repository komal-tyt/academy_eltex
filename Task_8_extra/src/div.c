#include "../include/div.h"

int Div(int a, int b){
	if (b == 0 ){
		printf("Error! b = 0!");
		return -1;
	}
	return (a/b);
}
