//
// C++ Implementation: xqwfirsthand
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
#include <xqde.h>
#include <QPainter>
#include <QRegion>
#include <QTimer>


#include "xqtext.h"
#include "xqwfirsthand.h"
#include "xqdeenvironment.h"
#include "xqdeicon.h"
#include "xqdebasket.h"
#include "xqdeanimation.h"
#include "xqdeaction.h"
#include "xqdeproxy.h"

//#include <X11/Xlib.h>


QWidget *MainWindow;
XQPillow *Global_XQPillow;


XQWFirstHand::XQWFirstHand(QObject *lRoot, QWidget *parent)
 : XQWidget(lRoot, parent)
{
        xInterpolationValue=1;
        //space between icons during zoom
        xMakeUp_Separation=0;
	//xMakeUp_ArrowSize=8;
	//xMakeUp_Raise=0;
	xMakeUp_sizeMatrix=0;
	// 2d X Axis displace on mouse over
	xMakeUp_XMatrix=0;
	// 2d Y Axis displace on mouse over
	xMakeUp_YMatrix=0;
	// 2d Zoom on mouse over
	xMakeUp_ZMatrix=0;
	// 3d Dinamic Axis displace on mouse over
	xMakeUp_DMatrix=0;
	// 2d X+ Axis displace on mouse over
	xMakeUp_KMatrix=0;
        SleepFPS=1;
        isRaised=0;
	xLastX=-1000;
	xLastY=-1000;
        xLastX_real=xLastX;
        xLastY_real=xLastY;

        xMakeUp_ArrowCoords.x=0;
        xMakeUp_ArrowCoords.y=0;
        xMakeUp_ArrowCoords.z=0;
	maskRaised=new QRegion();
	maskNormal=new QRegion();
	maskAutoRaise=new QRegion();
        activeIconsCounter=0;

        cacheBusy=new QMutex();

        MainWindow=this;

        /*

                QImage imageLoader;
                imageLoader.load("/home/stefano/documenti/studio/xqde/xqde/default/32x32/flip_closed_over.png");
                if(imageLoader.width()!=DesktopEnvironment->GUI.handIconsMax)imageLoader=imageLoader.scaled (DesktopEnvironment->GUI.handIconsMax,DesktopEnvironment->GUI.handIconsMax, Qt::KeepAspectRatio, Qt::SmoothTransformation );
                setImage(imageLoader,XQImage_Normal);
                imageLoader.load("/home/stefano/documenti/studio/xqde/xqde/default/32x32/flip_closed.png");
                if(imageLoader.width()!=DesktopEnvironment->GUI.handIconsMax)imageLoader=imageLoader.scaled (DesktopEnvironment->GUI.handIconsMax,DesktopEnvironment->GUI.handIconsMax, Qt::KeepAspectRatio, Qt::SmoothTransformation );
                setImage(imageLoader,XQImage_Over);
                imageLoader.load("/home/stefano/documenti/studio/xqde/xqde/default/32x32/flip_closed_click.png");
                if(imageLoader.width()!=DesktopEnvironment->GUI.handIconsMax)
                imageLoader=imageLoader.scaled (DesktopEnvironment->GUI.handIconsMax,DesktopEnvironment->GUI.handIconsMax, Qt::KeepAspectRatio, Qt::SmoothTransformation );
                setImage(imageLoader,XQImage_Clicked);
        */

        setMouseTracking (true);
        setAcceptDrops(true);


        /*
        NETWinInfo info(qt_xdisplay(), w, qt_xrootwin(),NET::WMState);

        info.setState( NET::Override | NET::StaysOnTop | NET::KeepAbove | NET::SkipTaskbar | NET::SkipPager , NET::Override | NET::StaysOnTop | NET::KeepAbove | NET::SkipTaskbar | NET::SkipPager );
                info.setDesktop( NETWinInfo::OnAllDesktops);
        */

        mousePolling=0;
        animationPolling=0;

        // start dock on bottom and show on all desktops
        // added (10.04.09)
        MakeWindowOnBottom((void*)winId());
}

XQWFirstHand::~XQWFirstHand()
{
//    if(maskRaised) delete maskRaised;
//    if(maskNormal) delete maskNormal;
//    if(maskAutoRaise) delete maskAutoRaise;
//    if(cacheBusy) delete cacheBusy;
}

void XQDE_IconAddedNewAnimation()
{
        if(MainWindow)
        {
                XQWFirstHand*fh=(XQWFirstHand*)MainWindow;
                fh->animationPolling->start(200);
        }
}


