#ifndef STRUCTURE_LIST_H
	#define STRUCTURE_LIST_H
	#include <stdio.h>
	
	#define SIZE             10
	#define STACK_OVERFLOW  -100
	#define STACK_UNDERFLOW -101
	#define OUT_OF_MEMORY   -102


	typedef struct node node_t;
	struct node
	{
		char *data;
		node_t *next;
	};


#endif

