//
// C++ Implementation: xqimage
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqimage.h"

#include <QPainter>

XQImage::XQImage(QObject *lRoot, QWidget *parent):XQWidget(lRoot,parent)
{
        pos.setX(0);
        pos.setY(0);
//	pos0.setX(0);
//	pos0.setY(0);

	//setAutoFillBackground(false);
	//setBackgroundRole(QPalette::NoRole);
	//setAttribute(Qt::WA_NoBackground);
	//setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	//move(50,50);
	setMouseTracking (true);
	setAcceptDrops(true);

	Buffer_Image_Status=0;
}


XQImage::~XQImage()
{
}
void XQImage::setPos(int lx,int ly)
{
        pos.setX(lx);
        pos.setY(ly);
//	posEnd.setX(lx);
//	posEnd.setY(ly);
	move(lx,ly);
}
void XQImage::setImage(const QString &item)
{
	setImage(item,0);
}
void XQImage::setCentered(int align)
{
	if(align)
	{
                pos.setX((width())/2-(buffer[Buffer_Image_Status].width()/2));
                pos.setY((height())/2-(buffer[Buffer_Image_Status].height()/2));
	}
	else
	{
                pos.setX(0);
                pos.setY(0);
	}
}
void XQImage::setImage(const QImage &item,int Focused)
{
        buffer[Focused]=item;
	update();
}

void XQImage::setImage(const QString &item,int Focused)
{
	bool rl=buffer[Focused].load(item);
	Q_UNUSED(rl);
	/*
	if(Focused==XQImage_Normal && rl)
	{
		if(posEnd.x()==pos.x())
		{
			resize(buffer[XQImage_Normal].width(),buffer[XQImage_Normal].height());
		}
		else
		{
			setCentered(1);
		}
	}
	else
	{
	}
*/
	update();
	//repaint();

}

void XQImage::paint(QPainter &p)
{
        p.drawImage(pos,buffer[Buffer_Image_Status]);
}
void XQImage::paint(int x,int y,QPainter &p)
{
	p.drawImage(QPoint(x,y),buffer[Buffer_Image_Status]);
}

void XQImage::paintEvent( QPaintEvent *e)
{
	XQWidget::paintEvent(e);
	return;
}
void XQImage::update()
{
	//paintBuffer=QImage(width(),height(),QImage::Format_ARGB32);
	// resize will be done in setFixedSize
        paintBuffer.fill(Qt::transparent);

	QPainter p;
	p.begin(&paintBuffer);
	p.drawImage(pos0,buffer[Buffer_Image_Status]);
	p.end();
}

void XQImage::mousePressEvent(QMouseEvent *)
{
	Buffer_Image_Status=XQImage_Clicked;
//        Buffer_Image_Status=Qt::MouseButtons;
	update();
	repaint();

}

void XQImage::mouseReleaseEvent (QMouseEvent *)
{
	Buffer_Image_Status=XQImage_Normal;
	update();
	repaint();

}

void XQImage::setRect(int top_right_x,int top_right_y,int bottom_left_x,int bottom_left_y)
{
//        pos.setX(top_right_x);
//        pos.setY(top_right_y);
//        posEnd.setX(bottom_left_x);
//        posEnd.setY(bottom_left_y);
        move(top_right_x, top_right_y);
}
