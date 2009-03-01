//
// C++ Implementation: xqderuler
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqderuler.h"

XQDERuler::XQDERuler(QObject *parent)
 : QObject(parent)
{
	for(int x32px=0;x32px<1024;x32px++)
	{
		for(int y32px=0;y32px<1024;y32px++)
		{
			DesktopBlock[x32px][y32px]=0;
		}
	}

	const int DisplayWidth=1280;
	const int DisplayHeight=800;

	const int width32=DisplayWidth/32+(((DisplayWidth)<(DisplayWidth/32)*32)?1:0);
	const int height32=DisplayHeight/32+(((DisplayHeight)<(DisplayHeight/32)*32)?1:0);

	for(int x32px=width32;x32px<1024;x32px++)
	{
		for(int y32px=height32;y32px<1024;y32px++)
		{
			//DesktopBlock[x32px][y32px]=(void*)-1;
			// TOCHECK
			DesktopBlock[x32px][y32px]=this;
		}
	}

}


XQDERuler::~XQDERuler()
{
}

void XQDERuler::lock(void *p, int x,int y, int size)
{
	const int x32=x/32;
	const int y32=y/32;
	const int size32=size/32+(((size)<(size/32)*32)?1:0);
	//qWarning("*Lsize32=%d",size32);
	for(int x32px=0;x32px<size32;x32px++)
	{
		for(int y32px=0;y32px<size32;y32px++)
		{
			DesktopBlock[x32+x32px][y32+y32px]=p;
		}
	}
}

void XQDERuler::unlock(int x,int y, int size)
{
	const int x32=x/32;
	const int y32=y/32;
	const int size32=size/32+(((size)<(size/32)*32)?1:0);
	for(int x32px=0;x32px<size32;x32px++)
	{
		for(int y32px=0;y32px<size32;y32px++)
		{
			DesktopBlock[x32+x32px][y32+y32px]=0;
		}
	}
}

bool XQDERuler::firstFit(int size, int &x,int &y)
{
	const int size32=size/32+(((size)<(size/32)*32)?1:0);
	int yReturn=-1;
	int xReturn=-1;
	int xfree=0;
	//qWarning("* size32=%d",size32);
	for(int x32px=0;x32px<1024;x32px++)
	{
		int yfree=0;
		for(int y32px=0;y32px<1024;y32px++)
		{
			if(DesktopBlock[x32px][y32px]==0)
			{
				yfree++;
				if(yfree>=size32)
				{
					yReturn=y32px;
					//qWarning("*      y=%d",y32px);
					break;
				}
			}
			else
			{
				yfree=0;
			}
		}
		if(yReturn>=0 && yfree>=size32)
		{
			xfree++;
			if(xfree>=size32)
			{
				//qWarning("*      x=%d",x32px);
				xReturn=x32px;
				break;
			}
		}
		else
		{
			xfree=0;
		}
	}
	if(xReturn>=0 && yReturn>=0)
	{
		x=(xReturn-size32+1)*32;
		y=(yReturn-size32+1)*32;
		return true;
	}
	else return false;
}
