//
// C++ Interface: xqdeaction
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEACTION_H
#define XQDEACTION_H

#include <QObject>
#include <QString>

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEAction: public QObject
{
Q_OBJECT
	public:
		virtual ~XQDEAction();
		XQDEAction();
		virtual int doTest();
		// list supported()
		virtual void doit();
		QString ActionType;
		QString Action;
		ulong ActionCounter;
		void *Pointer;
	protected:
		class QTimer *disableActionForWhile;
		int isEnabled;
public slots:
		void enableActionAgain();
};

#endif
