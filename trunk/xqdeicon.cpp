//
// C++ Implementation: xqdeicon
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include <QPainter>
#include <QMenu>
#include <QMap>


#include "xqdeicon.h"
#include "xqdeenvironment.h"
// will be remove
#include "xqdebasket.h"
#include "xqdeuiiconwindow.h"
#include "xqdeenvironment.h"
#include "xqdeaction.h"
#include "xqdeanimation.h"
#include "xqtext.h"

void MakeWindowOnTopPillow(void *);
extern QImage *XQDE_ImageReflectBottom(QImage &xImgSource,QImage &newImage, int rHeight);
extern QImage *XQDE_ImageReflectBottom(QPixmap &xImgSource,QImage &newImage, int rHeight);
extern QImage *XQDE_ImageReflectBottom(QPixmap &xImgSource,QImage &newImage);
void XRenderResizeImageGood(QPixmap &Source,QPixmap &thumbnail,int maxDimension);
void XRenderResizeImage(QPixmap &Source,QPixmap &thumbnail,int mx, int my);


XQDEIcon::XQDEIcon(QString logicName,QObject *parent, void *cData,QImage *defaultImg, QString strTitle, QString defaulticon): XQWidget(parent)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("XQDEIcon::XQDEIcon(QString logicName,QObject *parent, void *cData,QImage *defaultImg, QString strTitle, QString defaulticon): XQWidget(parent)");
	#endif
	//MakeWindowOnTopPillow((void *)winId());
	imageCachedDirty=0;
        isReflectionEnabled=2*18+2;
	//isReflectionEnabled=0;
	
	detachedRect.z=0;
	detachedRect.x=0;
	detachedRect.y=0;
	iconGeometry.x=0;
	imageCachedRect.x=0;
	imageCachedArrowRect.x=0;
	imageHotSpot.x=0;
	iconGeometry.y=0;
	imageCachedRect.y=0;
	imageCachedArrowRect.y=0;
	imageHotSpot.y=0;
	iconGeometry.y=0;
	imageCachedRect.z=0;
	imageCachedArrowRect.z=0;
	imageHotSpot.z=0;

	imageCachedMiniDirty=0;

	animations=new QList <class XQDEAnimation *>;
	enableIconFromWindow=1;
	slotsSensor=new QList <XQDESlotSensor*>;
	actions=new QMap<QString,class XQDEAction*>;
	enablePreview=1;
	groupWindows=0;
	ExternalConfigurator=0;
	storeOnExit=0;
//	forceRunning=0;
	overText=new XQText(0,0);
	ClientData=new QList <void *>;
	PIDData=new QList <void *>;
	localParent=parent;
	localLogicName=logicName;
	if(cData!=0)ClientData->append(cData);
	localThumbnail=QImage(1,1,QImage::Format_ARGB32);
        localThumbnail.fill(Qt::transparent);
	if(defaultImg)localIconImageWM=defaultImg->copy();
	if(strTitle!="")localTitle=strTitle;
	else localTitle=logicName;
	if(defaulticon!="")localIcon=defaulticon;
	else localIcon=localLogicName;
	ContextPopupMenu=new QMenu(localLogicName,this);
	overText->xSetText(localTitle);

	XQDEAction *MouseSXClick=new XQDEAction;
	MouseSXClick->ActionType="exec";
	MouseSXClick->Action=logic();
	actions->insert("XQDE_USER_ACTION_CLICKSX",MouseSXClick);

	XQDEAction *MouseDXClick=new XQDEAction;
	MouseDXClick->ActionType="menu";
	MouseDXClick->Action="";
	actions->insert("XQDE_USER_ACTION_CLICKDX",MouseDXClick);
	
	#ifdef ENABLEDEBUGMSG
	qWarning("XQDEIcon::XQDEIcon() end");
	#endif
	}


XQDEIcon::~XQDEIcon()
{
	if(localParent)
	{
		disconnect(SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)));
		disconnect(SIGNAL(fillPopup(QMenu *,XQDEIcon *)));
	}

//        if(animations) delete animations;
//        if(slotsSensor) delete slotsSensor;
//        if(actions) delete actions;
//        if(overText) delete overText;
//        if(ClientData) delete ClientData;
//        if(PIDData) delete PIDData;
//        if(ContextPopupMenu) delete ContextPopupMenu;
}

