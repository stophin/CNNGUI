//Vertex.cpp
//
#include "Vertex.h"

Vertex::Vertex():
info(""),
uniID(0),
pos()
{
}

Vertex::Vertex(int id):
info(""),
uniID(id),
pos()
{
}

Vertex::Vertex(string s):
info(s),
uniID(0),
pos()
{
}

Vertex::Vertex(int id,string s):
info(s),
uniID(id),
pos()
{
}

Vertex::Vertex(const Vertex& v):
info(v.info),
uniID(v.uniID),
pos(v.pos)
{
}

Vertex::~Vertex()
{
}

Vertex& Vertex::operator =(const Vertex& v)
{
	if (&v==this)
		return *this;
	this->info=v.info;
	this->uniID=v.uniID;
	return *this;
}

bool Vertex::operator ==(const Vertex& v)
{
	if (v.uniID==uniID)
		return true;
	return false;
}
