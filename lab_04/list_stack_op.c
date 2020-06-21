#include "list_stack_op.h"

void push_l(node_t** head, char *new_data) 
{ 
	node_t* new_node = (node_t*)malloc(sizeof(node_t));  //выделяем помять под структуру

	new_node->data  = malloc(strlen(new_data) + 1); //выделяем память под слово в структуре (+1 для терминального нуля)
	new_node->next = (*head); //в указатель на след структуру заносим переданную тк наша созданная будет выше нее

	strcpy(new_node->data, new_data); //копируем просто
		  
	*head = new_node;  //в хэд заносим последнюю структуру
	printf("\n Новый адрес: %p\n", (void*)new_node); //выводим адрес новой стркутуры
} 


node_t* pop_front(node_t **head)
{
	if(*head == NULL) //если у нас нет элементов в спискн
		return NULL;
	node_t *buf = *head; //в буффер заносим копию головы
	printf("\n Очищенный адрес: %p\n", (void*)buf); //пишем какой адрес у нас очистился
	*head = (*head)->next; // в голову заносим адрес на струкутуру изэтой головы то есть в head получается предыдущая структура
	
	free(buf->data); //удаляем слово в структуре buff но тк это указатель то это ссылка и удалится память самого head
	free(buf); //чистим саму строкутуру
	return *head; //возврщаем указатель на полученную голову
}

void print_stack_l(node_t *head)
{
	if(head != NULL)
	{
		printf("<-|");
		while (head != NULL)
		{
			printf(" %s|", head->data);
			head = head->next;
		}
		printf("|");
	}
	else
	printf("Стек пуст!\n");
	
}


void freeList(node_t** head)
{
	node_t *cur = *head;
	while(cur != NULL)
	{
		free(cur->data);
		cur = cur->next;
	}
}


node_t* print_back_list(node_t *head)
{
	//printf("|");
	while (head != NULL)
	{
		printf(" %s", head->data);
		pop_front(&head);
	}
	//printf("|");
	return head;
}


node_t* reverse(node_t* head)
{
	if(head->next == NULL)
		return head;
	node_t* prev = NULL;
	node_t* current = head;
	node_t* next;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}


int count(node_t *head)
{
	int count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return count;
}

void print_addresses(node_t *head)
{
	while (head != NULL)
	{
		printf("%p\n", (void*)head);
		head = head->next;
	}
}

node_t** delete_from_list(node_t *head, node_t **point)
{
	while(head != NULL)
	{
		if((void*)head == (void*)point[1])
		{
			free(point[1]);
			*point = NULL;
			break;
		}
		head = head->next;

	}
	return point;
}

void push_l_test(node_t** head, char *new_data) 
{ 
	node_t* new_node = (node_t*)malloc(sizeof(node_t)); 

	new_node->data  = malloc(strlen(new_data) + 1); 
	new_node->next = (*head); 

	strcpy(new_node->data, new_data);
		  
	*head = new_node; 
} 

//function without printf
node_t* pop_test(node_t **head)
{
	if(*head == NULL)
		return NULL;
	node_t *buf = *head;
	*head = (*head)->next;
	
	free(buf->data);
	free(buf);
	return *head;
}

