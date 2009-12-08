//
// C++ Interface: xqwfirsthand
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQWFIRSTHAND_H
#define XQWFIRSTHAND_H

//#include <xqimage.h>
#include "xqwidget.h"
#include "xqdeicon.h"
//#include <qicon.h>


class QMutex;
extern class XQPillow *Global_XQPillow;


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQWFirstHand : public XQWidget
{
Q_OBJECT
public:
	XQWFirstHand(QObject *lRoot, QWidget *parent);
	~XQWFirstHand();
	virtual void xReset();
	virtual void xRepaint();
	virtual void xRepaintSingleIndex(int);
	virtual void xRepaintSingleBackground(QPainter *, int ,int,int);
	virtual void xRepaintSingle(XQDEIcon *icon);
	virtual void xConfigurationChanged();
	virtual void repaintDock();
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);
	class QTimer *animationPolling;
protected:
	class QTimer *mousePolling;
	virtual void mouseMoveEventSW(int x,int y,int force=0,int bt=0);
	virtual void purgeCacheMovements();
	virtual void xMakeUp();
	virtual int iconIndexByCoords(int,int);
	virtual void wheelEvent(QWheelEvent *e);
	virtual void mouseReleaseEvent (QMouseEvent *e);
	virtual void mousePressEvent( QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual XQDEIconRect iconCoordsByIndex(int);
	virtual void xMakeCentered();
	virtual void onEnter();
	virtual void onExit();
	virtual void xMakeUp_BackgroundCoords();
	QRegion *maskRaised;
	QRegion *maskNormal;
	QRegion *maskAutoRaise;
	QMutex *cacheBusy;
	int xLastX;
	int xLastY;
	int xLastX_real;
	int xLastY_real;
	int activeIconsCounter;
	int isRaised;
	long SleepFPS;
	int xDesignVirtualEscapeMatrix;

        int lastButtonStatus;
        int hasDragged;
        int isDragging;
        int lastIcon;


/********** Porting from KXDocker OSX Panther engine single pass without CPU *****/
	int xInterpolationValue;

	XQDEIconRect xMakeUp_ArrowCoords;
	XQDEIconRect xMakeUp_Center;
	//int xMakeUp_Separation;
	int xMakeUpIsMirrored;
	//int xMakeUp_Raise;
	int xMakeUp_sizeMatrix;
	//int xMakeUp_MinSize;
	// 2d X Axis displace on mouse over
	int *xMakeUp_XMatrix;
	// 2d Y Axis displace on mouse over
	int *xMakeUp_YMatrix;
	// 2d Zoom on mouse over
	int *xMakeUp_ZMatrix;
	// 3d Dinamic Axis displace on mouse over
	int **xMakeUp_DMatrix;
	// 2d X+ Axis displace on mouse over
	int *xMakeUp_KMatrix;
/********** Porting from KXDocker END *****/
	int topBackgroundSize[2];
	int topBackgroundCoords[2];
	int topCornerCoords[2][2];



	QImage topCorner[2];
	QImage topCornerCached[2];
	QImage topBackground[2];
	QImage topCornerCache[2];
	QImage topBackgroundCached[2];


	virtual void mouseMoveEventSWIcon(int,int,int,XQDEIcon *,int);
	virtual void purgeCacheFixBorder(int ,int &,int &,int &);
	virtual void purgeCacheFixMouse(int ,int &,int &,int &);
	virtual void xMakeCenteredfix(int doResize=0);
public slots:
	void Basket_As_Changed(int,XQDEIcon*,void*);
        void slot_mousePolling();
	void slot_animationPolling();
};


class XQPillow: public XQWidget
{
public:
	XQPillow(QWidget *lRoot, int Align);
	~XQPillow();
	virtual void xRepaint();
	virtual void xReset();
	virtual void xDrawText(const QPixmap *);
	virtual void move(int,int);
protected:
	int m_Align;
	QWidget *m_NearOf;
	int last_kx;
};

#endif
