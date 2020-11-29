//GUIFrame.h
//GUIøÚº‹¿‡
#ifndef GUIFRAME_INCLUDE_H
#define GUIFRAME_INCLUDE_H

#include "GUIBase.h"

class GUIFrame
{
public:
	GUIFrame();
	GUIFrame(GUITYPE scrw,GUITYPE scrh);
	~GUIFrame();

	COLORREF bkcolor;
	COLORREF ftcolor;

	int objnum;
	void Update();
	void Redraw();
	template <class T>
	bool AddObject(const T& obj)
	{
		for (int i=0;i<objnum;i++)
		{
			if ((*this)[i]->uniname==obj.uniname)
				return false;
		}
		T* pobj=new T(obj);
		if (!pobj)
			return false;
		if (!link)
			link=pobj;
		if (last)
			last->next=pobj;
		last=pobj;
		objnum++;
		return true;
	}
	bool DeleteObject(const string& uni);
	PGObject GetObject(string uniname);
	PGObject operator[](int i);
	bool Focused(const string& uni);

	PGObject link;
	PGObject last;

	GPoint cur;
	int focused;

	GUITYPE scrwd;
	GUITYPE scrht;
	HWND hWnd;
};

#endif	//endof GUIFRAME_INCLUDE_H