void XQDEIcon::xSetParent( QObject *newParent)
{
        if(localParent)
        {
                disconnect(SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)));
                disconnect(SIGNAL(fillPopup(QMenu *,XQDEIcon *)));
        }
        localParent=newParent;
        if(localParent)
        {
                connect(this,SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)),localParent,SLOT(userAction(int,int,int,void *,XQDEIcon *)));

                connect(this,SIGNAL(fillPopup(QMenu *,XQDEIcon *)),localParent,SLOT(fillPopup(QMenu *,XQDEIcon *)));

        }
}


void XQDEIcon::localfillPopup(QMenu *ContextPopupMenu,XQDEIcon *pMe)
{
//        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("new")),tr("New window"),this,SLOT(menu_newWindow()));

        ContextPopupMenu->addAction(QIcon(":/images/new.png"),tr("New window"),this,SLOT(menu_newWindow()));
	if(storeOnExit==0)
	{
//                ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("keepindock")),tr("Keep in dock"),this,SLOT(menu_setKeepInDock()));
                ContextPopupMenu->addAction(QIcon(":/images/keepindock.png"),tr("Keep in dock"),this,SLOT(menu_setKeepInDock()));
	}
	else
	{
//                ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("removeonexit")),tr("Remove on exit"),this,SLOT(menu_setRemoveOnExit()));
                ContextPopupMenu->addAction(QIcon(":/images/removeonexit.png"),tr("Remove on exit"),this,SLOT(menu_setRemoveOnExit()));

	}

//        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("configure")),tr("Configure"),this,SLOT(xConfigure()));
//        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("configure")),tr("Global configuration"),this,SLOT(xConfigurator()));
        ContextPopupMenu->addAction(QIcon(":/images/configure.png"),tr("Configure"),this,SLOT(xConfigure()));
        ContextPopupMenu->addAction(QIcon(":/images/configure.png"),tr("Global configuration"),this,SLOT(xConfigurator()));
	Q_UNUSED(pMe);
}

void XQDEIcon::menu_newWindow()
{
	XQDEAction *sx=(actions->value("XQDE_USER_ACTION_CLICKSX"));
	sx->Pointer=this;
	sx->doit();
}

void XQDEIcon::menu_setKeepInDock()
{
	storeOnExit=1;
	Basket->FreezeSave("");
}

void XQDEIcon::menu_setRemoveOnExit()
{
	storeOnExit=0;
        Basket->FreezeSave("");
}

void XQDEIcon::userActionDefault(int a,int ,int )
{
	switch(a)
	{
		case XQDE_USER_ACTION_CLICKDX:
			if(actions->value("XQDE_USER_ACTION_CLICKDX")->ActionType=="menu")
			{
				ContextPopupMenu->clear();
				ContextPopupMenu->setTitle(localLogicName);
				localfillPopup( ContextPopupMenu,this);
				emit fillPopup(ContextPopupMenu,this);
				ContextPopupMenu->popup(QCursor::pos());
			}
		break;
		case XQDE_USER_ACTION_CLICKSX:
			if(PIDData->size()>0)
			{
			}
			else
			{
				XQDEAction *sx=(actions->value("XQDE_USER_ACTION_CLICKSX"));
				sx->Pointer=this;
				sx->doit();
			}
                //New (04.03.09) start application on middle click
                case XQDE_USER_ACTION_CLICKMI:
                        menu_newWindow();
		break;
	}
}
void XQDEIcon::userAction(int a,int b,int c)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::userAction(int %d,int %d,int %d)",a,b,c);
	#endif
	if (receivers(SIGNAL(sguserAction(int,int,int,void *, XQDEIcon *))) > 0)
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("void XQDEIcon::userAction sending signals");
	#endif
		emit sguserAction(a,b,c,clientData(),this);
	}
	else
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("void XQDEIcon::userAction default action");
	#endif
		userActionDefault(a,b,c);
	}
}
void XQDEIcon::xRepaintSmall()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaintSmall() %d", localImageWidthEffects.width());
	#endif
	#ifndef RESIZEVIAXRENDER
	imageCachedMini=localImageWidthEffects.scaled (DesktopEnvironment->GUI.handIconsMax,DesktopEnvironment->GUI.handIconsMax, Qt::KeepAspectRatio, Qt::SmoothTransformation );
	#else
	XRenderResizeImageGood(localImageWidthEffects,imageCachedMini,DesktopEnvironment->GUI.handIconsMax);
	#endif
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaintSmall() %d", localImageWidthEffects.width());
	#endif
	imageCachedMiniDirty=0;
}

