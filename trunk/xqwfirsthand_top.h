//
// C++ Interface: xqwfirsthand_top
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQWFIRSTHAND_TOP_H
#define XQWFIRSTHAND_TOP_H

#include <xqwfirsthand.h>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQWFirstHand_top : public XQWFirstHand
{
Q_OBJECT
protected:
	virtual void xMakeUp_BackgroundCoords();
	virtual void xMakeCentered();
	virtual void purgeCacheFixBorder(int ,int &,int &xLastY_notmanaged,int &);
	virtual void purgeCacheFixMouse(int ,int &,int &,int &);
	virtual int iconIndexByCoords(int,int);
	virtual void mouseMoveEventSWIcon(int,int,int,XQDEIcon *);
	virtual XQDEIconRect iconCoordsByIndex(int);
	virtual void xMakeCenteredfix(int doResize=0);
	virtual void xRepaintSingleBackground(QPainter *pp1_p,int sx,int sy,int sz);
public:
	virtual void xReset();
	XQWFirstHand_top(QObject *lRoot, QWidget *parent);
	~XQWFirstHand_top();
};
#endif
