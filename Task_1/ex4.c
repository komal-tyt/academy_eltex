#include <stdio.h>

int main(void){
    int a;
    int b;

    printf("Введите изначальное число: ");
    scanf("%d", &a);
    printf("Введите значение для третьего байта: ");
    scanf("%d", &b);

    int n = sizeof(int) * 8;

    printf("Изначальное число: ");
    for (int i = n-1; i >= 0; i--) {
        int bit = (a >> i) & 1;
        printf("%d", bit);
    }

    printf("\n");
    a = a & ~(0xFF << 16);
    a = a | (b << 16);
    printf("Новое число: ");
    for (int i = n-1; i >= 0; i--) {
        int bit = (a >> i) & 1;
        printf("%d", bit);
    }


}
