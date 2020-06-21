#ifndef LIST_STACK_OP_H
	#define LIST_STACK_OP_H
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "structure_list.h"

	void push_l(node_t** head, char *new_data);
	node_t *pop_front(node_t **head);
	void print_stack_l(node_t *head);
	void freeList(node_t** head);
	node_t* print_back_list(node_t *head);
	node_t* reverse(node_t* head);
	int count(node_t *head);
	void print_addresses(node_t *head);
	node_t** delete_from_list(node_t *head, node_t **point);
	void push_l_test(node_t** head, char *new_data);
	node_t* pop_test(node_t **head);
#endif

