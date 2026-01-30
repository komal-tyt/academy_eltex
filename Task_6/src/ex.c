#include "../include/abonent.h"

/*!
 * \file ex.c
 * \brief Файл с функцией main и с циклом для меню
 */


/*!
 * \brief Функция main с меню
 *
 * \code
 * int main(void){
	AbonentList* records = Create_abonent_list(); // Создаем список абонентов

	int answer = 0; // Инициализируем переменную ответа

	while (answer != 5) {
         printf("\n====================================");
         printf("\n1) Add abonent\n2) Remove abonent\n3) Search abonent by name\n4) Display all records\n5) Exit");//Рисовка меню
         printf("\n====================================");

         printf("\nChoose an answer: ");//Сообщение о выборе ответа

         scanf("%d", &answer);

         //При определенном ответе, определенные действия
         switch (answer) {
             case 1:
                 printf("Adding abonent...\n");
                 Add_abonent(records);
                 break;
             case 2:
                 printf("Removing abonent...\n");
                 Remove_abonent(records);
                 break;
             case 3:
                 printf("Searching abonent...\n");
                 Searching_abonent(records);
                 break;
             case 4:
                 printf("Displaying all records...\n");
                 Display_records(records);
                 break;
             case 5:
                 printf("Exiting...\n");
                 Free_records(records);
                 break;
             default:
                 printf("Error! Invalid choice '%d'. Please enter 1-5.\n", answer);
         }
     }

	return 0;
 }
 * \endcode
 * \return 0
 */
int main(void){
	AbonentList* records = Create_abonent_list();

	int answer = 0;

	while (answer != 5) {
        printf("\n====================================");
        printf("\n1) Add abonent\n2) Remove abonent\n3) Search abonent by name\n4) Display all records\n5) Exit");//Рисовка меню
        printf("\n====================================");

        printf("\nChoose an answer: ");//Сообщение о выборе ответа

        scanf("%d", &answer);

        //При определенном ответе, определенные действия
        switch (answer) {
            case 1:
                printf("Adding abonent...\n");
                Add_abonent(records);
                break;
            case 2:
                printf("Removing abonent...\n");
                Remove_abonent(records);
                break;
            case 3:
                printf("Searching abonent...\n");
                Searching_abonent(records);
                break;
            case 4:
                printf("Displaying all records...\n");
                Display_records(records);
                break;
            case 5:
                printf("Exiting...\n");
                Free_records(records);
                break;
            default:
                printf("Error! Invalid choice '%d'. Please enter 1-5.\n", answer);
        }
    }

	return 0;
}
