//
// C++ Implementation: xqwfirsthand_left
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
#include "xqwfirsthand_right.h"
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

XQWFirstHand_right::~XQWFirstHand_right()
{
}

XQWFirstHand_right::XQWFirstHand_right(QObject *lRoot, QWidget *parent)
 : XQWFirstHand(lRoot, parent)
{
	//qWarning("XQWFirstHand_right::XQWFirstHand_right(...)");
	xMakeUpIsMirrored=0;

}


void XQWFirstHand_right::xMakeCenteredfix(int doResize)
{
	//qWarning("XQWFirstHand_right::xReset()");
	if(doResize>0)
	{
	const int wsize=DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize*2;
	const int hsize=QApplication::desktop()->availableGeometry().height();
	const int sxc=QApplication::desktop()->availableGeometry().width()-(wsize);
	const int syc=0;
	setRect(sxc+DesktopEnvironment->GUI.dockAlignDisplaceX,syc+DesktopEnvironment->GUI.dockAlignDisplaceY,QApplication::desktop()->availableGeometry().width(),hsize);
	setFixedSize(wsize,hsize);
	setPos(sxc+DesktopEnvironment->GUI.dockAlignDisplaceX,syc+DesktopEnvironment->GUI.dockAlignDisplaceY);

qWarning("Displace:[%d][%d]",DesktopEnvironment->GUI.dockAlignDisplaceX,DesktopEnvironment->GUI.dockAlignDisplaceY);

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
	DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
	topBackground[0].height(),
	Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
buffer=topBackgroundCached[0].copy();
XQDE_ImageRepeat(buffer,topBackgroundCached[0],
	DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
	QApplication::desktop()->availableGeometry().height()
	+(DesktopEnvironment->GUI.handIconsMax+2)*4
	);

topBackgroundCached[1]=topBackground[1].scaled (DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,topBackground[0].height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
buffer=topBackgroundCached[1].copy();
XQDE_ImageRepeat(
buffer,
topBackgroundCached[1],
DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
QApplication::desktop()->availableGeometry().height()
+(DesktopEnvironment->GUI.handIconsMax+2)*4
);
	}

	xMakeUp();
}

void XQWFirstHand_right::xReset()
{


	QString imageFileName=DesktopEnvironment->Theme.pathImages+"right/background-left.png";
	if(!topCorner[0].load(imageFileName))
	{
		topCorner[0]=QImage(1,1,QImage::Format_ARGB32);
		topCorner[0].fill(0x00000000);
		//qWarning()<<"XQWFirstHand_right::xReset() Missing: "<<imageFileName;
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"right/background-right.png";
	if(!topCorner[1].load(imageFileName))
	{
		topCorner[1]=QImage(1,1,QImage::Format_ARGB32);
		topCorner[1].fill(0x00000000);
		//qWarning()<<"XQWFirstHand_right::xReset() Missing: "<<imageFileName;
	}

	imageFileName=DesktopEnvironment->Theme.pathImages+"right/background-center.png";
	if(!topBackground[0].load(imageFileName))
	{
		topBackground[0]=QImage(1,1,QImage::Format_ARGB32);
		topBackground[0].fill(0x00000000);
		//qWarning()<<"XQWFirstHand_right::xReset() Missing: "<<imageFileName;
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"right/background-fg.png";
	if(!topBackground[1].load(imageFileName))
	{
		topBackground[1]=QImage(1,1,QImage::Format_ARGB32);
		topBackground[1].fill(0x00000000);
		//qWarning()<<"XQWFirstHand_right::xReset() Missing: "<<imageFileName;
	}


	xMakeCenteredfix(1);
	// Bug fix 20071112
	DesktopEnvironment->GUI.handIconsMax=DesktopEnvironment->GUI.sizeIconsNormal;


	DesktopEnvironment->Theme.Arrow="right/arrow.png";
	xMakeUp_ArrowCoords.x=DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2;
	xMakeUp_ArrowCoords.y=0;
	xMakeUp_ArrowCoords.z=0;


	//qWarning("Hand %dx%d",width(),height());

	XQWFirstHand::xReset();
}

void XQWFirstHand_right::xRepaintSingleBackground(QPainter *pp1_p,int sx,int sy,int sz)
{
	pp1_p->drawImage(
		topBackgroundCoords[0],
		sy,
		topBackgroundCached[0],0,0,
		sz+xMakeUp_ArrowSize,
		sz
		);
}


void XQWFirstHand_right::purgeCacheFixMouse(int ,int &ax,int &, int &)
{
	//qWarning("void XQWFirstHand_right::purgeCacheFixMouse(%d,%d,%d,%d)",iconNum,ax,ay, recallme);
	//if(ax>=(xDesignVirtualEscapeMatrix-(xMakeUp_sizeMatrix*2)))
	if(ax>0)
	{
		ax=xDesignVirtualEscapeMatrix;
	}
}
void XQWFirstHand_right::purgeCacheFixBorder(int iconNum,int &ax,int &ay, int &recallme)
{
	//if(ax<=(xDesignVirtualEscapeMatrix-(xMakeUp_sizeMatrix*2)))
	if(ax<=0)
	{
		if(isRaised)
		{
			ax=xLastX-20;
			recallme=1;
		}
		else
		{
			ax=xLastX-20;
			releaseMouse();
			recallme=0;
		}
		return;
	}

	if(iconNum<0)
	{
		ay=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).y;
		releaseMouse();
		ax=xLastX-2000;
		recallme=0;
	}
	else
	if(iconNum>activeIconsCounter)// bug 20071112 wrong exit on last icon
	{
		ay=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).y;
		releaseMouse();
		ax=xLastX-2000;
		recallme=0;
	}
	else
	if(iconNum==0)// adaptive mouse horizontal
	{
		
		if(ay<(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).y)
		{
			ay=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).y;
		}
	}
	else
	if(iconNum>=activeIconsCounter-1)// bug 20071112 wrong exit on last icon
	{
		/*
		if(ay>xDesignVirtualEscapeMatrix+iconCoordsByIndex(activeIconsCounter-1).y)
		{
			ay=xDesignVirtualEscapeMatrix+iconCoordsByIndex(activeIconsCounter-1).y;
		}
		*/
		if(ay>(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).y)
		{
			ay=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).y;
		}
	}
	if(iconNum>=0 && iconNum<activeIconsCounter)
	{
		if(ax<0)
		{
		}
		else
		{
		Basket->items.at(iconNum)->overText->xDrawText();
		const QPixmap *pt=Basket->items.at(iconNum)->overText->getPixmap();
		const QRect *br=Basket->items.at(iconNum)->overText->getBoundingRect();
		Global_XQPillow->move(x()-br->width(),ay-br->height()/2);
		Global_XQPillow->xDrawText(pt);
		Global_XQPillow->repaint();
		}
	}
}

