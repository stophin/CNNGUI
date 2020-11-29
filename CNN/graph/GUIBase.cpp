//GUIBase.cpp
//
#include "GUIBase.h"

GUIObject::GUIObject():
lt(DEFOBJLX,DEFOBJLY),
rb(DEFOBJRX,DEFOBJRY),
next(NULL),
mousestate(0),
uniname(""),
bkcolor(WHITE),
fontcolor(BLACK),
isactive(true)
{
	hWnd=GetHWnd();
	dc=GetDC(hWnd);
};

GUIObject::GUIObject(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby):
lt(ltx,lty),
rb(rbx,rby),
next(NULL),
mousestate(0),
uniname(""),
bkcolor(WHITE),
fontcolor(BLACK),
isactive(true)
{
	if ((rbx<ltx)||(rby<lty))
	{
		rb.x=ltx+rbx;
		rb.y=lty+rby;
	}
	hWnd=GetHWnd();
	dc=GetDC(hWnd);
};

GUIObject::GUIObject(const GPoint& plt,const GPoint& prb):
lt(plt),
rb(prb),
next(NULL),
mousestate(0),
uniname(""),
bkcolor(WHITE),
fontcolor(BLACK),
isactive(true)
{
	if ((rb.x<lt.x)||(rb.y<lt.y))
	{
		rb.x=lt.x+rb.x;
		rb.y=lt.y+rb.y;
	}
	hWnd=GetHWnd();
	dc=GetDC(hWnd);
};

GUIObject::GUIObject(const GUIObject& obj):
lt(obj.lt),
rb(obj.rb),
next(NULL),
mousestate(obj.mousestate),
uniname(obj.uniname),
bkcolor(obj.bkcolor),
fontcolor(obj.fontcolor),
isactive(obj.isactive)
{
	hWnd=GetHWnd();
	dc=GetDC(hWnd);
};

GUIObject::~GUIObject()
{
	ReleaseDC(hWnd,dc);
}

bool GUIObject::isin(const GPoint& p)
{
	if ((p.x>=lt.x&&p.y>=lt.y)&&(p.x<=rb.x&&p.y<=rb.y))
		return true;
	return false;
}

void GUIObject::CaptureMouse(const GPoint& p)
{
	if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
	{
		mousestate|=MOUSEPRESSED;
	}
	else if (mousestate&MOUSEPRESSED)
	{
		mousestate^=MOUSEPRESSED;
		mousestate|=MOUSERELEASED;
	}
	else
	{
		mousestate=READYSTATE;
	}
}