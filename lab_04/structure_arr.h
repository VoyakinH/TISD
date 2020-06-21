#ifndef STRUCTURE_ARR_H
	#define STRUCTURE_ARR_H
	#include <stdio.h>
	
	#define SIZE         10
	#define STACK_OVERFLOW  -100
	#define STACK_UNDERFLOW -101
	#define OUT_OF_MEMORY   -102

	typedef struct {
	    char **strings;
	    int top;
	    int size;
	} Stack;

#endif

