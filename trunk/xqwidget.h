//
// C++ Interface: xqwidget
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQWIDGET_H
#define XQWIDGET_H

#include <QWidget>
#include <QImage>
#include "xqde.h"


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQWidget :  public QWidget //public XQDEClass,
{
Q_OBJECT
public:
	XQWidget(QObject  *, QWidget *parent, QString HasNamedIcon);
	XQWidget(QObject  *, QWidget *parent = 0);
        ~XQWidget();
	virtual void paintEvent( QPaintEvent *);
protected:
	void XQWidgetContructor(QObject  *, QWidget *, QString);

public slots:
//	virtual void setImage(const QString &);
	virtual void setPos(int,int);
	virtual void setRect(int,int,int,int);
	virtual void paint(QPainter &);
	virtual void paint(int,int,QPainter &);
	virtual void setFixedSize(int,int);
protected:
	QPoint pos;
	QPoint posEnd;
	QImage paintBuffer;


	// Common variables to speedup class access
        class QPainter *widgetpaint;


};

#endif
