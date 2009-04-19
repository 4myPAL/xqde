//
// C++ Interface: xqde
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//


#ifndef qt_xdisplay
	#include <QX11Info>
        #define qt_xdisplay() QX11Info::display()
	#define qt_xrootwin() QX11Info::appRootWindow()
	#define qt_xscreen() QX11Info::appScreen()
	#define qt_x_time  QX11Info::appTime()
	extern class QWidget *MainWindow;
	#define XQDESTRING "xqde"
        #define XQDESRCDATE "20090419"
	#define XQDE_USER_ACTION_CLICKSX	1
	#define XQDE_USER_ACTION_CLICKDX	2
	#define XQDE_USER_ACTION_CLICKMI	3
	#define XQDE_USER_ACTION_CLICKRU	4
	#define XQDE_USER_ACTION_CLICKRD	5
	#define XQDE_USER_ACTION_DRAGSX		6
	#define XQDE_USER_ACTION_DRAGDX		7
	#define XQDE_USER_ACTION_DROPSX		8
//	#define COMPOSITEMANAGER
//        #define RESIZEVIAXRENDER
//        #define ENABLEDEBUGMSG
//Not used (09.03.09)
//	const int PILLOWMAXHEIGHT=256;
//	const int PILLOWMAXWIDTH=256;
	const int xMakeUp_ArrowSize=8;
#endif
