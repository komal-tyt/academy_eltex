#include "../include/abonent.h"

/*!
	\file abonent.c
	\brief Реализация функций для работы с абонентами
*/

/*!
 * \brief Функция для создания списка абонентов
 *
 * Функция создает пустой список абонентов и инициализирует его размер, а также голову и хвост списка
 *
 * \code
	AbonentList* Create_abonent_list(void){
		AbonentList* list = malloc(sizeof(AbonentList));
		if (list == NULL){ // Проверка на ошибку выделения памяти
			perror("Malloc is failed");
			return NULL;
		}
		list->size=0;// Инициализация размера списка
		list->head=NULL;// Инициализация головы списка
		list->tail=NULL;// Инициализация хвоста списка

		return list;
	}
	\endcode
	\return Сам список абонентов
*/
AbonentList* Create_abonent_list(void){
	AbonentList* list = malloc(sizeof(AbonentList));
	if (list == NULL){
		perror("Malloc is failed");
		return NULL;
	}
	list->size=0;
	list->head=NULL;
	list->tail=NULL;

	return list;
}

/*!
 * \brief Функция для добавления абонента в список
 *
 * Функция добавляет абонента в конце списка
 *
 * \code
 * void Add_abonent(AbonentList* list){
	Abonent* new_abonent = malloc(sizeof(Abonent));

	if(new_abonent == NULL){ // Проверка на успешное выделение памяти
		perror("Malloc is failed: ");
		return;
	}

	printf("Enter name: ");
	scanf("%9s", new_abonent->name);
	printf("Enter second name: ");
	scanf("%9s", new_abonent->second_name);
	printf("Enter phone number: ");
	scanf("%9s", new_abonent->tel);

	new_abonent->next = NULL;
	new_abonent->prev = NULL;

	if (list->head == NULL){ // Если список пуст, то голова и хвост указывают на новый элемент
		list->head = new_abonent;
		list->tail = new_abonent;
	} else{                  // Иначе добавляем элемент в конец списка
		list->tail->next = new_abonent;
		new_abonent->prev = list->tail;
		list->tail = new_abonent;
	}

	list->size++; // +1 абонент
 }
 * \endcode
 * \param list Указатель на список абонентов
 */
void Add_abonent(AbonentList* list){
	Abonent* new_abonent = malloc(sizeof(Abonent));

	if(new_abonent == NULL){
		perror("Malloc is failed: ");
		return;
	}

	printf("Enter name: ");
	scanf("%9s", new_abonent->name);
	printf("Enter second name: ");
	scanf("%9s", new_abonent->second_name);
	printf("Enter phone number: ");
	scanf("%9s", new_abonent->tel);

	new_abonent->next = NULL;
	new_abonent->prev = NULL;

	if (list->head == NULL){
		list->head = new_abonent;
		list->tail = new_abonent;
	} else{
		list->tail->next = new_abonent;
		new_abonent->prev = list->tail;
		list->tail = new_abonent;
	}

	list->size++;
}

/*!
 * \brief Функция для отображения всех записей в списке
 *
 * Функция проходится по списку и выводит информацию о каждом абоненте
 *
 * \code
 * void Display_records(AbonentList* list){

	Abonent* ptr = list->head; // Создаем временный указатель на текущей элемент списка

	if (ptr == NULL) { // Проверка на пустой список
         printf("Records is empty!\n");
         return;
     }

	int i = 1; // id абонента
	while(ptr != NULL){
		printf("%d)\n", i);
		printf("Name: %s\n", ptr->name);
		printf("Second name: %s\n", ptr->second_name);
		printf("Phone: %s\n", ptr->tel);
		ptr = ptr->next; // Переходим к следующему элементу списка
		i++;

	}
 }
 * \endcode
 *param list Указатель на список абонентов
 */
void Display_records(AbonentList* list){

	Abonent* ptr = list->head;

	if (ptr == NULL) {
        printf("Records is empty!\n");
        return;
    }

	int i = 1;
	while(ptr != NULL){
		printf("%d)\n", i);
		printf("Name: %s\n", ptr->name);
		printf("Second name: %s\n", ptr->second_name);
		printf("Phone: %s\n", ptr->tel);
		ptr = ptr->next;
		i++;

	}
}

/*!
 * \brief Функция для удаления абонента из списка
 *
 * Функция удаляет абонента из списка по его индексу, удаляет, смотря, где находится абонент в списке
 *
 * \code
 * void Remove_abonent(AbonentList* list){
	int choice = 0; // Выбор пользователя
     printf("Please select a abonent index: ");
     scanf("%d", &choice);

     if (choice < 1 || (size_t)choice > list->size){ // Если выбор пользователя выходит за пределы списка, то выводим ошибку
    		printf("Invalid choice!");
     } else {
     	Abonent* ptr = list->head;
      	if (ptr == NULL) {
             printf("Records is empty!\n");
             return;
         }

     	for (int i = 1; i < choice; i++){ // Этим циклом мы доходим до нужного элемента
     		ptr = ptr->next;
      	}

	     if(list->head == list->tail){ // Если голова и хвост совпадают, значит список состоит из одного элемента и обнуляем его
	     	list->head = NULL;
	      	list->tail = NULL;
	     } else if (ptr == list->head){ // Если указатель совпал с головой(Мы хоти удалить голову), то обновляем голову  и обнуляем предыдущий элемент
	     	list->head = ptr->next;
	      	list->head->prev = NULL;
	     } else if (ptr == list->tail){ // Если указатель совпал с хвостом(Мы хоти удалить хвост), то обновляем хвост и обнуляем следующий элемент
	     	list->tail = ptr->prev;
	      	list->tail->next = NULL;
	     } else {                      // Иначе у нас элемент в середине и обновляем указатели предыдущего и следующего элементов
	     	ptr->prev->next = ptr->next;
	      	ptr->next->prev = ptr->prev;
	     }
		free(ptr);
      	list->size--;
     }
 }
 * \endcode
 * \param list Список абонентов
 */
