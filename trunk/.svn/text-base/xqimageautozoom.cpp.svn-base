//
// C++ Implementation: xqimageautozoom
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqimageautozoom.h"
#include <xqdeenvironment.h>
#include <QMouseEvent>

#include <xqdesensor_zoomengine.h>

XQImageAutoZoom::XQImageAutoZoom(QObject *lRoot, QWidget *parent):XQImage(lRoot,parent)
{
	ZoomXY=NULL;
//	MappedDevices.insert("Zoom",new XQDESensor_ZoomEngine);
//	ZoomXY=MappedDevices["Zoom"]->readMat(0,0,0);
//qWarning("XQImageAutoZoom::XQImageAutoZoom() end");
}


XQImageAutoZoom::~XQImageAutoZoom()
{
}


void XQImageAutoZoom::setImage(const QString &item,int Focused)
{
	XQImage::setImage(item,Focused);
	Source_buffer[Focused]=buffer[Focused];
	buffer[Focused]=buffer[Focused].scaled (DesktopEnvironment->GUI.sizeIconsNormal,DesktopEnvironment->GUI.sizeIconsNormal, Qt::KeepAspectRatio, Qt::SmoothTransformation );
	setCentered(1);
	update();
}

void XQImageAutoZoom::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
XQImage::mousePressEvent(event);
}


void XQImageAutoZoom::mouseMoveEvent(QMouseEvent *e)
{
	int y=(e->pos().y())+pos0.y();
	int x=(e->pos().x())+pos0.x();

	int dx=2*abs(((posEnd.x()-pos.x())/2)-x);
	int dy=2*abs(((posEnd.y()-pos.y())/2)-y);
	if(dx>MAXICONSIZE)dx=MAXICONSIZE-1;
	if(dy>MAXICONSIZE)dy=MAXICONSIZE-1;
/*

	int maxdif=DesktopEnvironment->GUI.sizeIconsMax-DesktopEnvironment->GUI.sizeIconsMin;
	int nextSize=(width()-abs(pos0.x()-x));
*/
	//qWarning("next");
	if(ZoomXY==NULL)return;

	//qWarning("[%3d][%3d][%3d][%3d]1",0,pos0.x(),pos0.y(),width());
	int nextSize=ZoomXY[dx][dy];
	//qWarning("[%3d][%3d][%3d][%3d]2",nextSize,pos0.x(),pos0.y(),width());

	//buffer[Buffer_Image_Status]=Source_buffer[Buffer_Image_Status].copy();
	//nextSize=;

buffer[Buffer_Image_Status]=Source_buffer[Buffer_Image_Status].scaled (nextSize,nextSize, Qt::KeepAspectRatio, Qt::SmoothTransformation );
	//qWarning("[%3d][%3d][%3d][%3d]2",nextSize,pos0.x(),pos0.y(),width());

	setCentered(1);
	//qWarning("[%3d][%3d][%3d][%3d]3",nextSize,pos0.x(),pos0.y(),width());

	//qWarning("[%3d][%3d][%3d][%3d]4",nextSize,pos0.x(),pos0.y(),width());

	update();
	//qWarning("[%3d][%3d][%3d][%3d]5",nextSize,pos0.x(),pos0.y(),width());
	repaint();

        if (e->buttons() == Qt::LeftButton) {
            move(e->globalPos() - dragPosition);
            e->accept();
        }
	else
	{
/*
	QWidget *pp=parentWidget();
	if(pp)pp->repaint(geometry ());
	else repaint();
*/
	}
	//qWarning("[%3d][%3d][%3d][%3d]6",nextSize,pos0.x(),pos0.y(),width());
}
