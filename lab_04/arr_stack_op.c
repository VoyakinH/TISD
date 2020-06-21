#include "arr_stack_op.h"

Stack *init() {
	Stack * created_stack = NULL;
	created_stack = malloc(sizeof(Stack));
	
	if (created_stack == NULL) {
		exit(OUT_OF_MEMORY);
	}
	
	created_stack->size = SIZE;
	created_stack->strings = malloc(created_stack->size * sizeof(char*));
	
	if (created_stack->strings == NULL) {
		free(created_stack);
		exit(OUT_OF_MEMORY);
	}
	
	created_stack->top = -1;
	
	return created_stack;
}

void destroy(Stack **stack) {
	for (int i = 0; i < (*stack)->top; i++)
	{
		free((*stack)->strings[i]);
	}
	free((*stack)->strings);
	free(*stack);
	*stack = NULL;
}

void push(Stack *stack, char *new_string) {

	if (stack->top != stack->size - 1) {
		stack->top++;
		stack->strings[stack->top] = malloc(strlen(new_string) + 1);
		strcpy(stack->strings[stack->top], new_string);
		
	}
	else
	printf("МАКСИМУМ ДОСТИГНУТ\n");
}

char *pop(Stack *stack) {
	if (stack->top == -1) { //если stack->top(индекс первого сверху элемента в массиве)  == -1
		return NULL;
	}
	stack->top--;   //просто уменьшаем верхушку без удаления самого слова тк в него запишем потом новое
	
	return stack->strings[stack->top]; //возвращаем текущее слово после удаления
}

void print(Stack *stack)
{
	printf("<-|");
	for (int i = stack->top; i >= 0; i--)
	{
		printf(" %s|", stack->strings[i]);	
	}
	printf("|");
	printf("\n");
}

void print_back(Stack *stack)
{
	if(stack->top != -1) //проверка на наличие элементов в массиве
	{
		int n = stack->top; //заносим кол-во элементов в массиве
		printf("%s ", stack->strings[stack->top]); //выводим верхний элемент
		for (int i = 0; i < n; i++)  //проходимся по всему массиву
		{
			printf("%s ", pop(stack)); // делаем pop и так он возвращает текущее слово после удаление то выводим его
		}
		pop(stack); //делаем последний pop без вывода тк в массиве ничего не останется
		printf("\n");
	}
	else
        printf("Стек пуст!\n");  //иначе пишем что массив пуст
}

void clear_arr(Stack *stack)
{
	if(stack->top != -1)
	{
		int n = stack->top;
		for (int i = 0; i < n; i++)
		{
			pop(stack);
		}
		pop(stack);
	}
	else
	printf("Стек пуст!\n");
}

