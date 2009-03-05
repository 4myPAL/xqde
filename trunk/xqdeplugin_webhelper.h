//
// C++ Interface: XQDEPlugin_WebHelper
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEWEBHELPER_H
#define XQDEWEBHELPER_H

#include "xqdeclass.h"


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEPlugin_WebHelper : public XQDEClass
{
Q_OBJECT
	public:
		XQDEPlugin_WebHelper(QObject *parent);
		~XQDEPlugin_WebHelper();
		QString WebHelper_DownloadResource(QString rsc, QString tgfolder);
	public slots:
		void XQDEEnvironmentTheme_findImage_miss(QString);
		void xReset();
		void XQDEEnvironmentTheme_findResources_miss(QString, QString);
	protected:
		
		
};


//extern class XQDEPlugin_WebHelper *WebHelper;
	
	
#endif
