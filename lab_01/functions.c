#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "defines.h"

enum FLOAT_NUM {
    SIGN_1,      // 0 - был введен знак
    DOT,        // 1 - была точка
    E,          // 2 - было E
    SIGN_2       // 3 - был введен знак порядка
};

// Функция чтения действительного числа
// rc - код возвращения работы программы
// str_fl - мантисса
// len_fl - длина числа
// minus - отрицательность числа
// order - порядок
// i_count - количество элементов в мантиссе
// after_dot - количество элементов после точки, но до порядрка
// tmp - буферная переменная
// was_zero - был ли ноль
// order_sign - знак порядка
// change_sign - знак мантиссы
int float_input(FILE *f_in, char *str_fl, int *len_fl, int *minus, int *order)
{
    int rc = OK;
    char tmp;
    int was_zero = 0, order_sign = 0, change_sign = 0;
    enum FLOAT_NUM num1 = SIGN_1;
    int mantissa_count = 0, order_count = 0, i_count = 0;
    
    int after_dot = 0;
    *len_fl = 0;
    *order = 0;
    
    while((tmp = fgetc(f_in)) != '\n')
    {
        if (i_count != N_FL)
        {
            if (mantissa_count > MANT)
            {
                rc = ERR_RANGE_MANT;
                break;
            }
            if (tmp == '-' && i_count == 0)
                change_sign = 1;
            else if (tmp == '.' && num1 == SIGN_1)
                num1 = DOT;
            else if (isdigit(tmp) && num1 <= DOT)
            {
                if (was_zero == 1|| (isdigit(tmp) && tmp != '0') || num1 == DOT)
                {
                    str_fl[*len_fl] = tmp;
                    was_zero = 1;
                    *len_fl += 1;
                    if (num1 == DOT)
                        after_dot += 1;
                }
                mantissa_count++;
            }
            else if ((tmp == 'E' || tmp == 'e') && mantissa_count > 0 && num1 != E)
                num1 = E;
            else if (tmp == '-' && num1 == E)
            {
                order_sign = 1;
                num1 = SIGN_2;
            }
            else if (tmp == '+' && num1 == E)
                num1 = SIGN_2;
            else if (isdigit(tmp) && num1 >= E)
            {
                order_count++;
                num1 = SIGN_2;
                if (order_count > 5)
                {
                    rc = ERR_RANGE_ORDER;
                    break;
                }
                else
                {
                    *order = *order * 10 + (tmp - '0');
                }
            }
            else
            {
                rc = ERR_INP;
                break;
            }

            i_count += 1;
        }
        else
        {
             rc = ERR_INP;
             break;
        }
    }

    if (mantissa_count == 0)
    {
        rc = ERR_NO_DATA;
    }
    else if (num1 == E)
    {
        rc = ERR_INP;
    }

    if (order_sign)
    {
        *order *= -1;
    }

    *order -= after_dot;

    if (change_sign == 1 && rc == OK)
    {
        *minus *= -1;
    }
    fseek(stdin, 0, SEEK_END);
    return rc;
}

// Функция чтения целого числа
// rc - код возвращения работы программы
// str_int - число
// len_int - длина числа
// minus - знак числа
// len_int - количество значимых элементов
int int_input(FILE *f_in, char *str_int, int *len_int, int *minus)
{
    char str_buff[N_INT + 2];
    int rc = OK;
    fgets(str_buff, 32, f_in);
    if (str_buff[0] == '-')
    {
        *minus = 1;
        int i = 1;
        while (str_buff[i] != '\n')
        {
            if (isdigit(str_buff[i]) == 0)
            {
                rc = ERR_INP;
                break;
            }
            str_int[i] = str_buff[i];
            i++;
        }
        *len_int = i - 1;
    }
    else
    {
        *minus = 0;
        int i = 0;
        while (str_buff[i] != '\n')
        {
            if (isdigit(str_buff[i]) == 0)
            {
                rc = ERR_INP;
                break;
            }
            str_int[i] = str_buff[i];
            i++;
        }
        *len_int = i;
    }
    if (*len_int == 0)
        rc = ERR_INP;
    else if (*len_int > N_INT)
        rc = ERR_RANGE_INT;
    fseek(stdin, 0, SEEK_END);
    return rc;
}

// Функция для инициализации массива
// arr - массив
// n - длина числа
void init_array(char *arr, int n)
{
    assert(n > 0);
    for (int i = 0; i < n; i++)
    {
        arr[i] = '0';
    }
}

// Функция округления числа
// arr - массив для округления
// first_sym - начало символа
// zeros - количество незначимых нулей после мантиссы
// order - порядок

// tmp - буферная переменная
// end_sym - конец массива
void round_answer(char *arr, int *first_sym, int *zeros, int *order)
{
    int tmp, end_sym;

    if(*first_sym <= ROUND && (arr[*first_sym + ROUND] - '0') >= 5)
    {
        for (int i_2 = *first_sym + ROUND - 1; i_2 >= *first_sym; i_2--)
        {
            tmp = (arr[i_2] - '0') + 1;
            arr[i_2] = tmp % 10 + '0';

            if (arr[i_2] != '0')
            {
                break;
            }
            else if (i_2 == *first_sym)
            {
                *first_sym -= 1;
                *order += 1;
            }
        }
    }

    if (N_ANS - 1 >= *first_sym + ROUND)
    {
        end_sym = *first_sym + ROUND;
        *zeros = N_ANS - (*first_sym + ROUND);
    }
    else
    {
        end_sym = N_ANS;
        *zeros = 0;
    }

    for (int i_2 = end_sym - 1; i_2 >= 0; i_2--)
    {
        if (arr[i_2] != '0')
        {
            break;
        }
        *zeros += 1;
    }
}

