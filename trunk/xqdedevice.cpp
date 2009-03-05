//
// C++ Implementation: xqdedevice
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "xqdedevice.h"

XQDEDevice::XQDEDevice(XQDEClass *parent)
 : XQDEIO(parent)
{
	InternalNodeList.append(".about");
	InternalNodeList.append(".type");
}


XQDEDevice::~XQDEDevice()
{
}

long XQDEDevice::readLong(long,long,long)
{
	return 0;
}

long *XQDEDevice::readArray(long,long,long)
{
	return NULL;
}

long **XQDEDevice::readMat(long,long,long)
{
	return NULL;
}

void XQDEDevice::connectInterrupt(QObject *item,long x,long y,long z)
{
	if(interrupts.indexOf(item)<0)return;
	interrupts.append(item);
	interruptsVect.append(new XQDEDeviceTriData(x,y,z));
}


void XQDEDevice::disconnectInterrupt(QObject *item)
{
	int i = interrupts.indexOf(item);
	if (i != -1)
	{
		interrupts.takeAt(i);
		delete interruptsVect.takeAt(i);
	}
}
