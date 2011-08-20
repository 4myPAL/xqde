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
#include <QBitmap>


#include "xqdeicon.h"
#include "xqdeenvironment.h"
// will be remove
#include "xqdebasket.h"
#include "xqdeuiiconwindow.h"
//#include "xqdeenvironment.h"
#include "xqdeaction.h"
#include "xqdeanimation.h"
#include "xqtext.h"

void MakeWindowOnTopPillow(void *);

#ifndef RESIZEVIAXRENDER
extern QImage *XQDE_ImageReflectBottom(QImage &xImgSource,QImage &newImage, int rHeight);
extern QImage *XQDE_ImageReflectBottom(QImage &xImgSource,QImage &newImage);
#else
extern QImage *XQDE_ImageReflectBottom(QPixmap &xImgSource,QImage &newImage, int rHeight);
extern QImage *XQDE_ImageReflectBottom(QPixmap &xImgSource,QImage &newImage);
void XRenderResizeImageGood(QPixmap &Source,QPixmap &thumbnail,int maxDimension);
void XRenderResizeImage(QPixmap &Source,QPixmap &thumbnail,int mx, int my);
#endif




XQDEIcon::XQDEIcon(QString logicName,QObject *parent, void *cData,QImage *defaultImg, QString strTitle, QString defaulticon) : XQWidget(parent) //QGraphicsWidget(parent)
{
        qDebug("XQDEIcon::XQDEIcon(QString logicName,QObject *parent, void *cData,QImage *defaultImg, QString strTitle, QString defaulticon): XQWidget(parent)");

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
        localThumbnail=QImage(0,0,QImage::Format_ARGB32);
//        localThumbnail.fill(Qt::transparent);
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
	
        qDebug("XQDEIcon::XQDEIcon() end");
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
        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("/icons/new")),tr("New window"),this,SLOT(menu_newWindow()));

//        ContextPopupMenu->addAction(QIcon(":/images/new.png"),tr("New window"),this,SLOT(menu_newWindow()));
	if(storeOnExit==0)
	{
                ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("/icons/keepindock")),tr("Keep in dock"),this,SLOT(menu_setKeepInDock()));
//                ContextPopupMenu->addAction(QIcon(":/images/keepindock.png"),tr("Keep in dock"),this,SLOT(menu_setKeepInDock()));
	}
	else
	{
                ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("/icons/removeonexit")),tr("Remove on exit"),this,SLOT(menu_setRemoveOnExit()));
//                ContextPopupMenu->addAction(QIcon(":/images/removeonexit.png"),tr("Remove on exit"),this,SLOT(menu_setRemoveOnExit()));

	}

        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("/icons/configure")),tr("Configure Icon"),this,SLOT(xConfigure()));
        ContextPopupMenu->addAction(QIcon(DesktopEnvironment->Theme.findImage("/icons/global_configure")),tr("Global configuration"),this,SLOT(xConfigurator()));
//        ContextPopupMenu->addAction(QIcon(":/images/configure.png"),tr("Configure"),this,SLOT(xConfigure()));
//        ContextPopupMenu->addAction(QIcon(":/images/global_configure.png"),tr("Global configuration"),this,SLOT(xConfigurator()));
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
                        else menu_newWindow();
                break;
                //New (04.03.09) start application on middle click
                case XQDE_USER_ACTION_CLICKMI:
                        menu_newWindow();
		break;
	}
}
void XQDEIcon::userAction(int a,int b,int c)
{
        qDebug("void XQDEIcon::userAction(int %d,int %d,int %d)",a,b,c);

	if (receivers(SIGNAL(sguserAction(int,int,int,void *, XQDEIcon *))) > 0)
	{
                qDebug("void XQDEIcon::userAction sending signals");

		emit sguserAction(a,b,c,clientData(),this);
	}
	else
	{
                qDebug("void XQDEIcon::userAction default action");

		userActionDefault(a,b,c);
	}
}
void XQDEIcon::xRepaintSmall()
{
        qDebug("void XQDEIcon::xRepaintSmall() %d", localImageWidthEffects.width());

	#ifndef RESIZEVIAXRENDER
	imageCachedMini=localImageWidthEffects.scaled (DesktopEnvironment->GUI.handIconsMax,DesktopEnvironment->GUI.handIconsMax, Qt::KeepAspectRatio, Qt::SmoothTransformation );
	#else
	XRenderResizeImageGood(localImageWidthEffects,imageCachedMini,DesktopEnvironment->GUI.handIconsMax);
	#endif
        qDebug("void XQDEIcon::xRepaintSmall() %d", localImageWidthEffects.width());

	imageCachedMiniDirty=0;
}

