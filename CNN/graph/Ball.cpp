//PhysicalBall.cpp
//PhysicalBall.h的实现函数
//
#include "Ball.h"
//全局宏定义
#ifndef PHXPI			//PI
#define PHXPI 3.141592654
#endif			//end of PHXPI

#ifndef PHXZERO			//zero
#define PHXZERO 1e-6
#endif			//end of PHXZERO

//小球的一些默认特性属性
#ifndef DEFRADIUS		//球的默认半径
#define DEFRADIUS 50.0
#endif			//end of DEFRADIUS

//判断PHXTYPE类型的数据是否是零（接近零）
int notZero(PHXTYPE x,PHXTYPE e=0.0)
{
	return ((x<(PHXZERO+e)&&x>-(PHXZERO+e))?0:(x<0?-1:1));
}

//class Point functions
Point::Point ():x(0),y(0){}

Point::Point(PHXTYPE x,PHXTYPE y):x(x),y(y)
{}

Point::Point(const Point& pt):x(pt.x),y(pt.y)
{}

Point::~Point()
{}

PHXTYPE Point:: getX() const
{
	return x;
}

PHXTYPE Point::getY() const
{
	return y;
}

PHXTYPE Point::getVal()
{
	return sqrt(x*x+y*y);
}

void Point::setX(PHXTYPE x)
{
	this->x=x;
}

void Point::setY(PHXTYPE y)
{
	this->y=y;
}

void Point::set(PHXTYPE x,PHXTYPE y)
{
	this->x=x;
	this->y=y;
}

void Point::set(const Point& pt)
{
	x=pt.getX();
	y=pt.getY();
}

//当前点绕指定点旋转
void Point::rotate(const Point& o,PHXTYPE angle,bool cast)
{
	*this-=o;
	rotate(angle,cast);
	*this+=o;
}

//四舍五入
//int round(PHXTYPE d)
//{
//	if (d<0)
//		return -int(-d+0.5);
//	else
//		return int(d+0.5);
//}

//向量绕其初始点旋转(比如向量是由A-B得来的，则向量是由B指向A,则就相当于A点绕B点旋转)
void Point::rotate(PHXTYPE angle,bool cast)
{
	PHXTYPE tx,ty;
	tx=this->getX();
	ty=this->getY();
	if (cast)	//四舍五入式
	{
		x=round(tx*cos(angle)-ty*sin(angle));
		y=round(ty*cos(angle)+tx*sin(angle));
	}
	else
	{
		x=tx*cos(angle)-ty*sin(angle);
		y=ty*cos(angle)+tx*sin(angle);
	}
}

//操作符重载
const Point Point::operator- (const Point& pt) const
{
	return Point(x-pt.getX(),y-pt.getY());
}

const Point Point::operator+ (const Point& pt) const
{
	return Point (x+pt.getX(),y+pt.getY());;
}

const Point Point::operator* (PHXTYPE pa) const
{
	return Point(x*pa,y*pa);
}

PHXTYPE Point::operator* (const Point& pt) const
{
	return (x*pt.getX()+y*pt.getY());
}

Point& Point::operator= (const Point& pt)
{
	x=pt.getX();
	y=pt.getY();
	return *this;
}

Point& Point::operator+= (const Point& pt)
{
	x+=pt.getX();
	y+=pt.getY();
	return *this;
}

Point& Point::operator-= (const Point& pt)
{
	x-=pt.getX();
	y-=pt.getY();
	return *this;
}

Point& Point::operator*= (PHXTYPE pa)
{
	x*=pa;
	y*=pa;
	return *this;
}


Point& Point::operator/= (PHXTYPE pa)
{
	if (!notZero(pa))
		pa=1.0;
	x/=pa;
	y/=pa;
	return *this;
}

//end of class Point functions

//class Ball functions
Ball::Ball():
pos(),
active(false),
radius(DEFRADIUS),
limlt(0,0),
limrb(PHXLIMX,PHXLIMY),
order(0)
{
}

Ball::Ball(PHXTYPE posx,PHXTYPE posy):
pos(posx,posy),
active(false),
radius(DEFRADIUS),
limlt(0,0),
limrb(PHXLIMX,PHXLIMY),
order(0)
{
}