void Remove_abonent(AbonentList* list){
	int choice = 0;//Выбор пользователя
    printf("Please select a abonent index: ");
    scanf("%d", &choice);

    if (choice < 1 || (size_t)choice > list->size){
   		printf("Invalid choice!");
    } else {
    	Abonent* ptr = list->head;
     	if (ptr == NULL) {
            printf("Records is empty!\n");
            return;
        }

    	for (int i = 1; i < choice; i++){
    		ptr = ptr->next;
     	}

	     if(list->head == list->tail){
	     	list->head = NULL;
	      	list->tail = NULL;
	     } else if (ptr == list->head){
	     	list->head = ptr->next;
	      	list->head->prev = NULL;
	     } else if (ptr == list->tail){
	     	list->tail = ptr->prev;
	      	list->tail->next = NULL;
	     } else {
	     	ptr->prev->next = ptr->next;
	      	ptr->next->prev = ptr->prev;
	     }
		free(ptr);
     	list->size--;
    }
}

/*!
 * \brief Функция для поиска абонента по имени
 *
 * Функция ищет абонента по имени пока не совпадет имя в списке и имя введенное пользователем
 *
 * \code
 * void Searching_abonent(AbonentList* list){
	char name_for_searching[10];//Создаем массив для хранения имени абонента для поиска
     printf("Enter the name for searching: ");
     scanf("%9s", name_for_searching);

     Abonent* ptr = list->head;
     if (ptr == NULL) {
            printf("Records is empty!\n");
            return;
     }

     int found = 0; // Флаг если абонент найден
     int id = 1; // айди абонента

     while(ptr != NULL){
     	int i = 0;
      	while (name_for_searching[i]!='\0' && ptr->name[i]!='\0' && name_for_searching[i] == ptr->name[i]){ // Этим циклом мы проходимся и проверяем, что символы в имени искомого абонента и имени текущего абонента совпадают
       		i++;
       	}
       	if (name_for_searching[i]=='\0' && ptr->name[i]=='\0') { // Если имена совпали, то выводим информацию
        		printf("ID: %d\n", id);
        		printf("Name: %s\n", ptr->name);
          		printf("Second Name: %s\n", ptr->second_name);
           		printf("Phone Number: %s\n", ptr->tel);
            	found = 1;
        }
        ptr = ptr->next; // Переходим к следующему элементу списка
        id++;
     }

     if (found == 0){ // Если абонент не найден
     	printf("Abonent is not found");
     }
 }
 * \endcode
 * \param list указатель на список абонентов
 */
void Searching_abonent(AbonentList* list){
	char name_for_searching[10];//Создаем массив для хранения имени абонента для поиска
    printf("Enter the name for searching: ");
    scanf("%9s", name_for_searching);

    Abonent* ptr = list->head;
    if (ptr == NULL) {
           printf("Records is empty!\n");
           return;
    }

    int found = 0;
    int id = 1;

    while(ptr != NULL){
    	int i = 0;
     	while (name_for_searching[i]!='\0' && ptr->name[i]!='\0' && name_for_searching[i] == ptr->name[i]){
      		i++;
      	}
      	if (name_for_searching[i]=='\0' && ptr->name[i]=='\0') {
       		printf("ID: %d\n", id);
       		printf("Name: %s\n", ptr->name);
         	printf("Second Name: %s\n", ptr->second_name);
          	printf("Phone Number: %s\n", ptr->tel);
           	found = 1;
       }
       ptr = ptr->next;
       id++;
    }

    if (found == 0){
    	printf("Abonent is not found");
    }
}

/*!
 * \brief Функция для освобождения памяти, выделенной под список абонентов
 *
 * Функция проходит по списку и освобождает память, выделенную под каждый элемент списка.
 *
 * \code
 * void Free_records(AbonentList* list){
	Abonent* ptr = list->head;
	while(ptr!=NULL){
		Abonent* next = ptr->next; // Сохраняем указатель на следующий элемент
		free(ptr); // Освобождаем память, выделенную под текущий элемент
		ptr = next; // Переходим к следующему элементу
	}
	free(list); // Очищаем память, выделенную под список
 }
 * \endcode
 * \param list указатель на список абонентов
 */
void Free_records(AbonentList* list){
	Abonent* ptr = list->head;
	while(ptr!=NULL){
		Abonent* next = ptr->next;
		free(ptr);
		ptr = next;
	}
	free(list);
}
