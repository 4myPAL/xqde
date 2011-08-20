//
// C++ Implementation: xqdeplugin_analogclock
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QtGui>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <math.h>

#include "xqdeplugin_analogclock.h"
//#include "../../xqdeenvironment.h"
//#include "../../xqdeplugin.h"


extern "C" QObject* xqdeplugin_register(QObject *parent)
{
	return new XQDEPlugin_AnalogClock(parent);
}

//#ifdef Q_WS_WIN
// #define MY_EXPORT __declspec(dllexport)
// #else
// #define MY_EXPORT
// #endif
//
//extern "C" MY_EXPORT int avg(int a, int b)
// {
//     return (a + b) / 2;
// }
//
XQDEPlugin_AnalogClock::XQDEPlugin_AnalogClock(QObject *p) : XQDEPluginInterface(p)
{
	qWarning("XQDEPlugin_AnalogClock::XQDEPlugin_AnalogClock(QObject *p)");

	PluginPollingRate=new QTimer();
	connect(PluginPollingRate,SIGNAL(timeout()),SLOT(AnalogClockPolling()));

	Value=0;
	lastValue=0;
}


XQDEPlugin_AnalogClock::~XQDEPlugin_AnalogClock()
{
//	if(PluginPollingRate) delete PluginPollingRate;
	qDebug("XQDEPlugin_AnalogClock::~XQDEPlugin_AnalogClock()");
}


void XQDEPlugin_AnalogClock::AnalogClockPolling()
{
	PluginPollingRate->stop();
	qDebug("void XQDEPlugin_AnalogClock::AnalogClockPolling()");

	XQDEPlugin_AnalogClockRepaint();

	PluginPollingRate->start(1000);
}


void XQDEPlugin_AnalogClock::attach(QObject *newI)
{
    qDebug("AnalogClock Attach()");
//	// We will attach to the docker
//	XQDEPlugin::attach(newI);
//	// after this we can test:
//	if(AttachedTo)
//	{
		PluginPollingRate=new QTimer();
		connect(PluginPollingRate,SIGNAL(timeout()),SLOT(AnalogClockPolling()));

		Value=0;
		lastValue=0;

		// load default themes
//		QString newImageFile="";
//		newImageFile=DesktopEnvironment->Theme.findImage("Analog Clock/gclock");
//		if(newImageFile!="")background_pixmap.load(newImageFile);
//		newImageFile=DesktopEnvironment->Theme.findImage("Analog Clock/gclock_h0");
//		if(newImageFile!="")hour_hand_pixmap.load(newImageFile);
//		newImageFile=DesktopEnvironment->Theme.findImage("Analog Clock/gclock_m0");
//		if(newImageFile!="")min_hand_pixmap.load(newImageFile);
//		newImageFile=DesktopEnvironment->Theme.findImage("Analog Clock/gclock_s0");
//		if(newImageFile!="")sec_hand_pixmap.load(newImageFile);

		background_pixmap.load("/home/luca/.xqde/icons/Analog Clock/gclock.png");
		hour_hand_pixmap.load("/home/luca/.xqde/icons/Analog Clock/gclock_h0.png");
		min_hand_pixmap.load("/home/luca/.xqde/icons/Analog Clock/gclock_m0.png");
		sec_hand_pixmap.load("/home/luca/.xqde/icons/Analog Clock/gclock_s0.png");

		AnalogClockPolling();
//	}
}


