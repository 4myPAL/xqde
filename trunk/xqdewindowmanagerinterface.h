//
// C++ Interface: xqdewindowmanagerinterface
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEWINDOWMANAGERINTERFACE_H
#define XQDEWINDOWMANAGERINTERFACE_H

#include <import_netwm.h>

#include "xqdeclass.h"

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEWindowManagerInterface : public XQDEClass
{
Q_OBJECT
public:
    XQDEWindowManagerInterface(XQDEClass *parent = 0);
    ~XQDEWindowManagerInterface();
public slots:
	void setOnAllDesktops(WId , bool );
};

extern XQDEWindowManagerInterface *WindowManagerInterface;

#endif
