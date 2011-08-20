//
// C++ Implementation: xqdeanimation
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QObject>

#include <QAbstractAnimation>
#include <QStateMachine>
#include <QAbstractTransition>
#include <QPropertyAnimation>
#include <QAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

#include <QGraphicsEffect>

#include "xqdeanimation.h"
#include "xqdeicon.h"
#include "xqdeaction.h"
#include "xqdeenvironment.h"

QImage *XQDE_ImageSetIntensity(QImage &lavoro,double i);

//static const char * const AnimationTypes[] = {
//    QT_TR_NOOP("fade"),
//    QT_TR_NOOP("magnify"),
//    QT_TR_NOOP("unmagnify")
//    QT_TR_NOOP("fly"),
//    0
//};

XQDEAnimation::XQDEAnimation(int type, XQDEIcon *icon,int endEffect,class XQDEAction *startaction, class XQDEAction *endAction)//, int ar)
{
	//autoRemove=ar;
        this->type=type;
        this->icon=icon;
        this->endEffect=endEffect;
	this->startaction=startaction;
        this->endAction=endAction;
        maxCicle=4;
	resetCurrentStep();
}

XQDEAnimation::~XQDEAnimation()
{
}

QStringList XQDEAnimation::getAnimationTypes()
{
    return QStringList() << "fade" << "unmagnify" << "magnify" << "fly";
}

const unsigned int N_MAX = 15; //80;
const unsigned int MAX_HEIGHT = 64; //256;

void XQDEAnimation::resetCurrentStep()
{
	switch(type)
	{
		case 4:
			currentStep=N_MAX;
		break;
		default:
			currentStep=10;
		break;
	}
}



