//GUIEditbox.h
//
#ifndef GUIEDITBOX_INCLUDE_H
#define GUIEDITBOX_INCLUDE_H
#include "GUIBase.h"

class GUIEditbox:public GUIObject
{
public:
	GUIEditbox();
	GUIEditbox(const string str);
	GUIEditbox(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby);
	GUIEditbox(const GPoint& plt,const GPoint& prb);
	GUIEditbox(const GUIEditbox& edit);

	string content;
	GPoint space;
	GPoint curpos;
	int curflash;
	int curdelay;
	int charht;
	bool curshow;
	

	void Show(bool focus);
};


#endif	//endof GUIEDITBOX_INCLUDE_H