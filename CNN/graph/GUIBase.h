//GUIBase.h
//GUI基本类
#ifndef GUIBASE_H_INCLUDE
#define GUIBASE_H_INCLUDE

#include <graphics.h>
//#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

//////////////////////////////////
#pragma warning(disable:4996)
#define LINESTYLE int
inline void setlinestyle(LINESTYLE * l) {
	setlinestyle(*l);
}
#define FILLSTYLE int
inline void getfillstyle(FILLSTYLE * f) {

}
inline void setfillstyle(FILLSTYLE * f) {

}
inline void setfillstyle(COLORREF f) {
	setfillstyle(SOLID_FILL, f);
}
inline void arc(int left, int top, int right, int bottom, double stangle, double endangle) {
	arc(left, top, stangle, endangle, right - left);
}

inline void BeginBatchDraw() {
	setrendermode(RENDER_MANUAL);
}
inline void EndBatchDraw() {

}
inline void FlushBatchDraw(int fps = 100) {
	delay_fps(fps);
}
inline HWND GetHWnd() {
	return getHWnd();
}
inline HWND InitGraph(int w, int h, int  m = INIT_RENDERMANUAL) {
	ege::initgraph(w, h, INIT_RENDERMANUAL);
	return GetHWnd();
}
#include "../platform/ELibrary.h"
inline int _kbhit() {
	return kbhit_console();
}
inline int _getch() {
	return getch_console();
}
///////////////////////////////////


#define GUITYPE int

#define DEFSCRWD	640
#define DEFSCRHT	480
#define DEFOBJLX	0
#define DEFOBJLY	0
#define DEFOBJRX	20
#define DEFOBJRY	20

#define READYSTATE		0x0000
#define MOUSEPRESSED	0x0001
#define MOUSERELEASED	0x0002

typedef class GUIPoint	//点类
{
public:
	GUIPoint():x(0),y(0){};
	GUIPoint(GUITYPE px,GUITYPE py):x(px),y(py){};
	GUIPoint(const GUIPoint& p):x(p.x),y(p.y){};
	~GUIPoint(){};

	GUIPoint& operator=(const GUIPoint& p);

	GUITYPE x;
	GUITYPE y;
}GPoint;

typedef class GUIObject		//对象类
{
public:
	GUIObject();
	GUIObject(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby);
	GUIObject(const GPoint& plt,const GPoint& prb);
	GUIObject(const GUIObject& obj);
	~GUIObject();

	HDC dc;
	HWND hWnd;

	GPoint lt;
	GPoint rb;

	string uniname;
	COLORREF bkcolor,fontcolor;

	bool isactive;
	int mousestate;
	void CaptureMouse(const GPoint& p);
	bool isin(const GPoint& pt);

	virtual void Show(bool focus)=0;

	class GUIObject* next;
}GObject,* PGObject;

#endif		//endof GUIBASE_INCLUDE_H