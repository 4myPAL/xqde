//
// C++ Implementation: xqdeplugin
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "xqdeplugin.h"

extern void GenericPluginNeedPolledEnable();

XQDEPlugin::XQDEPlugin(QObject *parent)
 : QObject(parent)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("XQDEPlugin::XQDEPlugin(QObject *parent)");
	#endif
	//isDirty=0;
	//isLocked=0;
	//isDirtyText=0;
	AttachedTo=0;
}

void XQDEPlugin::attach(QObject *newI)
{
		#ifdef ENABLEDEBUGMSG

	qWarning("void XQDEPlugin::attach(QObject *newI)");
	#endif
	AttachedTo=newI;

	disconnect(SIGNAL(xSetIconWM(QImage &)));
	disconnect(SIGNAL(xSetTitle(const QString &)));
	disconnect(SIGNAL(xSetIcon(const QString &)));
	disconnect(SIGNAL(xSetParent(QObject *)));
	disconnect(SIGNAL(xReset()));
	disconnect(SIGNAL(xUpdateBroadcast()));

	
	if(AttachedTo)
	{

		connect(this,SIGNAL(xSetIconWM(QImage &)),AttachedTo,SLOT(xSetIconWM(QImage &)));
		connect(this,SIGNAL(xSetTitle(const QString &)),AttachedTo,SLOT(xSetTitle(const QString &)));
		connect(this,SIGNAL(xSetIcon(const QString &)),AttachedTo,SLOT(xSetIcon(const QString &)));
		connect(this,SIGNAL(xSetParent(QObject *)),AttachedTo,SLOT(xSetParent(QObject *)));
		connect(this,SIGNAL(xReset()),AttachedTo,SLOT(xReset()));
		connect(this,SIGNAL(xUpdateBroadcast()),AttachedTo,SLOT(xUpdateBroadcast()));
		
		//emit xSetTitle("prova");
	}
	// xReset() will be called by other objects after this "attach"
}


XQDEPlugin::~XQDEPlugin()
{
		#ifdef ENABLEDEBUGMSG

		qWarning("XQDEPlugin::~XQDEPlugin()");
	#endif
}


QObject * XQDEPlugin::Respawn(QObject *p)
{
	#ifdef ENABLEDEBUGMSG
	
	qWarning("QObject * XQDEPlugin::Respawn(QObject *p)");
	#endif
	return (QObject *  )new XQDEPlugin(p);

}

void XQDEPlugin::Configure()
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEPlugin::Configure()");
	#endif
}

void XQDEPlugin::restore(QDomNode *)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEPlugin::restore(QDomNode *)");
#endif
}

void XQDEPlugin::store(QDomNode *)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEPlugin::store(QDomNode *)");
	#endif
}

void XQDEPlugin::ConfigurationChanged(void *,int)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("oid XQDEPlugin::ConfigurationChanged(void *,int)");
	#endif
}
