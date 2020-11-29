//BallSet.h
//
#pragma once
#include <graphics.h>

#include "Ball.h"
#include "Graph.h"

class BallBase
{
public:
	BallBase();
	BallBase(const Ball& b);
	BallBase(const Ball& b,int uniID);
	BallBase(const BallBase& bb);
	~BallBase();

	Ball ball;
	int uniID;
	BallBase *next;
};

class BallSet
{
public:
	BallSet();
	BallSet(int n);
	BallSet(const BallSet& bs);
	~BallSet();

	void Destory();

	BallBase& at(int i);
	BallBase at(int i) const;
	Ball& operator [](int i);
	Ball operator [](int i) const;
	BallSet& operator +=(const BallBase& b);
	BallSet& operator -=(int l);

	void Load(int n);
	void Load(const BallSet& bs);

	void savepostofile(const Graph& g);

	void lineGraph(const Graph& g);
	void lineBall(int i,int j, const Graph& g, bool arrow=false,WTYPE weight=INF,COLORREF c=BLUE,COLORREF a=RED,COLORREF w=BLUE);
	void drawBall( const Graph& g) const;
	void drawBallEx(int i, const Graph& g) const;

	void randomBall(const Graph& g);
	void randomPos(int i);
	void getBallPos(Graph& g);
	//EasyX版本需要重载arc函数，以使用角度
	void arcex(int x, int y, int stangle, int endangle, int radius) const;
	void conjunctionBall();

	int isin(const Point& p);
	bool isinlimit(const Point& p);
	int isactive();
	void clearactive();

	BallBase* ballset;
	BallBase errAdd;
	Ball errBallAdd;
	int num;
};