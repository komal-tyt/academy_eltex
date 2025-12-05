// Вывести квадратную матрицу по заданному N

#include "stdio.h"

#define N 3

int main(void){

    int a[N][N];

    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++){
            a[i][j] = N * i + j + 1;
            printf("%d", a[i][j]);
        }
        printf("\n");
    }

}
