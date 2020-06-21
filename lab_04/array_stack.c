#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structure_arr.h"
#include "structure_list.h"
#include "menu.h"
#include "arr_stack_op.h"
#include "list_stack_op.h"

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

int main()
{
	setbuf(stdout, NULL);
	menu_stack_type();
	int option = 0;
	scanf("%d", &option);
	if(option == 1)
	{
		Stack *stk;
		stk = init();

		while(option != 0)
		{
			menu_operations_array();
			printf("МАКСИМАЛЬНОЕ КОЛ-ВО ЭЛЕМЕНТОВ ДЛЯ МАССИВА: %d (СПИСОК НЕ ОГРАНИЧЕН)\n", SIZE);

			printf("\nВыберите операцию: \n");
			scanf("%d", &option);

			switch(option)
			{
				case 1:
				{
					char word[40];
					memset(word,0,strlen(word));
					printf("Введите слово для пуша: \n");
					scanf("%s", word);
					push(stk, word);

					break;
				}
				case 2:
				{
					pop(stk);
					if(stk->top != -1 )
						printf("Новое начало: %s\n", stk->strings[stk->top]);
					else
						printf("ПУСТО\n");
					break;
				}
				case 3:
				{
					printf("\nСТЕК: \n");
					print(stk);
					break;
				}
				case 4:
				{	
					printf("\nПОЛУЧЕННЫЙ СТЕК: \n");
					print_back(stk);
				
					break;
				}	
			}
		}

	destroy(&stk);
	}

	if(option == 2)
	{
		node_t *stk = NULL;
		node_t **pointers = malloc(SIZE*sizeof(node_t*));
		int i = 0;

		while(option != 0)
		{
			menu_operations_array();
            printf("5. Показать занятые/очищенные адреса\n");
			printf("МАКСИМАЛЬНОЕ КОЛ-ВО ЭЛЕМЕНТОВ ДЛЯ МАССИВА: %d (СПИСОК НЕ ОГРАНИЧЕН)\n", SIZE);

			printf("\nВЫБЕРИТЕ ОПЕРАЦИЮ: \n");
			scanf("%d", &option);

			switch(option)
			{
				case 1:
				{	
					char word[40];
					memset(word,0,strlen(word));
					printf("Введите слово для пуша: \n");
					scanf("%s", word);
					push_l(&stk, word);
					if(i > 0)
						i--;

					break;
				}
				case 2:
				{
					pointers[i] = stk;
					i++;
					pop_front(&stk);
					if(stk != 0)
						printf("\nНовое начало: %s ", stk->data);
					else
						printf("Стек пуст!\n");
					break;
				}
				case 3:
				{
					printf("\nСтек: \n");
					print_stack_l(stk);
					break;
				}
				case 4:
				{		
					printf("\nПолученный стек: \n");
					print_back_list(stk);
					stk = NULL;
					break;
				}
				case 5:
					printf("Очищенные адреса:\n");
					for (int j = 0; j < i; j++)
					{
						printf("%d) %p\n",j+1, (void*) pointers[j]);
					}
					printf("Заполненные адреса: \n");
					print_addresses(stk);

					break;
			}
		}
		freeList(&stk);
		free(pointers);
	}

	if(option == 3)
	{
		{
			unsigned long long tb, te;
			double time_spent = 0;

			Stack *stk_arr;
			stk_arr = init();

			node_t *stk_list = NULL;

			tb = tick();
			for (int i = 0; i < 10; i++)
			{
				push(stk_arr, "word");
			}
			te = tick();
			time_spent = ((double)(te - tb) /(double) CLOCKS_PER_SEC)/10;

			double push_arr = (double)time_spent;
			printf("Время PUSH для массива: %f", push_arr);
			//printf("Пуш массив %d%c\n", 100, '%');
			printf("\n");

			tb = tick();
			for (int i = 0; i < 10; i++)
			{
				push_l_test(&stk_list, "word");
			}
			te = tick();
			time_spent = ((double)(te - tb) /(double) CLOCKS_PER_SEC)/10;

			printf("Время PUSH для списка: %f\n", time_spent);
			printf("PUSH: список быстрее массива в %.1f %c \n", ((((double)push_arr)*100)/(double)time_spent), '%');

			/*---------------------------------------------------------------------------------*/

			tb = tick();
			for (int i = 0; i < 10; i++)
			{
				pop(stk_arr);
			}
			te = tick();
			time_spent = ((double)(te - tb) /(double) CLOCKS_PER_SEC)/10;

			double pop_arr = (double)time_spent;
			printf("\n-------------\n");
			printf("Время POP для массива: %f", pop_arr);
			//printf("Поп массив %d%c\n", 100, '%');
			printf("\n");


			tb = tick();
			for (int i = 0; i < 10; i++)
			{
				pop_test(&stk_list);
			}
			te = tick();
			time_spent = ((double)(te - tb) /(double) CLOCKS_PER_SEC)/10;

			printf("Время POP для списка: %f\n", time_spent);
			printf("POP: массив быстрее списка в %.1f %c \n", ((((double)time_spent)*100)/(double)pop_arr), '%');
			printf("\n");

			destroy(&stk_arr);
			freeList(&stk_list);
		}
	}
	

	return 0;
}

