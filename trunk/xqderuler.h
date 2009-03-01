//
// C++ Interface: xqderuler
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDERULER_H
#define XQDERULER_H

#include <QObject>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDERuler : public QObject
{
Q_OBJECT
public:
    XQDERuler(QObject *parent = 0);
    ~XQDERuler();
	bool firstFit(int,int &, int &);
	void lock(void *,int,int,int);
	void unlock(int,int,int);
protected:
	void *DesktopBlock[1024][1024];
};

#endif
