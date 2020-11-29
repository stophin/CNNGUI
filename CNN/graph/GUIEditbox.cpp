//GUIEditbox.cpp
//
#include "GUIEditbox.h"

GUIEditbox::GUIEditbox():
GObject(),
content(""),
space(10,10),
curflash(0),
curdelay(10),
charht(0),
curshow(false)
{
	curpos.x=lt.x+space.x;curpos.y=lt.y+space.y;
}

GUIEditbox::GUIEditbox(const string str):
GObject(),
content(str),
space(10,10),
curflash(0),
curdelay(10),
charht(0),
curshow(false)
{
	curpos.x=lt.x+space.x;
	curpos.y=lt.y+space.y;
}

GUIEditbox::GUIEditbox(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby):
GObject(ltx,lty,rbx,rby),
content(""),
space(10,10),
curflash(0),
charht(0),
curdelay(10),
curshow(false)
{
	curpos.x=lt.x+space.x;
	curpos.y=lt.y+space.y;
}

GUIEditbox::GUIEditbox(const GPoint& plt,const GPoint& prb):
GObject(plt,prb),
content(""),
space(10,10),
curflash(0),
curdelay(10),
charht(0),
curshow(false)
{
	curpos.x=lt.x+space.x;
	curpos.y=lt.y+space.y;
}

GUIEditbox::GUIEditbox(const GUIEditbox& edit):
GObject(edit),
content(edit.content),
space(edit.space),
curflash(edit.curflash),
curdelay(edit.curdelay),
charht(edit.charht),
curshow(edit.curshow)
{
	curpos.x=lt.x+space.x;
	curpos.y=lt.y+space.y;
	bkcolor=edit.bkcolor;
	fontcolor=edit.fontcolor;
}

void GUIEditbox::Show(bool focus)
{
	FILLSTYLE oldfill;
	COLORREF oldcolor;
	getfillstyle(&oldfill);
	oldcolor=getcolor();

	setcolor(bkcolor);
	setfillstyle(bkcolor);
	rectangle(lt.x,lt.y,rb.x,rb.y);
	floodfill(lt.x+1,lt.y+1,bkcolor);
	setcolor(BLACK);
	line(lt.x,lt.y,rb.x,lt.y);
	line(lt.x,lt.y,lt.x,rb.y);
	setcolor(WHITE);
	line(lt.x,rb.y,rb.x,rb.y);
	line(rb.x,rb.y,rb.x,lt.y);

	if (focus)
	{
		if (_kbhit())
		{
			char c=_getch();
			if (c=='\b')
			{
				if (content.length()>0)
				{
					if (content.at(content.length()-1)&0x8000)
						content.erase(content.end()-1);
					content.erase(content.end()-1);
				}
			}
			else if (c==27)
			{
			}
			else
			{
				content+=c;
			}
		}
		else
		{
			curflash++;
			if (curflash==curdelay)
			{
				curshow=!curshow;
				if (curshow)
				{
					curflash=-curdelay;
				}
				else
				{
					curflash=0;
				}
			}
			if (curshow)
			{
				setcolor(fontcolor);
				line(curpos.x,curpos.y,curpos.x,curpos.y+charht);
			}
		}
	}

	if (content=="")
	{
		curpos.x=lt.x+space.x;
		curpos.y=lt.y+space.y;

		//设置回原来的颜色
		setcolor(oldcolor);
		setfillstyle(&oldfill);

		return;
	}
	setcolor(fontcolor);
	setbkmode(TRANSPARENT);
	int dx=rb.x-lt.x;
	int dy=rb.y-lt.y;
	int x=lt.x+space.x,y=lt.y+space.y;
	int ptr=0;
	SIZE size;
	char temp[3];
	int len;
	while(ptr<content.length())
	{
		len=0;
		temp[len]=content.at(ptr++);
		if (temp[len++]&0x8000&&ptr<content.length())
		{
			temp[len++]=content.at(ptr++);
		}
		temp[len]='\0';
		GetTextExtentPoint32(dc,temp,len,&size);
		if (temp[0]!=13)
		{
			outtextxy(x,y,temp);
		}
		x+=size.cx;
		if (x>=rb.x-space.x||temp[0]==13)
		{
			x=lt.x+space.x;
			y+=size.cy;
		}
		curpos.x=x;
		curpos.y=y;
		charht=size.cy;
	}

	//设置回原来的颜色
	setcolor(oldcolor);
	setfillstyle(&oldfill);

	return;
}