#include <stdio.h>
#include "func.h"
#include "structs.h"
#include "constants.h"

void refresh_automat(queue_t *q1, automat *a)
{
    if (a->now != -1)
    {
        delete_elem(q1);
        a->now = -1;
        if (q1->num_of_elems > 0)
            a->now = q1->data_store[0];
        a->left1++;
        a->work_time = randfrom(T2_MIN, T2_MAX);
        a->work += a->work_time;
    }
    else
    {
        if (q1->num_of_elems == 0)
        {
            a->downtime += a->work_time;
            return;
        }
        else
        {
            a->now = q1->data_store[0];
            a->work_time = randfrom(T2_MIN, T2_MAX);
            a->work += a->work_time;
        }
    }
    return;
}

void refresh_automat_list(queue_t_list *q1, automat_list *a)
{
    if (a->now)
    {
        delete_elem_list(q1);
        a->now = NULL;
        if (q1->num_of_elems > 0)
            a->now = q1->pin;
        a->left1++;
        a->work_time = randfrom(T2_MIN, T2_MAX);
        a->work += a->work_time;
    }
    else
    {
        if (q1->num_of_elems == 0)
        {
            a->downtime += a->work_time;
            return;
        }
        else
        {
            a->now = q1->pin;
            a->work_time = randfrom(T2_MIN, T2_MAX);
            a->work += a->work_time;
        }
    }
    return;
}
