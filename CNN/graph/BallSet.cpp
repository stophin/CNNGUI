//BaseSet.cpp
//
#include "BallSet.h"

BallBase::BallBase():
ball(),
next(NULL),
uniID(0)
{
}

BallBase::BallBase(const Ball& b):
ball(b),
next(NULL),
uniID(0)
{
}

BallBase::BallBase(const Ball& b,int uniID):
ball(b),
next(NULL),
uniID(uniID)
{
}

BallBase::BallBase(const BallBase& bb):
ball(bb.ball),
next(NULL),
uniID(bb.uniID)
{
}

BallBase::~BallBase()
{
}

BallSet::BallSet():
ballset(NULL),
num(0),
errAdd()
{
}

BallSet::BallSet(int n):
ballset(NULL),
num(0),
errAdd()
{
	Load(n);
}

BallSet::BallSet(const BallSet& bs):
ballset(NULL),
num(0),
errAdd()
{
	Load(bs);
}

BallSet::~BallSet()
{
	Destory();
}

void BallSet::Load(int n)
{
	for (int i=0;i<n;i++)
	{
		BallBase* ball=new BallBase();
		ball->ball.order=i;
		if (ballset==NULL)
			ballset=ball;
		else
			(*this).at(num-1).next=ball;
		num++;
	}
}

void BallSet::Load(const BallSet& bs)
{
	for (int i=0;i<bs.num;i++)
	{
		BallBase* ball=new BallBase(bs[i]);
		ball->ball.order=i;
		ball->uniID=bs.at(i).uniID;
		if (ballset==NULL)
			ballset=ball;
		else
			(*this).at(num-1).next=ball;
		num++;
	}
}

void BallSet::Destory()
{
	BallBase* p=NULL;
	BallBase* t;
	for (t=ballset;t!=NULL;)
	{
		p=t;
		t=t->next;
		delete p;
	}
	ballset=NULL;
	for (t=errAdd.next;t!=NULL;)
	{
		p=t;
		t=t->next;
		delete p;
	}
	errAdd.next=NULL;
	num=0;
}

