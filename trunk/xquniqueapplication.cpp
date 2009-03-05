//
// C++ Implementation: xquniqueapplication
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusInterface>
#include <QStringList>

#include "xquniqueapplication.h"

XQUniqueApplication::XQUniqueApplication(Display * display, int & argc, char ** argv, Qt::HANDLE visual, Qt::HANDLE colormap):
QApplication (display,argc, argv,visual, colormap)
{
#ifdef AAAAA
	QString UniqueName="UniqueApplication";
/*
	if(argc>0)
	{
		int k=0;
		for(int i=0;i<strlen(argv[0]);i++)if(argv[0][i]=='.' ||argv[0][i]=='/')k++;
		UniqueName=argv[0]+k;
	}
*/
	SERVICE_NAME=SERVICE_NAME_BASE+UniqueName;
	bus = QDBus::sessionBus().interface();
	bool reg=true;
	while(reg)
	{
		reg=bus->isServiceRegistered(SERVICE_NAME);

if(reg){
		QDBusInterface remoteApp( SERVICE_NAME, "/xqde/test",SERVICE_NAME+".test" );
    remoteApp.call( "prova" );
}
//    remoteApp.call( "PushOperand", 2 );
//    remoteApp.call( "ExecuteOperation", "+" );
//    QDBusReply<int> reply = remoteApp.call( "PopOperand" );

//    if ( reply.isValid() )
//        printf( "%d", reply.value() );          // prints 4
		usleep(1000000);
	}
	QStringList ln=bus->registeredServiceNames ();
	if(0)
	{
		//exit(1);
	}
	else
	{
		if(bus->registerService(SERVICE_NAME))
		{
QDBus::sessionBus().connect (SERVICE_NAME,"/xqde/test",SERVICE_NAME+".test","prova",this,SLOT(prova()));
		}
		else
		{
			
		}
	}
#endif
}
void XQUniqueApplication::prova()
{

}

XQUniqueApplication::~XQUniqueApplication()
{
//	bus->releaseName(SERVICE_NAME);
}
