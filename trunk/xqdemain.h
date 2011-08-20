//
// C++ Interface: xqdemain
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEMAIN_H
#define XQDEMAIN_H

#include "xquniqueapplication.h"

#include "xqdeplugin.h"


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xatom.h>
#include <QX11Info>

#include "xqderoot.h"

class XQDEIcon;
class QDir;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEMain : public XQUniqueApplication
{
Q_OBJECT
public:
    XQDEMain(Display * display, int & argc, char ** argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0 );
    ~XQDEMain();
	void xReset();
	void loadPluginsWidgets();
	void loadPlugins(XQDERoot *);
public slots:
//void Basket_As_Changed(int,XQDEIcon*,void*);

protected:
	virtual int xmlLoad();
//	bool XQDEMain::eventFilter(QObject *obj, QEvent *ev);
//	bool x11EventFilter( XEvent * );
	QStringList *PluginListWhichWillBeLoaded;
	static QDir directoryOf(const QString &subdir);
};

extern void storeConfiguration();
extern 	QString DataPath;

#endif
