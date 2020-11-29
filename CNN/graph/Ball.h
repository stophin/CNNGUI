//PhysicalBall.h
//物理小球类，包括创建质量相等但体积不等的物理小球，以及小球的物理碰撞函数
//
#include <math.h>
#include <stdlib.h>
#include "Graph.h"

#ifndef PHYSICAL_BALL_INCLUDE
#define PHYSICAL_BALL_INCLUDE

#define SCRHT 600	//屏幕高度
#define SCRWD 1000	//屏幕宽度
#define BALLNUM		8
#define BALLRADIUS	20

#define BKCOLOR		RGB(0xFF, 0xFF, 0xFF)//RGB(0x07,0x9F,0x22)	//背景颜色
#define DARKBK		RGB(0x11,0x4B,0x0E)	//深色背景
#define LIGHTCOLOR	RGB(0x00,0xFF,0x00)	//亮色球体颜色
#define BALLCOLOR	RGB(0x0F,0xEE,0x0F)	//球体颜色及线颜色
#define SHADOWCOLOR RGB(0xFF, 0xFF, 0xFF)//RGB(0x0F,0xDD,0x0F)	//球体深色阴影
#define TEXTCOLOR	RGB(0x00,0x00,0x00)	//字体颜色
#define LINECOLOR	RGB(0xFF,0xFF,0xFF)	//线颜色

#define PI 3.141592654

#ifndef PHXTYPE
#define PHXTYPE float
#endif			//end of PHXTYPE

#ifndef PHXLIMIT
#define PHXLIMIT
#define PHXLIMX 1300
#define PHXLIMY 700
#endif			//end of PHXLIMIT

//定义向量类，有x、y两个成员变量，
//其中小球的质心位置、绝对速度、绝对加速度、以及阻尼系数都可以由该类来引申，但并不是继承
class Point		
{
public:
	Point();								//无参构造函数
	Point(PHXTYPE x,PHXTYPE y);				//成员变量初始构造函数
	Point(const Point& pt);					//类复制构造函数
	~Point();								//析构函数

	PHXTYPE getX() const;					//获取成员变量x
	PHXTYPE getY() const;					//获取成员变量y
	PHXTYPE getVal();						//获取矢量的长度
	void setX(PHXTYPE x);					//设置成员变量x
	void setY(PHXTYPE y);					//设置成员变量y
	void set(PHXTYPE x,PHXTYPE y);			//同时设置成员变量x、y
	void set(const Point &pt);				//使用结构体同时设置x、y

	
	//使当前点绕指定点旋转一定角度
	void rotate(const Point& o,PHXTYPE angle,bool cast=false);
	//当该类作为向量时,使向量绕其初始点旋转
	void rotate(PHXTYPE angle,bool cast=false);

	//操作符重载
	const Point operator- (const Point& pt) const;
	const Point operator+ (const Point& pt) const;
	const Point operator* (PHXTYPE pa) const;
	PHXTYPE operator* (const Point& pt) const;
	Point& operator= (const Point& pt);
	Point& operator+= (const Point& pt);
	Point& operator-= (const Point& pt);
	Point& operator*= (PHXTYPE pa);
	Point& operator/= (PHXTYPE pa);

private:	
	PHXTYPE x;						//成员变量x
	PHXTYPE y;						//成员变量y
};

//定义球体类
class Ball
{
public:
	Ball();										//无参构造函数
	Ball(const Ball& b);
	Ball(PHXTYPE posx,PHXTYPE posy);			//位置初始参数构造函数
	Ball(PHXTYPE r);
	~Ball();
	PHXTYPE getRadius() const;						//获取半径
	void setRadius(PHXTYPE r);					//设置半径
	void setPos(PHXTYPE x,PHXTYPE y);			//设置质心位置
	void setPos(const Point& p);				//设置质心位置
	void setPosX(PHXTYPE x);					//设置质心x位置
	void setPosY(PHXTYPE y);					//设置质心y位置
	PHXTYPE getPosX() const;							//获取质心x位置
	PHXTYPE getPosY() const;							//获取质心y位置
	Point getPos() const;								//获取位置坐标
	void setLimit(PHXTYPE rx,PHXTYPE ry,PHXTYPE lx=0,PHXTYPE ly=0);//设置球的运动限制
	void setLimitLtX(PHXTYPE x);				//设置x方向的运动限制(左上角)
	void setLimitLtY(PHXTYPE y);				//设置y方向的运动限制(左上角)
	void setLimitRbX(PHXTYPE x);				//设置x方向的运动限制(右下角)
	void setLimitRbY(PHXTYPE y);				//设置y方向的运动限制(右下角)
	PHXTYPE getLimitLtX() const;						//获取x方向的运动限制(左上角)
	PHXTYPE getLimitLtY() const;						//获取y方向的运动限制(左上角)
	Point getLimitLt() const;
	PHXTYPE getLimitRbX() const;						//获取x方向的运动限制(右下角)
	PHXTYPE getLimitRbY() const;						//获取y方向的运动限制(右下角)
	Point getLimitRb() const;
	PHXTYPE getLimitX() const;						//获取x方向的运动限制(绝对)
	PHXTYPE getLimitY() const;						//获取y方向的运动限制(绝对)
	Point getLimit() const;						//获取运动限制绝对坐标位移量


	//获取当前球和指定球之间的质心距离
	PHXTYPE getDistance(const Ball& ball) const;
	PHXTYPE getDistance(const Point& pt) const;
	//获取当前球和指定求之间理论最小质心距
	PHXTYPE getMinDistance(const Ball& ball) const;
	//处理小球粘连
	bool conjunctionBall(Ball& ball);

	bool isin(const Point& p);
	bool isin(const Point& lt,const Point& rb,bool disorder=true);
	bool isinlimit(const Point& p);

private:
	Point limlt;							//球的运动范围限制(左上角)
	Point limrb;							//球的运动范围限制(右上角)
	Point pos;								//球的质心位置
	PHXTYPE radius;							//球的半径
	
	
public:
	bool active;							//是否为活球
	int order;
};

#endif			//end of PHYSICAL_BALL_INCLUDE