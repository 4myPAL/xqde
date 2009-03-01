//
// C++ Interface: xqdeproxy
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEPROXY_H
#define XQDEPROXY_H

#include <QObject>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEProxy : public QObject
{
Q_OBJECT
public:
    XQDEProxy(QObject *parent = 0);
    ~XQDEProxy();

	void *newInstanceOf(const QString &ClassName);
	void xResetTo(QObject *tg);
signals:
	void sgn_xresetTo();

};

extern XQDEProxy *proxy;

#endif
