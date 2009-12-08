//
// C++ Implementation: xqdemain
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QDataStream>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QSystemTrayIcon>
#include <QMessageBox>

// need to be moved to proxy
#include "xqdeconfigurator.h"
#include "xqdemain.h"
#include "libxqdebase.h"
#include "xqderoot.h"
#include "xqdeenvironment.h"
#include "xqdewindowmanagerinterface.h"
#include "xqdesensor_systemtray.h"
#include "xqdesensor_taskmanager.h"
#include "xqdebasket.h"
#include "xqdeproxy.h"
#include "xqdesystray.h"




QString DataPath;
QString EXEPath;


XQDEMain::XQDEMain(Display * display, int & argc, char ** argv, Qt::HANDLE visual, Qt::HANDLE colormap): XQUniqueApplication(display, argc, argv, visual,colormap)
{
	DataPath="";
	PluginListWhichWillBeLoaded=new QStringList();
	if(argc)
	{
		qWarning("XQDE=[%s]",argv[0]);
		QString tmpEXEPath=QString(argv[0]);
		int tmpOK=0;
		tmpOK=tmpEXEPath.lastIndexOf("/");
		if(!tmpOK)tmpEXEPath=".";
		else tmpEXEPath=tmpEXEPath.left(tmpOK);
		qWarning("XQDEDIR=[%s]",tmpEXEPath.toAscii().data());
	}

	for(int k=1;k<argc;k++)
	{
		if(strncmp(argv[k],"--localdata",strlen("--localdata"))==0 && k+1<argc)
		{
			k++;
			DataPath=QString(argv[k]);
			qWarning("DataPath=[%s]",DataPath.toAscii().data());
		}
		if(strncmp(argv[k],"--loadplugin",strlen("--loadplugin"))==0 && k+1<argc)
		{
			k++;
			QString PluginToLoad=QString(argv[k]);
			qWarning("Plugin [%s]",PluginToLoad.toAscii().data());
			if(PluginListWhichWillBeLoaded)PluginListWhichWillBeLoaded->append(PluginToLoad);
		}
	}
}


XQDEMain::~XQDEMain()
{
	qWarning("~XQDEMain()");
        if(PluginListWhichWillBeLoaded) delete PluginListWhichWillBeLoaded;
}

void XQDEMain::xReset()
{
	qWarning("void XQDEMain::xReset()");
	// raise DesktopEnvironment
	DesktopEnvironment=new XQDEEnvironment;
	xmlLoad();

	XQDERoot *root=new XQDERoot();

	//
	proxy=new XQDEProxy(root);

	// WindowManagerInterface
	WindowManagerInterface=new XQDEWindowManagerInterface(root);
	//
        Basket=new XQDEBasket(root);
	// TaskManager
        TaskManager=new XQDESensor_TaskManager(root);
//	//
/////*
//        XQDESensor_SystemTray *SystemTray=new XQDESensor_SystemTray();
//        SystemTray->setRect(200,200,800,500);
////        SystemTray->xReset();
////        SystemTray->xRepaint();
//        SystemTray->show();
////*/

        //System Tray for XQDE
//        XQDESysTray *sys = new XQDESysTray(root);
//                SysTray = new XQDESysTray();
        // xTray
//	QObject *m_tray=XEObject::xFindObject("xTray");
//	if(m_tray!=NULL)connect(m_tray,SIGNAL(quitSelected()),this,SLOT(QueryClose()));

	// Desktop Widget
	XQDEBase *xqde=new XQDEBase(root);
//	if(!SystemTray)qWarning("Heavy error reported");
	if(!root)qWarning("Heavy error reported");
	if(!TaskManager)qWarning("Heavy error reported");
	if(!xqde)qWarning("Heavy error reported");

        //ToDo use the configurator class for import export settings...
	XQDEConfigurator *xcfg=new XQDEConfigurator(root);
        xcfg->show();
	if(!xcfg)qWarning("Heavy error reported");



        connect(Basket,SIGNAL(Basket_As_Changed(int,XQDEIcon*,void*)),this,SLOT(Basket_As_Changed(int,XQDEIcon*,void*)));
	
        // load external plugins
        if(PluginListWhichWillBeLoaded)
        {
                for(int pi=0;pi<(PluginListWhichWillBeLoaded->count());pi++)
                {
                        QString pn=PluginListWhichWillBeLoaded->at(pi);
                        void *ppi=proxy->newInstanceOf(pn);
                        if(ppi)
                        {
                                qWarning("void XQDEMain::xReset() loaded successfully plugin %s %ld",pn.toUtf8().constData(),(long)ppi);
                                proxy->xResetTo((QObject *)ppi);
                        }
                        else
                        {
                                qWarning("void XQDEMain::xReset() loaded UNsuccessfully plugin %s %ld",pn.toUtf8().constData(),(long)ppi);
                        }
                }
        }

        DesktopEnvironment->Theme.xReset();
        xqde->xReset();

        TaskManager->xReset();

        Basket->FreezeRestore(DataPath);
        xcfg->xReset();

}


