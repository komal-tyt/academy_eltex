/**
 * @file div.c
 * @brief Файл с реализацией функции для деления двух чисел
 * @param a Первое число для деления
 * @param b Второе число для деления
 * @return Результат деления чисел a на b
 * @note Если b равно 0, функция выводит сообщение об ошибке и возвращает -1
 * @code
 * if (b == 0 ){
		printf("Error! b = 0!");
		return -1;
	}
 * @endcode
 */
#include "../include/div.h"

int Div(int a, int b){
	if (b == 0 ){
		printf("Error! b = 0!");
		return -1;
	}
	return (a/b);
}
