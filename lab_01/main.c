/*
 Смоделировать операцию умножения целого числа длиной до 30 десятичных цифр
 на действительное число в форме +-m.n Е +-K, где суммарная длина мантиссы (m+n) - до 30
 значащих цифр, а величина порядка K - до 5 цифр.
 Результат выдать в форме +-0.m1 Е +-K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.
*/

#include <stdio.h>
#include "defines.h"
#include "functions.h"


int main()
{
    int rc = EMPTY;
    int len_fl, len_int;
    int minus = 0;
    int order = 0;
    int n;
    
    char str_fl[MANT], str_int[N_INT], str_ans[N_ANS];
    
    printf("Программа умножает целое число длиной до 30 десятичных цифр на \n"
           "действительное число, где суммарная длина мантиссы до 30 значащих \n"
           "цифр, а величина порядка до 5 цифр. \n");
    while (rc != OK)
    {
        printf("\n      Введите целое число:\n"
               "|                              |\n ");
        rc = int_input(stdin, str_int, &len_int, &minus);
        if (rc == ERR_INP)
            printf("Неверный ввод.");
        else if (rc == ERR_RANGE_INT)
            printf("Максимальная длина целого числа превышена");
    }
    
    printf("Введите действительное число с порядком \n"
           "Диапазон порядка [-99999, 99999]");
    rc = EMPTY;
    while (rc != OK)
    {
        printf("\nВведите действительное число: \n"
               "|           Мантисса           |По-ок|\n ");
        rc = float_input(stdin, str_fl, &len_fl, &minus, &order);
        if (rc == ERR_INP)
            printf("Неверный формат ввода.");
        else if (rc ==  ERR_RANGE_MANT)
            printf("Максимальная длина мантиссы = 30 цифр.");
        else if (rc == ERR_RANGE_ORDER)
            printf("Диапазон порядка [-99999, 99999].");
        else if (rc == ERR_NO_DATA)
            printf("Не найдена мантисса.");
    }
    
    rc = get_ans(str_fl, str_int, len_fl, len_int, str_ans, &order, minus, &n);
    if (rc == OK)
    {
        ans_text();
        ans_out(stdout, str_ans, n);
    }
    else
        printf("Рассчёт невозможен.\n");
    return rc;
}
