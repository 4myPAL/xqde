//
// C++ Interface: xqderoot
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEROOT_H
#define XQDEROOT_H

#include <xqdeclass.h>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDERoot : public XQDEClass
{
	Q_OBJECT
	public:
		XQDERoot();
		~XQDERoot();
		inline static QList <QObject *>*Plugins()
		{
			return &globalXQDEPlugins;
		}
		QObject *byName(const QString pName);
	public slots:
		static void PluginRegister(QObject *);
		static void PluginUnRegister(QObject *);
	signals:
		void sgn_GetNamedValue(const QString &, QString &);
		
};


#endif
