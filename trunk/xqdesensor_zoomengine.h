//
// C++ Interface: xqdesensor_zoomengine
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESENSOR_ZOOMENGINE_H
#define XQDESENSOR_ZOOMENGINE_H

#include "xqdedevice.h"

const int MAXICONSIZE=256;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDESensor_ZoomEngine : public XQDEDevice
{
Q_OBJECT
public:
    XQDESensor_ZoomEngine(XQDEClass *parent = 0);

    ~XQDESensor_ZoomEngine();
	virtual long readLong(long x=0,long y=0,long z=0);
	virtual long *readArray(long x=0,long y=0,long z=0);
	virtual long **readMat(long x=0,long y=0,long z=0);
protected:
	long localMat[MAXICONSIZE+1][MAXICONSIZE+1];
	long *exportMat[MAXICONSIZE+1];
	virtual void preload();

};

#endif
