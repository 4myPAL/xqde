//
// C++ Implementation: xqdeio
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdeio.h"

XQDEIO::XQDEIO(XQDEClass *parent)
 : XQDEClass(parent)
{
}


XQDEIO::~XQDEIO()
{
}


bool XQDEIO::nodeExists(const QString &)
{
	return false;
}

long XQDEIO::nodeWrite(long,const char *)
{
	return 0;
}
long XQDEIO::nodeRead(long,char *)
{
	return 0;
}

long XQDEIO::nodeList(QStringList &a)
{
	a=InternalNodeList;
	return InternalNodeList.count();
}
