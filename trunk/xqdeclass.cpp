//
// C++ Implementation: xqdeclass
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QDir>
#include <QStringList>
#include <QFile>
#include <QDomElement>
#include <QByteArray>
#include <QDateTime>

#include "xqdeclass.h"


QObject *XQDEClass::globalXQDERoot;
QObject *XQDEClass::globalXQDEConfiguration;
QObject *XQDEClass::globalXQDEEvents;
QObject *XQDEClass::globalXQDEEngine;
QList<QObject *> XQDEClass::globalXQDEPlugins;


XQDEClass::XQDEClass(QObject *lRoot) :QObject()
{
        // setup my virtual Root-father wich I will use as Window parent or other issues
        #ifdef ENABLEDEBUGMSG
        qWarning("XQDEClass::XQDEClass(QObject *lRoot) :QObject()");
        #endif
        ObjectRoot=lRoot;
        ObjectName=QString("com.xiaprojects.XQDEClass.") + QString::number((long)this);
        // Reset my ID
/*
        MyId.name="XQDEClass";
        MyId.type="none";
        MyId.status=0;
        MyId.path="";
*/
        // Register this new plugin on plugin list
        if(ObjectRoot!=NULL)
        {
        #ifdef ENABLEDEBUGMSG
                qWarning("XQDEClass::XQDEClass(QObject *lRoot) :QObject() registering...");
                #endif
                bool lIsConnected=connect(this, SIGNAL(sgPluginRegister(QObject *)),ObjectRoot,SLOT(PluginRegister(QObject *)));
                if(lIsConnected){
                        sgPluginRegister(this);
                        disconnect(SIGNAL(sgPluginRegister(QObject *)));
                }
        }
}

XQDEClass::~XQDEClass()
{
        if(ObjectRoot!=NULL)
        {
                bool lIsConnected=connect(this, SIGNAL(sgPluginUnRegister(QObject *)),ObjectRoot,SLOT(PluginUnRegister(QObject *)));
                if(lIsConnected){
                        sgPluginUnRegister(this);
                        disconnect(SIGNAL(sgPluginUnRegister(QObject *)));
                }
        }
}


void XQDEClass::FreezeSave(const QString &DataPath)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEClass::FreezeSave(const QString &)");
	#endif
	const QString MyStoreDataPathRelative="data";
	QString localPathDir=DataPath;
	if(localPathDir=="")
	{
		localPathDir=QDir::home().path();
	}
	#ifdef ENABLEDEBUGMSG
		qWarning("Home: %s",localPathDir.toAscii().data());
	#endif
        QDir *XQDEqd=new QDir(localPathDir);
        XQDEqd->mkpath(".xqde");
        XQDEqd->cd(".xqde");
        localPathDir=XQDEqd->path();

	#ifdef ENABLEDEBUGMSG
		qWarning("Created:%s",localPathDir.toAscii().data());
	#endif

	QDir *qd=new QDir(localPathDir);
	if(!qd->mkpath(MyStoreDataPathRelative))
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("Error creating data path while storing XMLs data");
	#endif
	}
	else
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("Created data xml data");
	#endif
	}
	if(!qd->cd(MyStoreDataPathRelative))
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("Error CD data path while storing XMLs data");
	#endif
		return;	
	}

	QString fileName=qd->absolutePath()+"/"+ObjectName+".xml";	
	
	QFile xmlFile(fileName);

	QDomDocument doc( "xiaprojects" );
	if ( !xmlFile.open( QIODevice::WriteOnly ) )
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("Error writing xml");
        #endif
		return;
	}
	QDomElement root=doc.createElement("xqde");
	doc.appendChild(root);

	// *** Start common XML format
	root.setAttribute("version","TODO");
	root.setAttribute("file",fileName);
	QDomElement xmlObjectIcon=doc.createElement("object");
	root.appendChild(xmlObjectIcon);
	xmlObjectIcon.setAttribute("class",ObjectName);
	xmlObjectIcon.setAttribute("type","plugin");
	// *** End common XML format
	// start XQDEIcon type storing
	for(int i=0;i<ConfigurationData.count();i++)
	{
		XQDEConfigurationPair *pk=ConfigurationData.at(i);
		xmlObjectIcon.setAttribute(pk->Key,pk->Value);
	}
	// **** Common XML
	QByteArray a=doc.toByteArray();
	xmlFile.write(a);
	xmlFile.flush();
        xmlFile.close();
	// ***
	// TODO: check garbage
	#ifdef ENABLEDEBUGMSG
	qWarning("End writing to %s",fileName.toUtf8().constData());
	#endif
	
}

