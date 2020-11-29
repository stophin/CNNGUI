//Graph.h
//
#pragma once

#include "GraphBase.h"
#include "VNode.h"
#include "Queue.h"
#include "Stack.h"

#define INF 999999.0

#define GHREADY		0x0000
#define GHDFS		0x0001
#define GHPRIM		0x0002
#define GHHAMILTON	0x0004



#include "../NN/Network.h"
class Graph
{
public:
	Graph();
	Graph(int num,bool random=false,bool dg=false,bool selfring=false,int degree=0);
	Graph(string fname);
	Graph(const Graph& g,bool reverse=false,bool remainweight=false);
	~Graph();

	void Destory(bool all=true);
	void CreateArrays();
	void Load(const Graph& g,bool reverse=false,bool remainweight=false);
	void Load(int num,bool random=false,bool dg=false,bool selfring=false,int degree=0);
	void Load(string fname);
	void Load(Network * n);
	void Update(Network * n);

	VNode& operator [](int i);
	VNode& operator [](int i) const;
	Graph& operator +=(const Vertex& v);
	Graph& AddPoint(const Vertex& v,int& ret);
	Graph& operator -=(const Vertex& v);
	Graph& operator -=(int uid);

	VNode* vnode;

	bool isDG;
	bool withWeight;
	bool withPos;
	string filename;

	int V;	
	int* iary;
	int* iary2;
	int** itary;
	string** stary;
	int index;

	int last;

	VNode errAdd;
	string lastErr;
	bool isLoaded;

	int FirstAdj(int v);
	int NextAdj(int v);
	int DirectAdj(int v,int w) const;
	int DirectAdjUniID(int v,int w) const;
	ArcNode* Graph::Arc(int v, int w) const;
	int VInDeg(int v);
	WTYPE Weight(int v,int w,bool equal=false) const;
	WTYPE WeightUniID(int v,int w,bool equal=false) const;


	void GRemove(int v,int w);
	void Remove(int v,int w);

	//深度优先搜索
	void DFS(int mode=1);
	void dfsR(int v,int& num);
	void dfsR(int ev,int ew,int& num);
	void dfsR(int ev,int ew,int& num,int& cntp);

	//哈密顿路径
	bool PathH(int v,int w);
	bool pathHR(int v,int w,int d);

	//Prim算法构造MST
	void Prim();

	//基于源点队列的拓扑排序
	bool SQTopoSort();
	
};