BallBase BallSet::at(int i) const
{
	BallBase b;
	if (i<0)
		return b;
	BallBase* t;
	for (t=ballset;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return *t;
	return b;
}

BallBase& BallSet::at(int i)
{
	if (i<0)
		return errAdd;
	BallBase* t;
	for (t=ballset;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return *t;
	return errAdd;
}

Ball& BallSet::operator [](int i)
{
	if (i<0)
		return errBallAdd;
	BallBase* t;
	for (t=ballset;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return t->ball;
	return errBallAdd;
}

Ball BallSet::operator [](int i) const
{
	Ball ball;
	if (i<0)
		return ball;
	BallBase* t;
	for (t=ballset;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return t->ball;
	return ball;
}

BallSet& BallSet::operator +=(const BallBase& bs)
{
	BallBase* ball=new BallBase(bs);
	if (ballset==NULL)
		ballset=ball;
	else
	{
		(*this).at(num-1).next=ball;
	}
	num++;
	return *this;
}

BallSet& BallSet::operator -=(int l)
{
	if (num)
	{
		BallBase* b=NULL;
		if (l)
		{
			int i=l;
			for (b=ballset;b!=NULL&&i>0;i--,b=b->next);
			if (b==NULL)
				return (*this);
			i=l-1;
			BallBase* t=NULL;
			for (t=ballset;t!=NULL&&i>0;i--,t=t->next);
			t->next=b->next;
		}
		else
		{
			b=ballset;
			ballset=b->next;
		}
		delete b;
		num--;
	}
	return *this;
}

void BallSet::lineBall(int i,int j,const Graph& g,bool arrow,WTYPE weight,COLORREF c,COLORREF a,COLORREF w)
{
	COLORREF oldcolor;
	oldcolor=getcolor();

	Ball b1=(*this)[i];
	Ball b2=(*this)[j];

	setcolor(c);
	
	int d=b1.getDistance(b2);
	Point th(b1.getPos());
	Point td(b2.getPos());
	th-=b2.getPos();
	Point mid(th);
	mid/=d;
	mid*=(d/2);
	mid+=b2.getPos();
	td-=b1.getPos();
	th/=d;
	td/=d;
	th*=b1.getRadius();
	td*=b2.getRadius();
	th+=b2.getPos();
	td+=b1.getPos();
	line(th.getX(),th.getY(),td.getX(),td.getY());
	
	if (arrow)
	{
		if (weight != INF)
		{
			PHXTYPE x1 = td.getX();
			PHXTYPE y1 = td.getY();
			PHXTYPE x2 = th.getX();
			PHXTYPE y2 = th.getY();
			PHXTYPE mode = -(abs(y2 - y1) - abs(x2 - x1));
			PHXTYPE mode1 = (mode > 0 ? x2 - x1 : y2 - y1);
			PHXTYPE a1 = (mode > 0 ? x1 : y1);
			PHXTYPE b1 = (mode > 0 ? y1 : x1);
			PHXTYPE d1 = (mode > 0 ? (x2 - x1) / 2.0 : (y2 - y1) / 2.0);
			PHXTYPE k1 = (mode > 0 ? ((y2 - y1) / (x2 - x1)) : ((x2 - x1) / (y2 - y1)));
			PHXTYPE p1 = (mode1 >= 0 ? 1.0 : -1.0);
			PHXTYPE p2 = x2 - x1;
			//setcolor(w);
			setcolor(BROWN);
			char c[100];
			int r = sprintf(c, "%.5e", weight);
			//outtextxy(mid.getX(),mid.getY(),c);
			for (int i = 0; i < r; i++) {
				//edit this param to change weight show position
				PHXTYPE x = a1 + p1 * i * 8 + p1 * 30;
				//PHXTYPE x = a1 + p1 * i * 10   +d1;
				PHXTYPE y = k1 * (x - a1) + b1;
				if (mode < 0) {
					PHXTYPE t = x;
					x = y;
					y = t;
				}
				int ii = i;
				if (p2 < 0) {
					ii = r - (i + 1);
				}

				outtextxy(x, y, c[ii]);
			}
			setcolor(LIGHTGRAY);
			r = sprintf(c, "%.5e", g.Arc(i,j)->edge.delta);
			//outtextxy(mid.getX(),mid.getY(),c);
			for (int i = 0; i < r; i++) {
				//edit this param to change weight show position
				//PHXTYPE x = a1 + p1 * i * 10 + p1 * 10;
				PHXTYPE x = a1 + p1 * i * 8 +d1;
				PHXTYPE y = k1 * (x - a1) + b1;
				if (mode < 0) {
					PHXTYPE t = x;
					x = y;
					y = t;
				}
				int ii = i;
				if (p2 < 0) {
					ii = r - (i + 1);
				}

				outtextxy(x, y, c[ii]);
			}
		}
		setcolor(a);
		Point arrow(td);
		arrow-=th;
		arrow/=arrow.getVal();
		arrow*=10.0;
		td=arrow;
		td.rotate(-12);
		td+=th;
		line(th.getX(),th.getY(),td.getX(),td.getY());
		td=arrow;
		td.rotate(12);
		td+=th;
		line(th.getX(),th.getY(),td.getX(),td.getY());
	}
	
	//设置回原来的颜色
	setcolor(oldcolor);
}

void BallSet::lineGraph(const Graph& g)
{
	LINESTYLE linestyle;
	getlinestyle(&linestyle);
	
	BallSet ball=(*this);
	COLORREF c=BLUE;
	COLORREF color;
	for (int i=0;i<g.V;i++)
	{
		for (int j=0;j<g.V;j++)
		{
			if (g.DirectAdjUniID(i,j)==1)
			{
				if (g.isDG&&(ball[i].active||(g.DirectAdjUniID(j,i)==1&&ball[j].active)))
					color=RED;
				else if (!g.isDG&&((ball[i].active)||(ball[j].active&&g.DirectAdjUniID(i,j)==1)))
					color=RED;
				else
					color=c++;
				if (g.last&GHPRIM)
				{
					if (g.iary2[i]==j||g.iary2[j]==i)
					{
						setlinestyle(0,3);
						color=RED;
					}
					else
					{
						setlinestyle(&linestyle);
					}
				}
				else if (g.last&GHHAMILTON)
				{
					int k;
					for (k=0;k<g.V-1;k++)
						if (g.iary2[k]==i)
							break;
					if (g.iary2[k]==i&&g.iary2[k+1]==j)
					{
						setlinestyle(0,3);
						color=RED;
					}
					else
					{
						setlinestyle(&linestyle);
					}
				}
				lineBall(i,j,g, g.isDG,g.withWeight?g.WeightUniID(i,j):INF,color,RED,BLACK);
			}
		}
	}

	setlinestyle(&linestyle);
}

void BallSet::drawBall(const Graph& g) const
{
	for (int i=0;i<num;i++)
	{
		drawBallEx(i, g);
	}
}

//EasyX版本需要重载arc函数，以使用角度
void BallSet::arcex(int x, int y, int stangle, int endangle, int radius) const
{
	arc(x-radius, y-radius,x+radius, y+radius,stangle/180.0*PI,endangle/180.0*PI);
}

void BallSet::randomBall(const Graph& g)
{
	for (int i=0;i<num;i++)
	{
		randomPos(i);
		this->at(i).uniID=g[i].v.uniID;
	}
}

void BallSet::randomPos(int i)
{
	Ball *newBall=&(*this)[i];
	BallSet ball=(*this);

	//设置随机球的属性，如果不设置，则属性为默认构造属性
	newBall->setLimit(SCRWD-200,SCRHT);
	newBall->setRadius(BALLRADIUS);

	int r=newBall->getRadius(),limx=newBall->getLimitX(),limy=newBall->getLimitY();
	Point coord;
	coord=newBall->getLimitLt();
	
	//在已存在的球体数组中，遍历，如果该球体坐标不在任何一个球的范围内，那么这就是新建的球体的坐标
	do
	{
		//球的位置可取范围为:x轴:半径~x限制-半径，y轴:半径~y限制-半径
		newBall->setPos(rand()%(limx-2*r)+r,rand()%(limy-2*r)+r);
		int i;
		for (i=0;i<num;i++)
		{
			if (newBall->getDistance(ball[i])<=ball[i].getMinDistance(*newBall))
				break;
		}
		if (i==num)
			break;
	}while(num);
	
	coord+=newBall->getPos();
	newBall->setPos(coord.getX(),coord.getY());
}

void BallSet::getBallPos(Graph& g)
{
	if (g.withPos)
	{
		for (int i = 0; i < num; i++)
		{
			//设置随机球的属性，如果不设置，则属性为默认构造属性
			(*this)[i].setLimit(SCRWD - 200, SCRHT);
			(*this)[i].setRadius(BALLRADIUS);
			(*this)[i].setPos(g[i].v.pos.x, g[i].v.pos.y);
			this->at(i).uniID = g[i].v.uniID;
		}
	}
	else
	{
		randomBall(g);
		for (int i = 0; i < num; i++)
		{
			g[i].v.pos.x = (*this)[i].getPosX();
			g[i].v.pos.y = (*this)[i].getPosY();
		}
	}
}

//使用外部库(EasyX库或者EGE库)的arc(或其重载)函数来绘制球
void BallSet::drawBallEx(int i, const Graph& g) const
{
	Ball ball=(*this)[i];
	FILLSTYLE oldfill;
	COLORREF oldcolor;
	getfillstyle(&oldfill);
	oldcolor=getcolor();
	//setfillstyle(BALLCOLOR);

	int r,x,y;
	//获得球的参数
	r=(int)ball.getRadius();
	x=(int)ball.getPosX();
	y=(int)ball.getPosY();
	/*
	//绘制球体
	setcolor(BALLCOLOR);
	fillcircle(x,y,r);
	//填充球体颜色
//	floodfill(x,y,BALLCOLOR);
	//绘制球体阴影
	setcolor(BLACK);
	int j;
	for (j=0;j<3;j++)
	{
		arcex(x,y,-135+10*j,-10*j,r+j);
	}
	//绘制球体背光面深色
	setcolor(SHADOWCOLOR);
	for (j=0;j<10;j++)
	{
		arcex(x,y,-150+10*j,40-4*j,r-j);
	}
	*/
	setbkmode(TRANSPARENT);
	setcolor(TEXTCOLOR);
	char c[100];
	sprintf(c, "%d", this->at(i).uniID);
	outtextxy(x, y, c);
	setcolor(RED);
	sprintf(c,"%d",ball.order);
	outtextxy(x-ball.getRadius()/2.0,y-ball.getRadius()/2.0,c);
	sprintf(c, "%.5e", g[i].v.bias);
	setcolor(BLUE);
	outtextxy(x - ball.getRadius(), y + ball.getRadius(), c);
	sprintf(c, "%.5e", g[i].v.sum);
	setcolor(GREEN);
	outtextxy(x - ball.getRadius(), y + ball.getRadius() + 10, c);
	sprintf(c, "%.5f", g[i].v.output);
	setcolor(LIGHTRED);
	outtextxy(x - ball.getRadius() - 10, y + ball.getRadius() + 20, c);
	if (g[i].v.value != g[i].v.uniID) {
		sprintf(c, "%.5f", g[i].v.value);
		setcolor(LIGHTRED);
		outtextxy(x - ball.getRadius() - 10, y + ball.getRadius() + 30, c);
	}
	if (ball.active)
	{
		setcolor(RED);
		circle(x,y,r);
	}
	else {
		setcolor(LIGHTBLUE);
		circle(x,y,r);
	}

	//设置回原来的颜色
	setcolor(oldcolor);
	setfillstyle(&oldfill);
	return;
}

int BallSet::isin(const Point& p)
{
	int i;
	for (i=0;i<num;i++)
	{
		if ((*this)[i].isin(p))
			break;
	}
	if (i==num)
		return -1;
	return i;
}

bool BallSet::isinlimit(const Point& p)
{
	int i;
	for (i=0;i<num;i++)
	{
		if ((*this)[i].isinlimit(p))
			break;
	}
	if (i==num)
		return false;
	return true;
}

int BallSet::isactive()
{
	int i;
	for (i=0;i<num;i++)
	{
		if ((*this)[i].active)
			break;
	}
	if (i==num)
		return -1;
	return i;
}

void BallSet::clearactive()
{
	for (int i=0;i<num;i++)
	{
		if ((*this)[i].active)
			(*this)[i].active=false;
	}
}

void BallSet::conjunctionBall()
{
	for (int i=0;i<num;i++)
		for (int k=0;k<num;k++)
			(*this)[i].conjunctionBall((*this)[k]);
}

void BallSet::savepostofile(const Graph& g)
{
	BallSet ball=(*this);

	if (g.filename!="")
	{
		string line="";
		char c[100];
		for (int i=0;i<ball.num;i++)
		{
			sprintf(c,"%e",ball[i].getPosX());
			line+=c;
			line+=',';
			sprintf(c,"%e",ball[i].getPosY());
			line+=c;
			if (i!=ball.num-1)
				line+=' ';
		}
		ifstream in(g.filename.c_str());
		string indata="";
		if (!in.fail())
		{
			string p;
			for (int i=0;!in.eof();i++)
			{
				getline(in,p);
				if (i!=2)
					indata+=p;
				else
					indata+=line;
				indata+="\n";
			}
			in.close();
		}
		ofstream out(g.filename.c_str());
		if (!out.fail())
		{
			out<<indata;
			out.close();
		}
	}
}
