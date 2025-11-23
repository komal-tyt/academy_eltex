// 1. Вывести двоичное представление целого положительного числа, используя битовые операции (число вводится с клавиатуры).


#include <stdio.h>

int main(void){
    unsigned int a;

    scanf("%u", &a);

    int n = sizeof(int) * 8;

    for (int i = n-1; i >= 0; i--) {
        int bit = (a >> i) & 1;
        printf("%d", bit);
    }

}