void XQWFirstHand_right::xMakeUp_BackgroundCoords()
{
	XQDEIcon *thisIcon0=Basket->items.at(0);
	XQDEIcon *thisIcon1=Basket->items.at(activeIconsCounter-1);
	topBackgroundCoords[0]=xMakeUp_ArrowCoords.x-xMakeUp_ArrowSize*2;
	topBackgroundCoords[1]=thisIcon0->imageCachedRect.y;
	topBackgroundSize[0]=xMakeUp_ArrowSize*2+DesktopEnvironment->GUI.handIconsMax;
	topBackgroundSize[1]=thisIcon1->imageCachedRect.y-thisIcon0->imageCachedRect.y+thisIcon1->imageCachedRect.z;

	topCornerCoords[0][0]=topBackgroundCoords[0];
	topCornerCoords[0][1]=topBackgroundCoords[1]-topBackgroundSize[0];
	topCornerCoords[1][0]=topBackgroundCoords[0];
	topCornerCoords[1][1]=topBackgroundCoords[1]+topBackgroundSize[1];
}
int XQWFirstHand_right::iconIndexByCoords(int,int scy)
{
	int cy=scy-xMakeUp_Center.y;
	cy=cy-DesktopEnvironment->GUI.handIconsMax;
	cy=cy/DesktopEnvironment->GUI.handIconsMax;
	//qWarning("int XQWFirstHand_right::iconIndexByCoords(int,int %d)=%d",scy,cy);
	return cy;
}
void XQWFirstHand_right::mouseMoveEventSWIcon(int tx, int ty,int ,XQDEIcon *icon)
{

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
	if(dy>0)
	{
		AreMovingToLeft=xMakeUp_DMatrix[DiffIconY][DiffIconX];
	}
	else
	{
		AreMovingToLeft=-xMakeUp_DMatrix[DiffIconY][DiffIconX];
	}

// left align=invert x<->y
		icon->imageCachedRect.y=
			icon->iconGeometry.y
			- xMakeUp_XMatrix[DiffIcon]+AreMovingToLeft;
		icon->imageCachedRect.x=(
			icon->iconGeometry.x
			-xMakeUp_YMatrix[DiffIcon]);
		icon->imageCachedRect.z=xMakeUp_ZMatrix[DiffIcon];
		icon->xSetZoom(icon->imageCachedRect.z);
		isRaised=1;
		if(icon->detachedRect.z)icon->xRepaintDetached();
}
else
{
	if(DiffIconX>=xMakeUp_sizeMatrix*2)
	{
		DiffIconX=xMakeUp_sizeMatrix*2-1;
		// all hotspot are =y
		// than if you are too away from 1 icon all icons are restored
	}
	// left x<->y
	if(dy>0)
	{
		AreMovingToLeft=xMakeUp_KMatrix[DiffIconX];
	}
	else
	{
		AreMovingToLeft=-xMakeUp_KMatrix[DiffIconX];
	}
		icon->imageCachedRect.y=
			icon->iconGeometry.y
			+AreMovingToLeft;
		icon->imageCachedRect.x=(
			icon->iconGeometry.x);
		icon->imageCachedRect.z=DesktopEnvironment->GUI.handIconsMax;
		icon->xSetZoom(icon->imageCachedRect.z);
		if(icon->detachedRect.z)icon->xRepaintDetached();
}

		icon->imageCachedArrowRect.x=xMakeUp_ArrowCoords.x;
		icon->imageCachedArrowRect.y=icon->imageCachedRect.y+icon->imageCachedRect.z/2-DesktopEnvironment->GUI.handIconsMax/2;
}


