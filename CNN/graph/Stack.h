//Stack.h
//
#pragma once

#include <stdlib.h>

#define STACKTYPE int

struct stack
{
	STACKTYPE item;
	struct stack *next;
};
typedef struct stack STACK;
typedef struct stack * PSTACK;

class Stack
{
public:	
	Stack(int m=100);
	~Stack();

	PSTACK stack;
	int max;
	int num;

	bool push(STACKTYPE elm);
	bool pop(STACKTYPE &eou);
	STACKTYPE pop();
	bool peek(STACKTYPE &eou);
	STACKTYPE peek();
	bool isEmpty();
	bool isFull();
	void freelink(STACK *ph);
};