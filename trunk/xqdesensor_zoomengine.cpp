//
// C++ Implementation: xqdesensor_zoomengine
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdesensor_zoomengine.h"
#include "xqdeenvironment.h"

XQDESensor_ZoomEngine::XQDESensor_ZoomEngine(XQDEClass *parent)
 : XQDEDevice(parent)
{
	preload();
}


XQDESensor_ZoomEngine::~XQDESensor_ZoomEngine()
{
}


void XQDESensor_ZoomEngine::preload()
{
	double startingSize=DesktopEnvironment->GUI.sizeIconsNormal;
	double endSize=DesktopEnvironment->GUI.sizeIconsMax;
	double totalSteps=(MAXICONSIZE)*2;
	double deltaSize=(endSize-startingSize)/totalSteps;
	for(long dx=0;dx<MAXICONSIZE+1;dx++)
	{
		for(long dy=0;dy<MAXICONSIZE+1;dy++)
		{
			localMat[dx][dy]=long(((double(totalSteps-(dx+dy)))*deltaSize)+startingSize);
		}
		exportMat[dx]=localMat[dx];
	}

	//qWarning("end preload");
}

long XQDESensor_ZoomEngine::readLong(long ,long ,long )
{
	return 0;
}

long *XQDESensor_ZoomEngine::readArray(long x,long,long)
{
	return localMat[x];
}

long **XQDESensor_ZoomEngine::readMat(long,long,long)
{
	return exportMat;
}