void XQWFirstHand::slot_animationPolling()
{
	animationPolling->stop();
	int NeedToContinueAnimation=0;
	for(int i=0;i<activeIconsCounter;i++)
	{
		XQDEIcon *icon=Basket->items.at(i);
		if(!icon)continue;
		int UpdateThisIcon=0;

		if(icon->animationsNextFrameCounter>0)
		{
			icon->animationsNextFrameCounter=0;
			icon->redoEffects();
			for(int k=0;k<icon->animations->count();k++)
			{
				XQDEAnimation *ani=icon->animations->at(k);
				ani->step();
                                #ifdef ENABLEDEBUGMSG
				qWarning("%ld",(long)ani->icon);
                                #endif
				
				int ThisIconMustBeDestroied=0;
				if(ani->endAction!=NULL && ani->endAction->ActionType=="removeicon" && ani->endAction->ActionCounter>0)
				{
					ThisIconMustBeDestroied++;
				}
				
				if(ani->icon==NULL)
				{
                                        #ifdef ENABLEDEBUGMSG
					qWarning("Remove the animation if we are at end...");
                                        #endif
					XQDEAnimation *ani=icon->animations->takeAt(k);
					delete ani;
					// TODO: garbage on actions!!
                                        k--;
				}
				
				
				if(ThisIconMustBeDestroied>0)
				{
                                        #ifdef ENABLEDEBUGMSG
					qWarning("We need to remove the icon!!");
                                        #endif
					Basket->items.takeAt(i);					
                                        Basket->sgeBasket_As_Changed(6, NULL, NULL);
                                        i--;
                                        
					UpdateThisIcon=0;
					delete icon;
				}
				else UpdateThisIcon++;
				

			}
			if(UpdateThisIcon)
			{
				if(icon->detachedRect.z>0)
				{
				}
				else
				{
					icon->imageHotSpot.z=0;
					icon->xSetZoom(icon->imageCachedRect.z);
                                        xRepaintSingle(icon);
                                        update(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCachedRect.z,icon->imageCachedRect.y+icon->imageCachedRect.z-2);
				}
				NeedToContinueAnimation+=UpdateThisIcon;
			}

		}
	}

        if(NeedToContinueAnimation>0)animationPolling->start(50);
}


void XQWFirstHand::purgeCacheFixMouse(int ,int &,int &,int &)
{

}



void XQWFirstHand::purgeCacheFixBorder(int ,int &,int &,int &)
{

}

void XQWFirstHand::purgeCacheMovements()
{
//	grabMouse();
        //mouse is over, isRaised? if no show dock raised
        if(!isRaised) onEnter();

// Removed (21.02.09)
//        static timespec req,rem;
//	req.tv_nsec=SleepFPS*1000;
//	req.tv_sec=0;
	
	
	
	// Main loop
	for(int recallme=1;recallme!=0;)
        {
                // process other events, this prevent to stop
                // icons animations
                // Bug solved: (21.03.09)
                QCoreApplication::processEvents();

		QPoint pos, vect;
                // Mouse polling vars
                QPoint mouse;
                mouse = mapFromGlobal(QCursor::pos());
		// engine vars
		int xLastX_notmanaged;
		int xLastY_notmanaged;
		// loop goto
		xLastX_notmanaged=mouse.x();
		xLastY_notmanaged=mouse.y();

                // when exit this multiply to animate it
                //	int escapeMoltiply=1;
                // exit?
                recallme=0;

                int ax,ay,iconNum;


                iconNum=iconIndexByCoords(xLastX_notmanaged,xLastY_notmanaged);
                purgeCacheFixMouse(iconNum,xLastX_notmanaged,xLastY_notmanaged,recallme);


                //Drag icons
                if(isDragging>0 && lastButtonStatus!=Qt::NoButton)
                {

                        if(hasDragged<0 && iconNum!=lastIcon)
                        {
                                isDragging=3;
                                        if(lastIcon<0)hasDragged=0;
                                        else if(lastIcon>=(int)activeIconsCounter)hasDragged=activeIconsCounter-1;
                                                else hasDragged=lastIcon;
                        }

                }

                if(isDragging>2)
                {
                        lastIcon=iconNum;
                        if(hasDragged>=0&&hasDragged<(int)activeIconsCounter&&lastIcon>=0&&lastIcon<(int)activeIconsCounter && hasDragged!=lastIcon)
                        {
                                if(DesktopEnvironment->GUI.updateViaDND>0)
                                {
                                        Basket->items.swap(hasDragged,lastIcon);
                                        xMakeCentered();
                                        Basket->FreezeSave("");
                                }
                                hasDragged=lastIcon;
                        }
                }
                else lastIcon=iconNum;


                ax=xLastX_notmanaged;
                ay=xLastY_notmanaged;

                // controllo se il mouse esce dalla dock

// Removed (21.02.09)
//                if(xLastX-xLastX_notmanaged>1)
//                {
//                        ax=xLastX-1-(xLastX-xLastX_notmanaged)/xInterpolationValue;
//                        recallme=1;
//                }
//                else
//                {
//                        if(xLastX-xLastX_notmanaged<-1)
//                        {
//                                ax=xLastX+1-(xLastX-xLastX_notmanaged)/xInterpolationValue;
//                                recallme=1;
//                        }
//                }
//                if(xLastY-xLastY_notmanaged>1)
//                {
//                        ay=xLastY-1-(xLastY-xLastY_notmanaged)/xInterpolationValue;
//                        recallme=1;
//                }
//                else
//                {
//                        if(xLastY-xLastY_notmanaged<-1)
//                        {
//                                ay=xLastY+1-(xLastY-xLastY_notmanaged)/xInterpolationValue;
//                                recallme=1;
//                        }
//                }

                purgeCacheFixBorder(iconNum,ax,ay,recallme);

//                qWarning("%dx%d to %dx%d",ax,ay, xLastX, xLastY);

//                qWarning("%dx%d ",ax,ay);

//Removed (22.02.09) - new gain in cpu %, and code semplified
                
//		if(ax==xLastX && ay==xLastY)
//		{
//                        mouseMoveEventSW(xLastX ,xLastY ,1,1);
//			recallme=0;
//			repaintDock();
//		}
//		else
//		{
                        mouseMoveEventSW(ax,ay,0,1);
//			if(isRaised)recallme=1;
			//xRepaint();
			repaintDock();
			//QApplication::flushX();
//			qApp->processEvents();
			//QApplication::syncX();
//                        nanosleep(&req,&rem);
//		}

	}
        if(!isRaised) onExit();
	
	cacheBusy->unlock();
}