XQDEIconRect XQWFirstHand_right::iconCoordsByIndex(int c)
{
	XQDEIconRect r;
	r.x=xMakeUp_Center.x;
	r.y=DesktopEnvironment->GUI.handIconsMax+c*DesktopEnvironment->GUI.handIconsMax+xMakeUp_Center.y;
	r.z=DesktopEnvironment->GUI.handIconsMax;
	return r;
}

void XQWFirstHand_right::xMakeCentered()
{
	xMakeUp_Center.x=0;
	xMakeUp_Center.y=0;
	xMakeUp_Center.z=0;

	int oldHandSizeIconMax=DesktopEnvironment->GUI.handIconsMax;

	int xMakeUp_MinSize=0;
	if(activeIconsCounter>0)
	{
		xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).y-iconCoordsByIndex(0).y;
		if(xMakeUp_MinSize>height())
		{
			for(;DesktopEnvironment->GUI.handIconsMax>15;DesktopEnvironment->GUI.handIconsMax-=4)
			{
	xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).y-iconCoordsByIndex(0).y;
	if(xMakeUp_MinSize<height())break;
			}
			//qWarning("Docker will be resized!!-from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);
			//xMakeCenteredfix();
		}
		else
		{
			if(DesktopEnvironment->GUI.sizeIconsNormal>DesktopEnvironment->GUI.handIconsMax)
			{
				for(;DesktopEnvironment->GUI.handIconsMax<DesktopEnvironment->GUI.sizeIconsNormal;DesktopEnvironment->GUI.handIconsMax+=4)
				{
		xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).y-iconCoordsByIndex(0).y;
		if(xMakeUp_MinSize>=height())break;
				}
				//qWarning("Docker will be resized!!+from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);

			}
		}
		
	}

	xMakeUp_Center.x=(width()-xMakeUp_ArrowSize-DesktopEnvironment->GUI.handIconsMax);
	xMakeUp_Center.y=(height()-xMakeUp_MinSize-iconCoordsByIndex(0).y)/2;

delete maskRaised;
delete maskNormal;
delete maskAutoRaise;

maskRaised=new QRegion(rect());
maskNormal=new QRegion(xMakeUp_Center.x,iconCoordsByIndex( 0).y,DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,iconCoordsByIndex(activeIconsCounter).y-iconCoordsByIndex( 0).y);

	/*
maskAutoRaise=new QRegion(
	xMakeUp_Center.x,
	iconCoordsByIndex(0).y,
	1,
	iconCoordsByIndex(activeIconsCounter).y-iconCoordsByIndex(0).y
	);
	*/

	// bug 20071112 right mode wont raise
maskAutoRaise=new QRegion(
	width()-1,
	iconCoordsByIndex(0).y,
	width(),
	iconCoordsByIndex(activeIconsCounter+1).y
	);	


	if(oldHandSizeIconMax!=DesktopEnvironment->GUI.handIconsMax)xMakeCenteredfix();


	//qWarning("Dock %d need: %d [%dx%d](%d-%d)=%d",activeIconsCounter,xMakeUp_MinSize,xMakeUp_Center.x,xMakeUp_Center.y,
//			iconCoordsByIndex(activeIconsCounter-1).y,iconCoordsByIndex(0).y,xMakeUp_Center.y);


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
