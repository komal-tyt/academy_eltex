// Вывести заданный массив размером N в обратном порядке.

#include "stdio.h"

#define N 5

int main(void){
    int a[N];
    for (int i = 0; i<N; i++) {
        a[i] = i;
        printf("%d ", a[i]);
    }

    printf("\n");

    for (int i = 0; i<N/2; i++) {
        int temp = a[i];
        a[i] = a[N - i - 1];
        a[N - i - 1] = temp;
    }

    for (int i = 0; i<N; i++) {
        printf("%d ", a[i]);
    }

}
