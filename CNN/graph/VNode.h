//VNode.h
//
#pragma once

#include "GraphBase.h"
#include "Vertex.h"

#define WTYPE	float

class Edge
{
public:
	Edge():w(),weight(0){};
	Edge(const Vertex& v):w(v),weight(0){};
	Edge(const Vertex& v,WTYPE w):w(v),weight(w){};
	Edge(int unid,INFOTYPE info,WTYPE w=0):w(unid,info),weight(w){};
	Edge(const Edge& eg):w(eg.w),weight(eg.weight){};
	~Edge(){};

	Vertex w;
	WTYPE weight;

	WTYPE delta;
};

class ArcNode
{
public:
	ArcNode():edge(),next(NULL){};
	ArcNode(const Vertex& v):edge(v),next(NULL){};
	ArcNode(const Vertex& v,WTYPE w):edge(v,w),next(NULL){};
	ArcNode(const Edge& eg):edge(eg),next(NULL){};
	~ArcNode(){};

	Edge edge;
	ArcNode *next;
};

class VNode
{
public:
	VNode();
	VNode(const Vertex& v);
	VNode(int unid,INFOTYPE info,WTYPE w=0);
	~VNode();

	VNode& operator +=(const Vertex& av);
	VNode& operator +=(const Edge& av);
	VNode& operator -=(int l);
	ArcNode& operator [](int i);

	Vertex v;
	int vnum;
	ArcNode* adj;
	VNode* next;
	ArcNode errAdd;
};