#include "stdio.h"

//Структура абонента
struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

//Функция добавления абонента
void Add_abonent(int *count_ptr, struct abonent *arr_ptr){
    if (*count_ptr >= 100){//Проверяем не вышли ли за пределы массива
        printf("The directory is full!");
        return;
    }
    //Ввод данных для абонента
    printf("Enter name: ");
    scanf("%9s", arr_ptr[*count_ptr].name);

    printf("Enter second name: ");
    scanf("%9s", arr_ptr[*count_ptr].second_name);

    printf("Enter phone number: ");
    scanf("%9s", arr_ptr[*count_ptr].tel);

    (*count_ptr)++;
}

//Функция отображения записей
void Display_records(struct abonent *arr_ptr, int count){
    for (int i = 0; i < count; i++) { //Выводит индекс, имя, фамилию и номер телефона абонентов
        printf("\n%d)\n", i + 1);
        printf("Name: %s\n", arr_ptr[i].name);
        printf("Second Name: %s\n", arr_ptr[i].second_name);
        printf("Phone Number: %s\n", arr_ptr[i].tel);
    }
}

//Функция удаления абонента
void Remove_abonent(int *count_ptr, struct abonent *arr_ptr){
    int choice = 0;//Выбор пользователя
    printf("Please select a abonent index: ");
    scanf("%d", &choice);

    if (*count_ptr == 0) {
        printf("\nRecords is empty!");
        return;
    }

    if (choice <= 0 || choice > *count_ptr) {//Смотрим не вышли ли за границы
        printf("Invalid choice!");
    } else {
        for (int i = 0; i < 10; i++) {//Если не вышли, то заполняем нулями выбранного абонента
            arr_ptr[choice-1].name[i] = 0;
            arr_ptr[choice-1].second_name[i] = 0;
            arr_ptr[choice-1].tel[i] = 0;
        }
        for (int j = choice-1; j < *count_ptr-1; j++) {//Сдвигаем массив на один элемент влево
            arr_ptr[j] = arr_ptr[j+1];
        }
        (*count_ptr)--;//Уменьшаем количество элементов в массиве на 1
    }
}

//Функция поиска абонента
void Searching_abonent(int *count_ptr, struct abonent *arr_ptr){
    char name_for_searching[10];//Создаем массив для хранения имени абонента для поиска
    printf("Enter the name for searching: ");
    scanf("%9s", name_for_searching);
    int found = 0;//Флаг, чтобы проверить найден ли абонент

    for (int i = 0; i < *count_ptr; i++) {
        int j = 0;
        int coincided = 1;//Флаг, чтобы проверить совпали ли имена

        while (arr_ptr[i].name[j] != '\0' && name_for_searching[j] != '\0') {//Пока не конец строки
            if (arr_ptr[i].name[j] != name_for_searching[j]){//Если символы не совпадают
                coincided = 0;
                break;
            }
            j++;
        }

        if (coincided && arr_ptr[i].name[j] == '\0' && name_for_searching[j] == '\0'){//Если имена совпали, то выводим информацию абонента
            printf("\n%d)\n", i + 1);
            printf("Name: %s\n", arr_ptr[i].name);
            printf("Second Name: %s\n", arr_ptr[i].second_name);
            printf("Phone Number: %s\n", arr_ptr[i].tel);
            found = 1;
        }
    }

    if (found == 0) {//Если не найден абонент, то выводим сообщение о том, что не нашли его
            printf("\nAbonent with name '%s' not found!\n", name_for_searching);
    }

}


int main(void){
    struct abonent arr[100];//Создаем массив структур для хранения абонентов
    int answer;//Ответ пользователя
    int count = 0;//Счетчик абонентов

    //Пока ответ не 5, бесконечно ждем ответа
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
                Add_abonent(&count, arr);
                break;
            case 2:
                printf("Removing abonent...\n");
                Remove_abonent(&count, arr);
                break;
            case 3:
                printf("Searching abonent...\n");
                Searching_abonent(&count, arr);
                break;
            case 4:
                printf("Displaying all records...\n");
                Display_records(arr, count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Error! Invalid choice '%d'. Please enter 1-5.\n", answer);
        }
    }

}
