#ifndef FUNC_H
#define FUNC_H
#include "structs.h"

void refresh_automat(queue_t *q1, automat *a);
automat* init_auto(void);
float randfrom(int min, int max);
queue_t *new_queue(int max_size);
int add_elem(queue_t *queue, float item);
void queue_free(queue_t* queue);
float delete_elem(queue_t *queue);
void queue_print(queue_t* q);
float get_time(queue_t *q1, automat *a);

automat_list *init_auto_list(void);
node_t *get_new_node_list(float time);
queue_t_list *init_queue_list(void);
int add_elem_list(queue_t_list *queue, float time);
float delete_elem_list(queue_t_list *queueptr);
void print_queue_list(queue_t_list *queueptr);
void free_queue_list(queue_t_list *queueptr);
float get_time_list(queue_t_list *q1, automat_list *a);
void refresh_automat_list(queue_t_list *q1, automat_list *a);


#endif // FUNC_H

