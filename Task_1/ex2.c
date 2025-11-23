// 2. Вывести двоичное представление целого отрицательного числа, используя битовые операции (число вводится с клавиатуры).


#include <stdio.h>

int main(void){
    int a;

    scanf("%d", &a);

    int n = sizeof(int) * 8;

    for (int i = n-1; i >= 0; i--) {
        int bit = (a >> i) & 1;
        printf("%d", bit);
    }

}