void XQWFirstHand::repaintDock()
{
	xRepaint();
        repaint();
}

void XQWFirstHand::mouseMoveEventSW(int x,int y,int force,int quality)
{
	xLastX=x;
	xLastY=y;

//Removed (22.02.09)
//	if(xLastX_real==x && xLastY_real==y && !force)
//	{
//		return;
//	}
//	xLastX_real=x;
//	xLastY_real=y;


        isRaised=0;
	if(activeIconsCounter>0)
	{
		for(int i=0;i<activeIconsCounter;i++)
		{
			XQDEIcon *thisIcon=Basket->items.at(i);
			mouseMoveEventSWIcon(x,y,i,thisIcon,quality);
                }
		xMakeUp_BackgroundCoords();
	}
}


void XQWFirstHand::xMakeUp_BackgroundCoords()
{
}

void XQWFirstHand::mouseReleaseEvent (QMouseEvent *e)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand::mouseReleaseEvent (QMouseEvent *e)");
	#endif

	//releaseMouse();
	//onExit();

	if(hasDragged>=0)
	{
		hasDragged=-1;
		isDragging=0;
		// We need to check if you have dropped out of the docker
		/*
		if(e->pos().y()>=0&&e->pos().y()<=ActiveConfiguration->Window.Height&&lastIcon>=0&&lastIcon<(int)activeIconsCounter)
		{
			// done into the engine
		}
		else
		{
			if(hasDragged>0&&hasDragged<(int)activeIconsCounter)
			{
				if(UpdateViaDND!="0" && UpdateViaDND!="no" )
				{
				XSGObjectIcon *itorm=ActiveConfiguration->ObjectsIcons.at(hasDragged);
				Configurator->xEventInRemovingIcon(hasDragged,0);
				ActiveConfiguration->RollingIcons.remove(itorm);
				}
			}
		}
		*/
	}
	else
	{
		isDragging=0;
		hasDragged=-1;

		if(!isRaised)return;
		if(!maskRaised->contains(e->pos()))return;
	
		int indexIcon=iconIndexByCoords(e->pos().x(),e->pos().y());

		int but=0;
		switch(e->button())
		{
			default:
				but=0;
			break;
			case Qt::LeftButton:
				but=XQDE_USER_ACTION_CLICKSX;
			break;
			case Qt::RightButton:
				but=XQDE_USER_ACTION_CLICKDX;
			break;
			case Qt::MidButton:
				but=XQDE_USER_ACTION_CLICKMI;
			break;
	
		}
		if(indexIcon>=0&&activeIconsCounter>indexIcon)
		{
			XQDEIcon *newIcon=Basket->items.at(indexIcon);
			newIcon->userAction(but,0,0);
                        newIcon->overText->xSetText(newIcon->title());
		}
	}
}

void XQWFirstHand::wheelEvent(QWheelEvent *e)
{
		releaseMouse();
		isDragging=0;
		hasDragged=-1;

		if(!isRaised)return;
		if(!maskRaised->contains(e->pos()))return;
	
		int indexIcon=iconIndexByCoords(e->pos().x(),e->pos().y());

		//int x=e->pos().x();
                //int y=e->pos().y();
                int but=0;
                if(e->delta()>0)but=XQDE_USER_ACTION_CLICKRU;
                else but=XQDE_USER_ACTION_CLICKRD;

		if(indexIcon>=0&&activeIconsCounter>indexIcon)
		{
			XQDEIcon *newIcon=Basket->items.at(indexIcon);
			newIcon->userAction(but,0,0);
		}			
}