void XQDEPlugin_AnalogClock::XQDEPlugin_AnalogClockRepaint()
{

	double h_degree=0;
	double m_degree=0;
	double s_degree=0;

	int h=QTime::currentTime().hour();
	int m=QTime::currentTime().minute();
	int s=QTime::currentTime().second();


	if(h>=12){
			h_degree=(360/12)*(h-12);
	}
	else
	{
			h_degree=(360/12)*(h);
	}

	m_degree=(360/60)*m;
	s_degree=(360/60)*s;
	h_degree=h_degree+(360/12)*(m_degree/360);


	theClockPixmap=background_pixmap.copy();

	Value=(int)(h_degree*60*60+m_degree*60+s_degree);
	if(lastValue!=Value)
	{
		emit xSetTitle(QDateTime::currentDateTime().toString("dddd d MMMM yyyy hh:mm"));

		const double PI = 3.14159265358979323846;
		double myRadiansDouble;
		double centerXDouble;
		double centerYDouble;
		int xShift, yShift;


		QPainter painter(&theClockPixmap);

		/********* Minutes ***********/

		centerXDouble = min_hand_pixmap.width()/2;
		centerYDouble = min_hand_pixmap.height()/2;
		//save the current canvas rotation
		painter.save();

		//rotate the canvas
		painter.rotate( m_degree );
		//work out how to shift the image so that it appears in the center of the canvas
		//(x cos a + y sin a - x, -x sin a + y cos a - y)

		myRadiansDouble = (PI/180) * m_degree;

		xShift = static_cast<int>((
			      (centerXDouble * cos(myRadiansDouble)) +
			      (centerYDouble * sin(myRadiansDouble))
			     ) - centerXDouble);
		yShift = static_cast<int>((
			      (-centerXDouble * sin(myRadiansDouble)) +
			      (centerYDouble * cos(myRadiansDouble))
			     ) - centerYDouble);


		//draw the pixmap in the proper position
		painter.drawImage(xShift,yShift,min_hand_pixmap);

		//unrotate the canvase again
		painter.restore();

		/********* Hour ***********/

		centerXDouble = hour_hand_pixmap.width()/2;
		centerYDouble = hour_hand_pixmap.height()/2;
		//save the current canvas rotation
		painter.save();

		//rotate the canvas
		painter.rotate( h_degree );
		//work out how to shift the image so that it appears in the center of the canvas
		//(x cos a + y sin a - x, -x sin a + y cos a - y)

		myRadiansDouble = (PI/180) * h_degree;

		xShift = static_cast<int>((
			      (centerXDouble * cos(myRadiansDouble)) +
			      (centerYDouble * sin(myRadiansDouble))
			     ) - centerXDouble);
		yShift = static_cast<int>((
			      (-centerXDouble * sin(myRadiansDouble)) +
			      (centerYDouble * cos(myRadiansDouble))
			     ) - centerYDouble);


		//draw the pixmap in the proper position
		painter.drawImage(xShift,yShift,hour_hand_pixmap);

		//unrotate the canvase again
		painter.restore();

		/********* Second ***********/

		centerXDouble = sec_hand_pixmap.width()/2;
		centerYDouble = sec_hand_pixmap.height()/2;
		//save the current canvas rotation
		painter.save();

		//rotate the canvas
		painter.rotate( s_degree );
		//work out how to shift the image so that it appears in the center of the canvas
		//(x cos a + y sin a - x, -x sin a + y cos a - y)

		myRadiansDouble = (PI/180) * s_degree;

		xShift = static_cast<int>((
			      (centerXDouble * cos(myRadiansDouble)) +
			      (centerYDouble * sin(myRadiansDouble))
			     ) - centerXDouble);
		yShift = static_cast<int>((
			      (-centerXDouble * sin(myRadiansDouble)) +
			      (centerYDouble * cos(myRadiansDouble))
			     ) - centerYDouble);


		//draw the pixmap in the proper position
		painter.drawImage(xShift,yShift,sec_hand_pixmap);

		//unrotate the canvase again
		painter.restore();

		painter.end();

		//send new icon Pixmap
		emit xSetIconWM(theClockPixmap);
		//load new icon
		emit xReset();
		//repaint new icon (local repaint)
		emit xUpdateBroadcast();

	}
}


QObject * XQDEPlugin_AnalogClock::Respawn(QObject *p)
{

	qDebug("QObject * XQDEPlugin_AnalogClock::Respawn(QObject *p)");

	return (QObject *  )new XQDEPlugin_AnalogClock(p);

}


void XQDEPlugin_AnalogClock::Configure()
{
	qDebug("void XQDEPlugin::Configure()");

}

void XQDEPlugin_AnalogClock::restore(QDomNode *)
{
	qDebug("void XQDEPlugin::restore(QDomNode *)");
}

void XQDEPlugin_AnalogClock::store(QDomNode *)
{
	qDebug("void XQDEPlugin::store(QDomNode *)");

}

void XQDEPlugin_AnalogClock::ConfigurationChanged(void *,int)
{
	qDebug("void XQDEPlugin::ConfigurationChanged(void *,int)");
}
