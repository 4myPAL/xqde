//
// C++ Implementation: xqtext
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QPixmap>
#include <QImage>
#include <QPainter>

#include "xqtext.h"


XQText::XQText(QObject *r, QWidget *p):XQWidget(r,p)
{
}

XQText::~XQText()
{
}


void XQText::xDrawText()
{
	if(isTextDrawed)return;

	XSCfgTextFont *FontStyle=&DesktopEnvironment->GUI.desktopFont;
        QFont font(FontStyle->FontFamily, FontStyle->FontSize);
        QFontMetrics fm(font);
        int pixelsWide = fm.width("  " + pillowText + "  ") ; //Add 2 spaces at the start and the end
        int pixelsHigh = fm.height();
        
	//qWarning("void XQText::xDrawText()");
	//qWarning("void XQText::xDrawText(%s,%d,%d,%d)",pillowText.toAscii().data(),h,w,FontStyle->FontSize);
        QPixmap text_area(pixelsWide,pixelsHigh);
        text_area.fill(Qt::transparent);
        QPainter painter(&text_area);
        painter.setRenderHint(QPainter::Antialiasing, true);
//        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        QRectF rectangle(0, 0, pixelsWide, pixelsHigh);
        
        text_rectangle = QRect (0,0,pixelsWide,pixelsHigh);

        //ToDo rendere il tutto costumizzabile dal pannello "Global configuration"
        painter.setPen(Qt::gray);
        painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
        painter.drawRoundedRect(rectangle, pixelsHigh/2, pixelsHigh/2);

        painter.setPen(QColor(
                FontStyle->FontRed,
                FontStyle->FontGreen,
                FontStyle->FontBlue
                ));

        painter.setFont(QFont(FontStyle->FontFamily,FontStyle->FontSize));
        painter.drawText(rectangle,Qt::AlignCenter,pillowText);
	painter.end();


	// second round...
        xPixmapText=text_area;
        isTextDrawed=1;  //text is drawed
	return;

}

void XQText::xPreparePillow(QRect &)
{

}

/*!
    \fn XQText::xSetText(const QString &)
 */
void XQText::xSetText(const QString &newText)
{
	pillowText=newText;
        isTextDrawed=0;
	isPixmapTextDrawed=0;
}

/*!
    \fn XQText::xSetBackgroundPath(const QString &)
 */
void XQText::xSetBackgroundPath(const QString &newPath)
{
	BackgroundPath=newPath;
//	PillowIsLoaded=0;
	isPixmapTextDrawed=0;
}

void XQText::paintEvent( QPaintEvent *e)
{
	XQWidget::paintEvent(e);
	return;
}
