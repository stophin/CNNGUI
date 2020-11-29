//Queue.cpp
//
#include "Queue.h"

Queue::Queue(int m):
base(NULL),
font(0),
rear(0),
num(0)
{
	if (m<0)
		return;
	base=(QElmType*)malloc(m*sizeof(QElmType));
	num=m;
}

Queue::~Queue()
{
	if (base)
		free(base);
	base=NULL;
}

void Queue::EnQueue(QElmType e)
{
	if ((rear+1)%num==font)
		return;
	base[rear]=e;
	rear=(rear+1)%num;
	return;
}

QElmType Queue::DeQueue()
{
	if (font==rear)
		return 0;
	QElmType e=base[font];
	font=(font+1)%num;
	return e;
}

void Queue::DeQueue(QElmType& e)
{
	if (font==rear)
		return;
	e=base[font];
	font=(font+1)%num;
	return;
}

bool Queue::EmptyQ()
{
	if ((rear-font+num)%num)
		return false;
	return true;
}