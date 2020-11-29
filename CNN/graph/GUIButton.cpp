//GUIButton.cpp
//GUI按钮类实现
#include "GUIButton.h"

GUIButton::GUIButton():
GObject(),
caption("")
{
	bkcolor=LIGHTGRAY;
	fontcolor=BLACK;
}

GUIButton::GUIButton(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby):
GObject(ltx,lty,rbx,rby),
caption("")
{
	bkcolor=LIGHTGRAY;
	fontcolor=BLACK;
}

GUIButton::GUIButton(const GPoint& plt,const GPoint& prb):
GObject(plt,prb),
caption("")
{
	bkcolor=LIGHTGRAY;
	fontcolor=BLACK;
}

GUIButton::GUIButton(const GUIButton& btn):
GObject(btn),
caption(btn.caption)
{
	isactive=btn.isactive;
}

void GUIButton::Show(bool focus)
{
	FILLSTYLE oldfill;
	COLORREF oldcolor;
	getfillstyle(&oldfill);
	oldcolor=getcolor();

	setfillstyle(bkcolor);
	setcolor(bkcolor);
	rectangle(lt.x,lt.y,rb.x,rb.y);
	floodfill(lt.x+1,lt.y+1,bkcolor);

	if (isactive)
	{
		if (mousestate&MOUSEPRESSED)
			setcolor(BLACK);
		else
			setcolor(WHITE);
		
		line(lt.x,lt.y,rb.x,lt.y);
		line(lt.x,lt.y,lt.x,rb.y);
		if (mousestate&MOUSEPRESSED)
			setcolor(WHITE);
		else
			setcolor(BLACK);
		line(lt.x,rb.y,rb.x,rb.y);
		line(rb.x,rb.y,rb.x,lt.y);
		
		setcolor(fontcolor);
	}
	else
	{
		setcolor(WHITE);
		line(lt.x,lt.y,rb.x,lt.y);
		line(lt.x,lt.y,lt.x,rb.y);
		setcolor(BLACK);
		line(lt.x,rb.y,rb.x,rb.y);
		line(rb.x,rb.y,rb.x,lt.y);

		setcolor(bkcolor+RGB(0x1F,0x1F,0x1F));
	}

	

	int dx=rb.x-lt.x;
	int dy=rb.y-lt.y;
	int x=lt.x,y=lt.y;
	int ptr=0,ptr1=0;
	SIZE size;
	char temp[3];
	int len;
	int width=0;
	while(ptr1<caption.length()&&width<dx)
	{
		len=0;
		temp[len]=caption.at(ptr1++);
		if (temp[len++]&0x8000&&ptr1<caption.length())
		{
			temp[len++]=caption.at(ptr1++);
		}
		temp[len]='\0';
		GetTextExtentPoint32(dc,temp,len,&size);
		width+=size.cx;
	}
	if (ptr1==caption.length())
	{
		x+=((dx-width)/2);
	}
	while(ptr<ptr1)
	{
		len=0;
		temp[len]=caption.at(ptr++);
		if (temp[len++]&0x8000&&ptr<caption.length())
		{
			temp[len++]=caption.at(ptr++);
		}
		temp[len]='\0';
		GetTextExtentPoint32(dc,temp,len,&size);
		if (isactive&&mousestate&MOUSEPRESSED)
			outtextxy(x+1,y+1+dy/2.0-size.cy/2.0,temp);
		else
			outtextxy(x,y+dy/2.0-size.cy/2.0,temp);
		x+=size.cx;
		if (x>=rb.x-size.cx)
		{
			break;
		}
	}

	//设置回原来的颜色
	setcolor(oldcolor);
	setfillstyle(&oldfill);

	return;
}

bool GUIButton::LBPressed()
{
	if (this->mousestate&MOUSERELEASED&&this->isactive)
		return true;
	return false;
}
