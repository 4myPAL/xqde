//
// C++ Interface: xquniqueapplication
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQUNIQUEAPPLICATION_H
#define XQUNIQUEAPPLICATION_H

#include <QApplication>

#define SERVICE_NAME_BASE            "com.xiaprojects.XQDE."

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQUniqueApplication : public QApplication
{
Q_OBJECT

public:

    XQUniqueApplication(Display * display, int & argc, char ** argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0 );
    ~XQUniqueApplication();
    bool isAppRunning;

protected:
	//class QDBusConnectionInterface *bus;
	QString SERVICE_NAME;
public slots:
	void prova();
};

#endif