Ball::Ball(PHXTYPE r):
pos(0,0),
active(false),
radius(r),
limlt(0,0),
limrb(PHXLIMX,PHXLIMY),
order(0)
{
}

Ball::Ball(const Ball& b):
pos(b.getPos()),
active(b.active),
radius(b.getRadius()),
limlt(b.getLimitLt()),
limrb(b.getLimitRb()),
order(b.order)
{
}

Ball::~Ball()
{
}

PHXTYPE Ball::getRadius() const
{
	return radius;
}

void Ball::setRadius(PHXTYPE r)
{
	radius=r;
}

void Ball::setPos(PHXTYPE x,PHXTYPE y)
{
	if (x>(limrb.getX()-radius))
		x=limrb.getX()-radius;
	else if (x<(radius+limlt.getX()))
		x=radius+limlt.getX();	
	if (y>(limrb.getY()-radius))
		y=limrb.getY()-radius;
	else if (y<(radius+limlt.getY()))
		y=(radius+limlt.getY());
	pos.set(x,y);
}

void Ball::setPos(const Point& p)
{
	setPos(p.getX(),p.getY());
}

void Ball::setPosX(PHXTYPE x)
{
	pos.setX(x);
}

void Ball::setPosY(PHXTYPE y)
{
	pos.setY(y);
}

PHXTYPE Ball::getPosX() const
{
	return pos.getX();
}

PHXTYPE Ball::getPosY() const
{
	return pos.getY();
}

Point Ball::getPos() const
{
	return pos;
}

void Ball::setLimit(PHXTYPE rx,PHXTYPE ry,PHXTYPE lx,PHXTYPE ly)
{
	if (lx<0||ly<0||rx<0||ry<0)
		return;
	if (lx>rx||ly>ry)
		return;
	if (!notZero(lx-rx)||!notZero(ly-ry))
		return;
	limlt.setX(lx);
	limlt.setY(ly);
	limrb.setX(rx);
	limrb.setY(ry);
}

void Ball::setLimitLtX(PHXTYPE x)
{
	if (x<0)
		return;
	if (x>limrb.getX())
		return;
	if (!notZero(x-limrb.getX()))
		return;
	limlt.setX(x);
}

void Ball::setLimitLtY(PHXTYPE y)
{
	if (y<0)
		return;
	if (y>limrb.getY())
		return;
	if (!notZero(y-limrb.getY()))
		return;
	limlt.setY(y);
}

void Ball::setLimitRbX(PHXTYPE x)
{
	if (x<0)
		return;
	if (x<limlt.getX())
		return;
	if (!notZero(x-limlt.getX()))
		return;
	limrb.setX(x);
}

void Ball::setLimitRbY(PHXTYPE y)
{
	if (y<0)
		return;
	if (y>limlt.getY())
		return;
	if (!notZero(y-limlt.getY()))
		return;
	limrb.setY(y);
}

PHXTYPE Ball::getLimitLtX() const
{
	return limlt.getX();
}

PHXTYPE Ball::getLimitLtY() const
{
	return limlt.getY();
}

Point Ball::getLimitLt() const
{
	return limlt;
}

Point Ball::getLimitRb() const
{
	return limrb;
}

PHXTYPE Ball::getLimitRbX() const
{
	return limrb.getX();
}

PHXTYPE Ball::getLimitRbY() const
{
	return limrb.getY();
}

PHXTYPE Ball::getLimitX() const
{
	return limrb.getX()-limlt.getX();
}

PHXTYPE	Ball::getLimitY() const
{
	return limrb.getY()-limlt.getY();
}

Point Ball::getLimit() const
{
	return limrb-limlt;
}