void XQWFirstHand::onEnter()
{
        //mostra XQwidget per testo
        MakeWindowOnTop((void*)winId());
//        Removed to fix bug and reimplemented in purgeCacheFixBorder function
//        Bug fix: usando setVisible qui, viene mostrato prima il testo
//        vecchio e solo dopo quello nuovo, questo causa uno sfarfallio
//        Global_XQPillow->setVisible(true);
//	qApp->syncX();
        MakeWindowOnTop((void*)Global_XQPillow->winId());
//	qApp->syncX();
//	MakeWindowOnTop((void*)Global_XQPillow->winId());
}

void XQWFirstHand::onExit()
{
        //nascondi XQwidget per testo
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand::onExit()");
	#endif
	MakeWindowOnBottom((void*)winId());
        //Timer mouse Polling, to detect end edge
        mousePolling->start(250);
        Global_XQPillow->setVisible(false);

}

int XQWFirstHand::iconIndexByCoords(int,int)
{
	return 0;
}

/***************************************************/
/******************** MOUSE CONTROL ****************/
/***************************************************/

void XQWFirstHand::mousePressEvent( QMouseEvent *e)
{
	lastButtonStatus=e->button();
	hasDragged=-1;
	isDragging=1;
}

void XQWFirstHand::mouseMoveEvent(QMouseEvent *e)
{
	if(cacheBusy->tryLock()==false)return;
	if(!isRaised && !maskNormal->contains(e->pos()))
	{
		cacheBusy->unlock();
	}
	else purgeCacheMovements();
}

void XQWFirstHand::slot_mousePolling()
{
        if(isRaised)
        {
                mousePolling->stop();
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQWFirstHand::slot_mousePolling() stop");
                #endif
                return;
        }

        // Mouse polling vars
        QPoint mouse;
        mouse = mapFromGlobal(QCursor::pos());

        if(maskAutoRaise->contains(mouse))
        {
                mousePolling->stop();
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQWFirstHand::slot_mousePolling() onEnter!!!");
                #endif
                onEnter();
        }

}

void XQWFirstHand::mouseMoveEventSWIcon(int,int,int,XQDEIcon *,int)
{
}


/***************************************************/
/******************** DRAG AND DROP ****************/
/***************************************************/

void XQWFirstHand::dragEnterEvent(QDragEnterEvent *event)
{
        #ifdef ENABLEDEBUGMSG
        qWarning("void XQWFirstHand::dragEnterEvent(QDragEnterEvent *event)");
                #endif
        if (event)
        {
                #ifdef ENABLEDEBUGMSG
                qWarning("[%d][%d][%s]",event->pos().x(),event->pos().y(),event->mimeData()->formats().join("+").toAscii().data());
                #endif
                //TODO: if the widget...
                //QByteArray remotePluginName=event->mimeData()->data("text/plain");
                //application/x-qabstractitemmodeldatalist
                const char *AddedDropTitle=event->mimeData()->text().toAscii().data();

                void *ClassWidget=proxy->newInstanceOf(event->mimeData()->text());
                if(ClassWidget!=0)
                {
                        Basket->AddtoBasketWidget((QObject *) ClassWidget,(void *)0,(class XQDEPlugin *)ClassWidget,AddedDropTitle);
                }
                event->acceptProposedAction();
        }
        /*
        ->mimeData()->hasFormat("text/plain"))
                 event->acceptProposedAction();
        */
}


void XQWFirstHand::dropEvent(QDropEvent *event)
{
        Q_UNUSED(event);
}


XQDEIconRect XQWFirstHand::iconCoordsByIndex(int)
{
	XQDEIconRect r;
	r.x=0;
	r.y=0;
	r.z=0;
	return r;
}

