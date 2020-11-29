//Queue.cpp
//
#pragma once

#include "GraphBase.h"

#define MAX_Q_SIZE 10
#define QElmType int

class Queue
{
public:
	Queue(int m=100);
	~Queue();

	void EnQueue(QElmType e);
	QElmType DeQueue();
	void DeQueue(QElmType& e);
	bool EmptyQ();

	QElmType *base;
	int font;
	int rear;
	int num;
};
