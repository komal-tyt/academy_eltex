// Поменять в целом положительном числе (типа int) значение третьего
// байта на введенное пользователем число (изначальное число также
// вводится с клавиатуры) через указатель (не применяя битовые
// операции).

#include "stdio.h"

int main(void){

    int a, b;

    unsigned char *ptr = NULL;

    printf("Введите изначальное число: ");
    scanf("%d", &a);
    printf("Введите значение для третьего байта: ");
    scanf("%d", &b);

    int n = sizeof(a);

    ptr = (unsigned char *)&a;

    printf("Изначальное число: %d", a);

    printf("\nБайты: ");
    for (int i = 0; i < n; i++) {
        printf("%x ", ptr[i]);
    }

    ptr[2] = b;

    printf("\nПолучившееся число: %d", a);

    printf("\nБайты: ");
    for (int i = 0; i < n; i++) {
        printf("%x ", ptr[i]);
    }
}
