//
// C++ Interface: xqwfirsthand_bottom
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQWFIRSTHAND_BOTTOM_H
#define XQWFIRSTHAND_BOTTOM_H

#include "xqwfirsthand.h"

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQWFirstHand_bottom : public XQWFirstHand
{
Q_OBJECT
protected:
	virtual void xMakeUp_BackgroundCoords();
	virtual void xMakeCentered();
	virtual void purgeCacheFixBorder(int ,int &,int &xLastY_notmanaged,int &);
        virtual void purgeCacheFixMouse(int ,int &,int &,int &);
	virtual int iconIndexByCoords(int,int);
	virtual void mouseMoveEventSWIcon(int,int,int,XQDEIcon *,int);
	virtual XQDEIconRect iconCoordsByIndex(int);
	virtual void xMakeCenteredfix(int doResize=0);
	virtual void xRepaintSingleBackground(QPainter *pp1_p,int sx,int sy,int sz);

public:
	virtual void xReset();
	XQWFirstHand_bottom(QObject *lRoot, QWidget *parent);
	~XQWFirstHand_bottom();
};

#endif