void XQDEIcon::xRepaintDetached()
{
        #ifdef ENABLEDEBUGMSG
        qWarning("void XQDEIcon::xRepaintDetached()");
        #endif

	paintBuffer.fill(Qt::transparent);
        widgetpaint->begin(&paintBuffer);
	#ifndef RESIZEVIAXRENDER
        widgetpaint->drawImage(0,0,imageCached);
	#else
        widgetpaint->drawPixmap(0,0,imageCached);
	#endif
        widgetpaint->end();
}

void XQDEIcon::xRepaint()
{

	#ifndef RESIZEVIAXRENDER
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaint() Qt");
	#endif
	#else
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaint() XRender");
	#endif
	#endif
	
        #ifndef RESIZEVIAXRENDER
                localImage=QImage(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax,QImage::Format_ARGB32);
        #else
                localImage=QPixmap(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
        #endif

        localImage.fill(Qt::transparent);
	

	if(localThumbnail.width()>8) //check if a thumbnail is present
	{
                #ifdef ENABLEDEBUGMSG
                        qWarning("void XQDEIcon::xRepaint() localThumbnail.width()=%d",localThumbnail.width());
                #endif
		//QPainter p;
		if(localThumbnail.width()!=DesktopEnvironment->GUI.sizeIconsMax||localThumbnail.height()!=DesktopEnvironment->GUI.sizeIconsMax)
		{
			localThumbnail=localThumbnail.scaled(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax,Qt::KeepAspectRatio,Qt::SmoothTransformation);
		}
                widgetpaint->begin(&localImage);
                //Show thumbnail window
                widgetpaint->drawImage(0,0,localThumbnail);
                //Show small icon
                widgetpaint->drawImage(DesktopEnvironment->GUI.sizeIconsMax/2,DesktopEnvironment->GUI.sizeIconsMax/2,localIconImage_DrawBuffer);
                widgetpaint->end();
	}
	else
	{
                widgetpaint->begin(&localImage);
                widgetpaint->drawImage(0,0,localIconImage);
                widgetpaint->end();
	}
	
        #ifdef ENABLEDEBUGMSG
        qWarning("void XQDEIcon::xRepaint() %d %d A",localImage.width(), localIconImage.width());
	#endif

	localImageWidthEffects=localImage.copy();
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaint() %d %d B",localImage.width(), localIconImage.width());
	#endif
	applyEffects();
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaint() %d %d C",localImage.width(), localIconImage.width());
	#endif
        imageHotSpot.z=0;

//	xRepaintSmall();
        
	if(isReflectionEnabled>0)
	{
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::xRepaint() Reflection repainting");
                #endif
                #ifndef RESIZEVIAXRENDER
                localImageWidthEffectsReflection=localImageWidthEffects.scaled(DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled, Qt::KeepAspectRatio, Qt::SmoothTransformation );
                #else
//                XRenderResizeImage(localImageWidthEffects,localImageWidthEffectsReflection,DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled);
                #endif
		QImage pip;
                XQDE_ImageReflectBottom(localImageWidthEffects,pip);
                localImageWidthEffectsReflection=localImageWidthEffectsReflection.fromImage(pip);
		
	}
	
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xRepaint() %d %d %d D",localImage.width(), localIconImage.width(),localImageWidthEffects.width());
	#endif
}

//Added(24.02.09)
extern QString DataPath;
#include <QDir>

void XQDEIcon::xReset()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xReset() %s",localIcon.toUtf8().constData());
	#endif

        // ricerca icona, 1) locale, 2) carica da Window Manager 3)imagine per removed icon
	int bad=1;
	QString newImageFile=DesktopEnvironment->Theme.findImage(localIcon);
	if(newImageFile!="")
	{
		if(localIconImage.load(newImageFile))bad=0;
	}
	if(bad > 0 && enableIconFromWindow>0 && localIconImageWM.width()>8)
        {
                localIconImage=localIconImageWM;
                //Temp HACK (24.02.09) to resolve bug when app. are closed (is a "cache")
                localIconImage.save(QDir::homePath() + "/.xqde/icons/"+localIcon, "PNG");
		bad=0;
	}
        if(bad>0)
        {
                //Todo: skip findImage if removeimage action is active
                //Bug: some applications show the correct icon in remove animation
                //      other show the unknown icon....
                newImageFile=DesktopEnvironment->Theme.findImage("unknown");
                if(newImageFile!="")
                {
                        if(!localIconImage.load(newImageFile))
                        {
                                #ifdef ENABLEDEBUGMSG
                                qWarning("Cannot find suitable icon");
                                #endif
                        }
                }
        }

	#ifdef ENABLEDEBUGMSG
        qWarning("void XQDEIcon::xReset() localIconImage.width()=%d to %ld", localIconImage.width(),DesktopEnvironment->GUI.sizeIconsMax);
	#endif
	qWarning("void XQDEIcon::xReset() localIconImage.width()=%d to %ld", localIconImage.width(),DesktopEnvironment->GUI.sizeIconsMax);
        if(localIconImage.width()!=DesktopEnvironment->GUI.sizeIconsMax)
        {
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::xReset() warning duty cicle %d to %ld", localIconImage.width(),DesktopEnvironment->GUI.sizeIconsMax);
                #endif
                localIconImage=localIconImage.scaled(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }

        //Create a small icon, used on thumbnail show
        localIconImage_DrawBuffer=localIconImage.scaled(DesktopEnvironment->GUI.sizeIconsMax/2,DesktopEnvironment->GUI.sizeIconsMax/2,Qt::KeepAspectRatio,Qt::SmoothTransformation);
	// Reload Arrow image
        if(imageArrow=="") imageArrow=DesktopEnvironment->Theme.Arrow;
	if(!imageArrowImage.load(DesktopEnvironment->Theme.pathImages+imageArrow))
	{
		imageArrowImage=QImage(1,1,QImage::Format_ARGB32);
                imageArrowImage.fill(Qt::transparent);
	}
        #ifndef RESIZEVIAXRENDER
        #else
        imageCachedArrowPixmap=QPixmap::fromImage(imageArrowImage);
        #endif

        #ifndef RESIZEVIAXRENDER
        imageCachedArrow=imageArrowImage.scaled (DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize,DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation );
        #else
        XRenderResizeImageGood(imageCachedArrowPixmap,imageCachedArrow,DesktopEnvironment->GUI.handIconsMax+xMakeUp_ArrowSize);
        #endif

	xRepaint();
	
}
void XQDEIcon::xSetIcon(QImage &newIcon)
{
	localThumbnail=newIcon;
	xReset();
	xRepaint();
}
void XQDEIcon::xSetIcon(const QString & newIcon)
{
	localIcon=newIcon;
	xReset();
	xRepaint();
}

void XQDEIcon::xSetTitle(const QString &newIcon)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::xSetTitle(QString newIcon)");
	#endif
	if(newIcon==localTitle)return;
	localTitle=newIcon;
	overText->xSetText(localTitle);
}

