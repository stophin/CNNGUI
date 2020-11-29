//GUIFrame.cpp
//GUIøÚº‹¿‡ µœ÷
#include "GUIFrame.h"

GUIFrame::GUIFrame():
scrwd(DEFSCRWD),
scrht(DEFSCRHT),
hWnd(NULL),
bkcolor(WHITE),
ftcolor(BLACK),
link(NULL),
last(NULL),
cur(),
objnum(0),
focused(-1)
{
	hWnd= InitGraph(scrwd, scrht);
}

GUIFrame::GUIFrame(GUITYPE scrw,GUITYPE scrh):
scrwd(scrw),
scrht(scrh),
hWnd(NULL),
bkcolor(WHITE),
ftcolor(BLACK),
link(NULL),
last(NULL),
cur(),
objnum(0),
focused(-1)
{
	if (scrwd<=0||scrht<=0)
	{
		scrwd=GetSystemMetrics(SM_CXSCREEN);
		scrht=GetSystemMetrics(SM_CYSCREEN);
		hWnd=InitGraph(scrwd,scrht, SHOWCONSOLE);
		SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)-WS_CAPTION);
		SetWindowPos(hWnd,HWND_TOP,0,0,scrwd,scrht,SWP_SHOWWINDOW);
	}
	else
	{
		hWnd= InitGraph(scrwd,scrht, SHOWCONSOLE);
	}
}

GUIFrame::~GUIFrame()
{
	PGObject temp;
	for (PGObject pobj=link;pobj!=NULL;)
	{
		temp=pobj->next;
		delete pobj;
		pobj=temp;
	}
	link=NULL;
	objnum=0;
	closegraph();
}

bool GUIFrame::DeleteObject(const string& uni)
{
	PGObject del=link;
	int i;
	for (i=0;i<objnum;i++)
	{
		if (del->uniname==uni)
			break;
		del=del->next;
	}
	if (i==objnum)
		return false;
	if (del==link)
	{
		link=del->next;
	}
	else
	{
		(*this)[i-1]->next=del->next;
	}
	if (del==last)
	{
		last=(*this)[i-1];
	}
	delete del;
	objnum--;
	return true;
}

PGObject GUIFrame::GetObject(string uniname)
{
	int i;
	for (i=0;i<objnum;i++)
	{
		if ((*this)[i]->uniname==uniname)
			break;
	}
	return ((*this)[i]);
}

PGObject GUIFrame::operator[](int i)
{
	if (i<0)
		return NULL;
	PGObject t;
	for (t=link;t&&i;i--,t=t->next);
	if (t)
		return t;
	return NULL;
}

bool GUIFrame::Focused(const string& uni)
{
	int i;
	for (i=0;i<objnum;i++)
	{
		if ((*this)[i]->uniname==uni)
			break;
	}
	return focused==i;
}

void GUIFrame::Update()
{
	setbkcolor(bkcolor);
//	setcolor(ftcolor);
//	cleardevice();
	if (hWnd==GetForegroundWindow())
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		cur.x=point.x;
		cur.y=point.y;
		if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
		{
			int i;
			for (i=objnum-1;i>=0;i--)
			{
				if ((*this)[i]->isin(cur))
					break;
				else
					(*this)[i]->mousestate=READYSTATE;
			}
			focused=i;
		}
	}
	else
		focused=-1;
}

void GUIFrame::Redraw()
{
	for (int i=0;i<objnum;i++)
	{
		if (focused==i)
		{
			(*this)[i]->CaptureMouse(cur);
		}
		(*this)[i]->Show(focused==i);
	}
}
