//Vertex.h
//
#pragma once

#include "GraphBase.h"
#include "GUIBase.h"

#define INFOTYPE	string

class Vertex
{
public:
	Vertex();
	Vertex(int id);
	Vertex(string s);
	Vertex(int id,string s);
	Vertex(const Vertex& v);
	~Vertex();

	int uniID;
	INFOTYPE info;
	GPoint pos;

	float value;
	float output;
	float bias;
	float sum;
	
	Vertex& operator =(const Vertex& v);
	bool operator ==(const Vertex& v);
};