void XQDEIcon::xGetImage(QImage &store)
{
#ifndef RESIZEVIAXRENDER
	store=localImageWidthEffects;
#else
	store=localImageWidthEffects.toImage();
#endif

}

void XQDEIcon::xConfigure()
{
	if(ExternalConfigurator==0)ExternalConfigurator=(QWidget *)new XQDEUIIconWindow();
	XQDEUIIconWindow *l=(XQDEUIIconWindow *)ExternalConfigurator;
	l->setObject(this);
	l->show();
}

void XQDEIcon::redoEffects()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEIcon::redoEffects() %d %d",localImageWidthEffects.width(), localImage.width());
	#endif
	localImageWidthEffects=localImage.copy();
        //xRepaintSmall();

	imageCachedMiniDirty=1;
        imageHotSpot.z=0;
}

void XQDEIcon::applyEffects()
{
        #ifdef ENABLEDEBUGMSG
        qWarning("void XQDEIcon::applyEffects() count=%d", animations->count());
        #endif
        for(int i=0;i<animations->count();i++)
        {
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::applyEffects() type=%d", animations->at(i)->getType());
                #endif
                animations->at(i)->stepAgain();
        }
}


void XQDEIcon::xSetIconWM(QImage &wmi)
	{
		localIconImageWM=wmi.copy();
	}