void XQWFirstHand::Basket_As_Changed(int action, XQDEIcon *newIcon, void *pW)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand::Basket_As_Changed(%d, %ld, %ld) in ",action, (long)newIcon, (long)pW);
	#endif

	int sx=0;
	int sy=0;
	int sz=0;
	XQDEAnimation *RequiredAnimation=NULL;
	XQDEAction *RequiredAction=NULL;
	XQDEAction *EndAction=NULL;
	switch(action)
	{
		case 0:	// remove
                        //If icon must be in dock dont remove it!
                        if(newIcon->storeOnExit == 1) break;

			EndAction=new XQDEAction();
			EndAction->ActionType="removeicon";
                        RequiredAnimation=new XQDEAnimation(2,newIcon,0,RequiredAction,EndAction);
			newIcon->animations->append(RequiredAnimation);
			RequiredAnimation->step(); 
			newIcon->animationsNextFrameCounter=1;
			animationPolling->start(200);
			newIcon->imageHotSpot.z=0;
			//activeIconsCounter=;
                        xMakeCentered();
		break;
		case 1: // add
//                        newIcon->animations->append(new XQDEAnimation(1,newIcon,5));//fade
			RequiredAnimation=new XQDEAnimation(3,newIcon,0,RequiredAction,EndAction);
			newIcon->animations->append(RequiredAnimation);// 0->iconsize...
			RequiredAnimation->step(); // this will resize the icon to 0 ;)
			newIcon->xRepaintSmall();
			newIcon->xSetZoom(newIcon->imageCachedRect.z);
			newIcon->animationsNextFrameCounter=1;
			animationPolling->start(200);
			//activeIconsCounter=Basket->items.size();
			activeIconsCounter++;
			xMakeCentered();
			//exit(1);
		break;
		case 2: // refresh
			newIcon->imageHotSpot.z=0;
			newIcon->xSetZoom(newIcon->imageCachedRect.z);
			xRepaintSingle(newIcon);
			sx=newIcon->imageCachedRect.x;
			sy=newIcon->imageCachedRect.y;
			sz=newIcon->imageCachedRect.z;
//                        qDebug("rectangle: x:%d y:%d z:%d", sx,sy,sz);
                        //ToDo: il valore 10 indica l'altezza del riflesso, rendere dinamico
                        repaint(sx,sy,sz,sz+10);
		break;
		case 3:	// free
		break;
		case 4:	// delete "rolling" or background window-sensor
                        Basket_As_Changed(5, newIcon,pW);
		break;
		case 5:	// add "rolling" or background window-sensor

			newIcon->imageHotSpot.z=0;
                        newIcon->xSetZoom(newIcon->imageCachedRect.z);
                        repaintDock();
		break;
		case 6:// removed from basket and icon is deleted! after this call!!!
			activeIconsCounter=Basket->items.size();
			xMakeCentered();
		break;
		default:
			activeIconsCounter=Basket->items.size();
			xMakeCentered();
		break;
	}
}

void XQWFirstHand::xRepaint()
{
	//paintBuffer.fill(0x80000000+(unsigned int)winId());
        paintBuffer.fill(Qt::transparent);

        widgetpaint->begin(&paintBuffer);
	if(activeIconsCounter>0){
		//
                //draw corners basket
		widgetpaint->drawImage(topCornerCoords[0][0],topCornerCoords[0][1],topCornerCached[0]);
                //draw center background
		widgetpaint->drawImage(
                        topBackgroundCoords[0],
                        topBackgroundCoords[1],
                        topBackgroundCached[0],0,0,
                        topBackgroundSize[0],
                        topBackgroundSize[1]
			);


//               /* for(int i=0;i<activeIconsCounter;i++)
//                {
//                    XQDEIcon *icon=Basket->items.at(i);
//                    if(icon->detachedRect.z) continue;
//
//                    // reflection
//                    switch(DesktopEnvironment->GUI.dockAlign)
//                    {
//                            case 0:// 0 bottom
//                                    #ifndef RESIZEVIAXRENDER
//                                    widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                    widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                                    #else
//                                    widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                    widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                                    #endif
//                                    break;
//                            case 1:// 1 top
//                                    #ifndef RESIZEVIAXRENDER
//                                    widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                    widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                                    #else
//                                    widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                    widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                                    #endif
//                                    break;
//                            case 2:// 2 left
//                            break;
//                            case 3:// 3 right
//                            break;
//                    }
//                    // icon
//                    #ifndef RESIZEVIAXRENDER
//                    widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                    #else
//                    widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
//                    #endif
//                    // arrow
//                    if(icon->isRunning())
//                    {
////                            icon->imageCachedArrow.fill(Qt::red);
//
//                            #ifndef RESIZEVIAXRENDER
//                            widgetpaint->drawImage(icon->imageCachedArrowRect.x,icon->imageCachedArrowRect.y,icon->imageCachedArrow);
//                            #else
//                            widgetpaint->drawPixmap(icon->imageCachedArrowRect.x,icon->imageCachedArrowRect.y,icon->imageCachedArrow);
//                            #endif
//                            //qWarning("%dx%d [%dx%d]",icon->imageCachedArrowRect.x,icon->imageCachedArrowRect.y,icon->imageCachedArrow.width(),icon->imageCachedArrow.height());
//                    }
//                }*/

                //draw final background
                widgetpaint->drawImage(topCornerCoords[1][0],topCornerCoords[1][1],topCornerCached[1]);
	}

        widgetpaint->end();


//      Icon refresh using icon xRepaint class trought xRepaintSingleIndex (11.09.2009)
        for(int i=0;i<activeIconsCounter;i++)
                {
                    xRepaintSingleIndex(i);
                }
//        slot_animationPolling();


}


void XQWFirstHand::xRepaintSingleIndex(int iconIndex)
{
        XQDEIcon *icon=Basket->items.at(iconIndex);

        // if an animation is running, update icon position
        // with stepAgain function
        // -> prevent to drow picture outside dock when
        // moving
        for(int k=0;k<icon->animations->count();k++)
        {
                XQDEAnimation *ani=icon->animations->at(k);
                ani->stepAgain();
        }

        if(icon)xRepaintSingle(icon);

}

