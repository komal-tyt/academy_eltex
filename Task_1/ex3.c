// 3. Найти количество единиц в двоичном представлении целого положительного числа (число вводится с клавиатуры).




#include <stdio.h>

int main(void){
    int a;
    int count = 0;

    scanf("%u", &a);

    int n = sizeof(int) * 8;

    for (int i = n-1; i >= 0; i--) {
        int bit = (a >> i) & 1;
        if (bit == 1) {
            count++;
        }
        printf("%d", bit);
    }
    printf("\n%d", count);

}
