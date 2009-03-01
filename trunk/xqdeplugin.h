//
// C++ Interface: xqdeplugin
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEPLUGIN_H
#define XQDEPLUGIN_H

#include <QObject>
#include <QPixmap>

class QDomNode;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEPlugin : public QObject
{
Q_OBJECT
public:
XQDEPlugin(QObject *parent = 0);
~XQDEPlugin();
virtual QObject * Respawn(QObject *p);
//int isDirty;
//int isLocked;
//int isDirtyText;
QPixmap SharedBuffer;
public slots:
virtual void attach(QObject *newI);
virtual void Configure();
virtual void restore(QDomNode *);
virtual void store(QDomNode *);
virtual void ConfigurationChanged(void *,int);

protected:
QObject *AttachedTo;

signals:
	void xSetIconWM(QImage &);
	void xSetTitle(const QString &);
	void xSetIcon(const QString &);
	void xSetParent(QObject *);
	void xReset();
	void xUpdateBroadcast();

};

#endif
