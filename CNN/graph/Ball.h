//PhysicalBall.h
//����С���࣬��������������ȵ�������ȵ�����С���Լ�С���������ײ����
//
#include <math.h>
#include <stdlib.h>
#include "Graph.h"

#ifndef PHYSICAL_BALL_INCLUDE
#define PHYSICAL_BALL_INCLUDE

#define SCRHT 600	//��Ļ�߶�
#define SCRWD 1000	//��Ļ���
#define BALLNUM		8
#define BALLRADIUS	20

#define BKCOLOR		RGB(0xFF, 0xFF, 0xFF)//RGB(0x07,0x9F,0x22)	//������ɫ
#define DARKBK		RGB(0x11,0x4B,0x0E)	//��ɫ����
#define LIGHTCOLOR	RGB(0x00,0xFF,0x00)	//��ɫ������ɫ
#define BALLCOLOR	RGB(0x0F,0xEE,0x0F)	//������ɫ������ɫ
#define SHADOWCOLOR RGB(0xFF, 0xFF, 0xFF)//RGB(0x0F,0xDD,0x0F)	//������ɫ��Ӱ
#define TEXTCOLOR	RGB(0x00,0x00,0x00)	//������ɫ
#define LINECOLOR	RGB(0xFF,0xFF,0xFF)	//����ɫ

#define PI 3.141592654

#ifndef PHXTYPE
#define PHXTYPE float
#endif			//end of PHXTYPE

#ifndef PHXLIMIT
#define PHXLIMIT
#define PHXLIMX 1300
#define PHXLIMY 700
#endif			//end of PHXLIMIT

//���������࣬��x��y������Ա������
//����С�������λ�á������ٶȡ����Լ��ٶȡ��Լ�����ϵ���������ɸ��������꣬�������Ǽ̳�
class Point		
{
public:
	Point();								//�޲ι��캯��
	Point(PHXTYPE x,PHXTYPE y);				//��Ա������ʼ���캯��
	Point(const Point& pt);					//�ิ�ƹ��캯��
	~Point();								//��������

	PHXTYPE getX() const;					//��ȡ��Ա����x
	PHXTYPE getY() const;					//��ȡ��Ա����y
	PHXTYPE getVal();						//��ȡʸ���ĳ���
	void setX(PHXTYPE x);					//���ó�Ա����x
	void setY(PHXTYPE y);					//���ó�Ա����y
	void set(PHXTYPE x,PHXTYPE y);			//ͬʱ���ó�Ա����x��y
	void set(const Point &pt);				//ʹ�ýṹ��ͬʱ����x��y

	
	//ʹ��ǰ����ָ������תһ���Ƕ�
	void rotate(const Point& o,PHXTYPE angle,bool cast=false);
	//��������Ϊ����ʱ,ʹ���������ʼ����ת
	void rotate(PHXTYPE angle,bool cast=false);

	//����������
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
	PHXTYPE x;						//��Ա����x
	PHXTYPE y;						//��Ա����y
};

//����������
class Ball
{
public:
	Ball();										//�޲ι��캯��
	Ball(const Ball& b);
	Ball(PHXTYPE posx,PHXTYPE posy);			//λ�ó�ʼ�������캯��
	Ball(PHXTYPE r);
	~Ball();
	PHXTYPE getRadius() const;						//��ȡ�뾶
	void setRadius(PHXTYPE r);					//���ð뾶
	void setPos(PHXTYPE x,PHXTYPE y);			//��������λ��
	void setPos(const Point& p);				//��������λ��
	void setPosX(PHXTYPE x);					//��������xλ��
	void setPosY(PHXTYPE y);					//��������yλ��
	PHXTYPE getPosX() const;							//��ȡ����xλ��
	PHXTYPE getPosY() const;							//��ȡ����yλ��
	Point getPos() const;								//��ȡλ������
	void setLimit(PHXTYPE rx,PHXTYPE ry,PHXTYPE lx=0,PHXTYPE ly=0);//��������˶�����
	void setLimitLtX(PHXTYPE x);				//����x������˶�����(���Ͻ�)
	void setLimitLtY(PHXTYPE y);				//����y������˶�����(���Ͻ�)
	void setLimitRbX(PHXTYPE x);				//����x������˶�����(���½�)
	void setLimitRbY(PHXTYPE y);				//����y������˶�����(���½�)
	PHXTYPE getLimitLtX() const;						//��ȡx������˶�����(���Ͻ�)
	PHXTYPE getLimitLtY() const;						//��ȡy������˶�����(���Ͻ�)
	Point getLimitLt() const;
	PHXTYPE getLimitRbX() const;						//��ȡx������˶�����(���½�)
	PHXTYPE getLimitRbY() const;						//��ȡy������˶�����(���½�)
	Point getLimitRb() const;
	PHXTYPE getLimitX() const;						//��ȡx������˶�����(����)
	PHXTYPE getLimitY() const;						//��ȡy������˶�����(����)
	Point getLimit() const;						//��ȡ�˶����ƾ�������λ����


	//��ȡ��ǰ���ָ����֮������ľ���
	PHXTYPE getDistance(const Ball& ball) const;
	PHXTYPE getDistance(const Point& pt) const;
	//��ȡ��ǰ���ָ����֮��������С���ľ�
	PHXTYPE getMinDistance(const Ball& ball) const;
	//����С��ճ��
	bool conjunctionBall(Ball& ball);

	bool isin(const Point& p);
	bool isin(const Point& lt,const Point& rb,bool disorder=true);
	bool isinlimit(const Point& p);

private:
	Point limlt;							//����˶���Χ����(���Ͻ�)
	Point limrb;							//����˶���Χ����(���Ͻ�)
	Point pos;								//�������λ��
	PHXTYPE radius;							//��İ뾶
	
	
public:
	bool active;							//�Ƿ�Ϊ����
	int order;
};

#endif			//end of PHYSICAL_BALL_INCLUDE