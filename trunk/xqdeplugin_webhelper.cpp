//
// C++ Implementation: XQDEPlugin_WebHelper
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QFile>
#include <QDir>
#include <QProcess>

#include "xqdeplugin_webhelper.h"
#include "xqdeenvironment.h"
#include "xqde.h"

XQDEPlugin_WebHelper::XQDEPlugin_WebHelper(QObject *parent) : XQDEClass(parent)
{
	qWarning("XQDEPlugin_WebHelper::XQDEPlugin_WebHelper(QObject *parent) : QObject(parent)");
	ObjectName="com.xiaprojects.WebHelper";
	// loading configuration for xml
	
	// todo translations!!
	ConfigurationData.append(new XQDEConfigurationPair("serverurl","http://xqde.xiaprojects.com/findtheme.php"));
	ConfigurationData.append(new XQDEConfigurationPair("email","xqde@xiaprojects.com"));
	ConfigurationData.append(new XQDEConfigurationPair("author","Stefano Zingarini"));
	ConfigurationData.append(new XQDEConfigurationPair("web","http://xqde.xiaprojects.com"));
	ConfigurationData.append(new XQDEConfigurationPair("version","20071116"));
	ConfigurationData.append(new XQDEConfigurationPair("autoupdate","http://xqde.xiaprojects.com/todo.php"));
}

XQDEPlugin_WebHelper::~XQDEPlugin_WebHelper()
{
	qWarning("XQDEPlugin_WebHelper::~XQDEPlugin_WebHelper()");
}

extern QString DataPath;

void XQDEPlugin_WebHelper::xReset()
{
	qWarning("void XQDEPlugin_WebHelper::xReset()");
	disconnect(SLOT(XQDEEnvironmentTheme_findImage_miss(QString)));
	disconnect(SLOT(XQDEEnvironmentTheme_findResources_miss(QString,QString)));
	if(DesktopEnvironment != NULL && &DesktopEnvironment->Theme !=NULL )
	{
		connect(&DesktopEnvironment->Theme,SIGNAL(XQDEEnvironmentTheme_findImage_miss(QString)),SLOT(XQDEEnvironmentTheme_findImage_miss(QString)));	
		connect(&DesktopEnvironment->Theme,SIGNAL(XQDEEnvironmentTheme_findResources_miss(QString,QString)),SLOT(XQDEEnvironmentTheme_findResources_miss(QString,QString)));
	}
	
	
	//TODO: remove DataPath from plugins
	FreezeRestore(DataPath);
}


void XQDEPlugin_WebHelper::XQDEEnvironmentTheme_findResources_miss(QString a, QString b)
{
	qWarning("void XQDEPlugin_WebHelper::XQDEEnvironmentTheme_findResources_miss(QString %s, QString %s)",a.toUtf8().constData(),b.toUtf8().constData());
	qWarning("Please wait! XQDE is going to download resources from www.xiaprojects.com");
	QString ris=WebHelper_DownloadResource("resources.default.tar.bz2", QDir::home().path()+"/.xqde/");
	if(ris=="")
	{
		qWarning("Sorry you cannot download XQDE resources from www.xiaprojects.com via WebHelper plugin please disable it to continue start XQDE without this tool");
//		exit(1);
	}
	
	qWarning("Successfully downloaded resources please wait while unpacking...");
	char cmdLine[1025];
	sprintf(cmdLine,"tar -jxf \"%s\" -C \"%s\"", ris.toUtf8().constData(),QString(QDir::home().path()+"/.xqde/").toUtf8().constData());
	qWarning("Running [%s]",cmdLine);
	QProcess::execute(cmdLine);
	QFile pippo(ris);
	pippo.remove();
}

QString XQDEPlugin_WebHelper::WebHelper_DownloadResource(QString rsc, QString tgfolder)
{
	// TODO: cache on harddisk
	QString rit="";
	char targetUrl[1025];
	char cmdLine[1025];
	char username[512];
	char password[512];
	sprintf(username,"betatester");
	sprintf(password,"betatester");
	
	sprintf(targetUrl,"%s?project=xqde&version=%s&username=%s&password=%s&find=%s",GetNamedValueString("serverurl").toUtf8().constData(),XQDESRCDATE,username,password,rsc.toUtf8().constData());
	char destDir[512];
	sprintf(destDir,"%s",tgfolder.toUtf8().constData());
	QDir d;
	d.mkpath(destDir);
	rit=tgfolder+"/"+rsc;
	sprintf(cmdLine,"curl -L \"%s\" -o \"%s\"",targetUrl,rit.toUtf8().constData());
	qWarning("Running [%s]",cmdLine);
	QProcess::execute(cmdLine);
	QFile pippo(rit);
	if(pippo.size()<1)
	{
		qWarning("WebHelper_DownloadResource: Failed to download webresource");
		pippo.remove();
		return "";
	}
	return rit;
}


void XQDEPlugin_WebHelper::XQDEEnvironmentTheme_findImage_miss(QString logicName)
{
	qWarning("void XQDEPlugin_WebHelper::XQDEEnvironmentTheme_findImage_miss(QString)");

	QString ris=WebHelper_DownloadResource(
	QString(logicName+".png"),
	QString(QDir::home().path()+"/.xqde/icons"));
	
}