//解决两球粘连的问题，如果两球粘连，则质心距与半径和之差一定小于0，将两球拉开到相切,
bool Ball::conjunctionBall(Ball& ball)
{
	PHXTYPE ida,idb;
	ida=this->getDistance(ball);
	idb=this->getRadius()+ball.getRadius();
	//求质心距与半径和之差
	PHXTYPE dts=ida-idb;
	if (dts<0)		//如质心距与半径和之差为负，则拉开
	{	
		PHXTYPE pa,pb,pc;			//临时变量，用于取模等
		Point verH,verV;			//单位向量
		//如果设置为质心点拉开模式,取由指定球质心到当前球质心的方向向量
		verH.set(this->getPosX()-ball.getPosX(),this->getPosY()-ball.pos.getY());
		//取方向向量的模
		pa=sqrt(pow(verH.getX(),2)+pow(verH.getY(),2));
		//设置为单位向量，该方向为当前球被拉开的方向
		if (!notZero(pa))
			pa=1.0;
		verH.set(verH.getX()/pa,verH.getY()/pa);
		//如果设置为质心点拉开模式，则两球分别拉开其质心距半径之差的一半，否则值为下面if语句中给出
		dts/=-2.0;

		//分别定义新的x、y坐标，指定新的位置
		PHXTYPE tposx,tposy;
		
		//单位向量与负的差距相乘，求得当前球拉开向量
		verH.set(verH.getX()*dts,verH.getY()*dts);
		
		tposx=this->getPosX();			//得到原位置
		tposy=this->getPosY();
		tposx+=verH.getX();				//新位置为原位置加拉开向量
		pa=this->getLimitRbX();
		pc=this->getLimitLtX();
		pb=this->getRadius();
		//如果拉开后超过指定区域范围，则停止拉动
		if (tposx>(pa-pb)||tposx<(pb+pc))
		{
			if (tposx<(pb+pc))
				tposx=pb+pc;
			else
				tposx=pa-pb;
		}
		//以下同上
		tposy+=verH.getY();
		pa=this->getLimitRbY();
		pc=this->getLimitLtY();
		pb=this->getRadius();
		if (tposy>(pa-pb)||tposy<(pb+pc))
		{
			if (tposy<(pb+pc))
				tposy=pb+pc;
			else
				tposy=pa-pb;
		}
		setPos(tposx,tposy);
		
		//指定球的拉开，其拉开向量为当前球的拉开向量的反向量
		//算法同上
		tposx=ball.getPosX();
		tposx-=verH.getX();
		pa=ball.getLimitRbX();
		pc=ball.getLimitLtX();
		pb=ball.getRadius();
		if (tposx>(pa-pb)||tposx<(pb+pc))
		{
			if (tposx<(pb+pc))
				tposx=pb+pc;
			else
				tposx=pa-pb;
		}
		tposy=ball.getPosY();
		tposy-=verH.getY();
		pa=ball.getLimitRbY();
		pc=ball.getLimitLtY();
		pb=ball.getRadius();
		if (tposy>(pa-pb)||tposy<(pb+pc))
		{
			if (tposy<(pb+pc))
				tposy=pb+pc;
			else
				tposy=pa-pb;
		}
		ball.setPos(tposx,tposy);
		return true;
	}
	else
		return false;
}

//获取质心距离
PHXTYPE Ball::getDistance(const Ball& ball) const
{
	return sqrt(pow(pos.getX()-ball.pos.getX(),2)+pow(pos.getY()-ball.pos.getY(),2));
}

PHXTYPE Ball::getDistance(const Point& pt) const
{
	return sqrt(pow(pos.getX()-pt.getX(),2)+pow(pos.getY()-pt.getY(),2));
}

//获取最小质心距离
PHXTYPE Ball::getMinDistance(const Ball& ball) const
{
	return radius+ball.radius;
}

bool Ball::isin(const Point& p)
{
	if (this->getDistance(p)<=this->getRadius())
		return true;
	return false;
}

bool Ball::isin(const Point& lt,const Point& rb,bool disorder)
{
	int px=(*this).getPosX(),py=(*this).getPosY();
	if (px>=lt.getX()&&px<=rb.getX()&&py>=lt.getY()&&py<=rb.getY())
		return true;
	else if (px>=rb.getX()&&px<=lt.getX()&&py>=rb.getY()&&py<=lt.getY())
	{
		if (disorder)
			return true;
		else 
			return false;
	}
	return false;
}

bool Ball::isinlimit(const Point& p)
{
	if (p.getX()>=limlt.getX()&&p.getX()<=limrb.getX()&&p.getY()>=limlt.getY()&&p.getY()<=limrb.getY())
		return true;
	return false;
}

//end of class Ball functions