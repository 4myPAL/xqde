//
// C++ Interface: xqtext
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQTEXT_H
#define XQTEXT_H

//#include <xqimage.h>
#include "xqwidget.h"
#include "xqdeenvironment.h"


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/



class XQText : public XQWidget
{
Q_OBJECT
public:
	XQText(QObject *, QWidget *parent = 0);
	virtual ~XQText();
//	virtual void xSetFontStyle(const XSCfgTextFont *);
	virtual void xSetText(const QString &);
	virtual void xDrawText();
	virtual void xSetBackgroundPath(const QString &);
	//virtual const QImage *getImage(){return &xImageText;};
	virtual const QPixmap *getPixmap(){return &xPixmapText;};
        virtual const QRect *getBoundingRect(){return &text_rectangle;};

        void paintEvent( QPaintEvent *e);
/*
	int xTextDecentre;
	int PillowIsLoaded;
	QImage PPillow_Center;
	QImage PPillow_Left;
	QImage PPillow_Right;
	QImage TMiniBuffer;
	QImage TBuffer;
	QPixmap xImgText;
	QPixmap	overTextBuffer;
//	QBitmap	overTextMask;
//	static XSConfigurations * ActiveConfiguration;
*/
protected:
	QString BackgroundPath;
	//QImage xImageText;
        QRect text_rectangle;
	QPixmap xPixmapText;
	QString	pillowText;
	int isTextDrawed;
	int isPixmapTextDrawed;
//	const XSCfgTextFont *FontStyle;
//	XSCfgTextFont *FontStyleDefault;
	virtual void xPreparePillow(QRect &);
};


#endif
