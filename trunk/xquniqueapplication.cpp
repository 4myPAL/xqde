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

//#include <QtDBus/QDBusConnection>
//#include <QtDBus/QDBusConnectionInterface>
//#include <QtDBus/QDBusInterface>
//#include <QtDBus/QDBusReply>
#include <QtDBus>
#include <QDebug>

#include <QStringList>

#include "xquniqueapplication.h"

XQUniqueApplication::XQUniqueApplication(Display * display, int & argc, char ** argv, Qt::HANDLE visual, Qt::HANDLE colormap):
QApplication (display,argc, argv,visual, colormap)
{


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

    //***********************************//
    //codice per implementazioni future, il codice funziona
    //***********************************//

    QDBusConnectionInterface *bus = QDBusConnection::sessionBus().interface();
    //is service registered?
    isAppRunning=bus->isServiceRegistered(SERVICE_NAME);

//        isunique=true;
//        while(isunique)
//        {
//
//            isunique=bus->isServiceRegistered(SERVICE_NAME);
//            if(isunique){
//                QDBusInterface remoteApp( SERVICE_NAME, "/xqde/test",SERVICE_NAME+".test" );
//                remoteApp.call( "prova" );
//                break;
//            }
//            usleep(1000000);
//        }
//
//        QStringList ln=bus->registeredServiceNames ();
//
        if(bus->registerService(SERVICE_NAME))
        {
        QDBusConnection::sessionBus().connect (SERVICE_NAME,"/xqde/test",SERVICE_NAME+".test","prova",this,SLOT(prova()));
        }
        else
        {
        }
}
void XQUniqueApplication::prova()
{

}

XQUniqueApplication::~XQUniqueApplication()
{
//	bus->releaseName(SERVICE_NAME);
}
