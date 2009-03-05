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

#include "xqdeanimation.h"
#include "xqdeicon.h"
#include "xqdeaction.h"
#include "xqdeenvironment.h"

QImage *XQDE_ImageSetIntensity(QImage &lavoro,double i);

XQDEAnimation::XQDEAnimation(int type, XQDEIcon *icon,int endEffect,class XQDEAction *test, class XQDEAction *endAction)//, int ar)
{
	//autoRemove=ar;
        this->type=type;
        this->icon=icon;
        this->endEffect=endEffect;
        this->test=test;
        this->endAction=endAction;
        maxCicle=4;
	resetCurrentStep();
}

XQDEAnimation::~XQDEAnimation()
{
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
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEAnimation::step() %ld %d %ld %d",(long)test,currentStep,(long)endAction, maxCicle);
	#endif
        if(test)    //usato per effetto balzo
	{
            //Rimosso controllo per far continuare l'animazione fino alla fine
            //altrimenti si ferma dopo aver caricato la finestra
//		if(test->doTest()>0)
//		{
                        #ifdef ENABLEDEBUGMSG
			qWarning("void XQDEAnimation::step() A %d",currentStep);
			#endif
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
                        #ifdef ENABLEDEBUGMSG
			qWarning("void XQDEAnimation::step() X %d",currentStep);
			#endif
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
		
                #ifdef ENABLEDEBUGMSG
                qWarning("void XQDEAnimation::step() C");
                #endif
		if(currentStep>1)
		{
			currentStep--;
			icon->animationsNextFrameCounter++;
			stepAgain();
		}
		else
		{
                        #ifdef ENABLEDEBUGMSG
			qWarning("void XQDEAnimation::step(end) %ld %d %ld",(long)test,currentStep,(long)endAction);
			#endif
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
void XQDE_ImageResizeWithBorder(QImage &cleanSource, QImage &source, QImage &Buffer,int currentSize)
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
void MakeWindowOnTopPillow(void *);

void XQDEAnimation::stepAgain()
{
#ifndef RESIZEVIAXRENDER
	QImage *image;
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
                        image=icon->image();
                        #ifndef RESIZEVIAXRENDER
                        XQDE_ImageSetIntensity(image,currentFade);
                        #else
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
                                #ifdef ENABLEDEBUGMSG
                                qWarning("if(lastZ!=icon->detachedRect.z)");
                                #endif
                                lastZ=icon->detachedRect.z;
                                icon->setFixedSize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
                                icon->xRepaintDetached();
                                icon->repaint();
                        }
                        icon->move(icon->detachedRect.x+MainWindow->x(),icon->detachedRect.y+MainWindow->y());
//                        MakeWindowOnTopPillow((void *)icon->winId());
                        icon->show();
                        }
                        break;
        }

}
