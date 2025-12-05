// Заполнить верхний треугольник матрицы а нижний 0.
// Пример:
// 0 0 1
// 0 1 1
// 1 1 1

#include "stdio.h"

#define N 5

int main(void){
    int a[N][N];


    for (int i =0 ; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = 1;
            if (j < N - i - 1){
                a[i][j] = 0;
            }
            printf("%d", a[i][j]);
        }
        printf("\n");
    }


}