// Функция генерирования конечного ответа
// rc - код возвращения работы программы
// str_ans - массив для округления
// str_prev - массив из чисел мантиссы
// order - порядок
// minus - отрицательность числа
// n - длина числа
// first_sym - начало символа
// zeros - количество незначимых нулей после мантиссы
int generate_answer(char *str_ans, char *str_prev, int order,
    int minus, int *n, int first_sym, int zeros)
{
    int rc = OK;
    int end_sym, order_reverse = 0;
	int was_zero = 0;
    *n = 0;
    if (minus == 1)
        str_ans[*n] = '-';
    else
        str_ans[*n] = '+';
    *n += 1;
    str_ans[*n] = '0';
    *n += 1;
    str_ans[*n] = '.';
    *n += 1;
    if (N_ANS - zeros > first_sym + ROUND)
        end_sym = first_sym + ROUND;
	else
		end_sym = N_ANS - zeros;
    for (int i_2 = first_sym; i_2 < end_sym; i_2++)
    {
        str_ans[*n] = str_prev[i_2];
        *n += 1;
    }
    str_ans[*n] = 'E';
    *n += 1;
    if (order >= 0)
        str_ans[*n] = '+';
    else
        str_ans[*n] = '-';
    *n += 1;
    if (order < MIN_ORDER || order > MAX_ORDER)
        rc = ERR_RANGE_ORDER;
    else
    {
		zeros = 0;
        if (order < 0)
            order *= -1;
		if (order == 0)
			zeros++;
        while (order != 0)
        {
            order_reverse = order_reverse * 10 + order % 10;
			if (order % 10 == 0 && was_zero == 0)
				zeros++;
			else
				was_zero = 1;
            order = order / 10;
        }
        while (order_reverse != 0)
        {
            str_ans[*n] = (order_reverse % 10) + '0';
            order_reverse = order_reverse / 10;
            *n += 1;
        }
		for (int i = 0; i < zeros; i++)
        {
			str_ans[*n] = '0';
			*n += 1;
		}
    }
    return rc;
}

// Функция умножения действительного числа на целое
// rc - код возвращения работы программы
// str_fl - действительное число
// str_int - целое число
// len_fl - длина действительного числа
// len_int - длина целого числа
// str_ans - результат умножения
// order - порядок
// minus - отрицательность числа
// was_zero - был ли ноль
// zeros - количество незначимых нулей после мантиссы
int multiplication (char *str_fl, char *str_int, int len_fl, int len_int,
                    char *str_ans, int *order, int minus, int *n)
{
    int rc = OK;
    int i_prev = N_ANS - 1, tmp, zeros = 0, first_sym;
    char str_prev[N_ANS];
    int was_zero;

    init_array(str_ans, N_FL);
    init_array(str_prev, N_ANS);

    // Умножение чисел
    for (int i = len_int - 1; i >= 0; i--)
    {
        for (int j = len_fl - 1; j >= 0; j--)
        {
            tmp = (str_prev[i_prev] - '0') + (str_fl[j] - '0') * (str_int[i] - '0');
            str_prev[i_prev] = tmp % 10 + '0';
            str_prev[i_prev - 1] = (tmp / 10 + (str_prev[i_prev - 1] - '0')) + '0';
            i_prev--;
        }
        i_prev = N_ANS - len_int + i - 1;
    }
    was_zero = 0;
    for (int i_2 = 0; i_2 < N_ANS; i_2++)
    {
        if (was_zero == 1 || str_prev[i_2] != '0')
        {
            was_zero = 1;
            *order += 1;
        }
    }

    // считаем количество незначимых нулей после мантиссы
    for (int i_2 = N_ANS - 1; i_2 >= 0; i_2--)
    {
        if (str_prev[i_2] != '0')
            break;
        zeros += 1;
    }

    // находим первый значимый символ
    for (int i_2 = 0; i_2 < N_ANS - zeros; i_2++)
        if (str_prev[i_2] != '0')
        {
           first_sym = i_2;
           break;
        }
    round_answer(str_prev, &first_sym, &zeros, order);
    rc = generate_answer(str_ans, str_prev, *order, minus,
        n, first_sym, zeros);
    return rc;
}

// Вывод массива на экран
// str_ans - полученный массив
// n - количество элементов в массиве
void ans_out(FILE *f_out, char *str_ans, int n)
{
    for (int i = 0; i < n; i++)
        fprintf(f_out, "%c", str_ans[i]);
    fprintf(f_out, "\n");
}

// Функция вывода информации об ответе
void ans_text()
{
    printf("Ответ - действительное число: \n");
}

// Функция получения ответа
// rc - код возвращения работы программы
// str_fl - действительное число
// str_int - целое число
// len_fl - длина действительного числа
// len_int - длина целого числа
// str_ans - результат умножения
// order - порядок
// minus - отрицательность числа
// n - количество элементов
int get_ans(char *str_fl, char *str_int, int len_fl, int len_int, char *str_ans, int *order, int minus, int *n)
{
    int rc = OK;
    if (len_fl == 0 || len_int == 0)
    {
        ans_text();
        printf("0");
    }
    else
        rc = multiplication(str_fl, str_int, len_fl, len_int,str_ans, order, minus, n);
    return rc;
}