extern QImage *XQDE_ImageCopyRop(const QImage &source, QImage &dest, uint sx, uint sy, uint sz);

void XQWFirstHand::xRepaintSingleBackground(QPainter *,int ,int ,int )
{
	#ifdef ENABLEDEBUGMSG
        qWarning("void XQWFirstHand::xRepaintSingleBackground(QPainter *pwidgetpaint,int sx,int sy,int sz)");
	#endif
}

void XQWFirstHand::xRepaintSingle(XQDEIcon *icon)
{
	if(icon->detachedRect.z)
	{
                icon->xRepaintDetached();
	}
	else
	{
		int sx=icon->imageCachedRect.x;
		int sy=icon->imageCachedRect.y;
                int sz=icon->imageCachedRect.z;
		//QImage paint2Buffer=QImage(sz,sz,QImage::Format_ARGB32);
		// this will erase only the interesting area
                //ToDo erase the reflection!!!
                //ToDo erase with transparent background!!
//                XQDE_ImageEraseRect(paintBuffer,sx,sy,sz);
		//memset(paint2Buffer.bits(),0xFFFFFFFF,sizeof(uint)*sz*sz);


                widgetpaint->begin(&paintBuffer);
       //         widgetpaint->setCompositionMode(QPainter::CompositionMode_SourceOver);
                //Erase image area
     //           widgetpaint->fillRect(sx,sy,sz,sz,Qt::transparent);
//                widgetpaint->eraseRect(sx,sy,sz,sz);
                //Repaint background
    //            xRepaintSingleBackground(widgetpaint,sx,sy,sz);


                widgetpaint->setCompositionMode(QPainter::CompositionMode_Source);
//                widgetpaint->fillRect(sx,sy,sz,sz, Qt::transparent);

                //repaint backgound behind icon
//                xRepaintSingleBackground(widgetpaint,sx,sy,sz);

                //repaint backgound behind icon, with full dock height
                widgetpaint->drawImage(
                        sx,                                 //icon x coordinate
                        topBackgroundCoords[1],             //dock top y coordinate
                        topBackgroundCached[0],             //dock background image
                        0,                                  //no deplacement x or y
                        0,
                        sz,                                 //repaint width
                        topBackgroundSize[1]                //repaint height
                        );
                //erase remaing area before draw icon (Bug fix: 19.04.09)
                //bug fix: now work OK (26.04.09
                widgetpaint->fillRect(sx,DesktopEnvironment->GUI.dockAlignDisplaceY, sz, DesktopEnvironment->GUI.dockAlignDisplaceY + topBackgroundCoords[1], Qt::transparent);

                //Start drawing images on top of source(background)
                widgetpaint->setCompositionMode(QPainter::CompositionMode_SourceOver);



//                widgetpaint->drawImage(
//                        xMakeUp_ArrowCoords.x,
//                        xMakeUp_ArrowCoords.y,
//                        topBackgroundCached[0],xMakeUp_ArrowCoords.x,xMakeUp_ArrowCoords.y,
//                        sz,
//                        sz
//                );

		// TODO!!! bug of emblems on icons!! the outher draw will not be clerated... 

		// TODO: reflection may or not may be update on hispeed repaint?		
		
//                #ifndef RESIZEVIAXRENDER
//                //widgetpaint->drawImage(sx,sy+sz-2,icon->imageCachedReflection);
//                widgetpaint->drawImage(sx,sy,icon->imageCached);
//                #else
//                //ToDo check correct reflection (25.02.09)
//                widgetpaint->drawPixmap(sx,sy+sz-2,icon->imageCachedReflection);
//                //Paint icon
//                widgetpaint->drawPixmap(sx,sy,icon->imageCached);
//                #endif

		
                // Paint reflection + icon
                switch(DesktopEnvironment->GUI.dockAlign)
                {
                        case 0:// 0 bottom
                                #ifndef RESIZEVIAXRENDER
                                widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
                                #else
                                widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
                                #endif
                                break;
                        case 1:// 1 top
                                #ifndef RESIZEVIAXRENDER
                                widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
                                #else
                                widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y+icon->imageCachedRect.z-2,icon->imageCachedReflection);
//                                widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
                                #endif
                                break;
                        case 2:// 2 left
                        break;
                        case 3:// 3 right
                        break;
                }
                // icon
                #ifndef RESIZEVIAXRENDER
                widgetpaint->drawImage(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
                #else
                widgetpaint->drawPixmap(icon->imageCachedRect.x,icon->imageCachedRect.y,icon->imageCached);
                #endif


                //Repaint arrow if is running
		if(icon->isRunning())
		{
			#ifndef RESIZEVIAXRENDER
                        widgetpaint->drawImage(icon->imageCachedArrowRect.x,icon->imageCachedArrowRect.y,icon->imageCachedArrow);
			#else
                        widgetpaint->drawPixmap(icon->imageCachedArrowRect.x,icon->imageCachedArrowRect.y,icon->imageCachedArrow);
			#endif
		}
                
                widgetpaint->end();
		//XQDE_ImageCopyRop(paint2Buffer, paintBuffer,sx,sy,sz);
	}
}

