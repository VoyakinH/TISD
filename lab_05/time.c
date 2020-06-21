#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structs.h"
#include "func.h"

static float time_now = 0;
static alarm_t al1;
static alarm_t al2;

float get_time(queue_t *q1, automat *a)
{
    if(!al1.time && !al2.time)
    {
        al1.time = randfrom(T1_MIN, T1_MAX);
        time_now = al1.time;
        if (add_elem(q1, randfrom(T1_MIN, T1_MAX)) != 0)
        {
            printf("Переполнение! Измените параметр ELEM (размер массива)\n");
            return 0;
        }
        //a->left1++;
        a->now = q1->data_store[0];
        a->work_time = randfrom(T2_MIN, T2_MAX);
        al1.time = time_now + q1->data_store[0];
        al2.time = time_now + a->work_time;
    }
    else
        {
        if(al1.time <= al2.time)
        {
            time_now = al1.time;
            if (add_elem(q1, randfrom(T1_MIN, T1_MAX)) != 0)
            {
                printf("Переполнение! Измените параметр ELEM (размер массива)\n");
                return 0;
            }
            al1.time += q1->data_store[q1->front-1];
        }
        if(al2.time <= al1.time)
        {
            float chance = randfrom(CHANCE_MIN, CHANCE_MAX);
            //printf("%f", chance);
            if (chance <= 80 && q1->num_of_elems > 0)
            {
                float buff = q1->data_store[q1->front-1];
                if (q1->num_of_elems > 2)
                    q1->data_store[q1->front-1] = 0;
                if (add_elem(q1, buff) != 0)
                {
                    printf("Переполнение! Измените параметр ELEM (размер массива)\n");
                    return 0;
                }
                a->now = q1->data_store[0];
            }
            if (chance > 80 && q1->num_of_elems > 0)
                a->diferent_elems++;
            refresh_automat(q1, a);
            time_now = al2.time;
            al2.time += a->work_time;
        }
    }
//    printf("STATISTIC:\n"
//       "Automat:\n"
//       "count q1 : %d\n"
//       "a->work time %f\n\n", a->left1, a->work_time);
//        printf("al1 %f\n"
//           "al2 %f\n\n", al1.time, al2.time);
//    queue_print(q1);
//    printf("------\n");

    return time_now;

}

float get_time_list(queue_t_list *q1, automat_list *a)
{
    if(!al1.time && !al2.time)
    {
        al1.time = randfrom(T1_MIN, T1_MAX);
        time_now = al1.time;
        add_elem_list(q1, randfrom(T1_MIN, T1_MAX));
        a->now = q1->pin;
        a->work_time = randfrom(T2_MIN, T2_MAX);
        al1.time = time_now + q1->pin->time;
        al2.time = time_now + a->work_time;
    }
    else
        {
        if(al1.time <= al2.time)
        {
            time_now = al1.time;
            add_elem_list(q1, randfrom(T1_MIN, T1_MAX));
            al1.time += q1->pout->time;
        }
        if(al2.time <= al1.time)
        {
            float chance = randfrom(CHANCE_MIN, CHANCE_MAX);
            if (chance <= 80 && q1->num_of_elems > 0)
            {
                float buff = q1->pout->time;
                if (q1->num_of_elems > 2)
                    q1->pout->time = 0;
                add_elem_list(q1, buff);
                a->now = q1->pin;
            }
            if (chance > 80 && q1->num_of_elems > 0)
                a->diferent_elems++;
            refresh_automat_list(q1, a);
            time_now = al2.time;
            al2.time += a->work_time;
        }
    }
//    printf("STATISTIC:\n"
//       "Automat:\n"
//       "count q1 : %d\n"
//       "a->work time %f\n\n", a->left1, a->work_time);
//        printf("al1 %f\n"
//           "al2 %f\n\n", al1.time, al2.time);
//    queue_print(q1);
//    printf("------\n");

    return time_now;

}
