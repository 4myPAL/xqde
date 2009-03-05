//
// C++ Implementation: xqdeproxy
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdeproxy.h"
#include "xqdeplugin_analogclock.h"
#include "xqdeplugin_webhelper.h"

XQDEProxy *proxy;

XQDEProxy::XQDEProxy(QObject *parent)
 : QObject(parent)
{
	qWarning("XQDEProxy::XQDEProxy(QObject *parent)");
}


XQDEProxy::~XQDEProxy()
{
	qWarning("XQDEProxy::~XQDEProxy()");
}

void *XQDEProxy::newInstanceOf(const QString &ClassName)
{
	qWarning("void *XQDEProxy::newInstanceOf(const QString &ClassName)");
	qWarning("void *XQDEProxy::newInstanceOf(const QString &ClassName) asking for %s",ClassName.toAscii().data());
        if(ClassName=="Analog Clock")
	{
		return (void *)new XQDEPlugin_AnalogClock(0);
	}
	if(ClassName=="WebHelper")
	{
		return (void *)new XQDEPlugin_WebHelper(parent());
	}
	
	qWarning("void *XQDEProxy::newInstanceOf(const QString &ClassName) asking for %s not found",ClassName.toAscii().data());
	return 0;
}


void XQDEProxy::xResetTo(QObject *tg)
{
	if(connect(this,SIGNAL(sgn_xresetTo()),tg,SLOT(xReset())))
	{
	emit sgn_xresetTo();
	disconnect(SIGNAL(sgn_xresetTo()));
	}
}
