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
#include <QtGui>
#include <QDataStream>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QAbstractEventDispatcher>


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
#include "xqdewidgetinterface.h"
#include "xqwfirsthand.h"


QList<XQDEWidgetInterface *> widgets;

QString DataPath;
QString EXEPath;

//this recive all events form X not only the event of the widget
static bool customx11EventFilter(void *message)
{
    XEvent *event = reinterpret_cast<XEvent*>(message);
    QEvent *qevent = reinterpret_cast<QEvent*>(message);
    XAnyEvent *ae = reinterpret_cast<XAnyEvent*>(event);
//    QHash<QX11Mirror*, Qt::HANDLE>::const_iterator itr;
//    for (itr = s_mirrors.constBegin(); itr != s_mirrors.constEnd();
//         ++itr) {
//        if (itr.value() == ae->window) {
//            itr.key()->x11Event(event);
//        }
//    }
//    qWarning()<<"event"";

//#define KeyPress		2
//#define KeyRelease		3
//#define ButtonPress		4
//#define ButtonRelease		5
//#define MotionNotify		6
//#define EnterNotify		7
//#define LeaveNotify		8

    //improuvements direct interface to xorg events
    //Todo :check if mouse is over mask
//    if(event->type == EnterNotify) qDebug("Enter Dock");
//    if(event->type == LeaveNotify) qDebug("Exit Dock");

//    if(qevent->type() == QEvent::MouseMove){
//	XQWFirstHand.mouseMoveEvent(static_cast<QMouseEvent*>(qevent));
//    }

    if(TaskManager!=NULL)return TaskManager->x11EventFilter(event);
    else return false;
//    return false;
}


XQDEMain::XQDEMain(Display * display, int & argc, char ** argv, Qt::HANDLE visual, Qt::HANDLE colormap): XQUniqueApplication(display, argc, argv, visual,colormap)
{

    setApplicationName("xqde");
    setOrganizationDomain ("www.xiaprojects.com");
    setOrganizationName("XIA Projects 2009");

    //Loading a interface translation, ex: "xqde_it.qm"
    QTranslator appTranslator;
    QString translationFile = ":/translations/xqde_" + QLocale::system().name() + ".ts";
    appTranslator.load(translationFile);
    installTranslator(&appTranslator);
    qWarning()<<"Loaded language is: "<<translationFile;

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
//	XQDESysTray *sys = new XQDESysTray(root);
	SysTray = new XQDESysTray(root);
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
	//xcfg->show();
	if(!xcfg)qWarning("Heavy error reported");


	//ToDO: controllare se serve
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

//	loadPluginsWidgets();

	loadPlugins(root);

        DesktopEnvironment->Theme.xReset();
        xqde->xReset();

	TaskManager->xReset();

	Basket->FreezeRestore(DataPath);
        xcfg->xReset();

	QAbstractEventDispatcher::instance()->setEventFilter(customx11EventFilter);

}

QDir XQDEMain::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

//#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
	    || dir.dirName().toLower() == "release")
	dir.cdUp();
//#elif defined(Q_OS_MAC)
//    if (dir.dirName() == "MacOS") {
//	dir.cdUp();
//	dir.cdUp();
//	dir.cdUp();
//    }
//#endif
    dir.cd(subdir);
    return dir;
}

void XQDEMain::loadPluginsWidgets()
{
    QDir pluginsDir = directoryOf("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
	QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
	if (XQDEWidgetInterface *widget = qobject_cast<XQDEWidgetInterface *>(loader.instance()))
	    widgets.append(widget);
    }
}


typedef QObject *(*pPluginLoader)(QObject *);

typedef int (*AvgFunction)(int, int);