//
//void XQDEMain::Basket_As_Changed(int ,XQDEIcon*,void*)
//{
//}

void storeConfiguration()
{
    QString localPathDir="";
    if(DataPath=="")
    {
	localPathDir=QDir::home().path();
    }
    else
    {
	localPathDir=DataPath;
    }
    qWarning("Home: %s",localPathDir.toAscii().data());
    QDir *XQDEqd=new QDir(localPathDir);
    XQDEqd->mkpath(".xqde");
    XQDEqd->cd(".xqde");
    localPathDir=XQDEqd->path();
    qWarning("Created:%s",localPathDir.toAscii().data());


    QFile xmlFile(localPathDir+"/xqde.xml");

    QDomDocument doc( "xiaprojects" );
    if ( !xmlFile.open( QIODevice::WriteOnly ) )
    {
	qWarning("Error writing xml");
	return;
    }
    QDomElement root=doc.createElement("xqde");
    doc.appendChild(root);

    root.setAttribute("version","TODO");
    root.setAttribute("file",localPathDir+"/xqde.xml");

    QDomElement xmlObjectGUI=doc.createElement("object");
    root.appendChild(xmlObjectGUI);
    xmlObjectGUI.setAttribute("class","XQDEEnvironmentGUI");

    DesktopEnvironment->GUI.store(&xmlObjectGUI);

    QDomElement xmlObjectTheme=doc.createElement("object");
    root.appendChild(xmlObjectTheme);
    xmlObjectTheme.setAttribute("class","XQDEEnvironmentTheme");
    DesktopEnvironment->Theme.store(&xmlObjectTheme);

    // **** Common XML
    QByteArray a=doc.toByteArray();
    xmlFile.write(a);
    xmlFile.flush();
    xmlFile.close();

}

int XQDEMain::xmlLoad()
{
    QString localPathDir="";
    if(DataPath=="")
    {
	localPathDir=QDir::home().path();
    }
    else
    {
	localPathDir=DataPath;
    }

    int k=0;

    qWarning("Home: %s",localPathDir.toAscii().data());
    QDir *XQDEqd=new QDir(localPathDir);
    XQDEqd->mkpath(".xqde");
    XQDEqd->cd(".xqde");
    localPathDir=XQDEqd->path();
    qWarning("Created:%s",localPathDir.toAscii().data());


	QFile xmlFile(localPathDir+"/xqde.xml");

	if ( !xmlFile.open( QIODevice::ReadOnly ) )
	{
		qWarning("Error reading xml");
		return 0;
	}
	QDomDocument doc( "xiaprojects" );
	doc.setContent(&xmlFile);
	QDomNodeList nl=doc.elementsByTagName("object");
	if(nl.count()<1)return 0;
	for(int i=0;i<nl.count();i++)
	{
		QString addedclass=nl.at(i).toElement().attribute("class","XQDEMain");
		if(addedclass=="XQDEMain")
		{
			QString xml_item_type=nl.at(i).toElement().attribute("type","");
			if(xml_item_type=="")continue;
			if(xml_item_type=="module")
			{
                                k++;
				// adding some modules! (internal classes)
			}
			if(xml_item_type=="lib")
			{
				// adding some external .so
			}
		}
		if(addedclass=="XQDEEnvironmentGUI")
		{
			QDomNode dome=nl.at(i);
			DesktopEnvironment->GUI.restore(&dome);
		}
		if(addedclass=="XQDEEnvironmentTheme")
		{
			QDomNode dome=nl.at(i);
			DesktopEnvironment->Theme.restore(&dome);
		}
	}
	xmlFile.close();
	return k;
}


bool XQDEMain::x11EventFilter( XEvent *ev )
{
	if(TaskManager!=NULL)return TaskManager->x11EventFilter(ev);
	else return false;
}



extern class XQPillow *Global_XQPillow;
extern Display *dpy;
extern Visual *visual;
extern QWidget *GlobalConfigurator;
	
void SetNullOnAllPointers()
{
	Basket=NULL;
	DataPath="";
	DesktopEnvironment=NULL;
	EXEPath="";
	Global_XQPillow=NULL;
	MainWindow=NULL;
	WindowManagerInterface=NULL;
	dpy=NULL;
	proxy=NULL;
	visual=NULL;
	GlobalConfigurator=NULL;
}
