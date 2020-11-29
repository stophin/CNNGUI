//Stack.cpp
//
#include "Stack.h"

Stack::Stack(int m):
num(0),
max(m),
stack(NULL)
{
    stack=(PSTACK)malloc(sizeof(STACK));
    stack->item='#';
	stack->next=NULL;
}

Stack::~Stack()
{
	freelink(stack);
}

void Stack::freelink(STACK *ph)
{
    STACK *p=ph;
	STACK *q;
	while(NULL!=p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	ph=NULL;
	return;
}

bool Stack::push(STACKTYPE elm)
{
	if (isFull())
		return false;
	PSTACK newstack=(PSTACK)malloc(sizeof(STACK));
	if (!newstack)
		return false;
	newstack->item=elm;
	newstack->next=stack->next;
	stack->next=newstack;
	num++;
	return true;
}

bool Stack::pop(STACKTYPE &eou)
{
	if (isEmpty())
		return false;
	eou=stack->next->item;
	PSTACK t=stack->next;
	stack->next=t->next;
	free(t);
	num--;
	return true;
}

STACKTYPE Stack::pop()
{
	STACKTYPE elm;
	if (pop(elm))
		return elm;
	return 0;
}

bool Stack::peek(STACKTYPE &eou)
{
	if (isEmpty())
		return false;
	eou=stack->next->item;
	return true;
}

STACKTYPE Stack::peek()
{
	STACKTYPE elm;
	if (peek(elm))
		return elm;
	return 0;
}

bool Stack::isEmpty()
{
	if (0>=num)
		return true;
	return false;
}
bool Stack::isFull()
{
	if (max<=num)
		return true;
	return false;
}


