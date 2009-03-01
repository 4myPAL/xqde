//
// C++ Implementation: xqwfirsthand_bottom
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QMimeData>
#include <QMetaType>
#include "xqwfirsthand_top.h"
#include <xqdeenvironment.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QtDebug>
#include <QMatrix>
#include <xqdeicon.h>
#include <xqdebasket.h>
#include <QObject>
#include <QMouseEvent>
#include <QMutex>
#include <xqde.h>
#include <QPainter>
#include <QRegion>
#include <QTimer>
#include <xqtext.h>
#include <xqdeanimation.h>
#include <xqdeaction.h>

#include <X11/Xlib.h>

XQWFirstHand_top::~XQWFirstHand_top()
{
qWarning("void XQWFirstHand_top::~XQWFirstHand_top()");
}

XQWFirstHand_top::XQWFirstHand_top(QObject *lRoot, QWidget *parent)
 : XQWFirstHand(lRoot, parent)
{
	qWarning("XQWFirstHand_top::XQWFirstHand_top(...)");
	xMakeUpIsMirrored=0;
}


void XQWFirstHand_top::xMakeCenteredfix(int doResize)
{
	qWarning("XQWFirstHand_top::xMakeCenteredfix()");
	if(doResize>0)
	{
		setRect(0+DesktopEnvironment->GUI.dockAlignDisplaceX,
			QApplication::desktop()->availableGeometry().height()-(DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize*2)+DesktopEnvironment->GUI.dockAlignDisplaceY,
			QApplication::desktop()->availableGeometry().width(),
			QApplication::desktop()->availableGeometry().height()
		);
		setFixedSize(QApplication::desktop()->availableGeometry().width(),DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize*2);
	}
	topCornerCached[0]=topCorner[0].scaled(
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	topCornerCached[1]=topCorner[1].scaled(
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	if(true)
	{
		QImage buffer;
		topBackgroundCached[0]=topBackground[0].scaled (
			topBackground[0].width(),
			DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
			Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
		buffer=topBackgroundCached[0].copy();
		XQDE_ImageRepeat(buffer,topBackgroundCached[0],
			QApplication::desktop()->availableGeometry().width()+(DesktopEnvironment->GUI.handIconsMax+2)*4,
			DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2
			
		);
		topBackgroundCached[1]=topBackground[1].scaled (
			topBackground[0].width(),
			DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
			Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
		buffer=topBackgroundCached[1].copy();
		XQDE_ImageRepeat(
			buffer,
			topBackgroundCached[1],
			QApplication::desktop()->availableGeometry().width()+(DesktopEnvironment->GUI.handIconsMax+2)*4,
			DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2
		);
	}
	xMakeUp();
}

void XQWFirstHand_top::xReset()
{
qWarning("void XQWFirstHand_top::xReset()");

	QString imageFileName=DesktopEnvironment->Theme.pathImages+"background-left.png";
	if(!topCorner[0].load(imageFileName))
	{
		topCorner[0]=QImage(1,1,QImage::Format_ARGB32);
		topCorner[0].fill(0x00000000);
		qWarning()<<"XQWFirstHand_top::xReset() Missing: "<<imageFileName;
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"background-right.png";
	if(!topCorner[1].load(imageFileName))
	{
		topCorner[1]=QImage(1,1,QImage::Format_ARGB32);
		topCorner[1].fill(0x00000000);
		qWarning()<<"XQWFirstHand_top::xReset() Missing: "<<imageFileName;
	}

	imageFileName=DesktopEnvironment->Theme.pathImages+"background-center.png";
	if(!topBackground[0].load(imageFileName))
	{
		topBackground[0]=QImage(1,1,QImage::Format_ARGB32);
		topBackground[0].fill(0x00000000);
		qWarning()<<"XQWFirstHand_top::xReset() Missing: "<<imageFileName;
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"background-fg.png";
	if(!topBackground[1].load(imageFileName))
	{
		topBackground[1]=QImage(1,1,QImage::Format_ARGB32);
		topBackground[1].fill(0x00000000);
		qWarning()<<"XQWFirstHand_top::xReset() Missing: "<<imageFileName;
	}


	xMakeCenteredfix(1);

	// Bug fix 20071112
	DesktopEnvironment->GUI.handIconsMax=DesktopEnvironment->GUI.sizeIconsNormal;

	DesktopEnvironment->Theme.Arrow="arrow.png";
	xMakeUp_ArrowCoords.x=0;
	xMakeUp_ArrowCoords.y=DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2;
	xMakeUp_ArrowCoords.z=0;


	qWarning("Hand %dx%d",width(),height());

	XQWFirstHand::xReset();
}

void XQWFirstHand_top::xRepaintSingleBackground(QPainter *pp1_p,int sx,int sy,int sz)
{
	pp1_p->drawImage(
		sx,
		topBackgroundCoords[1],
		topBackgroundCached[0],0,0,
		sz,
		sz+xMakeUp_ArrowSize
		);
}


void XQWFirstHand_top::purgeCacheFixMouse(int iconNum,int &ax,int &ay, int &recallme)
{
	qWarning("void XQWFirstHand_top::purgeCacheFixMouse(%d,%d,%d,%d)",iconNum,ax,ay, recallme);

	if(ay>=(xDesignVirtualEscapeMatrix-(xMakeUp_sizeMatrix*2)))
	{
		ay=(xDesignVirtualEscapeMatrix);
		qWarning("void XQWFirstHand_top::purgeCacheFixMouse(%d,%d,%d,%d) patch",iconNum,ax,ay, recallme);

	}

}
void XQWFirstHand_top::purgeCacheFixBorder(int iconNum,int &ax,int &ay, int &recallme)
{
	qWarning("void XQWFirstHand_top::purgeCacheFixBorder(%d,%d,%d,%d)",iconNum,ax,ay, recallme);
	if(ay<=(xDesignVirtualEscapeMatrix-(xMakeUp_sizeMatrix*2))) // TODO: test
	{
		if(isRaised)
		{
			ay=xLastY-20;
			recallme=1;
		}
		else
		{
			releaseMouse();
			ay=xLastY-20;
			recallme=0;
		}
	}

	if(iconNum<0)
	{
		ax=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x;
		releaseMouse();
		ay=xLastY-2000;
		recallme=0;
	}
	else
	if(iconNum>activeIconsCounter-1)
	{
		ax=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x;
		releaseMouse();
		ay=xLastY-2000;
		recallme=0;
	}
	else
	if(iconNum==0)// adaptive mouse horizontal
	{
		
		if(ax<(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x)
		{
			ax=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x;
		}
	}
	else
	if(iconNum==activeIconsCounter-1)// adaptive mouse horizontal
	{
		if(ax>(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x)
		{
			ax=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x;
		}
	}
	if(iconNum>=0 && iconNum<activeIconsCounter)
	{
		if(ay<0)
		{
		}
		else
		{
		Basket->items.at(iconNum)->overText->xDrawText();
		const QPixmap *pt=Basket->items.at(iconNum)->overText->getPixmap();
		const QRect *br=Basket->items.at(iconNum)->overText->getBoundingRect();
		Global_XQPillow->move(ax-br->width()/2,y()-Global_XQPillow->height());
		Global_XQPillow->xDrawText(pt);
		Global_XQPillow->repaint();
		}
	}
}

void XQWFirstHand_top::xMakeUp_BackgroundCoords()
{
qWarning("void XQWFirstHand_top::xMakeUp_BackgroundCoords()");

	XQDEIcon *thisIcon0=Basket->items.at(0);
	XQDEIcon *thisIcon1=Basket->items.at(activeIconsCounter-1);
	topBackgroundCoords[0]=thisIcon0->imageCachedRect.x;
	topBackgroundCoords[1]=xMakeUp_ArrowCoords.y-xMakeUp_ArrowSize*2;
	topBackgroundSize[0]=thisIcon1->imageCachedRect.x-thisIcon0->imageCachedRect.x+thisIcon1->imageCachedRect.z;
	topBackgroundSize[1]=xMakeUp_ArrowSize*2+DesktopEnvironment->GUI.handIconsMax;

	topCornerCoords[0][0]=topBackgroundCoords[0]-DesktopEnvironment->GUI.handIconsMax-xMakeUp_ArrowSize*2;
	topCornerCoords[0][1]=topBackgroundCoords[1];
	topCornerCoords[1][0]=topBackgroundCoords[0]+topBackgroundSize[0];
	topCornerCoords[1][1]=topBackgroundCoords[1];
}
int XQWFirstHand_top::iconIndexByCoords(int scy,int )
{
	int cy=scy-xMakeUp_Center.x;
	cy=cy-DesktopEnvironment->GUI.handIconsMax;
	cy=cy/DesktopEnvironment->GUI.handIconsMax;
	qWarning("int XQWFirstHand_top::iconIndexByCoords(int,int %d)=%d",scy,cy);
	return cy;
}
void XQWFirstHand_top::mouseMoveEventSWIcon(int tx, int ty,int ,XQDEIcon *icon)
{
	qWarning("mouseMoveEventSWIcon(int %d, int %d,int ,%ld)",tx,ty,(long)icon);

int dx=0;
int dy=0;
int DiffIconX=0;
int DiffIconY=0;
int DiffIcon=0;
int AreMovingToLeft=0;


/****************************************/
dx=icon->imageHotSpot.x-tx;
DiffIconX=abs(dx);
dy=icon->imageHotSpot.y-ty;
DiffIconY=abs(dy);

DiffIcon=DiffIconY+DiffIconX;


if(DiffIcon<xMakeUp_sizeMatrix *2)
{
// left align=invert x<->y
	if(dx>0)
	{
		AreMovingToLeft=xMakeUp_DMatrix[DiffIconX][DiffIconY];
	}
	else
	{
		AreMovingToLeft=-xMakeUp_DMatrix[DiffIconX][DiffIconY];
	}

// left align=invert x<->y
		icon->imageCachedRect.y=
			icon->iconGeometry.y
			-xMakeUp_YMatrix[DiffIcon];
		icon->imageCachedRect.x=
			icon->iconGeometry.x
			-xMakeUp_XMatrix[DiffIcon]+AreMovingToLeft;
		icon->imageCachedRect.z=xMakeUp_ZMatrix[DiffIcon];
		icon->xSetZoom(icon->imageCachedRect.z);
		isRaised=1;
		if(icon->detachedRect.z)icon->xRepaintDetached();
}
else
{
	if(DiffIconY>=xMakeUp_sizeMatrix*2)
	{
		DiffIconY=xMakeUp_sizeMatrix*2-1;
		// all hotspot are =y
		// than if you are too away from 1 icon all icons are restored
	}
	// left x<->y
	if(dx>0)
	{
		AreMovingToLeft=xMakeUp_KMatrix[DiffIconY];
	}
	else
	{
		AreMovingToLeft=-xMakeUp_KMatrix[DiffIconY];
	}
		icon->imageCachedRect.y=
			icon->iconGeometry.y
			;
		icon->imageCachedRect.x=(
			icon->iconGeometry.x)+AreMovingToLeft;
		icon->imageCachedRect.z=DesktopEnvironment->GUI.handIconsMax;
		//icon->imageCached=icon->imageCachedMini;
		//icon->imageHotSpot.z=icon->imageCachedRect.z;
		//icon->xSetZoom(DesktopEnvironment->GUI.handIconsMax);
		icon->xSetZoom(icon->imageCachedRect.z);
		if(icon->detachedRect.z)icon->xRepaintDetached();
}

		icon->imageCachedArrowRect.x=icon->imageCachedRect.x+icon->imageCachedRect.z/2-DesktopEnvironment->GUI.handIconsMax/2;
		icon->imageCachedArrowRect.y=xMakeUp_ArrowCoords.y;
}


XQDEIconRect XQWFirstHand_top::iconCoordsByIndex(int c)
{
	qWarning("XQWFirstHand_top::iconCoordsByIndex(%d)",c);

	XQDEIconRect r;
	r.y=xMakeUp_Center.y;
	r.x=DesktopEnvironment->GUI.handIconsMax+c*DesktopEnvironment->GUI.handIconsMax+xMakeUp_Center.x;
	r.z=DesktopEnvironment->GUI.handIconsMax;
	return r;
}

void XQWFirstHand_top::xMakeCentered()
{
qWarning("void XQWFirstHand_top::xMakeCentered()");
	xMakeUp_Center.x=0;
	xMakeUp_Center.y=0;
	xMakeUp_Center.z=0;

	int oldHandSizeIconMax=DesktopEnvironment->GUI.handIconsMax;

	int xMakeUp_MinSize=0;

	if(activeIconsCounter>0)
	{
		xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
		if(xMakeUp_MinSize>height())
		{
			for(;DesktopEnvironment->GUI.handIconsMax>15;DesktopEnvironment->GUI.handIconsMax-=4)
			{
	xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
	if(xMakeUp_MinSize<width())break;
			}
			//qWarning("Docker will be resized!!-from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);
			//xMakeCenteredfix();
		}
		else
		{
			if(DesktopEnvironment->GUI.sizeIconsNormal>DesktopEnvironment->GUI.handIconsMax)
			{
				for(;DesktopEnvironment->GUI.handIconsMax<=DesktopEnvironment->GUI.sizeIconsNormal;DesktopEnvironment->GUI.handIconsMax+=4)
				{
		xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
		if(xMakeUp_MinSize>=width())break;
				}
				//qWarning("Docker will be resized!!+from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);

			}
		}
		
	}

	xMakeUp_Center.x=(width()-xMakeUp_MinSize-iconCoordsByIndex(0).x)/2;
	xMakeUp_Center.y=height()-xMakeUp_ArrowSize-DesktopEnvironment->GUI.handIconsMax;

delete maskRaised;
delete maskNormal;
delete maskAutoRaise;

maskRaised=new QRegion(rect());
maskNormal=new QRegion(
	xMakeUp_Center.x,
	iconCoordsByIndex(0).y,
	iconCoordsByIndex(activeIconsCounter).x-iconCoordsByIndex(0).x+DesktopEnvironment->GUI.handIconsMax,
	DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2
	);

maskAutoRaise=new QRegion(
	iconCoordsByIndex(0).x,
	height()-1,
	iconCoordsByIndex(activeIconsCounter).x,
	height()
	);


	if(oldHandSizeIconMax!=DesktopEnvironment->GUI.handIconsMax)xMakeCenteredfix();


	qWarning("Dock %d need: %d [%dx%d](%d-%d)=%d",activeIconsCounter,xMakeUp_MinSize,xMakeUp_Center.x,xMakeUp_Center.y,iconCoordsByIndex(activeIconsCounter-1).y,iconCoordsByIndex(0).y,xMakeUp_Center.y);


	for(int i=0;i<activeIconsCounter;i++)
	{
		XQDEIconRect r=iconCoordsByIndex(i);
		Basket->items.at(i)->setIconGeometry(r.x,r.y,r.z);
		//Basket->items.at(i)->xRepaintSmall();
	}
	mouseMoveEventSW(xLastX,xLastY,1);
	//xRepaint();
	repaintDock();
}