void XQDEMain::loadPlugins(XQDERoot *root)
{
    QDir pluginsDir = directoryOf("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
	//look in the plugins folder and search for all files
	//remove the .so extension before use QLibrary to load plugin
//	fileName = fileName.left(fileName.length()-3); // remove ".so" 3xChar
	fileName = pluginsDir.absolutePath() + "/" + fileName;
	QLibrary myLib(fileName.toAscii());
	if(myLib.isLibrary(fileName)) { //have a valid extension? (.so)

//	    myLib.load();
//	    if(myLib.isLoaded()) qWarning() << "loaded";
//	    AvgFunction avg =
//		     (AvgFunction) myLib.resolve("avg");
//	    if (avg){
//		 int temp = avg(5, 8);
//	     }
//	    qWarning() << myLib.errorString();
//

	    myLib.load();
	    if(myLib.isLoaded()) qWarning() << "loaded";
	    pPluginLoader xqdeplugin =
		    (pPluginLoader) myLib.resolve("xqdeplugin_register");
	    if (xqdeplugin){
//		int temp = avg(5, 8);
		QObject *LoadedPlugin= xqdeplugin(parent());
//		if(PluginListWhichWillBeLoaded)PluginListWhichWillBeLoaded->append(PluginToLoad);
//		if(LoadedPlugin!=NULL) root->PluginRegister(LoadedPlugin);
	    }
	    qWarning() << myLib.errorString();
	    myLib.unload();
//
//	    typedef QObject* (*ptr)(QObject*);
//	    ptr function = (ptr) myLib.resolve("xqdeplugin_register");
////	    if(function!=NULL) root->PluginRegister(/*(QObject *)*/ function);
////
////	    qWarning() << function;
//
//	    pPluginLoader PluginLoader;
//	    PluginLoader=(pPluginLoader)myLib.resolve("xqdeplugin_register");
//	    if(myLib.isLoaded()) qWarning() << "loaded" << PluginLoader;
//	    if(PluginLoader)
//	    {
//		QObject *LoadedModule=PluginLoader(parent());
//		if(PluginLoader!=NULL) root->PluginRegister((void *) PluginLoader);
	    }
	else qWarning() << myLib.errorString();
    }

}


//
//void XQDEMain::Basket_As_Changed(int ,XQDEIcon*,void*)
//{
//}

void storeConfiguration()
{
//    QString localPathDir="";
//    if(DataPath=="")
//    {
//	localPathDir=QDir::home().path();
//    }
//    else
//    {
//	localPathDir=DataPath;
//    }
//    qWarning("Home: %s",localPathDir.toAscii().data());
//    QDir *XQDEqd=new QDir(localPathDir);
//    XQDEqd->mkpath(".xqde");
//    XQDEqd->cd(".xqde");
//    localPathDir=XQDEqd->path();
//    qWarning("Created:%s",localPathDir.toAscii().data());
//
//
//    QFile xmlFile(localPathDir+"/xqde.xml");
//
//    QDomDocument doc( "xiaprojects" );
//    if ( !xmlFile.open( QIODevice::WriteOnly ) )
//    {
//	qWarning("Error writing xml");
//	return;
//    }
//    QDomElement root=doc.createElement("xqde");
//    doc.appendChild(root);
//
//    root.setAttribute("version","TODO");
//    root.setAttribute("file",localPathDir+"/xqde.xml");
//
//    QDomElement xmlObjectGUI=doc.createElement("object");
//    root.appendChild(xmlObjectGUI);
//    xmlObjectGUI.setAttribute("class","XQDEEnvironmentGUI");
//
//    DesktopEnvironment->GUI.store(&xmlObjectGUI);
//
//    QDomElement xmlObjectTheme=doc.createElement("object");
//    root.appendChild(xmlObjectTheme);
//    xmlObjectTheme.setAttribute("class","XQDEEnvironmentTheme");
//    DesktopEnvironment->Theme.store(&xmlObjectTheme);
//
//    // **** Common XML
//    QByteArray a=doc.toByteArray();
//    xmlFile.write(a);
//    xmlFile.flush();
//    xmlFile.close();

    QString localPathDir="";
    if(DataPath=="") {
    	localPathDir=QDir::home().path();
    }
    else {
    	localPathDir=DataPath;
    }
    qWarning("Home: %s",localPathDir.toAscii().data());
    QDir *XQDEqd=new QDir(localPathDir);
    XQDEqd->mkpath(".xqde");
    XQDEqd->cd(".xqde");
    localPathDir=XQDEqd->path();
    qWarning("Created:%s",localPathDir.toAscii().data());

    QSettings settings(localPathDir+"/xqde.conf", QSettings::NativeFormat);
    settings.beginGroup("XQDEEnvironmentGUI");
    DesktopEnvironment->GUI.store(&settings);
    settings.endGroup();

    settings.beginGroup("XQDEEnvironmentTheme");
    DesktopEnvironment->Theme.store(&settings);
    settings.endGroup();

    settings.beginGroup("XQDEEnvironmentUserProfile");
    DesktopEnvironment->UserProfile.store(&settings);
    settings.endGroup();

}

