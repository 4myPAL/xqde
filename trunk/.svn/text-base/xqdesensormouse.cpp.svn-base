//
// C++ Implementation: xqdesensormouse
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdesensormouse.h"

XQDESensor_Mouse::XQDESensor_Mouse(XQDEClass *parent)
 : XQDEDevice(parent)
{
	//
	polling=NULL;

	//
	if(polling==NULL)
	{
		polling=new QTimer();
		connect(polling,SIGNAL(timeout()),this, SLOT(xStep()));
	}
}


XQDESensor_Mouse::~XQDESensor_Mouse()
{
}



void XQDESensor_Mouse::xStep()
{
	// Polling version of Mouse sensor
	//if(MousePollingMutex->tryLock()==false)return;
//	XQueryPointer(display, root, &RootIDRet, &ChildIDRet, &XCoord,&YCoord, &WinX, &WinY, &StateMask);
	//MousePollingMutex->unlock();
}



