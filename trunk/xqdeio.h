//
// C++ Interface: xqdeio
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEIO_H
#define XQDEIO_H

#include <xqdeclass.h>
#include <QStringList>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEIO : public XQDEClass
{
Q_OBJECT
public:
    XQDEIO(XQDEClass *parent = 0);
    ~XQDEIO();
public:
	bool nodeExists(const QString &);
	long nodeWrite(long,const char *);
	long nodeRead(long,char *);
	long nodeList(QStringList &);
protected:
	QStringList InternalNodeList;
};

#endif
