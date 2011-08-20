//
// C++ Interface: xqimageautozoom
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQIMAGEAUTOZOOM_H
#define XQIMAGEAUTOZOOM_H

#include <xqimage.h>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQImageAutoZoom : public XQImage
{
Q_OBJECT
public:
    XQImageAutoZoom(QObject *, QWidget *parent = 0);

    ~XQImageAutoZoom();
    virtual void MoveEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
public slots:
	virtual void setImage(const QString &,int);
protected:
	QImage Source_buffer[XQImage_MAXARRAY];
	long **ZoomXY;
private:
        QPoint dragPosition;
};

#endif