void XQDEAnimation::step()
{
	qDebug("void XQDEAnimation::step() %ld %d %ld %d",(long)startaction,currentStep,(long)endAction, maxCicle);
	if(startaction)    //usato per effetto balzo
	{
            //Rimosso controllo per far continuare l'animazione fino alla fine
            //altrimenti si ferma dopo aver caricato la finestra
//		if(startaction->doaction()>0)
//		{
                        qDebug("void XQDEAnimation::step() A %d",currentStep);
			if(currentStep>1)
			{
				currentStep--;
			}
			else
			{
				if(maxCicle>0)
				{
					maxCicle--;
					resetCurrentStep();
				}
				else
				{
					currentStep--;
				}
			}
                        qDebug("void XQDEAnimation::step() X %d",currentStep);
                        icon->animationsNextFrameCounter++;
                        stepAgain();

                        //check the end of the effect
			if(currentStep<1)
			{
				icon->redoEffects();
				if(endAction)
				{
					endAction->Pointer=icon;
					endAction->doit();
				}
                                icon->hide();
                                icon->detachedRect.z=0;
				icon=NULL;				
			}
//		}
//		else
//		{
//                        #ifdef ENABLEDEBUGMSG
//			qWarning("void XQDEAnimation::step() B");
//			#endif
//			currentStep=0;
//			icon->animationsNextFrameCounter++;
//			stepAgain();
//			icon->redoEffects();
//			/*
//			if(autoRemove>0)
//			{
//				qWarning("void XQDEAnimation::step(end) Autoremove!!");
//				int kaniindex=icon->animations->indexOf(this);
//				if(kaniindex>=0){
//					icon->animations->takeAt(kaniindex);
//					qWarning("void XQDEAnimation::step(end) removed! %d",kaniindex);
//				}
//				else
//				{
//					qWarning("void XQDEAnimation::step(end) Warning! cannot found me on animations");
//				}
//			}
//			*/
//
//			if(endAction)
//			{
//				endAction->Pointer=icon;
//				endAction->doit();
//			}
//			icon=NULL;
//		}
	}
	else
	{
		
                qDebug("void XQDEAnimation::step() C");
		if(currentStep>1)
		{
			currentStep--;
			icon->animationsNextFrameCounter++;
			stepAgain();
		}
		else
		{
			qDebug("void XQDEAnimation::step(end) %ld %d %ld",(long)startaction,currentStep,(long)endAction);
			stepAgain();
			icon->redoEffects();
			/*
			if(autoRemove>0)
			{
				qWarning("void XQDEAnimation::step(end) Autoremove!!");
				int kaniindex=icon->animations->indexOf(this);
				if(kaniindex>=0){
					icon->animations->takeAt(kaniindex);
					qWarning("void XQDEAnimation::step(end) removed! %d",kaniindex);
				}
				else
				{
					qWarning("void XQDEAnimation::step(end) Warning! cannot found me on animations");
				}
			}
			*/
			
			if(endAction)
			{
				endAction->Pointer=icon;
				endAction->doit();
			}
			icon=NULL;
		}
	}
}
#ifndef RESIZEVIAXRENDER
void XQDE_ImageResizeWithBorder(QImage &cleanSource, QImage &image, QImage &Buffer, int sourceSize, int currentSize)
#else
void XQDE_ImageResizeWithBorder(QPixmap &cleanSource, QPixmap &image, QPixmap &Buffer,int sourceSize, int currentSize)
#endif
{
	int currentSizeDisplaced;
	if(currentSize>=sourceSize && sourceSize>0)
	{
		Buffer=cleanSource.copy();
	}
	else
	{
		#ifndef RESIZEVIAXRENDER
		Buffer=QImage(sourceSize,sourceSize,QImage::Format_ARGB32);
		#else
		Buffer=QPixmap(sourceSize,sourceSize);
		#endif
		Buffer.fill(Qt::transparent);
		
		if(currentSize)
		{
			currentSizeDisplaced=((sourceSize-currentSize)/2);
			QPainter p;
			p.begin(&Buffer);
			#ifndef RESIZEVIAXRENDER
			QImage Buffer2=image.scaled(currentSize,currentSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
			p.drawImage(currentSizeDisplaced,currentSizeDisplaced,Buffer2);
			#else
			QPixmap Buffer2;
			XRenderResizeImage(image,Buffer2,currentSize);
			p.drawPixmap(currentSizeDisplaced,currentSizeDisplaced,Buffer2);
			#endif
			p.end();
		}
		else
		{
		}
	}
}

void XQDEAnimation::stepAgain()
{
#ifndef RESIZEVIAXRENDER
        QImage image;
	QImage Buffer;
#else
	QPixmap *image;
	QImage imageImage;
	QPixmap Buffer;
#endif

        double currentFade;
        int currentSize;

        switch(type)
        {
                case 1://fade!
                        currentFade=((1.0-((double)endEffect/10))/(double)10)*currentStep+((double)endEffect/10);

                        #ifndef RESIZEVIAXRENDER
			image=icon->image()->copy();
                        XQDE_ImageSetIntensity(image,currentFade);
                        icon->xSetImage(image);
                        #else
			image=icon->image();
                        imageImage=image->toImage();
                        XQDE_ImageSetIntensity(imageImage,currentFade);
                        Buffer=QPixmap::fromImage(imageImage);

                        //pix.fill(QColor(255,0,0));
                        icon->xSetImage(Buffer);
                        delete image;
                        #endif
                        break;
                case 2://resize from z->0
                        currentSize=(int)(((double)icon->imageCachedRect.z/(double)10)*(double)currentStep);
                        XQDE_ImageResizeWithBorder(*icon->imageClean(),*icon->image(),Buffer,icon->imageCachedRect.z,currentSize);
			icon->xSetImage(Buffer);
                        break;
                case 3://resize from 0->.z
                        currentSize=(int)(((double)icon->imageCachedRect.z/(double)10)*(double)(10-currentStep));
                        XQDE_ImageResizeWithBorder(*icon->imageClean(),*icon->image(),Buffer,icon->imageCachedRect.z,currentSize);
			icon->xSetImage(Buffer);
                        break;
                case 4:	// fly object
                {
                        static int lastZ=0;

                        int n=currentStep;
                        double t  = N_MAX - n;
                        double v0 = (MAX_HEIGHT*this->maxCicle)/N_MAX;
                        double g = (2*v0)/N_MAX;
                        currentSize = (unsigned int)(v0*t - g*t*t/2);

                        icon->detachedRect.z=icon->imageCachedRect.z;
                        switch(DesktopEnvironment->GUI.dockAlign)
                        {
                                case 0:
                                        icon->detachedRect.x=icon->imageCachedRect.x;
                                        icon->detachedRect.y=(icon->imageCachedRect.y-currentSize);
                                break;
                                case 1:
                                        icon->detachedRect.x=icon->imageCachedRect.x;
                                        icon->detachedRect.y=icon->imageCachedRect.y-currentSize;
                                break;
                                case 2:
                                        icon->detachedRect.x=icon->imageCachedRect.x+currentSize;
                                        icon->detachedRect.y=icon->imageCachedRect.y;
                                break;
                                case 3:
                                        icon->detachedRect.x=icon->imageCachedRect.x-currentSize;
                                        icon->detachedRect.y=icon->imageCachedRect.y;
                                break;
                        }
			if(lastZ!=icon->detachedRect.z)
			{
				qDebug("if(lastZ!=icon->detachedRect.z)");
				lastZ=icon->detachedRect.z;
				icon->setFixedSize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
				icon->xRepaintDetached();
				icon->repaint();
			}
			icon->move(icon->detachedRect.x+MainWindow->x(),icon->detachedRect.y+MainWindow->y());
			//ToDo: non usare show per mostrare icona, resta sopra alle finestre
			icon->show();

//			QPropertyAnimation *animation = new QPropertyAnimation(icon, "geometry");
//			animation->setDuration(1000);
//			animation->setStartValue(QRect(icon->imageCachedRect.x, icon->imageCachedRect.y, DesktopEnvironment->GUI.sizeIconsMax, DesktopEnvironment->GUI.sizeIconsMax));
//			animation->setEndValue(QRect(icon->imageCachedRect.x, icon->imageCachedRect.y-currentSize, DesktopEnvironment->GUI.sizeIconsMax, DesktopEnvironment->GUI.sizeIconsMax));

//			animation->setEasingCurve(QEasingCurve::OutBounce);

//			animation->start();

//			//newIcon->move(QPoint(100,100));
//			icon->raise();

//			QGraphicsDropShadowEffect *m_glowEffect = new QGraphicsDropShadowEffect(icon);
//			m_glowEffect->setOffset(0);
//			icon->setGraphicsEffect(m_glowEffect);

//			m_glowEffect->setEnabled(true);
//			m_glowEffect->setBlurRadius(5);
//			m_glowEffect->setColor(Qt::blue);


                        }
                        break;
        }

}