void XQWFirstHand::xMakeCentered()
{
}

extern void storeConfiguration();

void XQWFirstHand::xConfigurationChanged()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand::xConfigurationChanged()");
	#endif

        xMakeCentered();
        xMakeCenteredfix(1);

        // DoTo aggiornare dock altrimenti resta nera, soluzione provvisoria.
        // Bug: la dock non si sposta in modo fluido (minor Bug)
        xRepaint();

        for(int i=0;i<activeIconsCounter;i++)
        {
                XQDEIcon *icon=Basket->items.at(i);
                if(!icon)continue;
                icon->overText->xSetText(icon->title());
        }

	storeConfiguration();
}


void XQWFirstHand::xReset()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQWFirstHand::xReset()");
	#endif
        lastIcon=0;
        lastButtonStatus=-1;
        hasDragged=-1;
        isDragging=-1;
        ((XQDEClass *)this)->connect(Basket,
	SIGNAL(Basket_As_Changed(int,XQDEIcon*,void*)),
	SLOT(Basket_As_Changed(int,XQDEIcon*,void*)),
	Qt::AutoCompatConnection);

        if(mousePolling==0)
        {
                mousePolling=new QTimer();
                connect(mousePolling,SIGNAL(timeout()),this,SLOT(slot_mousePolling()));
        }
        if(animationPolling==0)
        {
                animationPolling=new QTimer();
                connect(animationPolling,SIGNAL(timeout()),this,SLOT(slot_animationPolling()));
        }


}


void XQWFirstHand::xMakeCenteredfix(int)
{
}

void XQWFirstHand::xMakeUp()
{
    double ratio=0;
    double ratioy=0;
    int xMakeUp_Raise=0;

    if(!xMakeUpIsMirrored)
    {
        // bottom
        xMakeUp_Raise=-int((double(DesktopEnvironment->GUI.sizeIconsMax/2)-double(DesktopEnvironment->GUI.handIconsMax/2)));
        // bug 20071116
        //xDesignVirtualEscapeMatrix=(DesktopEnvironment->GUI.sizeIconsMax+xMakeUp_ArrowSize*2)-(DesktopEnvironment->GUI.handIconsMax/2)+xMakeUp_ArrowSize;
        xDesignVirtualEscapeMatrix=(DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax/2);
    }
    else
    {
        // left
        xMakeUp_Raise=-(-int((double(DesktopEnvironment->GUI.sizeIconsMax/2)-double(DesktopEnvironment->GUI.handIconsMax/2))));
        xDesignVirtualEscapeMatrix=(DesktopEnvironment->GUI.handIconsMax/2)+xMakeUp_ArrowSize;
    }

    xMakeUp_sizeMatrix=(DesktopEnvironment->GUI.handIconsMax + xMakeUp_Separation)*2;

    ratio=double(DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax) / double(xMakeUp_sizeMatrix*2);


    // quantum icon must raise
    // double
    ratioy=(-double(xMakeUp_Raise)/double(xMakeUp_sizeMatrix*2));
    // horizontal displacement

    // TODO: garbage on reloadig matrix
    // ex?: delete xMakeUp_XMatrix;
    // Allocate arrays
    xMakeUp_XMatrix=
            new int[xMakeUp_sizeMatrix*2];
    xMakeUp_YMatrix=
            new int[xMakeUp_sizeMatrix*2];
    xMakeUp_ZMatrix=
            new int[xMakeUp_sizeMatrix*2];

    for (int mouseinx=0;mouseinx<xMakeUp_sizeMatrix*2;mouseinx++)
    {
            double ZMatrixDouble=double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*mouseinx);

            xMakeUp_ZMatrix[mouseinx]=(int)ZMatrixDouble;

            xMakeUp_YMatrix[mouseinx]=(int)
                    double(
                    ZMatrixDouble/2
                    +double(xMakeUp_sizeMatrix*2 -mouseinx) * ratioy
                    -double(DesktopEnvironment->GUI.handIconsMax/2));
            xMakeUp_XMatrix[mouseinx]=(int)
                    double(ZMatrixDouble/2
                    -double(DesktopEnvironment->GUI.handIconsMax/2));
            #ifdef ENABLEDEBUGMSG
            qWarning("[%3d][%3d][%3d][%3d]",mouseinx,xMakeUp_ZMatrix[mouseinx],xMakeUp_YMatrix[mouseinx],xMakeUp_XMatrix[mouseinx]);
            #endif
    }
    // dynamic horizontal displacement
    xMakeUp_DMatrix= new int*[xMakeUp_sizeMatrix*2];
    int contaIcone=(xMakeUp_sizeMatrix*2)/(DesktopEnvironment->GUI.handIconsMax+xMakeUp_Separation);

    double dMax=(double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*0))/2;
    double dMin=dMax;
    int XIcona=xMakeUp_sizeMatrix*2;
    dMin+=(double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*XIcona))/2;

    for(int contaIcona=0;contaIcona<contaIcone;contaIcona++)
    {
        XIcona=(xMakeUp_sizeMatrix*2)-contaIcona*(DesktopEnvironment->GUI.handIconsMax + xMakeUp_Separation);
        dMin+=(double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*XIcona));

    }
    for (int mouseinx=0;mouseinx<xMakeUp_sizeMatrix*2;mouseinx++)
    {

        int *vett=new int[xMakeUp_sizeMatrix*2];
        for(int mouseiny=0;mouseiny<xMakeUp_sizeMatrix*2;mouseiny++)
        {
            double pinco=(double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*double(mouseinx+mouseiny)/2));
            pinco=pinco-(double(DesktopEnvironment->GUI.handIconsMax));

            pinco=pinco*3;

            pinco=pinco+(DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.handIconsMax)*
            (double(DesktopEnvironment->GUI.sizeIconsMax)-double(ratio*double(mouseinx+mouseiny)/2))/DesktopEnvironment->GUI.sizeIconsMax;

            double pincoRatio = double(mouseinx) / double(xMakeUp_sizeMatrix*2);
            pinco=pinco*pincoRatio;

            vett[mouseiny]=int(pinco);
        }
        xMakeUp_DMatrix[mouseinx]=vett;
    }

    xMakeUp_KMatrix = new int[xMakeUp_sizeMatrix*2];
    double ratiok = double(xMakeUp_DMatrix[xMakeUp_sizeMatrix*2-1][0]) / double(xMakeUp_sizeMatrix*2);

    for (int mouseinx=0;mouseinx<xMakeUp_sizeMatrix*2;mouseinx++)
    {
        xMakeUp_KMatrix[mouseinx]=int(ratiok * double(xMakeUp_sizeMatrix*2-mouseinx));
    }

    #ifdef ENABLEDEBUGMSG
    qWarning("xMakeUp() done %d",xMakeUp_sizeMatrix);
    #endif
}


