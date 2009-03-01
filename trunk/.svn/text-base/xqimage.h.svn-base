//
// C++ Interface: xqimage
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQIMAGE_H
#define XQIMAGE_H

#include <xqwidget.h>
#include <QImage>


const int XQImage_Normal=0;
const int XQImage_Over=1;
const int XQImage_Clicked=2;
const int XQImage_Disabled=3;
const int XQImage_MAXARRAY=4;


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQImage: public XQWidget
{
public:
    XQImage(QObject *, QWidget *parent = 0);
    ~XQImage();
	virtual void paintEvent( QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent (QMouseEvent *);
public slots:
	virtual void setImage(const QImage &,int);
	virtual void setImage(const QString &);
	virtual void setImage(const QString &,int);
	virtual void paint(QPainter &);
	virtual void paint(int,int,QPainter &);
	virtual void setPos(int,int);
	virtual void setRect(int,int,int,int);
	virtual void setCentered(int);
	virtual void update();
protected:
	QImage buffer[XQImage_MAXARRAY];
	QPoint pos0;
	int Buffer_Image_Status;

};

#endif
