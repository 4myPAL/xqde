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
#include <QApplication>
#include <QDesktopWidget>
#include <QtDebug>
#include <QMatrix>
#include <QObject>
#include <QMouseEvent>
#include <QMutex>
#include <QPainter>
#include <QRegion>
#include <QTimer>

#include "xqwfirsthand_bottom.h"
#include "xqdeenvironment.h"
#include "xqdeicon.h"
#include "xqdebasket.h"
#include "xqtext.h"
#include "xqde.h"
#include "xqdeanimation.h"
#include "xqdeaction.h"

//#include <X11/Xlib.h>


XQWFirstHand_bottom::XQWFirstHand_bottom(QObject *lRoot, QWidget *parent)
 : XQWFirstHand(lRoot, parent)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("XQWFirstHand_bottom::XQWFirstHand_bottom(...)");
		#endif
        xMakeUpIsMirrored=0;
}

XQWFirstHand_bottom::~XQWFirstHand_bottom()
{
	#ifdef ENABLEDEBUGMSG
qWarning("void XQWFirstHand_bottom::~XQWFirstHand_bottom()");
		#endif
}

void XQWFirstHand_bottom::xRepaintSingleBackground(QPainter *pp1_p,int sx,int sy,int sz)
{
	pp1_p->drawImage(
		sx,
                topBackgroundCoords[1],
                topBackgroundCached[0],
                0,
                0,
		sz,
                sz+xMakeUp_ArrowSize
		);
}


