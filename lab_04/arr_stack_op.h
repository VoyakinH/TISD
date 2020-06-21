#ifndef ARR_STACK_OP_H
	#define ARR_STACK_OP_H
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "structure_arr.h"

	Stack *init();
	void print(Stack *stack);
	void destroy(Stack **stack);
	void push(Stack *stack, char *new_string);
	char *pop(Stack *stack);
	void print_back(Stack *stack);
	void clear_arr(Stack *stack);

#endif