void XQDEIcon::xUpdateBroadcast()
{
	Basket->sgeBasket_As_Changed(2, this, NULL);
}

void XQDEIcon::xSetZoom(int newZoom)
{
    //the CPU load with smooth effect is less than without :D (08.03.09)
    //this improuve image rendering a lot!
    xSetSmoothZoom(newZoom);

//        if(newZoom==imageHotSpot.z)return;
//        #ifdef ENABLEDEBUGMSG
//                qWarning("void XQDEIcon::xSetZoom(%d) %d %d begin", newZoom,localImageWidthEffects.width(),imageCached.width());
//        #endif
//        imageCachedDirty=1;
//        if(newZoom==DesktopEnvironment->GUI.handIconsMax && imageCachedMiniDirty==0)
//        {
//                imageCached=imageCachedMini;
//        }
//        else
//        {
//                if(newZoom==DesktopEnvironment->GUI.sizeIconsMax)
//                {
//                        imageCached=localImageWidthEffects;
//                }
//                else
//                {
//                #ifndef RESIZEVIAXRENDER
//                    imageCached=localImageWidthEffects.scaled(newZoom,newZoom, Qt::KeepAspectRatio, Qt::SmoothTransformation );
//                #else
//                XRenderResizeImage(localImageWidthEffects,imageCached,newZoom);
//                #endif
//                }
//        }
//        #ifdef ENABLEDEBUGMSG
//        qWarning("void XQDEIcon::xSetZoom(%d) %d %d end", newZoom,localImageWidthEffects.width(),imageCached.width());
//        #endif
//        imageHotSpot.z=newZoom;
//
//	if(isReflectionEnabled>0)
//	{
//            #ifdef ENABLEDEBUGMSG
//                qWarning("void XQDEIcon::xSetZoom(...) reflection");
//            #endif
//            #ifndef RESIZEVIAXRENDER
//                imageCachedReflection=localImageWidthEffectsReflection.scaled(newZoom,isReflectionEnabled, Qt::KeepAspectRatio, Qt::SmoothTransformation );
//            #else
//            XRenderResizeImage(localImageWidthEffectsReflection,imageCachedReflection,newZoom,isReflectionEnabled);
//            #endif
//
//	}
        /*
        QImage pip;
        XQDE_ImageReflectBottom(imageCached,pip, 8);
        imageCached=QPixmap(pip.width(),pip.height());
        imageCached.fill(Qt::transparent);
        widgetpaint->begin(&imageCached);
        widgetpaint->drawImage(0,0,pip);
        widgetpaint->end();
        */
}

void XQDEIcon::xSetSmoothZoom(int newZoom)
{
        //qWarning("void XQDEIcon::xSetSmoothZoom(int newZoom)");
        if(newZoom==imageHotSpot.z)return;
         #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::xSetSmoothZoom(%d) %d %d begin", newZoom,localImageWidthEffects.width(),imageCached.width());
        #endif
        imageCachedDirty=1;
        if(newZoom==DesktopEnvironment->GUI.handIconsMax && imageCachedMiniDirty==0)
        {
                imageCached=imageCachedMini;
        }
        else
        {
                if(newZoom==DesktopEnvironment->GUI.sizeIconsMax)
                {
                        imageCached=localImageWidthEffects;
                }
                else
                {
                #ifndef RESIZEVIAXRENDER
                imageCached=localImageWidthEffects.scaled(newZoom,newZoom, Qt::KeepAspectRatio, Qt::SmoothTransformation );
                #else
                XRenderResizeImageGood(localImageWidthEffects,imageCached,newZoom);
                #endif
                }
        }
        #ifdef ENABLEDEBUGMSG
        qWarning("void XQDEIcon::xSetZoom(%d) %d %d end", newZoom,localImageWidthEffects.width(),imageCached.width());
        #endif
        imageHotSpot.z=newZoom;
        if(isReflectionEnabled>0)
        {
            #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::xSetZoom(...) reflection");
            #endif
            #ifndef RESIZEVIAXRENDER
            imageCachedReflection=localImageWidthEffectsReflection.scaled(newZoom,isReflectionEnabled, Qt::KeepAspectRatio, Qt::SmoothTransformation );
             #else
            XRenderResizeImage(localImageWidthEffectsReflection,imageCachedReflection,newZoom,isReflectionEnabled);

            #endif

        }
        /*
        QImage pip;
        XQDE_ImageReflectBottom(imageCached,pip, 8);
        imageCached=QPixmap(pip.width(),pip.height());
        imageCached.fill(Qt::transparent);
        widgetpaint->begin(&imageCached);
        widgetpaint->drawImage(0,0,pip);
        widgetpaint->end();
        */
}

