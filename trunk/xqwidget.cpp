//
// C++ Implementation: xqwidget
//
// Description: 
// Main Widget to paint all the dock
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QPaintEvent>
//#include <stdlib.h>
#include <QApplication>
#include <QPainter>

#include "xqwidget.h"
#include "xqde.h"


XQWidget::XQWidget(QObject *,QWidget *parent) : QWidget(parent)
{
        XQWidgetContructor(0,parent, "");
}

XQWidget::XQWidget(QObject *,QWidget *parent, QString HasNamedIcon)
 : QWidget(parent)
{
        XQWidgetContructor(0,parent, HasNamedIcon);
}


XQWidget::~XQWidget()
{
    if(widgetpaint) delete widgetpaint;
}


void XQWidget::XQWidgetContructor(QObject *,QWidget *parent, QString HasNamedIcon)
{


        widgetpaint = new QPainter();

        paintBuffer=QImage(0,0,QImage::Format_ARGB32);
//        paintBuffer.fill(Qt::transparent);

        //remove window frame
        setWindowFlags(Qt::FramelessWindowHint);
//        setAttribute(Qt::WA_OpaquePaintEvent);
        setAttribute(Qt::WA_TranslucentBackground);


        //Bug: white background on showing widget - SOLVED! (21.02.09)
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window, Qt::transparent);
        this->setPalette(palette);
        setAutoFillBackground(true);
//        widgetpaint->setCompositionMode(QPainter::CompositionMode_SourceOver);


}



void XQWidget::paintEvent( QPaintEvent *e)
{
//        widgetpaint->setCompositionMode(QPainter::CompositionMode_Source);

        widgetpaint->begin(this);

//        widgetpaint->setRenderHint(QPainter::Antialiasing, true);
//        widgetpaint->fillRect(rect(), Qt::transparent);
//        widgetpaint->eraseRect(rect());

        widgetpaint->drawImage(e->rect(), paintBuffer, e->rect());

        widgetpaint->end();

        // resolve bug on kwin and shadows
        // disable shadows when using kwin (es. KWin::setShadowSize())
        // http://bugs.kde.org/show_bug.cgi?id=99198
        setMask(rect());

}
					

void XQWidget::setPos(int top_left_x,int top_left_y)
{
        pos.setX(top_left_x);
        pos.setY(top_left_y);
}

void XQWidget::paint(QPainter &p)
{
	p.drawImage(pos,paintBuffer);
}

void XQWidget::paint(int x,int y,QPainter &p)
{
	p.drawImage(QPoint(x,y),paintBuffer);
}

void XQWidget::setFixedSize(int width,int height)
{

        //controllo se devo fare il resize del widget
        if((width * height) != (this->width()*this->height()))
        {
            paintBuffer=QImage(width,height,QImage::Format_ARGB32);
            QWidget::setFixedSize(width,height);
        }
	
}


void XQWidget::setRect(int top_left_x,int top_left_y,int bottom_right_x,int bottom_right_y)
{
//        pos.setX(top_left_x);
//        pos.setY(top_left_y);
//        posEnd.setX(bottom_right_x);
//        posEnd.setY(bottom_right_y);
        setFixedSize(bottom_right_x - top_left_x, bottom_right_y - top_left_y);
        move(top_left_x, top_left_y);
}
