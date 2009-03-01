//
// C++ Interface: xqdesensormouse
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESENSORMOUSE_H
#define XQDESENSORMOUSE_H

#include <xqdedevice.h>


#include <QTimer>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDESensor_Mouse : public XQDEDevice
{
Q_OBJECT
public:
    XQDESensor_Mouse(XQDEClass *parent = 0);
    ~XQDESensor_Mouse();
	int X,Y;
	int WinX, WinY;
public slots:
	void xStep();
protected:
	QTimer *polling;
};

#endif
