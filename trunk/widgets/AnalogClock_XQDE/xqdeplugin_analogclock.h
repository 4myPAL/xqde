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

#include <QObject>
#include "../libxqde.h"

#ifndef RESIZEVIAXRENDER
	#include <QImage>
#else
	#include <QPixmap>
#endif

class QDomNode;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEPlugin_AnalogClock : public QObject, public XQDEPluginInterface
{
Q_OBJECT
//Q_INTERFACES(XQDEPluginInterface)
public:
    XQDEPlugin_AnalogClock(QObject *p);
    ~XQDEPlugin_AnalogClock();
    QObject * Respawn(QObject *p);

    virtual void attach(QObject *newI);
    virtual void Configure();
    virtual void restore(QDomNode *);
    virtual void store(QDomNode *);
    virtual void ConfigurationChanged(void *,int);

private:
		QTimer *PluginPollingRate;
private slots:
	void AnalogClockPolling();

signals:
	void xSetIconWM(QImage &);
	void xSetTitle(const QString &);
	void xSetIcon(const QString &);
	void xSetParent(QObject *);
	void xReset();
	void xUpdateBroadcast();

private:
	int Value;
	int lastValue;
	void XQDEPlugin_AnalogClockRepaint();
//
//
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


