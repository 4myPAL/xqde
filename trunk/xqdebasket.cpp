//
// C++ Implementation: xqdebasket
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QDir>
#include <QFile>
#include <QDomElement>
#include <QByteArray>
#include <QDateTime>
#include <QMap>

#include "xqdeenvironment.h"
#include "xqdebasket.h"
#include "xqde.h"
#include "xqdeaction.h"
#include "xqdeplugin.h"

//#include <import_netwm.h>

XQDEBasket *Basket;

XQDEBasket::XQDEBasket(XQDEClass *parent)
 : XQDEClass(parent)
{
    ObjectName="com.xiaprojects.Basket";
    ConfigurationData.append(new XQDEConfigurationPair("serverurl","http://xqde.xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("email","xqde@xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("author","Stefano Zingarini"));
    ConfigurationData.append(new XQDEConfigurationPair("web","http://xqde.xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("version",""));
    ConfigurationData.append(new XQDEConfigurationPair("autoupdate",""));
}


XQDEBasket::~XQDEBasket()
{
}

void XQDEBasket::setTitleViaData(void *cData,QString &title, QObject *pf)
{
	XQDEIcon *ic=getViaData(cData,pf);
	if(!ic)return;
        ic->xSetTitle(title);
	//emit Basket_As_Changed(2, ic, NULL);
}
void XQDEBasket::setImageViaData(void *cData,QImage &i, QObject *pf)
{
        qDebug("void XQDEBasket::setImageViaData");
	XQDEIcon *ic=getViaData(cData,pf);
	if(!ic)return;
	ic->xSetIcon(i);
	emit Basket_As_Changed(2, ic, NULL);
}
void XQDEBasket::setImageViaData(void *cData,QImage &i)
{
        qDebug("void XQDEBasket::setImageViaData");
	XQDEIcon *ic=getViaData(cData);
	if(!ic)return;
	ic->xSetIcon(i);
	emit Basket_As_Changed(2, ic, NULL);
}
XQDEIcon *XQDEBasket::getViaLogicName(const QString & logicName)
{
	for(int i=0;i<items.size();i++)
	{
		XQDEIcon *newItem=items.at(i);
		if(newItem->logic()==logicName)
		{
			return newItem;
		}
	}
	return 0;
}
XQDEIcon *XQDEBasket::getViaData(void *cData)
{
	for(int i=0;i<items.size();i++)
	{
		XQDEIcon *newItem=items.at(i);
		if(newItem->clientData()==cData)
		{
			return newItem;
		}
	}
	return NULL;
}
XQDEIcon *XQDEBasket::getViaPID(long pid)
{
	for(int i=0;i<items.size();i++)
	{
		XQDEIcon *rit=items.at(i);
		for(int p=0;p<rit->pidsData()->size();p++)
		{
			long lpid=(long)rit->pidsData()->at(p);
			if(lpid==pid)return rit;
		}
	}	
	return NULL;
}
XQDEIcon *XQDEBasket::getViaData(void *cData, QObject *pf)
{
        qWarning("XQDEBasket::getViaData()");
	for(int i=0;i<items.size();i++)
	{
		XQDEIcon *newItem=items.at(i);
		if(pf==NULL || newItem->sensor()==NULL || newItem->sensor()==pf)
		{
			int pfi=newItem->clientsData()->indexOf(cData);
			if(pfi>=0)
			{
				return newItem;
			}
		}
	}
	return NULL;
}
void XQDEBasket::sgeBasket_As_Changed(int a,XQDEIcon* b,void* c)
{
        qDebug("void XQDEBasket::sgeBasket_As_Changed(int a,XQDEIcon* b,void* c) start");


        emit Basket_As_Changed(a,b,c);

        qDebug("void XQDEBasket::sgeBasket_As_Changed(int a,XQDEIcon* b,void* c) end");

}


void XQDEBasket::DelFromBasket(XQDEIcon *cData,int WithOutAnimation)
{
	qWarning("XQDEBasket::DelFromBasket() emit [size=%d]",items.size());
	if(WithOutAnimation>0)
	{
		int o=-1;;
		for(int i=0;i<items.size();i++)
		{
			if(items.at(i)==cData)
			{
				o=i;
				break;
			}
		}
		if(o>=0)
		{
		XQDEIcon *delItem=items.takeAt(o);
		emit Basket_As_Changed(6, cData, NULL);
		delete delItem;
		}
	}
	else
	{
		emit Basket_As_Changed(0, cData, NULL);
	}

}

void XQDEBasket::DelFromBasketViaData(void *cData, int WithOutAnimation)
{
        //qWarning("XQDEBasket::DelFromBasketViaData()");
/*
        for(int i=0;i<items.size();i++)
        {
                XQDEIcon *newItem=items.at(i);
                if(newItem->clientData()==cData)
                {
                        qWarning("XQDEBasket::DelFromBasketViaData() emit [size=%d]",items.size());
                        XQDEIcon *delItem=items.takeAt(i);
                        i--;
                        emit Basket_As_Changed(0, newItem, NULL);
                        //qWarning("XQDEBasket::DelFromBasketViaData() end");
                        delete delItem;
                        //qWarning("XQDEBasket::DelFromBasketViaData() deleted!!");
                }
        }*/
        DelFromBasketViaData(cData,0,WithOutAnimation);
}

void XQDEBasket::DelFromBasketViaData(void *cData, QObject *pf,int WithOutAnimation)
{
        qWarning("XQDEBasket::DelFromBasketViaData()");
	for(int i=0;i<items.size();i++)
	{
		XQDEIcon *newItem=items.at(i);
		if(pf==0 || newItem->sensor()==pf ||newItem->sensor()==0)
		{
			int pfi=newItem->clientsData()->indexOf(cData);
			if(pfi>=0)
			{
				newItem->clientsData()->takeAt(pfi);
				if(newItem->clientsData()->size()>0 || newItem->storeOnExit || newItem->pidsData()->size()>0)
				{
					QImage none;
					newItem->xSetIconWM(none);
					newItem->xSetIcon(none);
					newItem->xSetTitle(newItem->logic());
					emit Basket_As_Changed(4, newItem, NULL);
					return;
				}
				DelFromBasket(newItem,WithOutAnimation);
			}
		}
	}
}

XQDEIcon *XQDEBasket::clone(XQDEIcon *sourceIcon, QObject *cloneSender)
{
/*
    XQDEIcon(QString logicName,QObject * p=0, void *cData=0,QImage *defaultImg=0, QString strTitle=0, QString defaulticon=0);
QObject *SensorManager,void *cData,const char *logicName, const char *, const char *title, QImage *defaultIcon)
*/
	//QImage nullI;
	XQDEIcon *addedIcon=new XQDEIcon(sourceIcon->logic(),
				cloneSender,(void *)0,0,sourceIcon->title(),sourceIcon->icon());
/*Basket->AddtoBasket(
		cloneSender,finto,
		sourceIcon->logic().toAscii().data(),
		finto,
		sourceIcon->title().toAscii().data(),&nullI,sourceIcon->icon());
*/
	addedIcon->enablePreview=sourceIcon->enablePreview;
	addedIcon->groupWindows=sourceIcon->groupWindows;
	// actions...
	return addedIcon;
}

XQDEIcon *XQDEBasket::findTemplate(QString &stringmatch, QString &classmatch,QObject *)
{
	for(int ix=0;ix<templates.size();ix++)
	{
		XQDEIcon *icon=templates.at(ix);
		for(int i=0;i<icon->slotsSensor->count();i++)
		{
                        qWarning("[%s][%s]",stringmatch.toAscii().data(),icon->slotsSensor->at(i)->Slot.toAscii().data());
			if(stringmatch.indexOf(icon->slotsSensor->at(i)->Slot)>=0)
			{
				return icon;
			}
		}
	}
/*
	for(int ix=0;ix<templates.size();ix++)
	{
		XQDEIcon *icon=templates.at(ix);
		if(classmatch.indexOf(icon->logic())>=0)return icon;
	}
*/
	Q_UNUSED(classmatch);
	return NULL;
}

XQDEIcon *XQDEBasket::AddtoBasketWidget(QObject *SensorManager,void *cData,XQDEPlugin *WidgetClass, QString Title)
{
	if(WidgetClass==0)return 0;

	QString logicName=QString::number((long int)WidgetClass);
	XQDEIcon *newItem=new XQDEIcon(logicName,SensorManager,cData,0,Title,Title);
	WidgetClass->attach(newItem);
	newItem->xReset();

	
	items.append(newItem);
	//qWarning("XQDEBasket::AddtoBasket_Window() emit");
	emit Basket_As_Changed(1, newItem, NULL);
	//qWarning("XQDEBasket::AddtoBasket_Window() end");
	return newItem;
}

XQDEIcon *XQDEBasket::AddtoBasket(QObject *SensorManager,void *cData,QString logicName, QString, QString title, QImage *defaultIcon, QString defaultIconFile)
{
	qWarning("XQDEBasket::AddtoBasket_Window()");
	if(title==0 || title.length()<1)title=logicName;
	XQDEIcon *newItem=new XQDEIcon(logicName,SensorManager,cData,defaultIcon,title,defaultIconFile);
	newItem->xReset();
	items.append(newItem);
	qWarning("XQDEBasket::AddtoBasket_Window() emit");
	emit Basket_As_Changed(1, newItem, NULL);
	qWarning("XQDEBasket::AddtoBasket_Window() end");


	return newItem;
}

void XQDEBasket::FreezeSave(const QString &DataPath)
{
	// this function store all icons into separate XMLs
	qWarning("void XQDEBasket::FreezeSave(const QString &DataPath)");
	const QString MyStoreDataPathRelative="basket";
	QString localPathDir=DataPath;
	if(localPathDir=="")
	{
		localPathDir=QDir::home().path();
	}
		qWarning("Home: %s",localPathDir.toAscii().data());
		QDir *XQDEqd=new QDir(localPathDir);
		XQDEqd->mkpath(".xqde");
		XQDEqd->cd(".xqde");
		localPathDir=XQDEqd->path();
		qWarning("Created:%s",localPathDir.toAscii().data());
	QDir *qd=new QDir(localPathDir);
	if(!qd->mkpath(MyStoreDataPathRelative))
	{
		qWarning("Error creating basket path while storing XMLs data");
		//return;
	}
	else
	{
		qWarning("Created basket xml data");
	}
	if(!qd->cd(MyStoreDataPathRelative))
	{
		qWarning("Error CD basket path while storing XMLs data");
		return;	
	}
	qWarning("Cleaning old icons from:%s",qd->path().toAscii().data());
	QStringList AllXMLs;
	AllXMLs<<"*.xml";
	
	QStringList OldXMLs=qd->entryList (AllXMLs);//,QDir::Writable);
	for(int i=0;i<OldXMLs.count();i++)
	{
		qWarning("Removing:%s",OldXMLs[i].toAscii().data());
		qd->remove(OldXMLs[i]);
	}
	qWarning("Exporting all icons to:%s",qd->path().toAscii().data());
	int StoredIconCounter=0;
	for(int isc=0;isc<items.count();isc++)
	{
		XQDEIcon *icToStore=items.at(isc);
		if(icToStore==0)continue;
		if(icToStore->storeOnExit==0)continue;


		char NumeroIndice[10];
		memset(NumeroIndice,0,9);
		sprintf(NumeroIndice,"%03d",StoredIconCounter++);

		QString fileNametarget=qd->absolutePath()+"/"+QString(NumeroIndice)+"_"+icToStore->logic()+".xml";
		qWarning("Exporting icon:%d to %s",isc,fileNametarget.toAscii().data());
		iconExport(icToStore,fileNametarget);
	}
}
void XQDEBasket::FreezeRestoreLoadFromandStoreTo(QDir *qd,QList<XQDEIcon *> *con)
{
	qWarning("void XQDEBasket::FreezeRestoreLoadFromandStoreTo() %s",qd->path().toAscii().data());
	QStringList AllXMLs;
	AllXMLs<<"*.xml";
	
	QStringList OldXMLs=qd->entryList (AllXMLs);//,QDir::Writable);
	for(int i=0;i<OldXMLs.count();i++)
	{
		qWarning("Adding:%s",OldXMLs[i].toAscii().data());
		XQDEIcon *newItem=iconImport(qd->path()+"/"+OldXMLs[i]);
		newItem->xReset();
		con->append(newItem);
		if(con==&items)emit Basket_As_Changed(1, newItem, NULL);
	}

	qWarning("void XQDEBasket::FreezeRestoreLoadFromandStoreTo() end");
}

void XQDEBasket::FreezeRestore(const QString &DataPath)
{
	// this function store all icons into separate XMLs
	qWarning("void XQDEBasket::FreezeSave(const QString &DataPath)");
	const QString MyStoreDataPathRelative="basket";
	const QString MyStoreDataPathRelativeTemplate="templates";

	QString localPathDir=DataPath;

	if(localPathDir=="")
	{
		localPathDir=QDir::home().path();
	}

        qWarning("Home: %s",localPathDir.toAscii().data());
        QDir *XQDEqd=new QDir(localPathDir);
        XQDEqd->mkpath(".xqde");
        XQDEqd->cd(".xqde");
        localPathDir=XQDEqd->path();
        qWarning("Created:%s",localPathDir.toAscii().data());
//	QDir *qd=new QDir(localPathDir);
        if(!XQDEqd->mkpath(MyStoreDataPathRelative))
	{
		qWarning("Error creating basket path while storing XMLs data");
		//return;
	}
	else
	{
		qWarning("Created basket xml data");
	}
        if(XQDEqd->cd(MyStoreDataPathRelative))
	{
                FreezeRestoreLoadFromandStoreTo(XQDEqd,&items);
//		qd->cd("..");
	}
        if(XQDEqd->cd(MyStoreDataPathRelativeTemplate))
	{
                FreezeRestoreLoadFromandStoreTo(XQDEqd,&templates);
//		qd->cd("..");
	}
        delete XQDEqd;
}

XQDEIcon *XQDEBasket::iconImport(const QString &fileName)
{
	qWarning("Importing:%s", fileName.toAscii().data());

	// **** Start common XML format
	QFile xmlFile(fileName);

	if ( !xmlFile.open( QIODevice::ReadOnly ) )
	{
		qWarning("Error reading xml");
		return 0;
	}
	QDomDocument doc( "xiaprojects" );
	doc.setContent(&xmlFile);
	QDomNodeList nl=doc.elementsByTagName("object");
	if(nl.count()<1)return 0;

        XQDEIcon *addedIcon=NULL;

	for(int i=0;i<nl.count();i++)
	{
		QString logicName="";
		QString title="";


		QString addedIconclass=nl.at(i).toElement().attribute("class","XQDEIcon");
		if(addedIconclass!="XQDEIcon")continue;
		QString addedIcontype=nl.at(i).toElement().attribute("type","icon");
		if(addedIcontype!="icon")continue;


		logicName=nl.at(i).toElement().attribute("name","");
		QString defaulticon=nl.at(i).toElement().attribute("icon","");


		QDateTime a=QDateTime::currentDateTime();
		QString randomName=a.toString("mmss");


		if(logicName=="")logicName="AddedIcon_"+randomName;

		if(title=="")title=logicName;
		QImage defaultimg;
		//defaultimg.load(DesktopEnvironment->Theme.findImage(srcImage));
		addedIcon=new XQDEIcon(logicName,0,0,&defaultimg,title,defaulticon);
		addedIcon->storeOnExit=1;// this will avoid lost of icon after

                addedIcon->storeOnExit=nl.at(i).toElement().attribute("storeOnExit",0).toInt();
                addedIcon->enablePreview=nl.at(i).toElement().attribute("enablePreview",0).toInt();
                addedIcon->groupWindows=nl.at(i).toElement().attribute("groupWindows",0).toInt();

		QDomNodeList nla=nl.at(i).toElement().elementsByTagName("action");
		for(int a=0;a<nla.count();a++)
		{
			addedIcon->actions->remove(nla.at(a).toElement().attribute("name"));
			XQDEAction *ac=new XQDEAction;
			ac->Action=nla.at(a).toElement().attribute("value");
			ac->ActionType=nla.at(a).toElement().attribute("type");
			addedIcon->actions->insert(nla.at(a).toElement().attribute("name"),ac);
		}
		QDomNodeList nls=nl.at(i).toElement().elementsByTagName("slot");
		addedIcon->slotsSensor->clear();
		for(int a=0;a<nls.count();a++)
		{
			XQDESlotSensor *ac=new XQDESlotSensor;
			QDomElement e=nls.at(a).toElement();
			ac->readXMLElement(e);
			addedIcon->slotsSensor->append(ac);
		}
	}

        xmlFile.close();
	// ***
	qWarning("End reading");
	return addedIcon;
}
void XQDEBasket::iconExport(XQDEIcon *eicon,const QString &fileName)
{
//	qWarning("Exporting:(%d)%s", (int)eicon,eicon->logic().toAscii().data());

	// **** Start common XML format
	QFile xmlFile(fileName);

	QDomDocument doc( "xiaprojects" );
	if ( !xmlFile.open( QIODevice::WriteOnly ) )
	{
		qWarning("Error writing xml");
		return;
	}
	QDomElement root=doc.createElement("xqde");
	doc.appendChild(root);

	root.setAttribute("version","TODO");
	root.setAttribute("file",fileName);
	
	QDomElement xmlObjectIcon=doc.createElement("object");
	root.appendChild(xmlObjectIcon);
	xmlObjectIcon.setAttribute("class","XQDEIcon");
	xmlObjectIcon.setAttribute("type","icon");
	// *** End common XML format
	// start XQDEIcon type storing
	xmlObjectIcon.setAttribute("name",eicon->logic());
	xmlObjectIcon.setAttribute("icon",eicon->icon());
	xmlObjectIcon.setAttribute("storeOnExit",eicon->storeOnExit);
	xmlObjectIcon.setAttribute("enablePreview",eicon->enablePreview);
	xmlObjectIcon.setAttribute("groupWindows",eicon->groupWindows);

	QDomElement xmlObjectIconActions=doc.createElement("actions");
	xmlObjectIcon.appendChild(xmlObjectIconActions);

	QMapIterator<QString, XQDEAction *> i(*eicon->actions);
	while (i.hasNext())
	{
		i.next();
		QDomElement xmlObjectIconAction=doc.createElement("action");
		xmlObjectIconActions.appendChild(xmlObjectIconAction);
		xmlObjectIconAction.setAttribute("name",i.key());
		xmlObjectIconAction.setAttribute("type",i.value()->ActionType);
		xmlObjectIconAction.setAttribute("value",i.value()->Action);
	}

	QDomElement xmlObjectIconSlots=doc.createElement("slots");
	xmlObjectIcon.appendChild(xmlObjectIconSlots);
	for(int k=0;k<eicon->slotsSensor->count();k++)
	{
		QDomElement xmlObjectIconSlot=doc.createElement("slot");
		xmlObjectIconSlots.appendChild(xmlObjectIconSlot);
		XQDESlotSensor *sl=(eicon->slotsSensor->at(k));
		sl->writeXMLElement(xmlObjectIconSlot);
	}

	// **** Common XML
	QByteArray a=doc.toByteArray();
	xmlFile.write(a);
	xmlFile.flush();
        xmlFile.close();
	// ***
	qWarning("End writing");
}
