#include <dlfcn.h>
#include <stdio.h>



int main(void){
	int answer = 0;
	int a, b = 0;
	int result = 0;

	void *handle;
	int (*Add_ptr)(int, int);
	int (*Div_ptr)(int, int);
	int (*Mul_ptr)(int, int);
	int (*Sub_ptr)(int, int);

	handle = dlopen("build/lib/libcalc.so", RTLD_LAZY);
	if (handle == NULL){
		printf("\nError! %s\n", dlerror());
		return 1;
	}

	Add_ptr = dlsym(handle, "Add");
	if(Add_ptr == NULL){
		printf("\nError! %s\n", dlerror());
	}
	Sub_ptr = dlsym(handle, "Sub");
	if(Sub_ptr == NULL){
		printf("\nError! %s\n", dlerror());
	}
	Mul_ptr = dlsym(handle, "Mul");
	if(Mul_ptr == NULL){
		printf("\nError! %s\n", dlerror());
	}
	Div_ptr = dlsym(handle, "Div");
	if(Div_ptr == NULL){
		printf("\nError! %s\n", dlerror());
	}


	while(answer != 5){

		printf("\n==========\n");
		printf("   MENU\n");
		printf("==========\n");
		if (Add_ptr != NULL) printf("1) Addition\n");
		if (Sub_ptr != NULL) printf("2) Subtraction\n");
		if (Mul_ptr != NULL) printf("3) Multiplication\n");
		if (Div_ptr != NULL) printf("4) Division\n");
		printf("5) Exit\n");

		printf("\nEnter the number: ");
		scanf("%d", &answer);
		switch(answer){
			case 1:
				if (Add_ptr == NULL){
     				printf("\nFunction not available!\n");
				} else{
					printf("\nEnter the a: ");
					scanf("%d", &a);
					printf("\nEnter the b: ");
					scanf("%d", &b);
					result = Add_ptr(a, b);
					printf("\na + b = %d", result);
				}
				break;
			case 2:
				if (Sub_ptr == NULL){
	     				printf("\nFunction not available!\n");
				} else{
					printf("\nEnter the a: ");
					scanf("%d", &a);
					printf("\nEnter the b: ");
					scanf("%d", &b);
					result = Sub_ptr(a, b);
					printf("\na - b = %d", result);
				}
				break;
			case 3:
				if (Mul_ptr == NULL){
	     				printf("\nFunction not available!\n");
				} else{
					printf("\nEnter the a: ");
					scanf("%d", &a);
					printf("\nEnter the b: ");
					scanf("%d", &b);
					result = Mul_ptr(a, b);
					printf("\na * b = %d", result);
				}
				break;
			case 4:
				if (Div_ptr == NULL){
	     				printf("\nFunction not available!\n");
				} else{
					printf("\nEnter the a: ");
					scanf("%d", &a);
					printf("\nEnter the b: ");
					scanf("%d", &b);
					result = Div_ptr(a, b);
					printf("\na / b = %d", result);
				}
				break;
			case 5:
				printf("Exiting...");
				break;
		}
	}
	dlclose(handle);
}
