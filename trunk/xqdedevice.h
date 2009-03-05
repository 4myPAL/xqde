//
// C++ Interface: xqdedevice
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEDEVICE_H
#define XQDEDEVICE_H

#include "xqdeio.h"

class XQDEDeviceTriData
{
public:	inline XQDEDeviceTriData(long ix=0,long iy=0,long iz=0){x=ix;y=iy;z=iz;}
	long x,y,z;
};

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEDevice : public XQDEIO
{
Q_OBJECT
public:
    XQDEDevice(XQDEClass *parent = 0);

    ~XQDEDevice();
	protected:
		QList<QObject *> interrupts;
		QList<XQDEDeviceTriData *> interruptsVect;

public:
	virtual long readLong(long x=0,long y=0,long z=0);
	virtual long *readArray(long x=0,long y=0,long z=0);
	virtual long **readMat(long x=0,long y=0,long z=0);
	virtual void connectInterrupt(QObject *item,long x=0,long y=0,long z=0);
	virtual void disconnectInterrupt(QObject *item);
signals:
	void interrupt(long x=0,long y=0,long z=0);
	void polling(long x=0,long y=0,long z=0);
};

#endif
