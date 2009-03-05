//
// C++ Interface: xqdeplugin_analogclock
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEPLUGIN_ANALOGCLOCK_H
#define XQDEPLUGIN_ANALOGCLOCK_H

#include "xqdeplugin.h"

#ifndef RESIZEVIAXRENDER
	#include <QImage>
#else
	#include <QPixmap>
#endif

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEPlugin_AnalogClock : public XQDEPlugin
{
Q_OBJECT
public:
    XQDEPlugin_AnalogClock(QObject *p);

    ~XQDEPlugin_AnalogClock();
	virtual void attach(QObject *newI);
protected:
		QTimer *PluginPollingRate;
public slots:
	void AnalogClockPolling();


protected:
	int Value;
	int lastValue;
void XQDEPlugin_AnalogClockRepaint();


#ifndef RESIZEVIAXRENDER
	QImage theClockPixmap;
	QImage background_pixmap;
	QImage min_hand_pixmap;
	QImage day_image_pixmap;
	QImage hour_hand_pixmap;
        QImage sec_hand_pixmap;
	QImage foreground_pixmap;
#else
	QPixmap theClockPixmap;
	QPixmap background_pixmap;
	QPixmap day_image_pixmap;
	QPixmap min_hand_pixmap;
	QPixmap hour_hand_pixmap;
        QPixmap sec_hand_pixmap;
	QPixmap foreground_pixmap;
#endif	

};

#endif
