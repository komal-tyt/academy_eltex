// Напишите программу, которая ищет введенной строке (с клавиатуры)
// введенную подстроку (с клавиатуры) и возвращает указатель на начало
// подстроки, если подстрока не найдена в указатель записывается NULL.
// В качестве срок использовать статические массивы.

#include "stdio.h"

#define N 5
#define K 3

int main(void){
    char a[N], b[K];
    char *ptr = NULL;

    for (int i = 0; i < N; i++) {
        scanf("%c", &a[i]);
    }

    char temp;
    scanf("%c", &temp);

    for (int i = 0; i < K; i++) {
        scanf("%c", &b[i]);
    }

    printf("\n");

    int found = 0;

    for (int i = 0; i <= N - K; i++) {
        int match = 1;

        for (int j = 0; j < K; j++) {
            if (a[i + j] != b[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            ptr = &a[i];
            found = 1;
            break;
        }
    }

    if (found) {
        printf("%c\n", *ptr);
    } else {
        printf("Подстрока не найдена\n");
    }

    return 0;
}