extern void MakeWindowOnTopPillow(void *);

XQPillow::XQPillow(QWidget *p, int align)
 : XQWidget(0,0)
{
//	m_NearOf=p;
	m_Align=align;
	Global_XQPillow=this;
	setFixedSize(1,1);
        //move(-2000,-2000);
//	last_kx=0;

//	MakeWindowOnTopPillow((void*)winId());
}

XQPillow::~XQPillow()
{
}

void XQPillow::move(int nx,int ny)
{
	switch(DesktopEnvironment->GUI.dockAlign)
	{
                case 0: // bottom
                        XQWidget::move(nx,ny);
//			last_kx=nx;
                        break;
                case 1: // top
                        XQWidget::move(nx,ny);
//                        last_kx=nx;
                        break;
                case 2: // left // Todo: change position on dock alignement
			XQWidget::move(nx,ny);
                        break;
                case 3: // right
			XQWidget::move(nx,ny);
                        break;
	}
}

void XQPillow::xReset()
{
}

void XQPillow::xRepaint()
{
}

void XQPillow::xDrawText(const QPixmap *TextPixmap)
{
    // Compare the 2 Pixmap, a pointer to the old one is used
    // if pointer change new image is repaint
//    static const void *lastTextPixmapDrawed;
//    if(TextPixmap==lastTextPixmapDrawed) return;
//    lastTextPixmapDrawed=TextPixmap;

//    int nw = TextPixmap->width();
//    int nh = TextPixmap->height();
//    int w  = width();
//    int kw = 0;


//    switch(DesktopEnvironment->GUI.dockAlign)
//    {
//        case 0: // bottom
//        case 1: // top
////                kw=last_kx;
//                if(w < QApplication::desktop()->availableGeometry().width())
//                {
//                        //if(nh>32)nh=32;
//                        setFixedSize(QApplication::desktop()->availableGeometry().width(),nh);
//                }
//                break;
//        case 2: // left
//        case 3: // right
//                if((w < nw) && w<800)
//                {
//                        if(nw>800)nw=800;
//                        if(nh>32)nh=32;
//                                setFixedSize(nw,nh);
//                }
//                else
//                {
//                }
//                break;
//    }

    // Resize the widget size!
    setFixedSize(TextPixmap->width(),TextPixmap->height());

//    QRect rect = QApplication::desktop()->geometry();
//    QPoint rectWidget = QWidget::pos();
//
//    setPos(rect.center().x(),rectWidget.x() - TextPixmap->height());
    
    //paintBuffer.fill(0x80000000+(unsigned int)winId());

    //        last_kx=QApplication::desktop()->availableGeometry().width()/2-nw/2; //sempre al centro


    paintBuffer.fill(Qt::transparent);

    widgetpaint->begin(&paintBuffer);
    widgetpaint->drawPixmap(0,0,*TextPixmap);
    widgetpaint->end();
}
