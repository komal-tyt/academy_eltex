#include "../include/add.h"
#include "../include/sub.h"
#include "../include/mul.h"
#include "../include/div.h"

int main(void){
	int answer = 0;
	int a, b = 0;
	int result = 0;

	while(answer != 5){

		printf("\n==========\n");
		printf("   MENU\n");
		printf("==========\n");
		printf("\n1) Addition\n2) Subtraction\n3) Multiplication\n4) Division\n5) Exit\n");

		printf("\nEnter the number: ");
		scanf("%d", &answer);
		switch(answer){
			case 1:
				printf("\nEnter the a: ");
				scanf("%d", &a);
				printf("\nEnter the b: ");
				scanf("%d", &b);
				result = Add(a, b);
				printf("\na + b = %d", result);
				break;
			case 2:
				printf("\nEnter the a: ");
				scanf("%d", &a);
				printf("\nEnter the b: ");
				scanf("%d", &b);
				result = Sub(a, b);
				printf("\na - b = %d", result);
				break;
			case 3:
				printf("\nEnter the a: ");
				scanf("%d", &a);
				printf("\nEnter the b: ");
				scanf("%d", &b);
				result = Mul(a, b);
				printf("\na * b = %d", result);
				break;
			case 4:
				printf("\nEnter the a: ");
				scanf("%d", &a);
				printf("\nEnter the b: ");
				scanf("%d", &b);
				result = Div(a, b);
				printf("\na / b = %d", result);
				break;
			case 5:
				printf("Exiting...");
				break;


		}
	}
}
