// Заполнить матрицу числами от 1 до N^2 улиткой
// Пример:
// 1 2 3 4 5
// 16 17 18 19 6
// 15 24 25 20 7
// 14 23 22 21 8
// 13 12 11 10 9

#include "stdio.h"

#define N 5

int main(void){
    int a[N][N];

    int count = 0, left = 0, right = N - 1, top = 0, bottom = N - 1;

    while (count < N * N) {
        for (int i = left; i <= right; i++) {
            a[top][i] = count++;
        }
        top++;

        for (int i = top; i <= bottom ; i++) {
            a[i][right] = count++;
        }
        right--;

        for (int i = right; i >= left; i--) {
            a[bottom][i] = count++;
        }
        bottom--;

        for (int i = bottom; i >= top; i--) {
            a[i][left] = count++;
        }
        left++;
    }



    for (int i = 0; i<N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}
