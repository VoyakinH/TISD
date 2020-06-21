#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LR2_IO.h"
#include "LR2_process.h"

int main(void)
{
	srand(time(0));
	setbuf(stdout, NULL);
	int action = 0, count = 0;
	int keys[TABLE][2]; // Матрица для ключей
	struct spectacle table[TABLE]; // Массив структур для таблицы спектаклей
	printf("Данная программа предназначена для хранения репертуара театров\n");
	printf("в табличной форме. Вы можете заполнить таблицу самостоятельно или заполнить\n");
	printf("ее автоматически. Далее вы сможете удалять записи из таблицы, добавлять их,\n");
	printf("сортировать спектакли по самым дешевым билетам с помощью сортировок по ключам и самой таблицы и\n");
	printf("сравнивать эти способы сортировки.\n");
	
	while (action != 1 && action != 2) // Меню для выбора типа ввода
	{
		printf("\nВыберите, как заполнить таблицу:\n1 - вручную\n2 - автоматически\n");
		if (read_int(&action))
		{
			if (action == 1 || action == 2)
			{
				if (action == 1)				
					fill_manually(table, &count); // Вбивать записи вручную
				if (action == 2)
					fill_file(table, &count); // Автоматически заполнить из файла
			}
			else
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			action = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
	action = -1;
	while (action != 0) // Основное меню действий
	{
		printf("\nВыберите действие:\n");
		printf("1 - вывести таблицу\n");
		printf("2 - добавить запись в конец таблицы:\n");
		printf("3 - удалить запись по ее индексу\n");
		printf("4 - отсортировать ключи по меньшей цене билетов и вывести их\n");
		printf("5 - отсортировать таблицу по меньшей цене билетов и вывести ее\n");
		printf("6 - отсортировать ключи по меньшей цене билетов и вывести таблицу \n");
		printf("7 - сравнить сортировку по ключам и сортировку таблицы \n");
		printf("8 - сравнить быструю сортировку и сортировку пузырьком\n");
		printf("9 - найти музыкальные записи по указанному возрастному ограничению и продолжительности\n");
		printf("0 - выход\n");
		if (read_int(&action))
		{
			if (action == 1 || action == 2 || action == 3 || action == 4 || action == 5 || action == 6 || action == 7 || action == 8 || action == 9 || action == 0)
			{
				if (action == 1) // Вывести таблицу на экран
				{
					if (count > 0)
						print(table, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 2) // Добавить запись в конец таблицы
				{
					if (count < TABLE)
					{
						add_struct(table, count);
						count++;
					}
					else
						printf("\nДостигут максимум записей\n");
				}
				else if (action == 3) // Удалить запись по ее индексу
				{
					if (count > 0)
						remove_struct(table, &count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 4) // Отсортировать и вывести на экран ключи при неотсортированной таблице
				{
					if (count > 0)
					{
						fill_keys(keys, table, count);
						bubble(keys, count);
						print_keys(keys, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 5) // Отсортировать таблицу и вывести ее на экран
				{
					if (count > 0)
					{
						sort_table_qs(table, 0, count - 1);
						fill_keys(keys, table, count);
						print(table, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 6) // Отсортировать ключи и вывести по ним на экран таблицу
				{
					if (count > 0)
					{
						fill_keys(keys, table, count);
						qs(keys, 0, count - 1);
						print_table_by_keys(table, keys, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 7) // Сравнить сортировку по ключам и таблицы 
				{
					if (count > 0)
						time_table(table, keys, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 8) // Сравнить сортировку пузырьком и быструю сортировку ключей
				{
					if (count > 0)
						time_keys(table, keys, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 9) // Вывести музыкальные записи по указанным параметрам
				{
					if (count > 0)
						search(table, count);
					else
						printf("\nВ таблице нет записей\n");
				}
			}
			else
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			action = -1;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	return 0;
}
				
	
	