void XQDEIcon::setLogic(const QString &nl)
	{
		localLogicName=nl;
	}

QObject *XQDEIcon::sensor()
	{
		return localParent;
	}

int XQDEIcon::isRunning()
	{
//		if(forceRunning)return forceRunning;
		return ClientData->size() + PIDData->size();
	}
	
QStringList XQDEIcon::slotsSensorList()
	{
                QStringList list;
		for(int i=0;i<slotsSensor->count();i++)
		{
                        list.append(slotsSensor->at(i)->Slot);
		}
                return list;
	}

QString XQDEIcon::logic()
	{
		return localLogicName;
	}

QString XQDEIcon::icon()
	{
		return localIcon;
	}

QString XQDEIcon::title()
	{
		return localTitle;
	}
#ifndef RESIZEVIAXRENDER
QImage *XQDEIcon::imageClean()
#else
QPixmap *XQDEIcon::imageClean()
#endif
	{
		return &localImage;
	}


#ifndef RESIZEVIAXRENDER
void XQDEIcon::xSetImage(QImage &i)
#else
void XQDEIcon::xSetImage(QPixmap &i)
#endif
{
        //copy new image
	localImageWidthEffects=i;        
        
        if(isReflectionEnabled>0)
        {
            //create new reflection
            XRenderResizeImage(localImageWidthEffects,localImageWidthEffectsReflection,DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled);
            QImage pip;
            XQDE_ImageReflectBottom(localImageWidthEffectsReflection,pip);
            localImageWidthEffectsReflection=localImageWidthEffectsReflection.fromImage(pip);

            #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::xSetImage(...) reflection");
            #endif
//            #ifndef RESIZEVIAXRENDER
//            imageCachedReflection=localImageWidthEffectsReflection.scaled(newZoom,isReflectionEnabled, Qt::KeepAspectRatio, Qt::SmoothTransformation );
//             #else
////            XRenderResizeImage(localImageWidthEffectsReflection,imageCachedReflection,imageHotSpot.z,isReflectionEnabled);
//            imageCachedReflection = localImageWidthEffectsReflection.copy();
//            #endif

        }

        //copy new image in
        //xRepaintSmall();
	imageCachedMiniDirty=1;
	imageHotSpot.z=0;
}



#ifndef RESIZEVIAXRENDER
QImage *XQDEIcon::image()
#else
QPixmap *XQDEIcon::image()
#endif
{
		return &localImageWidthEffects;
}

QList <void *> *XQDEIcon::pidsData()
	{
		return PIDData;
	}
	
QList <void *> *XQDEIcon::clientsData()
	{
		return ClientData;
	}

void *XQDEIcon::clientData()
	{
		if(ClientData->size()>0)return ClientData->at(0);
		return 0;
	}

void XQDEIcon::setIconGeometry(int x,int y,int z)
	{
		iconGeometry.x=x;
		iconGeometry.y=y;
		iconGeometry.z=z;
		imageCachedRect.x=x;
		imageCachedRect.y=y;
		imageCachedRect.z=z;
		imageHotSpot.x=iconGeometry.x+iconGeometry.z/2;
		imageHotSpot.y=iconGeometry.y+iconGeometry.z/2;
		imageHotSpot.z=0;

		imageCachedArrowRect=imageHotSpot;
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEIcon::setIconGeometry(%d,%d,%d) to (%d,%d,%d)",x,y,z,x+MainWindow->x(),y+MainWindow->y(),z);
		#endif

		emit setGeometry(clientData(),x+MainWindow->x(),y+MainWindow->y(),z);
	}

extern QWidget *GlobalConfigurator;

void XQDEIcon::xConfigurator()
{
	GlobalConfigurator->show();
}
