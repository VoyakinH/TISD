#include <stdio.h>
#include <string.h>
#include <time.h>
#include "LR2_IO.h"
#include "LR2_process.h"

// Фунция сортировки матрицы ключей пузырьком
void bubble(int keys[TABLE][2], int count)
{
	int tmp;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count ; j++)
		{
			if (keys[i][1] > keys[j][1]) // Перестановка строк матрицы
			{
				tmp = keys[j][1];
				keys[j][1] = keys[i][1];
				keys[i][1] = tmp;
				tmp = keys[j][0];
				keys[j][0] = keys[i][0];
				keys[i][0] = tmp;
			}
		}
	}
}

// Функция быстрой сортировки матрицы ключей
void qs(int keys[TABLE][2], int first, int last)
{
	int tmp;
    if (first < last) // Верхняя и нижняя границы
    {
        int left = first, right = last, middle = keys[(left + right) / 2][1];
        do // Пока границы не сомкнутся
        {
            while (keys[left][1] < middle) left++; // Сдвиг левой границы
            while (keys[right][1] > middle) right--; // Сдвиг правой границы 
            if (left <= right) // Перестановка строк матрицы
            {
				tmp = keys[left][1]; 
                keys[left][1] = keys[right][1];
                keys[right][1] = tmp;
				tmp = keys[left][0];
                keys[left][0] = keys[right][0];
                keys[right][0] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qs(keys, first, right); // Рекурсия для левой и правой частей матрицы
        qs(keys, left, last);
    }
}

// Функция быстрой сортировки массива структур
void sort_table_qs(struct spectacle *table, int first, int last)
{
	struct spectacle tmp;
	if (first < last) // Верхняя и нижняя границы
    {
        int left = first, right = last, middle = table[(left + right) / 2].low;
        do // Пока границы не сомкнутся
        {
            while (table[left].low < middle) left++; // Сдвиг левой границы
            while (table[right].low > middle) right--; // Сдвиг правой границы 
            if (left <= right) // Перестановка строк матрицы
            {
				tmp = table[left];
                table[left] = table[right];
                table[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        sort_table_qs(table, first, right); // Рекурсия для левой и правой частей массива
        sort_table_qs(table, left, last);
    }
}

// Фунция сортировки массива структур пузырьком
void sort_table_bubble(struct spectacle *table, int count)
{
	struct spectacle tmp;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count ; j++)
		{
			if (table[i].low > table[j].low) // Перестановка элементов массива
			{
				tmp = table[j];
				table[j] = table[i];
				table[i] = tmp;
			}
		}
	}
}
// Функция возврата тактов процессора
unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d));
	return d;
}

// Функция сравнения времени сортировки таблицы и по ключам
void time_table(struct spectacle *table, int keys[TABLE][2], int count)
{
	unsigned long long tb, te, all_k = 0, all_t = 0;
	struct spectacle table_test[count];
	float result;
	for (int i = 0; i < 10; i++) // Для усреднения делается 10 замеров
	{
		for (int j = 0; j < count; j++) // Заполнение тестового массива структур
			table_test[j] = table[j];
		fill_keys(keys, table, count); // Заполнение матрицы ключей
		tb = tick(); // Замер времени для быстрой сортировки ключей
		qs(keys, 0, count - 1);
		te = tick();
		all_k += te - tb; // Прибавление к общему времени сортировки ключей
		tb = tick(); // Замер времени для быстрой сортировки таблицы
		sort_table_qs(table_test, 0, count - 1);
		te = tick();
		all_t += te - tb; // Прибавление к общему времени сортировки таблицы
	}
	printf("\nСортировка по ключам(в тактах): %d\n", (int)all_k/10);
	printf("\nСортировка таблицы(в тактах): %d\n", (int)all_t/10);
	if (all_t >= all_k)
	{
		result = (all_t - all_k)/(float)all_t * 100; // Перевод результата в проценты
		printf("\nСортировка по ключам быстрее сортировки таблицы на %.3f %%", result);
	}
	else if (all_t < all_k)
	{
		result = (all_k - all_t)/(float)all_k * 100;
		printf("\nСортировка таблицы быстрее сортировки по ключам на %.3f %%", result);
	}
	result = (sizeof(keys[0][0]) * 2 * TABLE) / (float)(sizeof(table[0]) * TABLE) * 100;
	printf("\nМатрица для индексов использует дополнительные %.3f%% памяти относительно массива структур\n", result);
}

// Функция сравнения времени сортировки ключей быстрой сортировкой и сортировкой пузырьком
void time_keys(struct spectacle *table, int keys[TABLE][2], int count)
{
	float result;
	unsigned long long tb, te, all_k1 = 0, all_k2 = 0;
	for (int i = 0; i < 10; i++) // Для усреднения делается 10 замеров
	{
		fill_keys(keys, table, count); // Заполнение матрицы ключей
		tb = tick();
		bubble(keys, count); // Замер времени для сортировки ключей пузырьком
		te = tick();
		all_k1 += te - tb; // Прибавление к общему времени сортировки ключей пузырьком
		fill_keys(keys, table, count); // Заполнение матрицы ключей
		tb = tick(); 
		qs(keys, 0, count - 1); // Замер времени для быстрой сортировки ключей
		te = tick();
		all_k2 += te - tb; // Прибавление к общему времени сортировки ключей быстрой сортировкой
	}
	printf("\nБыстрая сортировка(в тактах): %d\n", (int)all_k2/10);
	printf("\nСортировка пузырьком(в тактах): %d\n", (int)all_k1/10);
	if (all_k1 >= all_k2)
	{
		result = (all_k1 - all_k2)/(float)all_k1 * 100; // Перевод результата в проценты
		printf("\nБыстрая сортировка быстрее сортировки пузырьком на %.3f %%\n", result);
	}
	else if (all_k1 < all_k2)
	{
		result = (all_k2 - all_k1)/(float)all_k2 * 100;
		printf("\nСортировка пузырьком быстрее быстрой сортировки на %.3f%%\n", result);
	}
}

// Функция поиска элементов по заданным параметрам
void search(struct spectacle *table, int count)
{
	int age = -1, duration = 0, count_s = 0;
	while (age < 0 || age > 18)
	{
		printf("\nВведите возраст ребенка(от 0 до 18):\n");
		if (read_int(&age))
		{
			if (age < 0 || age > 18 )
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			age = -1;
			printf("\nНеверный ввод, введите еще раз\n");
		}	
	}
	while (duration <= 0)
	{
		printf("\nВведите максимальную продолжительность спектакля(в минутах):\n");
		if (read_int(&duration))
		{
			if (duration <= 0)
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			duration = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	for (int i = 0; i < count; i++)
	{
		if (table[i].type_spc == 3)
		{
			if (table[i].spct.musical.age <= age)
			{
				if (table[i].spct.musical.dur <= duration)
				{
					printf("\n\nСтрока №%d\n", i + 1);
					print_string(&table[i]);
					count_s++;
				}
			}
		}
	}
	if (count_s == 0)
		printf("\nМузыкальных спектаклей по указанным параметрам не найдено\n");
	else
		printf("\n");
}
