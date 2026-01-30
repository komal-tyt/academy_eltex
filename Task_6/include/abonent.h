/*!
 * \file abonent.h
 * \brief Заголовочный файл для работы с абонентами
 */
#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

///Структура для хранения информации об абоненте
typedef struct Abonent{
	char name[10]; ///< Имя абонента
	char second_name[10]; ///< Фамилия абонента
	char tel[10]; ///< Номер телефона
	struct Abonent* next; ///< Указатель на следующий элемент списка
	struct Abonent* prev; ///< Указатель на предыдущий элемент списка
} Abonent;

///Структура для хранения списка абонентов
typedef struct AbonentList{
	size_t size; ///< Количество элементов в списке
	Abonent* head; ///< Указатель на первый элемент списка
	Abonent* tail; ///< Указатель на последний элемент списка
} AbonentList;

AbonentList* Create_abonent_list(void);
void Add_abonent(AbonentList* list);
void Display_records(AbonentList* list);
void Remove_abonent(AbonentList* list);
void Searching_abonent(AbonentList* list);
void Free_records(AbonentList* list);

#endif
