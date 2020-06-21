#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "LR2_IO.h"

// Функция вывода одной записи таблицы на экран
void print_string(struct spectacle *table)
{
	printf("\nНазвание театра: ");
	printf("%s",table->theater);
	printf("\nНазвание спектакля: ");
	printf("%s",table->name_spc);
	printf("\nРежиссер: ");
	printf("%s",table->director);
	printf("\nДиапазон цен: ");
	printf("%d", table->low);
	printf(" - ");
	printf("%d", table->high);
	printf("\nТип спектакля: ");
	if (table->type_spc == 1)
		printf("Детский");
	else if (table->type_spc == 2)
		printf("Взрослый");
	else
		printf("Музыкальный");
	if (table->type_spc == 1) // Разветвление по типам спектакля
	{
		printf("\nМинимальный возраст: ");
		printf("%d", table->spct.child.age);
		printf("\nТип детского спектакля: ");
		if (table->spct.child.type == 1)
			printf("Сказка");
		else if (table->spct.child.type == 2)
			printf("Пьеса");
		else
			printf("Музыкальный");
	}
	else if (table->type_spc == 2)
	{
		printf("\nТип взрослого спектакля: ");
		if (table->spct.adult.type == 1)
			printf("Пьеса");
		else if (table->spct.adult.type == 2)
			printf("Драма");
		else
			printf("Комедия");
	}
	else if (table->type_spc == 3)
	{
		printf("\nКомпозитор: ");
		printf("%s",table->spct.musical.composer);
		printf("\nСтрана: ");
		printf("%s",table->spct.musical.country);
		printf("\nМинимальный возраст: ");
		printf("%d", table->spct.musical.age);
		printf("\nПродолжительность: ");
		printf("%d", table->spct.musical.dur);
	}
}

// Функция вывода всей таблицы на экран
void print(struct spectacle *table, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\n\nСтрока №%d\n", i + 1);
		print_string(&table[i]);

	}
	printf("\n");

}

// функция вывода исходной таблицы по ключам
void print_table_by_keys(struct spectacle *table, int keys[TABLE][2], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\n\nСтрока №%d\n", keys[i][0]);
		print_string(&table[keys[i][0] - 1]);
	}
	printf("\n");
}

// Функция чтения строкового типа данных
int read_line(char *s, int n)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) // Пока не достигнут конец потока ввода
	{
        if (i < n - 1) // Проверка на максимальную длину
            s[i] = ch;
		i++;
	}
    s[i] = '\0';
    return i;
}

// Функция чтения целочисленного типа данных
int read_int(int *a)
{
	int ch, i = 0, rc = 1;
	*a = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) // Пока не достигнут конец потока ввода
	{
        if (ch >= '0' && ch <= '9') // Проверка на число
             *a = *a * 10 + ch - '0';
		else
			rc = 0;
		i++;
	}
	if (rc == 0)
		return rc;
    return i;
}

