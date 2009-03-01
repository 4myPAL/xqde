//
// C++ Implementation: xqderoot
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqderoot.h"



XQDERoot::XQDERoot():XQDEClass(NULL)
{
	globalXQDERoot=this;
}
XQDERoot::~XQDERoot()
{
	globalXQDERoot=NULL;
}
void XQDERoot::PluginRegister(QObject *item)
{
	if(globalXQDEPlugins.indexOf(item)>=0)return;
	globalXQDEPlugins.append(item);
}

void XQDERoot::PluginUnRegister(QObject *item)
{
	int i = globalXQDEPlugins.indexOf(item);
	if (i != -1)delete globalXQDEPlugins.takeAt(i);
}


QObject *XQDERoot::byName(const QString pName)
{
	for(int i=0;i<globalXQDEPlugins.count();i++)
	{
		QString lpName="";
		QObject *lp=globalXQDEPlugins.at(i);
		if(connect(this,SIGNAL(sgn_GetNamedValue(const QString &, QString &)),lp,SLOT(GetNamedValue(const QString &, QString &))))
		{
			emit sgn_GetNamedValue("name", lpName);
			disconnect(SIGNAL(sgn_GetNamedValue(const QString &, QString &)));
			if(lpName==pName)
			{
				return globalXQDEPlugins.at(i);
			}
			
		}
	}
	return NULL;
}
