#ifndef XQDEBase_H
#define XQDEBase_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QApplication>
#include <QList>

#include "xqdeclass.h"
#include "xqwidget.h"
#include "xqimageautozoom.h"


class XQDEBase : public XQWidget 
{
	Q_OBJECT
	public:
	XQDEBase(XQDEClass *parent = 0);
	~XQDEBase();
	virtual void paintEvent(QPaintEvent *);
	virtual void paint(QPainter &);
	virtual void xReset();
	void mouseMoveEvent(QMouseEvent *);
	
	QList<XQWidget *> globalXQDEWidgets;
	QList<XQImageAutoZoom *> globalXQImages;
	QImage iBuffer;
	QPainter pBuffer;
};

#endif
