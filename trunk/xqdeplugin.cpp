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
        qDebug("XQDEPlugin::XQDEPlugin(QObject *parent)");
	//isDirty=0;
	//isLocked=0;
	//isDirtyText=0;
	AttachedTo=0;
}

XQDEPlugin::~XQDEPlugin()
{

      qDebug("XQDEPlugin::~XQDEPlugin()");

}

void XQDEPlugin::attach(QObject *newI)
{

        qDebug("void XQDEPlugin::attach(QObject *newI)");
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



QObject * XQDEPlugin::Respawn(QObject *p)
{
	
        qDebug("QObject * XQDEPlugin::Respawn(QObject *p)");

	return (QObject *  )new XQDEPlugin(p);

}

void XQDEPlugin::Configure()
{
        qDebug("void XQDEPlugin::Configure()");

}

void XQDEPlugin::restore(QDomNode *)
{
        qDebug("void XQDEPlugin::restore(QDomNode *)");
}

void XQDEPlugin::store(QDomNode *)
{
        qDebug("void XQDEPlugin::store(QDomNode *)");

}

void XQDEPlugin::ConfigurationChanged(void *,int)
{
        qDebug("oid XQDEPlugin::ConfigurationChanged(void *,int)");
}