// Функция заполнения таблицы из файла
void fill_file(struct spectacle *table, int *count)
{
	*count = 480;
	char current;
	FILE *f;
	f = fopen("base.txt", "r");
	assert(f);
	for (int i = 0; i < *count; i++)
	{
		fgets(table[i].theater, NAME, f);
		if (table[i].theater[strlen(table[i].theater)-1] == '\n')
			table[i].theater[strlen(table[i].theater)-1] = '\0';
		fgets(table[i].name_spc, NAME, f);
		if (table[i].name_spc[strlen(table[i].name_spc)-1] == '\n')
			table[i].name_spc[strlen(table[i].name_spc)-1] = '\0';
		fgets(table[i].director, NAME, f);
		if (table[i].director[strlen(table[i].director)-1] == '\n')
			table[i].director[strlen(table[i].director)-1] = '\0';
		fscanf(f, "%d", &table[i].low);
		fscanf(f, "%d", &table[i].high);
		fscanf(f, "%d", &table[i].type_spc);
        fscanf(f, "%c", &current);
		if (table[i].type_spc == 1) // Детский
		{
			fscanf(f, "%d", &table[i].spct.child.age);
			fscanf(f, "%d", &table[i].spct.child.type);
            fscanf(f, "%c", &current);
		}
		else if (table[i].type_spc == 2) // Взрослый
        {
			fscanf(f, "%d", &table[i].spct.adult.type);
            fscanf(f, "%c", &current);
        }
		else if (table[i].type_spc == 3) // Музыкальный
		{
            fscanf(f, "%c", &current);
			fgets(table[i].spct.musical.composer, NAME, f);
			if (table[i].spct.musical.composer[strlen(table[i].spct.musical.composer)-1] == '\n')
				table[i].spct.musical.composer[strlen(table[i].spct.musical.composer)-1] = '\0';
			fgets(table[i].spct.musical.country, THEATER, f);
			if (table[i].spct.musical.country[strlen(table[i].spct.musical.country)-1] == '\n')
				table[i].spct.musical.country[strlen(table[i].spct.musical.country)-1] = '\0';
			fscanf(f, "%d", &table[i].spct.musical.age);
			fscanf(f, "%d", &table[i].spct.musical.dur);
            fscanf(f, "%c", &current);
		}
		fscanf(f, "%c", &current);
        //fscanf(f, "%c", &current);
	}
	fclose(f);
}

// Функция заполнения матрицы ключей и индексов
void fill_keys(int keys[TABLE][2], struct spectacle *table, int count)
{
	for (int i = 0; i < count; i++)
	{
		keys[i][0] = i + 1;
		keys[i][1] = table[i].low;
	}
}
// Функция печати ключей и индексов
void print_keys(int keys[TABLE][2], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\nИндекс %d\n", keys[i][0]);
		printf("Наименьшая цена билета: %d\n", keys[i][1]);
	}
}

