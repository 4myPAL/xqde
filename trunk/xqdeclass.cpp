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
        qDebug("XQDEClass::XQDEClass(QObject *lRoot) :QObject()");

        ObjectRoot=lRoot;
	ObjectName=QString("com.XQDE.XQDEClass.") + QString::number((long)this);
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
                qDebug("XQDEClass::XQDEClass(QObject *lRoot) :QObject() registering...");

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
        qDebug("void XQDEClass::FreezeSave(const QString &)");

	const QString MyStoreDataPathRelative="data";
	QString localPathDir=DataPath;
	if(localPathDir=="")
	{
		localPathDir=QDir::home().path();
	}

        qDebug("Home: %s",localPathDir.toAscii().data());
        QDir *XQDEqd=new QDir(localPathDir);
        XQDEqd->mkpath(".xqde");
        XQDEqd->cd(".xqde");
        localPathDir=XQDEqd->path();

        qDebug("Created:%s",localPathDir.toAscii().data());

	QDir *qd=new QDir(localPathDir);
	if(!qd->mkpath(MyStoreDataPathRelative))
	{
		qWarning("Error creating data path while storing XMLs data");
	}
	else
	{
		qWarning("Created data xml data");
	}
	if(!qd->cd(MyStoreDataPathRelative))
	{
		qWarning("Error CD data path while storing XMLs data");
		return;	
	}

	QString fileName=qd->absolutePath()+"/"+ObjectName+".xml";	
	
	QFile xmlFile(fileName);

	QDomDocument doc( "xiaprojects" );
	if ( !xmlFile.open( QIODevice::WriteOnly ) )
	{
                qWarning("Error opening xml");
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
        qDebug("End writing to %s",fileName.toUtf8().constData());

	
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
        qDebug("Importing data: %s",fn.toAscii().data());
	import(fn);
}

void XQDEClass::import(const QString &fileName)
{
	QFile xmlFile(fileName);

	if ( !xmlFile.open( QIODevice::ReadOnly ) )
	{
		qWarning("Error reading xml");	
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
				
                        qDebug("importing %s",nn.toUtf8().constData());

			QString nv=nl.at(i).toElement().attributes().item(a).nodeValue();
			WriteNamedValue(nn,nv);
		}
	}
        xmlFile.close();

        qDebug("End reading");

}


// Interface to exchange data with remoteObj
void XQDEClass::GetNamesList(QStringList &a)
{
        qDebug("void XQDEClass::GetNamesList(QStringList &a)");
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
