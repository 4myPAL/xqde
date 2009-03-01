//
// C++ Interface: xqdesensor_systemtray
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESENSOR_SYSTEMTRAY_H
#define XQDESENSOR_SYSTEMTRAY_H

#include <xqwidget.h>
#include <import_netwm.h>
class QVBoxLayout;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDESensor_SystemTray : public XQWidget
{
Q_OBJECT
public:
	void xRepaint();
	virtual void xReset();
	XQDESensor_SystemTray(QObject *parent = 0);
	~XQDESensor_SystemTray();
protected:
	QVBoxLayout *vContainer;
	Atom net_system_tray_selection;
	Atom net_system_tray_opcode;
	bool x11Event( XEvent *e );
	bool isWinManaged(WId w);
	void embedWindow( WId w, bool kde_tray );
	void emb( WId w);
	void layoutTray();
	QList<Window >managed_trayWindows;
};

#endif