// Функция добавления структуры в конец файла
void add_struct(struct spectacle *table, int i)
{
	int count_let, low_price, high_price, action, age, duration;
	count_let = 0;
	while (count_let == 0 || count_let > THEATER) // Проверка на правильность ввода стрового типа
	{
		printf("\nВведите название театра(до 35 символов)\n");
		count_let = read_line(table[i].theater, THEATER);
		if (count_let == 0 || count_let >= THEATER)
		{
			count_let = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
		count_let = 0;
	while (count_let == 0 || count_let > NAME)
	{
		printf("\nВведите название спектакля(до 40 символов)\n");
		count_let = read_line(table[i].name_spc, NAME);
		if (count_let == 0 || count_let >= NAME)
		{
			count_let = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
	count_let = 0;
	while (count_let == 0 || count_let > NAME)
	{
		printf("\nВведите режиссера(до 40 символов)\n");
		count_let = read_line(table[i].director, NAME);
		if (count_let == 0 || count_let >= NAME)
		{
			count_let = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
	low_price = 0;
	while (low_price <= 0) // Проверка на правильность ввода целочисленного типа
	{
		printf("\nВведите нижний предел цены билета:\n");
		if (read_int(&low_price))
		{
			if (low_price <= 0)
				printf("\nНеверный ввод, введите еще раз\n");
			else
				table[i].low = low_price;
		}
		else
		{
			low_price = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
		
	}
	
	high_price = 0;
	while (high_price <= 0 || high_price < low_price)
	{
		printf("\nВведите верхний предел цены билета(должен быть больше или равен нижнему):\n");
		if (read_int(&high_price))
		{
			if (high_price <= 0 || high_price < low_price)
				printf("\nНеверный ввод, введите еще раз\n");
			else
				table[i].high = high_price;
		}
		else
		{
			high_price = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
	action = 0;
	while (action != 1 && action != 2 && action != 3)
	{
		printf("\nВыберите тип спектакля:\n1 - детский\n2 - взрослый\n3 - музыкальный\n");
		if (read_int(&action))
		{
			if (action != 1 && action != 2 && action != 3)
				printf("\nНеверный ввод, введите еще раз\n");
			else
				table[i].type_spc = action;
		}
		else
		{
			action = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	
	if (action == 1) // Детский
	{
		age = -1;
		while (age < 0 || age > 18)
		{
			printf("\nВведите возрастное ограничение(от 0 до 18):\n");
			if (read_int(&age))
			{
				if (age < 0 || age > 18 )
					printf("\nНеверный ввод, введите еще раз\n");
				else
					table[i].spct.child.age = age;
			}
			else
			{
				age = -1;
				printf("\nНеверный ввод, введите еще раз\n");
			}
			
		}
		
		action = 0;
		while (action != 1 && action != 2 && action != 3)
		{
			printf("\nВыберите тип детского спектакля:\n1 - сказка\n2 - пьеса\n3 - музыкальный\n");
			if (read_int(&action))
			{
				if (action != 1 && action != 2 && action != 3)
					printf("\nНеверный ввод, введите еще раз\n");
				else
					table[i].spct.child.type = action;
			}
			else
			{
				action = 0;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
	}
	else if (action == 2) // Взрослый
	{
		action = 0;
		while (action != 1 && action != 2 && action != 3)
		{
			printf("\nВыберите тип взрослого спектакля:\n1 - пьеса\n2 - драма\n3 - комедия\n");
			if (read_int(&action))
			{
				if (action != 1 && action != 2 && action != 3)
					printf("\nНеверный ввод, введите еще раз\n");
				else
					table[i].spct.adult.type = action;
			}
			else
			{
				action = 0;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
	}
	else if (action == 3) // Музыкальный
	{
		count_let = 0;
		while (count_let == 0 || count_let > NAME)
		{
			printf("\nВведите композитора(до 40 символов)\n");
			count_let = read_line(table[i].spct.musical.composer, NAME);
			if (count_let == 0 || count_let >= NAME)
			{
				count_let = 0;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
		
		count_let = 0;
		while (count_let == 0 || count_let > THEATER)
		{
			printf("\nВведите страну(до 35 символов)\n");
			count_let = read_line(table[i].spct.musical.country, THEATER);
			if (count_let == 0 || count_let >= THEATER)
			{
				count_let = 0;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
			
		age = -1;
		while (age < 0 || age > 18)
		{
			printf("\nВведите возрастное ограничение(от 0 до 18):\n");
			if (read_int(&age))
			{
				if (age < 0 || age > 18 )
					printf("\nНеверный ввод, введите еще раз\n");
				else
					table[i].spct.musical.age = age;
			}
			else
			{
				age = -1;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
		duration = 0;
		while (duration <= 0)
		{
			printf("\nВведите продолжительность(в минутах):\n");
			if (read_int(&duration))
			{
				if (duration <= 0)
					printf("\nНеверный ввод, введите еще раз\n");
				else
					table[i].spct.musical.dur = duration;
			}
			else
			{
				duration = 0;
				printf("\nНеверный ввод, введите еще раз\n");
			}
		}
	}
}

// Функция заполнения таблицы вручную
void fill_manually(struct spectacle *table, int *count)
{
	int i = 0;
	*count = 0;
	while (*count <= 0 || *count > TABLE) // Ввод количества записей в таблице
	{
		printf("\nВведите число строк таблицы(от 1 до 45):\n");
		if (read_int(count))
		{
			if (*count <= 0 || *count > TABLE)
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			*count = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}

	while (i < *count) // Ввод по записи
	{
		printf("\n\nСтрока №%d\n", i+1);
		add_struct(table, i);
		i++;
	}
}

// Функция удаления записи по ее индексу
void remove_struct(struct spectacle *table, int *count)
{
	int index = 0;
	while (index <= 0 || index > *count) // Ввод индекса
	{
		printf("\nВведите индекс удаляемой строки(от 1 до %d):\n", *count);
		if (read_int(&index))
		{
			if (index <= 0 || index > *count)
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			*count = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	index--;
	for (int i = index; i < *count - 1; i++) // Сдвиг массива структур на 1 начиная с введенного индекса
		table[i] = table[i + 1];
	*count -= 1;
}
	
