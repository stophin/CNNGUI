//GUIButton.h
//GUI∞¥≈•¿‡
#ifndef GUIBUTTON_INCLUDE_H
#define GUIBUTTON_INCLUDE_H

#include "GUIBase.h"

class GUIButton:public GObject
{
public:
	GUIButton();
	GUIButton(GUITYPE ltx,GUITYPE lty,GUITYPE rbx,GUITYPE rby);
	GUIButton(const GPoint& plt,const GPoint& prb);
	GUIButton(const GUIButton& btn);

	string caption;

	void Show(bool focus);
	bool LBPressed();
};

#endif	//endof GUIBUTTON_INCLUDE_H