void XQWFirstHand_bottom::xMakeCenteredfix(int doResize)
{
#ifdef ENABLEDEBUGMSG
qWarning("XQWFirstHand_bottom::xMakeCenteredfix(%d)",doResize);
qWarning("Screen about:");	
qWarning("W:%d",QApplication::desktop()->availableGeometry().width());	
qWarning("H:%d",QApplication::desktop()->availableGeometry().height());	
qWarning("T:%d",QApplication::desktop()->availableGeometry().top());	
qWarning("L:%d",QApplication::desktop()->availableGeometry().left());	
qWarning("AX:%d",DesktopEnvironment->GUI.dockAlignDisplaceX);
qWarning("AY:%d",DesktopEnvironment->GUI.dockAlignDisplaceY);
qWarning("Max:%ld",DesktopEnvironment->GUI.sizeIconsMax);
qWarning("Arrow:%d",xMakeUp_ArrowSize);
#endif
	
	if(doResize>0)
	{
		// TODO: patch for other align
		/*
		setRect(
			0+DesktopEnvironment->GUI.dockAlignDisplaceX,
			QApplication::desktop()->availableGeometry().height()-(DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize*2)
			+DesktopEnvironment->GUI.dockAlignDisplaceY,
			QApplication::desktop()->availableGeometry().width()
			+QApplication::desktop()->availableGeometry().left()
			,
			QApplication::desktop()->availableGeometry().height()
			+QApplication::desktop()->availableGeometry().top()
		);
		*/
                int myHeight = (DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize);
                int myWidth  = (activeIconsCounter+1)*DesktopEnvironment->GUI.handIconsMax*2;
                setRect(DesktopEnvironment->GUI.dockAlignDisplaceX,
                        QApplication::desktop()->availableGeometry().bottom() - myHeight+DesktopEnvironment->GUI.dockAlignDisplaceY,
                        QApplication::desktop()->availableGeometry().width()  + QApplication::desktop()->availableGeometry().left(),
                        QApplication::desktop()->availableGeometry().bottom() + DesktopEnvironment->GUI.dockAlignDisplaceY
                );
//                qWarning("W: %d, H: %d", myWidth, myHeight);
//                setFixedSize(myWidth, myHeight);
//                move(QApplication::desktop()->geometry().center().x() - myWidth/2, QApplication::desktop()->availableGeometry().bottom() - myHeight+DesktopEnvironment->GUI.dockAlignDisplaceY);

	}
                #ifdef ENABLEDEBUGMSG
		qWarning("%dx%d", width(),height());
                #endif
	topCornerCached[0]=topCorner[0].scaled(
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	topCornerCached[1]=topCorner[1].scaled(
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QImage buffer;
        topBackgroundCached[0]=topBackground[0].scaled (
                topBackground[0].width(),
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

        buffer=topBackgroundCached[0].copy();

        XQDE_ImageRepeat(buffer,topBackgroundCached[0],
                QApplication::desktop()->availableGeometry().width()+(DesktopEnvironment->GUI.handIconsMax+2)*4,
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2 );

        topBackgroundCached[1]=topBackground[1].scaled (
                topBackground[0].width(),
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

        buffer=topBackgroundCached[1].copy();

        XQDE_ImageRepeat(buffer,topBackgroundCached[1],
                QApplication::desktop()->availableGeometry().width()+(DesktopEnvironment->GUI.handIconsMax+2)*4,
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2 );

        xMakeUp();
}

void XQWFirstHand_bottom::xReset()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand_bottom::xReset()");
		#endif
	

	QString imageFileName=DesktopEnvironment->Theme.pathImages+"background-left.png";

	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand_bottom::xReset() loading: %s",imageFileName.toUtf8().constData());
		#endif

	if(!topCorner[0].load(imageFileName))
	{
		topCorner[0]=QImage(1,1,QImage::Format_ARGB32);
                topCorner[0].fill(Qt::transparent);
		
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"background-right.png";
	if(!topCorner[1].load(imageFileName))
	{
		topCorner[1]=QImage(1,1,QImage::Format_ARGB32);
                topCorner[1].fill(Qt::transparent);
	}

	imageFileName=DesktopEnvironment->Theme.pathImages+"background-center.png";
	if(!topBackground[0].load(imageFileName))
	{
		topBackground[0]=QImage(1,1,QImage::Format_ARGB32);
                topBackground[0].fill(Qt::transparent);
	}
	imageFileName=DesktopEnvironment->Theme.pathImages+"background-fg.png";
	if(!topBackground[1].load(imageFileName))
	{
		topBackground[1]=QImage(1,1,QImage::Format_ARGB32);
                topBackground[1].fill(Qt::transparent);
	}

        //xMakeCentered();
        xMakeCenteredfix(1);


	DesktopEnvironment->Theme.Arrow="arrow.png";
	
	// Bug Fix 20071116
	if(DesktopEnvironment->GUI.sizeIconsMax < DesktopEnvironment->GUI.sizeIconsNormal)
	{
		DesktopEnvironment->GUI.sizeIconsMax = DesktopEnvironment->GUI.sizeIconsNormal;
	}
	
	
	// Bug fix 20071112
	DesktopEnvironment->GUI.handIconsMax = DesktopEnvironment->GUI.sizeIconsNormal;



	// Bug Fix 20071115
	xMakeUp_ArrowCoords.x=0;
	xMakeUp_ArrowCoords.y=DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax;
	//xMakeUp_ArrowCoords.y=0;
	xMakeUp_ArrowCoords.z=0;

	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand_bottom::xReset() %dx%d MAX:%ld Min:%ld",width(),height(), DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.handIconsMax);
	#endif


	XQWFirstHand::xReset();
}


void XQWFirstHand_bottom::purgeCacheFixMouse(int ,int &cursor_x,int &cursor_y, int &)
{
	#ifdef ENABLEDEBUGMSG
        qWarning("void XQWFirstHand_bottom::purgeCacheFixMouse(,,%d,)",cursor_y);
        #endif
	// bug 20071116
        //manitiene lo zoom quando mouse si sposta verticalmente
       if(cursor_y >= 0)
        {
              cursor_y = xDesignVirtualEscapeMatrix;
        #ifdef ENABLEDEBUGMSG
                qWarning("void XQWFirstHand_bottom::purgeCacheFixMouse(,,%d,) b",cursor_y);
        #endif

        }

}


void XQWFirstHand_bottom::purgeCacheFixBorder(int iconNum,int &cursor_x,int &cursor_y, int &recallme)
{
	//int kky=(xDesignVirtualEscapeMatrix-(xMakeUp_sizeMatrix*2));
        //Removed (21.02.09)
        //int kky=(0);
	#ifdef ENABLEDEBUGMSG
        qWarning("void XQWFirstHand_bottom::purgeCacheFixBorder(%d,%d,%d,%d) ay<=%d %d",iconNum,cursor_x,cursor_y, recallme ,xDesignVirtualEscapeMatrix,xMakeUp_sizeMatrix);
		#endif

        /*if(cursor_y<=kky)*/ // TODO: test
        //Bug Solved (21.02.09): smooth dock con mouse in uscita x e y dock
        if(!maskNormal->contains(QPoint(cursor_x,cursor_y)))
	{
            //Improvement (22.02.09): con (DesktopEnvironment->GUI.handIconsMax/4) ottengo l'effetto gradevole di rimpicciolimento in funzione
            //della altezza della dock
		if(isRaised)
		{
                        cursor_y=xLastY-(DesktopEnvironment->GUI.handIconsMax/4); //-20
			recallme=1;
		}
		else
		{
			releaseMouse();
                        cursor_y=xLastY-(DesktopEnvironment->GUI.handIconsMax/4);
			recallme=0;                        
		}
                
                //Bug Solved (22.02.09): now dock is always on center
                //blocco movimento dock quando arrivo a metà della prima o ultima icona
                if(iconNum<0) 
                {
                    cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x;
                }
                
                else if(iconNum>activeIconsCounter)
                {
                    cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x;
                }
                
                #ifdef ENABLEDEBUGMSG
		qWarning("return");
		#endif
		return;
	}

        // Removed (21.02.09)
//	if(iconNum<0)
//	{
//		cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x;
//		releaseMouse();
//		cursor_y=xLastY-2000;
//		recallme=0;
//	}
//	else
//	if(iconNum>activeIconsCounter)
//	{
//		cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x;
//		releaseMouse();
//		cursor_y=xLastY-2000;
//		recallme=0;
//	}
//	else
	if(iconNum<=0)// adaptive mouse horizontal
	{
		
		if(cursor_x<(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x)
		{
			cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(0).x;
		}
	}
	else
	if(iconNum>=activeIconsCounter-1)// adaptive mouse horizontal
	{
		if(cursor_x>(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x)
		{
			cursor_x=(DesktopEnvironment->GUI.handIconsMax/2)+iconCoordsByIndex(activeIconsCounter-1).x;
		}
	}
	
        // Mostra testo sopra icona selezionata (iconNum)
	if(iconNum>=0 && iconNum<activeIconsCounter)
	{
//Removed: (21.02.09)
//		if(cursor_y<0)
//		{
//		}
//		else
//		{

                //BUG solved!! 19.03.09
                //il testo non è al centro sopra l'icona

                // Prepare Pixmap with the text
                Basket->items.at(iconNum)->overText->xDrawText();
                const QPixmap *textPixmap=Basket->items.at(iconNum)->overText->getPixmap();
                const QRect *textRect=Basket->items.at(iconNum)->overText->getBoundingRect();

                Global_XQPillow->move((DesktopEnvironment->GUI.dockAlignDisplaceX + (Basket->items.at(iconNum)->imageHotSpot.x)) - (textRect->width()/2)
                                      ,y()-Global_XQPillow->height());

                //qWarning("Deplacement x: %d  y:%d", (DesktopEnvironment->GUI.dockAlignDisplaceX + (Basket->items.at(iconNum)->imageHotSpot.x)) - (textRect->width()/2), y()-Global_XQPillow->height());

//                qWarning("width:%d ; h%d", textPixmap->size().width(), textPixmap->size().height());
                Global_XQPillow->xDrawText(textPixmap);
                Global_XQPillow->repaint();
                Global_XQPillow->setVisible(true);
//		}
	}
}

void XQWFirstHand_bottom::xMakeUp_BackgroundCoords()
{
	#ifdef ENABLEDEBUGMSG
        qWarning("void XQWFirstHand_bottom::xMakeUp_BackgroundCoords()");
        #endif

        XQDEIcon *IconFirst=Basket->items.at(0);
        XQDEIcon *IconLast=Basket->items.at(activeIconsCounter-1);
        topBackgroundCoords[0]=IconFirst->imageCachedRect.x;
	topBackgroundCoords[1]=xMakeUp_ArrowCoords.y-xMakeUp_ArrowSize;
        topBackgroundSize[0]=IconLast->imageCachedRect.x-IconFirst->imageCachedRect.x+IconLast->imageCachedRect.z;
	topBackgroundSize[1]=xMakeUp_ArrowSize*2+DesktopEnvironment->GUI.handIconsMax;

	topCornerCoords[0][0]=topBackgroundCoords[0]-DesktopEnvironment->GUI.handIconsMax-xMakeUp_ArrowSize*2;
	topCornerCoords[0][1]=topBackgroundCoords[1];
	topCornerCoords[1][0]=topBackgroundCoords[0]+topBackgroundSize[0];
	topCornerCoords[1][1]=topBackgroundCoords[1];
}

void XQWFirstHand_bottom::mouseMoveEventSWIcon(int tx, int ty,int ,XQDEIcon *icon,int quality)
{
	//qWarning("mouseMoveEventSWIcon(int %d, int %d,int ,%d)",tx,ty,(int)icon);

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
    //qWarning("%d %d %d %d %d",DiffIcon,DiffIconX,DiffIconY, icon->imageHotSpot.y, xDesignVirtualEscapeMatrix);


    if(DiffIcon < xMakeUp_sizeMatrix *2)
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
            icon->imageCachedRect.y = icon->iconGeometry.y - xMakeUp_YMatrix[DiffIcon];
            icon->imageCachedRect.x = icon->iconGeometry.x - xMakeUp_XMatrix[DiffIcon] + AreMovingToLeft;
            icon->imageCachedRect.z = xMakeUp_ZMatrix[DiffIcon];
//            qWarning("%d %d %d",DiffIcon,xMakeUp_ZMatrix[DiffIcon],icon->imageCachedRect.z);
            if(quality==0)
            {
                    icon->xSetZoom(icon->imageCachedRect.z);
            }
            else
            {
//                    icon->imageHotSpot.z=0;
                    icon->xSetSmoothZoom(icon->imageCachedRect.z);
            }

            isRaised=1;
            if(icon->detachedRect.z) icon->xRepaintDetached();
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
                    AreMovingToLeft = xMakeUp_KMatrix[DiffIconY];
                }
            else
                {
                    AreMovingToLeft = -xMakeUp_KMatrix[DiffIconY];
                }
            
            icon->imageCachedRect.y = icon->iconGeometry.y;
            icon->imageCachedRect.x = (icon->iconGeometry.x)+AreMovingToLeft;
            icon->imageCachedRect.z = DesktopEnvironment->GUI.handIconsMax;
            //icon->imageCached=icon->imageCachedMini;
            //icon->imageHotSpot.z=icon->imageCachedRect.z;
            //icon->xSetZoom(DesktopEnvironment->GUI.handIconsMax);
            icon->xSetZoom(icon->imageCachedRect.z);
            if(icon->detachedRect.z) icon->xRepaintDetached();
        }

    icon->imageCachedArrowRect.x=icon->imageCachedRect.x+icon->imageCachedRect.z/2-DesktopEnvironment->GUI.handIconsMax/2-xMakeUp_ArrowSize/2;
    icon->imageCachedArrowRect.y=xMakeUp_ArrowCoords.y;
}


XQDEIconRect XQWFirstHand_bottom::iconCoordsByIndex(int c)
{
	//qWarning("XQWFirstHand_bottom::iconCoordsByIndex(%d)",c);

	XQDEIconRect r;
	r.y=xMakeUp_Center.y;
	r.x=DesktopEnvironment->GUI.handIconsMax+c*DesktopEnvironment->GUI.handIconsMax+xMakeUp_Center.x;
        r.z=DesktopEnvironment->GUI.handIconsMax;
	return r;
}

int XQWFirstHand_bottom::iconIndexByCoords(int cursor_x, int cursor_y)
{
        //return the icon where the mouse is over
        int iconIndexX = cursor_x - xMakeUp_Center.x;
        iconIndexX = iconIndexX - DesktopEnvironment->GUI.handIconsMax;
        iconIndexX = iconIndexX / DesktopEnvironment->GUI.handIconsMax;
        //qWarning("int XQWFirstHand_bottom::iconIndexByCoords(int,int %d)=%d",scy,cy);
        return iconIndexX;
}



void XQWFirstHand_bottom::xMakeCentered()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand_bottom::xMakeCentered()");
		#endif
	xMakeUp_Center.x=0;
	xMakeUp_Center.y=0;
	xMakeUp_Center.z=0;

	int oldHandSizeIconMax=DesktopEnvironment->GUI.handIconsMax;

	int xMakeUp_MinSize=0;

	if(activeIconsCounter>0)
	{
		xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
                #ifdef ENABLEDEBUGMSG
		qWarning("void XQWFirstHand_bottom::xMakeCentered() xMakeUp_MinSize=%d height=%d width=%d",xMakeUp_MinSize,height(), width());
		#endif
		
                if(xMakeUp_MinSize > width())
		{
                        for(;DesktopEnvironment->GUI.handIconsMax > 15;DesktopEnvironment->GUI.handIconsMax -= 4)
			{
				xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
				if(xMakeUp_MinSize < width())break;
			}
                        #ifdef ENABLEDEBUGMSG
                        qWarning("Docker will be resized (1)!!-from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);
                        #endif
		}
                else if (DesktopEnvironment->GUI.sizeIconsNormal > DesktopEnvironment->GUI.handIconsMax)
		{
//Removed (22.02.09)
//                        #ifdef ENABLEDEBUGMSG
//			qWarning("sizeIconsNormal=%d handIconsMax=%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);
//                        #endif
//			if(DesktopEnvironment->GUI.sizeIconsNormal > DesktopEnvironment->GUI.handIconsMax)
//			{

                        for(;DesktopEnvironment->GUI.handIconsMax < DesktopEnvironment->GUI.sizeIconsNormal; DesktopEnvironment->GUI.handIconsMax += 4)
                        {
                                xMakeUp_MinSize=iconCoordsByIndex(activeIconsCounter+1).x-iconCoordsByIndex(0).x;
                                if(xMakeUp_MinSize >= width())break;
                        }
                        #ifdef ENABLEDEBUGMSG
                        qWarning("Docker will be resized (2)!!+from:%d to:%d",DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.handIconsMax);
                        #endif

			//exit(1);

//			}
		}
		
	}
        
        //Bug Fix: se più grande dello schermo fa il resize, ma poi se si aggiunge widget lo ridimensiona con dimensioni "normali"
        //Now autoresize work correctly (25.04.09)
        //Other Bug: la dock si rimpicciolisce ma non si espande più
        //questo è succede perchè la funzione "DesktopEnvironment->GUI.sizeIconsNormal > DesktopEnvironment->GUI.handIconsMax"
        //non è mai soddisfatta
        DesktopEnvironment->GUI.sizeIconsNormal = DesktopEnvironment->GUI.handIconsMax;


        //New coordinate x and y for the dock
	xMakeUp_Center.x=(width()-xMakeUp_MinSize-iconCoordsByIndex(0).x)/2;
        xMakeUp_Center.y=height()-xMakeUp_ArrowSize-DesktopEnvironment->GUI.handIconsMax;

        delete maskRaised;
        delete maskNormal;
        delete maskAutoRaise;

        maskRaised=new QRegion(rect());

        maskNormal=new QRegion(
                xMakeUp_Center.x,
                iconCoordsByIndex(0).y,
                (width()/2-xMakeUp_Center.x)*2, //better dock width calcule (23.02.09) iconCoordsByIndex(activeIconsCounter).x-iconCoordsByIndex(0).x+DesktopEnvironment->GUI.handIconsMax,
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
                QRegion::Rectangle
                );

        //Bug Solved: (21.02.09), selection mask has only the dock with
        maskAutoRaise=new QRegion(
                xMakeUp_Center.x,
                height()-1,
                (width()/2-xMakeUp_Center.x)*2,
                DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize*2,
                QRegion::Rectangle
                );



        //Bug Fix now on resize background is on the right y position
        //(25.04.09)
        xMakeUp_ArrowCoords.x=0;
        xMakeUp_ArrowCoords.y=DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax;
        xMakeUp_ArrowCoords.z=0;

	if(oldHandSizeIconMax!=DesktopEnvironment->GUI.handIconsMax) xMakeCenteredfix();


        #ifdef ENABLEDEBUGMSG
        qWarning("Dock %d need: %d [%dx%d](%d-%d)=%d",activeIconsCounter,xMakeUp_MinSize,xMakeUp_Center.x,xMakeUp_Center.y,iconCoordsByIndex(activeIconsCounter-1).y,iconCoordsByIndex(0).y,xMakeUp_Center.y);
        #endif


	for(int i=0;i<activeIconsCounter;i++)
	{
		XQDEIconRect r = iconCoordsByIndex(i);
                Basket->items.at(i)->setIconGeometry(r.x,r.y,r.z);
		//Basket->items.at(i)->xRepaintSmall();
	}

	mouseMoveEventSW(xLastX,xLastY,1);
	//xRepaint();
	repaintDock();
}