void XQDEClass::FreezeRestore(const QString &DataPath)
{
	const QString MyStoreDataPathRelative="data";
	QString localPathDir=DataPath;
	if(localPathDir=="")
	{
		localPathDir=QDir::home().path();
	}
	QString fn=localPathDir+"/.xqde/"+MyStoreDataPathRelative+"/"+ObjectName + ".xml";
	#ifdef ENABLEDEBUGMSG
	qWarning("Importing data: %s",fn.toAscii().data());
        #endif
	import(fn);
}

void XQDEClass::import(const QString &fileName)
{
	QFile xmlFile(fileName);

	if ( !xmlFile.open( QIODevice::ReadOnly ) )
	{
	#ifdef ENABLEDEBUGMSG
		qWarning("Error reading xml");
	#endif
		return;
	}
	QDomDocument doc( "xiaprojects" );
	doc.setContent(&xmlFile);
	QDomNodeList nl=doc.elementsByTagName("object");
	if(nl.count()<1)return;

	for(int i=0;i<nl.count();i++)
	{
		QString addedIconclass=nl.at(i).toElement().attribute("class",ObjectName);
		if(addedIconclass!=ObjectName)continue;
		QString addedIcontype=nl.at(i).toElement().attribute("type","plugin");
		if(addedIcontype!="plugin")continue;
		// ok now we can restore data!!
		for(int a=0;a<nl.at(i).toElement().attributes().count();a++)
		{
			QString nn=nl.at(i).toElement().attributes().item(a).nodeName();
			
			if(nn=="version")continue;
			if(nn=="name")continue;
			if(nn=="author")continue;
			if(nn=="web")continue;
			if(nn=="email")continue;
			if(nn=="autoupdate")continue;
				
                        #ifdef ENABLEDEBUGMSG
			qWarning("importing %s",nn.toUtf8().constData());
                        #endif
			QString nv=nl.at(i).toElement().attributes().item(a).nodeValue();
			WriteNamedValue(nn,nv);
		}
	}
        xmlFile.close();

	#ifdef ENABLEDEBUGMSG
	qWarning("End reading");
	#endif
}


// Interface to exchange data with remoteObj
void XQDEClass::GetNamesList(QStringList &a)
{
	#ifdef ENABLEDEBUGMSG
	qWarning("void XQDEClass::GetNamesList(QStringList &a)");
	#endif
	a.clear();
	for(int i=0;i<ConfigurationData.count();i++)
	{
		a.append(ConfigurationData.at(i)->Key);
	}
}

void XQDEClass::GetNamedValue(const QString &k, QString &v)
{
	if(k=="name")
	{
		v=ObjectName;
	}
	else
	{
		for(int i=0;i<ConfigurationData.count();i++)
		{
			if(ConfigurationData.at(i)->Key==k)
			{
				v=ConfigurationData.at(i)->Value;
			}
		}
	}
}

QString XQDEClass::GetNamedValueString(const QString &k)
{
	QString v="";
	GetNamedValue(k,v);
	return v;
}

void XQDEClass::GetNamedDecription(const QString &k, QString &v)
{
	if(k=="name")
	{
		v="Object Name";
	}
	else
	{
		for(int i=0;i<ConfigurationData.count();i++)
		{
			if(ConfigurationData.at(i)->Key==k)
			{
				v=ConfigurationData.at(i)->Description;
			}
		}
	}
}
void XQDEClass::GetNamedType(const QString &k, QString &v)
{
	if(k=="name")
	{
		v="string";
	}
	else
	{
		for(int i=0;i<ConfigurationData.count();i++)
		{
			if(ConfigurationData.at(i)->Key==k)
			{
				v=ConfigurationData.at(i)->Type;
			}
		}
	}
}

extern QString DataPath;

void XQDEClass::WriteNamedValue(const QString &k,const QString &v)
{
	if(k=="name")
	{
		
	}
	else
	{
		for(int i=0;i<ConfigurationData.count();i++)
		{
			if(ConfigurationData.at(i)->Key==k)
			{
				ConfigurationData.at(i)->setValue(v);
			}
		}
	}
	
	// Ensure changes has being wrote
	FreezeSave(DataPath);
}

void XQDEClass::parseString(const QString &, int, void *)
{
}