void XQDEIcon::xRepaintDetached()
{
        qDebug("void XQDEIcon::xRepaintDetached()");

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
        qDebug("void XQDEIcon::xRepaint() Qt");

	#else
        qDebug("void XQDEIcon::xRepaint() XRender");

	#endif
	
        #ifndef RESIZEVIAXRENDER
                localImage=QImage(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax,QImage::Format_ARGB32);
        #else
                localImage=QPixmap(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
        #endif

        localImage.fill(Qt::transparent);
	

//	if(localThumbnail.width()>8) //check if a thumbnail is present
        if(!localThumbnail.isNull()) //check if a thumbnail is present
	{

                qDebug("void XQDEIcon::xRepaint() localThumbnail.width()=%d",localThumbnail.width());
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
	
        qDebug("void XQDEIcon::xRepaint() %d %d A",localImage.width(), localIconImage.width());


//	localImageWidthEffects=localImage.copy();
        qDebug("void XQDEIcon::xRepaint() %d %d B",localImage.width(), localIconImage.width());
	applyEffects();
        qDebug("void XQDEIcon::xRepaint() %d %d C",localImage.width(), localIconImage.width());

//        imageHotSpot.z=0;

//	xRepaintSmall();
        
//	if(isReflectionEnabled>0)
//	{
//                #ifdef ENABLEDEBUGMSG
//                qWarning("void XQDEIcon::xRepaint() Reflection repainting");
//                #endif
//                #ifndef RESIZEVIAXRENDER
//                localImageWidthEffectsReflection=localImageWidthEffects.scaled(DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled, Qt::IgnoreAspectRatio, Qt::FastTransformation );
//                #else
//                XRenderResizeImage(localImageWidthEffects,localImageWidthEffectsReflection,DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled);
//                #endif
//		QImage pip;
//                XQDE_ImageReflectBottom(localImageWidthEffectsReflection,pip);
//                #ifndef RESIZEVIAXRENDER
//                localImageWidthEffectsReflection=pip.copy();
//                #else
//                localImageWidthEffectsReflection=localImageWidthEffectsReflection.fromImage(pip);
//                #endif
//	}
//	
//	#ifdef ENABLEDEBUGMSG
//	qWarning("void XQDEIcon::xRepaint() %d %d %d D",localImage.width(), localIconImage.width(),localImageWidthEffects.width());
//	#endif
        
        xSetImage(localImage);
}

//Added(24.02.09)
extern QString DataPath;
#include <QDir>

void XQDEIcon::xReset()
{
        qDebug("void XQDEIcon::xReset() %s",localIcon.toUtf8().constData());

	if( localIconImage.isNull()){
        // ricerca icona, 1) locale, 2) carica da Window Manager 3)imagine per removed icon
	int bad=1;
	QString newImageFile=DesktopEnvironment->Theme.findImage(localIcon);
	if(newImageFile!="")
	{
		if(localIconImage.load(newImageFile)) bad=0;
	}
	if(bad > 0 && enableIconFromWindow>0 && localIconImageWM.width()>8)
        {
                localIconImage=localIconImageWM;
                //Temp HACK (24.02.09) to resolve bug when app. are closed (is a "cache")
		//localIconImage.save(QDir::homePath() + "/.xqde/icons/"+localIcon, "PNG");
		bad=0;
	}
	if(bad>0)
        {
                //Todo: skip findImage if removeimage action is active
                //Bug: some applications show the correct icon in remove animation
                //      other show the unknown icon....
		newImageFile=DesktopEnvironment->Theme.findImage("unknown");
		if(newImageFile!="" && localIconImage.isNull()) //new! use a unknow image if no other images was loaded
		{
			if(!localIconImage.load(newImageFile))
			{
				qWarning("Cannot find suitable icon");
			}
		}
        }
    }
        qDebug("void XQDEIcon::xReset() localIconImage.width()=%d to %ld", localIconImage.width(),DesktopEnvironment->GUI.sizeIconsMax);

	//check if the size of the icon is correct
        if(localIconImage.width()!=DesktopEnvironment->GUI.sizeIconsMax)
        {
                qDebug("void XQDEIcon::xReset() warning duty cicle %d to %ld", localIconImage.width(),DesktopEnvironment->GUI.sizeIconsMax);

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

void XQDEIcon::xSetTitle(const QString &newIconTitle)
{
        qDebug("void XQDEIcon::xSetTitle(QString newIcon)");

        if(newIconTitle==localTitle)return;
        localTitle=newIconTitle;
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
        XQDEUIIconWindow *iconConfig=(XQDEUIIconWindow *)ExternalConfigurator;
        iconConfig->setObject(this);
        iconConfig->setWindowTitle(this->title());
        iconConfig->show();
}

void XQDEIcon::redoEffects()
{
        qDebug("void XQDEIcon::redoEffects() %d %d",localImageWidthEffects.width(), localImage.width());

	localImageWidthEffects=localImage.copy();
        //xRepaintSmall();

	imageCachedMiniDirty=1;
        imageHotSpot.z=0;
}

void XQDEIcon::applyEffects()
{
        qDebug("void XQDEIcon::applyEffects() count=%d", animations->count());
        for(int i=0;i<animations->count();i++)
        {
                qDebug("void XQDEIcon::applyEffects() type=%d", animations->at(i)->getType());
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

        qDebug("void XQDEIcon::xSetSmoothZoom(%d) %d %d begin", newZoom,localImageWidthEffects.width(),imageCached.width());
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

        qDebug("void XQDEIcon::xSetZoom(%d) %d %d end", newZoom,localImageWidthEffects.width(),imageCached.width());

        imageHotSpot.z=newZoom;
        if(isReflectionEnabled>0)
        {
            qDebug("void XQDEIcon::xSetZoom(...) reflection");

            #ifndef RESIZEVIAXRENDER
            imageCachedReflection=localImageWidthEffectsReflection.scaled(newZoom,isReflectionEnabled, Qt::IgnoreAspectRatio, Qt::FastTransformation );
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
    if(i.isNull()) localImageWidthEffects.fill(Qt::transparent);
    else localImageWidthEffects=i.copy();
        
        if(isReflectionEnabled>0)
        {
            //create new reflection
            #ifndef RESIZEVIAXRENDER
            localImageWidthEffectsReflection = localImageWidthEffects.scaled(DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled, Qt::IgnoreAspectRatio, Qt::FastTransformation);
            #else
            XRenderResizeImage(localImageWidthEffects,localImageWidthEffectsReflection,DesktopEnvironment->GUI.sizeIconsMax,isReflectionEnabled);
            #endif

            QImage pip;
            XQDE_ImageReflectBottom(localImageWidthEffectsReflection,pip);
            #ifndef RESIZEVIAXRENDER
            localImageWidthEffectsReflection=pip.copy();
            #else
            localImageWidthEffectsReflection=localImageWidthEffectsReflection.fromImage(pip);
            #endif

            qDebug("void XQDEIcon::xSetImage(...) reflection");
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

QRect XQDEIcon::getAttachedWindowsPosition() const
{
    return m_position;
}

void XQDEIcon::setAttachedWindowsPosition(QRect newpos)
{
    m_position = newpos;
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
                qDebug("void XQDEIcon::setIconGeometry(%d,%d,%d) to (%d,%d,%d)",x,y,z,x+MainWindow->x(),y+MainWindow->y(),z);


		emit setGeometry(clientData(),x+MainWindow->x(),y+MainWindow->y(),z);
	}

extern QWidget *GlobalConfigurator;

void XQDEIcon::xConfigurator()
{
	GlobalConfigurator->show();
}


//void XEPlugin_Command::dropIcon(int icon,QDropEvent*event)
//{
//	QString basket;
//	if(QTextDrag::decode (event, basket)==true)
//	{
//		if(icon<0)return;
//		uint TargetIcon=icon;
//		if(TargetIcon <ActiveConfiguration->ObjectsIcons.count())
//		{
//
//#ifdef ENABLE_STATS
////0.36 TODO!
//ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Statistics.onDropExec++;
//#endif
//
//
//
//			//qWarning(QString("(%1)[%1][%1] %1").arg(ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Info.Name).arg(event->pos().x()).arg(event->pos().y()).arg(basket));
//
//			if(0)
//			{
//				dropIconAddIcon(icon,event);
//			}
//			else
//			{
//	QString name;
//	QStringList lst;
//	QUriDrag::decodeLocalFiles(event, lst);
//	name=lst[0];
//	int pos=name.findRev(".desktop", -1);
//	basket="";
//	if(pos!=-1)
//	{
//		KSimpleConfig *desktopfile;
//		desktopfile = new KSimpleConfig(lst[0], TRUE);
//		desktopfile->setGroup("Desktop Entry");
//		if(desktopfile->readEntry("Type")=="Link")
//		{
//			basket=desktopfile->readEntry("URL");
//		}
//		else if(desktopfile->readEntry("Type")=="Application")
//		{
//			dropIconAddIcon(icon,event);
//			return;
//		}
//		else
//		{
//			basket=desktopfile->readEntry("Exec");
//		}
//
//		delete(desktopfile);
//	}
//	else
//	{
//		pos=name.findRev("/", -1);
//		if(pos!=-1)
//		{
//			name.remove(1, pos);
//			name.remove("/", TRUE);
//		}
//		basket=lst[0];
//
//	}
//			//qWarning(basket);
//			if(ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Actions.onDropExec=="")
//			{
//			ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Actions.onDropExec=ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Actions.onClickExec+" \"%1\"";
//			}
//			//qWarning(ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Actions.onDropExec.arg(basket));
//			KRun::runCommand(ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Actions.onDropExec.arg(basket));
//
//			}
//
//		}
//	}
//
//}
//
//
///*!
//    \fn XEPlugin_Command::dropIconAddIcon(int,XSGObjectIcon *)
// */
//void XEPlugin_Command::dropIconAddIcon(int TargetIcon,QDropEvent*event)
//{
//
//	if(Configurator==NULL)return;
//	XSGObjectIcon *addedCfg=Configurator->iconAdd();
//
////	XSGObjectIcon *addedCfg=new XSGObjectIcon;
//
//	QString className;
//	QString fileName;
//	QString groupName;
//	QString onClickExec;
//	QString overText;
//	QString newImg;
//
//
//	QString name;
//	QStringList lst;
//	QUriDrag::decodeLocalFiles(event, lst);
//	name=lst[0];
//	int pos=name.findRev(".desktop", -1);
//	if(pos!=-1)
//	{
//		KSimpleConfig *desktopfile;
//		desktopfile = new KSimpleConfig(lst[0], TRUE);
//		desktopfile->setGroup("Desktop Entry");
//		name=		desktopfile->readEntry("Name");
//		onClickExec=	desktopfile->readEntry("Exec");
//		newImg=		desktopfile->readEntry("Icon");
//		overText=	desktopfile->readEntry("GenericName");
//		if(overText=="")
//		{
//			overText=	desktopfile->readEntry("Comment");
//		}
//		groupName=		desktopfile->readEntry("Categories");
//		delete(desktopfile);
//	}
//	else
//	{
//		pos=name.findRev("/", -1);
//		if(pos!=-1)
//		{
//			name.remove(1, pos);
//			name.remove("/", TRUE);
//		}
//
//		onClickExec=lst[0];
//		newImg=name;
//		overText=name;
//		groupName=name;
//	}
//
//	if(name=="")
//	{
//		name=lst[0];
//	}
//	if(groupName=="")
//	{
//		groupName=name;
//	}
//	if(overText=="")
//	{
//		overText=name;
//	}
//
//	if(ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Info.className!="GSeparator")
//	{
//	groupName=ActiveConfiguration->ObjectsIcons.at(TargetIcon)->Info.Group;
//	}
//
//	className="GIcon";
//
//	addedCfg->Tasks.PopupMenu=NULL;
//	addedCfg->PluginPopupMenu=NULL;
//
//	addedCfg->Tasks.Proces.clear();
//	addedCfg->Tasks.MiniTextShow=1;
//	addedCfg->Info.className=className;
//	addedCfg->Info.fileName=fileName;
//	addedCfg->Info.Name=name;
//	addedCfg->Info.Group=groupName;
//	addedCfg->Actions.onClickExec=onClickExec;
//	addedCfg->Actions.onDropExec=onClickExec+" \"%1\"";
//	addedCfg->OverText=overText;
//	addedCfg->Images.imgFileName=newImg;
//	addedCfg->Images.imgFileArrow="arrow.png";
//	addedCfg->Images.imgFileDrop="drop.png";
//	addedCfg->Images.imgFileOverlay="";
//
//	addedCfg->Tasks.WindowTitle.append(overText);
//	addedCfg->Tasks.TaskName.append(name);
//	addedCfg->Tasks.ClassName.append(name);
//
//	addedCfg->Tasks.ShowThumbnail=0;
//	addedCfg->Actions.iAnimationMask=0;
//	addedCfg->Tasks.TaskInfo=NULL;
//	addedCfg->TimeToLive=0;
//
//
//	// check for existent icons
//	for(uint i=0;i<ActiveConfiguration->RollingIcons.count();i++)
//	{
//		// we add only on rolling icons
//		if(addedCfg->Info.Name==ActiveConfiguration->RollingIcons.at(i)->Info.Name)
//		{
//		/*
//			// we only update the image:
//			changeImageByName(addedCfg->Info.Name,addedCfg->Images.imgFileName);
//		*/
//			delete addedCfg;
//			return;
//		}
//	}
//
//	ActiveConfiguration->RollingIcons.append(addedCfg);
//
//	for(uint i=0;i<ActiveConfiguration->ObjectsIcons.count();i++)
//	{
//		// we add only on rolling icons
//		if(addedCfg->Info.Group==ActiveConfiguration->ObjectsIcons.at(i)->Info.Group)return;
//	}
//
//	ActiveConfiguration->ObjectsIcons.append(addedCfg);
//	xGDocker->xEventTaskAppend(ActiveConfiguration->ObjectsIcons.count()-1);
//
//
//}

