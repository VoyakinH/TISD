#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "structs.h"

automat* init_auto()
{
    automat *my_auto = malloc(sizeof(automat));
    if (my_auto == NULL)
    {
        return NULL;
    }
    else
        {
        my_auto->now = -1;
        my_auto->work_time = 0;
        my_auto->left1 = 0;
        my_auto->downtime = 0;
        my_auto->work = 0;
        my_auto->diferent_elems = 0;
        return my_auto;
    }
}

automat_list *init_auto_list()
{
    automat_list *my_auto = malloc(sizeof(automat_list));
    if (my_auto == NULL)
    {
        return NULL;
    }
    else
    {
        my_auto->now = NULL;
        my_auto->work_time = 0;
        my_auto->left1 = 0;
        my_auto->downtime = 0;
        my_auto->work = 0;
        my_auto->diferent_elems = 0;
        return my_auto;
    }
}

