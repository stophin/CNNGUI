//PhysicalBall.cpp
//PhysicalBall.h��ʵ�ֺ���
//
#include "Ball.h"
//ȫ�ֺ궨��
#ifndef PHXPI			//PI
#define PHXPI 3.141592654
#endif			//end of PHXPI

#ifndef PHXZERO			//zero
#define PHXZERO 1e-6
#endif			//end of PHXZERO

//С���һЩĬ����������
#ifndef DEFRADIUS		//���Ĭ�ϰ뾶
#define DEFRADIUS 50.0
#endif			//end of DEFRADIUS

//�ж�PHXTYPE���͵������Ƿ����㣨�ӽ��㣩
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

//��ǰ����ָ������ת
void Point::rotate(const Point& o,PHXTYPE angle,bool cast)
{
	*this-=o;
	rotate(angle,cast);
	*this+=o;
}

//��������
//int round(PHXTYPE d)
//{
//	if (d<0)
//		return -int(-d+0.5);
//	else
//		return int(d+0.5);
//}

//���������ʼ����ת(������������A-B�����ģ�����������Bָ��A,����൱��A����B����ת)
void Point::rotate(PHXTYPE angle,bool cast)
{
	PHXTYPE tx,ty;
	tx=this->getX();
	ty=this->getY();
	if (cast)	//��������ʽ
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

//����������
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

//�������ճ�������⣬�������ճ���������ľ���뾶��֮��һ��С��0������������������,
bool Ball::conjunctionBall(Ball& ball)
{
	PHXTYPE ida,idb;
	ida=this->getDistance(ball);
	idb=this->getRadius()+ball.getRadius();
	//�����ľ���뾶��֮��
	PHXTYPE dts=ida-idb;
	if (dts<0)		//�����ľ���뾶��֮��Ϊ����������
	{	
		PHXTYPE pa,pb,pc;			//��ʱ����������ȡģ��
		Point verH,verV;			//��λ����
		//�������Ϊ���ĵ�����ģʽ,ȡ��ָ�������ĵ���ǰ�����ĵķ�������
		verH.set(this->getPosX()-ball.getPosX(),this->getPosY()-ball.pos.getY());
		//ȡ����������ģ
		pa=sqrt(pow(verH.getX(),2)+pow(verH.getY(),2));
		//����Ϊ��λ�������÷���Ϊ��ǰ�������ķ���
		if (!notZero(pa))
			pa=1.0;
		verH.set(verH.getX()/pa,verH.getY()/pa);
		//�������Ϊ���ĵ�����ģʽ��������ֱ����������ľ�뾶֮���һ�룬����ֵΪ����if����и���
		dts/=-2.0;

		//�ֱ����µ�x��y���ָ꣬���µ�λ��
		PHXTYPE tposx,tposy;
		
		//��λ�����븺�Ĳ����ˣ���õ�ǰ����������
		verH.set(verH.getX()*dts,verH.getY()*dts);
		
		tposx=this->getPosX();			//�õ�ԭλ��
		tposy=this->getPosY();
		tposx+=verH.getX();				//��λ��Ϊԭλ�ü���������
		pa=this->getLimitRbX();
		pc=this->getLimitLtX();
		pb=this->getRadius();
		//��������󳬹�ָ������Χ����ֹͣ����
		if (tposx>(pa-pb)||tposx<(pb+pc))
		{
			if (tposx<(pb+pc))
				tposx=pb+pc;
			else
				tposx=pa-pb;
		}
		//����ͬ��
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
		
		//ָ���������������������Ϊ��ǰ������������ķ�����
		//�㷨ͬ��
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

//��ȡ���ľ���
PHXTYPE Ball::getDistance(const Ball& ball) const
{
	return sqrt(pow(pos.getX()-ball.pos.getX(),2)+pow(pos.getY()-ball.pos.getY(),2));
}

PHXTYPE Ball::getDistance(const Point& pt) const
{
	return sqrt(pow(pos.getX()-pt.getX(),2)+pow(pos.getY()-pt.getY(),2));
}

//��ȡ��С���ľ���
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