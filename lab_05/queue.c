#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structs.h"

queue_t* new_queue(int max_size)
{
    queue_t* queue = malloc(sizeof(queue_t));
    if (queue)
    {
        float* data_store = malloc(sizeof(float) * max_size);
        if (data_store)
        {
            queue->data_store = data_store;
            queue->front = 0;
            queue->max_size = max_size;
            queue->num_of_elems = 0;
            queue->summ_of_elems = 0;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }

    return queue;
}

int add_elem(queue_t *queue, float item)
{
    if (queue->num_of_elems >= queue->max_size || queue->num_of_elems >= ELEM)
    {
        return FAIL;
    }

    queue->data_store[queue->front] = item;

    queue->front++;
    queue->num_of_elems++;
    queue->summ_of_elems++;

    return SUCCESS;
}

float delete_elem(queue_t *queue)
{
    if (queue->num_of_elems < 1)
    {
        return FAIL;
    }

    float result = queue->data_store[0], buf;

    queue->num_of_elems--;
    queue->front--;

    for (int i = 0; i < queue->front; i++)
    {
        buf = queue->data_store[i + 1];
        queue->data_store[i] = buf;
        queue->data_store[i + 1] = 0;
    }
    return result;
}

void queue_free(queue_t* queue)
{
    free(queue->data_store);
    free(queue);
}


void queue_print(queue_t* q)
{
    for (int i = 0; i < q->front; i++)
    {
        printf("%d   %f  \n", i,  q->data_store[i]);
    }
}


node_t *get_new_node_list(float time)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return new_node;
    }
    new_node->time = time;
    new_node->next = NULL;
    return new_node;
}

queue_t_list *init_queue_list()
{
    queue_t_list *new_node = (queue_t_list *)malloc(sizeof(queue_t_list));
    if (NULL == new_node)
    {
        return new_node;
    }
    new_node->pin = new_node->pout = NULL;
    new_node->num_of_elems = 0;
    new_node->summ_of_elems = 0;
    return new_node;
}

int add_elem_list(queue_t_list *queue, float time)
{
    if (queue == NULL)
    {
        return FAIL;
    }

    node_t *new_node = get_new_node_list(time);
    if (new_node == NULL)
    {
        return FAIL;
    }
    if (queue->pin == NULL)
    {
        queue->pout =  new_node;
        queue->pin = new_node;
        queue->num_of_elems++;
        queue->summ_of_elems++;
        return SUCCESS;
    }
    queue->pout->next = new_node;
    queue->pout = new_node;
    queue->num_of_elems++;
    queue->summ_of_elems++;

    return SUCCESS;
}

float delete_elem_list(queue_t_list *queueptr)
{

    if (queueptr == NULL || queueptr->pin == NULL)
    {
        return FAIL;
    }
    node_t *temp = queueptr->pin;
    float time = temp->time;
    queueptr->pin = temp->next;
    free(temp);
    queueptr->num_of_elems--;
    return time;
}

void print_queue_list(queue_t_list *queueptr)
{
    node_t *temp = queueptr->pin;
    while (temp != NULL)
    {
        printf("%g \t", temp->time);
        temp=temp->next;
    }
}

void free_queue_list(queue_t_list *queueptr)
{
    queue_t_list *temp;
    for (; queueptr; queueptr = temp)
    {
        temp = queueptr;
        free(queueptr);
    }
}
