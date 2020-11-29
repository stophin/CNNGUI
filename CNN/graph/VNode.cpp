//VNode.cpp
//
#include "VNode.h"

VNode::VNode():
v(),
vnum(0),
adj(NULL),
next(NULL),
errAdd()
{
}

VNode::VNode(const Vertex& v):
v(v),
vnum(0),
adj(NULL),
next(NULL),
errAdd()
{
}

VNode::VNode(int unid,INFOTYPE info,WTYPE w):
v(unid,info),
vnum(0),
adj(NULL),
next(NULL),
errAdd()
{
}


VNode::~VNode()
{
	ArcNode* p;
	ArcNode* node;
	for (node=adj;node!=NULL;)
	{
		p=node;
		node=node->next;
		delete p;
	}
	adj=NULL;
	for (node=errAdd.next;node!=NULL;)
	{
		p=node;
		node=node->next;
		delete p;
	}
	errAdd.next=NULL;
}

VNode& VNode::operator +=(const Vertex& av)
{
	ArcNode* newnode=new ArcNode(av);
	
	if (adj)
	{
		ArcNode *t,*p;
		t=adj;
		for (p=adj;p!=NULL;p=p->next)
		{
			if (p->edge.w==av)
				break;
			if (p!=t)
				t=t->next;
		}
		if (p!=NULL)
		{
			delete newnode;
			return *this;
		}
		t->next=newnode;
	}
	else
		adj=newnode;
	vnum++;
	return *this;
}

VNode& VNode::operator +=(const Edge& eg)
{
	ArcNode* newnode=new ArcNode(eg);
	
	if (adj)
	{
		ArcNode *t,*p;
		t=adj;
		for (p=adj;p!=NULL;p=p->next)
		{
			if (p->edge.w==eg.w)
				break;
			if (p!=t)
				t=t->next;
		}
		if (p!=NULL)
		{
			delete newnode;
			return *this;
		}
		t->next=newnode;
	}
	else
		adj=newnode;
	vnum++;
	return *this;
}

VNode& VNode::operator -=(int l)
{
	if (vnum)
	{
		ArcNode* t=NULL;
		if (l)
		{
			t=&(*this)[l];
			(*this)[l-1].next=t->next;
		}
		else
		{
			t=adj;
			adj=t->next;
		}
		delete t;
		vnum--;
	}
	return *this;
}

ArcNode& VNode::operator [](int i)
{
	if (i<0)
		return errAdd;
	ArcNode* t;
	for (t=adj;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return *t;
	return errAdd;
}