int XQDEMain::xmlLoad()
{
//    QString localPathDir="";
//    if(DataPath=="")
//    {
//	localPathDir=QDir::home().path();
//    }
//    else
//    {
//	localPathDir=DataPath;
//    }
//
//    int k=0;
//
//    qWarning("Home: %s",localPathDir.toAscii().data());
//    QDir *XQDEqd=new QDir(localPathDir);
//    XQDEqd->mkpath(".xqde");
//    XQDEqd->cd(".xqde");
//    localPathDir=XQDEqd->path();
//    qWarning("Created:%s",localPathDir.toAscii().data());
//
//
//	QFile xmlFile(localPathDir+"/xqde.xml");
//
//	if ( !xmlFile.open( QIODevice::ReadOnly ) )
//	{
//		qWarning("Error reading xml");
//		return 0;
//	}
//	QDomDocument doc( "xiaprojects" );
//	doc.setContent(&xmlFile);
//	QDomNodeList nl=doc.elementsByTagName("object");
//	if(nl.count()<1)return 0;
//	for(int i=0;i<nl.count();i++)
//	{
//		QString addedclass=nl.at(i).toElement().attribute("class","XQDEMain");
//		if(addedclass=="XQDEMain")
//		{
//			QString xml_item_type=nl.at(i).toElement().attribute("type","");
//			if(xml_item_type=="")continue;
//			if(xml_item_type=="module")
//			{
//                                k++;
//				// adding some modules! (internal classes)
//			}
//			if(xml_item_type=="lib")
//			{
//				// adding some external .so
//			}
//		}
//		if(addedclass=="XQDEEnvironmentGUI")
//		{
//			QDomNode dome=nl.at(i);
//			DesktopEnvironment->GUI.restore(&dome);
//		}
//		if(addedclass=="XQDEEnvironmentTheme")
//		{
//			QDomNode dome=nl.at(i);
//			DesktopEnvironment->Theme.restore(&dome);
//		}
//	}
//	xmlFile.close();
//	return k;


    QString localPathDir="";
    if(DataPath=="") {
    	localPathDir=QDir::home().path();
    }
    else {
    	localPathDir=DataPath;
    }
    qWarning("Home: %s",localPathDir.toAscii().data());
    QDir *XQDEqd=new QDir(localPathDir);
    XQDEqd->mkpath(".xqde");
    XQDEqd->cd(".xqde");
    localPathDir=XQDEqd->path();
    qWarning("Created:%s",localPathDir.toAscii().data());

    QSettings settings(localPathDir+"/xqde.conf", QSettings::NativeFormat);
    settings.beginGroup("XQDEEnvironmentGUI");
    DesktopEnvironment->GUI.restore(&settings);
    settings.endGroup();

    settings.beginGroup("XQDEEnvironmentTheme");
    DesktopEnvironment->Theme.restore(&settings);
    settings.endGroup();

    settings.beginGroup("XQDEEnvironmentUserProfile");
    DesktopEnvironment->UserProfile.restore(&settings);
    settings.endGroup();
    return 0;
}


// protected f()
//bool XQDEMain::eventFilter(QObject *obj, QEvent *ev)
//{
//    // (this) Active only if MainWindow installEventFitler is uncommented
//    if ( obj == testWidget || obj == this ) {
//	switch( ev->type() ){
//	    case QEvent::Enter:
//		qDebug( "Enter %s", obj->objectName() );
//		break;
//	    case QEvent::Leave:
//		qDebug( "Leave %s", obj->objectName() );
//		break;
//	    default:
//		// uncomment to log everything
//		//logEntry( obj->objectName()+": "+tr( "%1" ).arg( ev->type() ) );
//		break;
//	}
//    }
//
//    return QMainWindow::eventFilter( obj, ev );
//}


//bool XQDEMain::x11EventFilter( XEvent *ev )
//{
//	if(TaskManager!=NULL)return TaskManager->x11EventFilter(ev);
//	else return false;
//}


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
