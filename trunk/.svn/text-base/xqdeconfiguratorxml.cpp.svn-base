//
// C++ Implementation: xqdeconfigurator
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdeconfiguratorxml.h"
#include <QListWidget>


XQDEConfiguratorXML::XQDEConfiguratorXML() : QDialog()
{
	setupUi(this);
	connect(pOK, SIGNAL(clicked()),SLOT(accept()));
	connect(list_names, SIGNAL(itemClicked(QListWidgetItem *)),SLOT(ln_itemClicked(QListWidgetItem *)));
	connect(var_value, SIGNAL(textChanged(const QString &)),SLOT(value_textChanged(const QString &)));
	lastKeyName="";	
}


XQDEConfiguratorXML::~XQDEConfiguratorXML()
{

}

void XQDEConfiguratorXML::value_textChanged(const QString &tt)
{
	if(lastKeyName=="" || lastRemoteObj==NULL)return;
	
		QObject *remoteObj=lastRemoteObj;
		connect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));
	
		WriteNamedValue(lastKeyName,tt);

		disconnect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));

}
void XQDEConfiguratorXML::ln_itemClicked(QListWidgetItem *lw)
{
	if(!lw)return;
		lastKeyName="";
		QObject *remoteObj=lastRemoteObj;
		connect(this, SIGNAL(GetNamedValue(const QString &, QString &)), remoteObj, SLOT(GetNamedValue(const QString &, QString &)));
		connect(this, SIGNAL(GetNamesList(QStringList &)), remoteObj, SLOT(GetNamesList(QStringList &)));
		connect(this, SIGNAL(GetNamedDecription(const QString &, QString &)), remoteObj, SLOT(GetNamedDecription(const QString &, QString &)));
		connect(this, SIGNAL(GetNamedType(const QString &, QString &)), remoteObj, SLOT(GetNamedType(const QString &, QString &)));
		connect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));
	
		QString t;
		t="";
		GetNamedDecription(lw->text(),t);
		var_description->setText(t);
		t="";
		GetNamedValue(lw->text(),t);
		var_value->setText(t);

		disconnect(this, SIGNAL(GetNamedValue(const QString &, QString &)), remoteObj, SLOT(GetNamedValue(const QString &, QString &)));
		disconnect(this, SIGNAL(GetNamesList(QStringList &)), remoteObj, SLOT(GetNamesList(QStringList &)));
		disconnect(this, SIGNAL(GetNamedDecription(const QString &, QString &)), remoteObj, SLOT(GetNamedDecription(const QString &, QString &)));
		disconnect(this, SIGNAL(GetNamedType(const QString &, QString &)), remoteObj, SLOT(GetNamedType(const QString &, QString &)));
		disconnect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));
	
		lastKeyName=lw->text();
}

void XQDEConfiguratorXML::configureThisComponentViaXML(QObject *remoteObj)
{
	lastKeyName="";
	lastRemoteObj=remoteObj;
		// Erase all data!
		list_names->reset();
		var_description->setText("");
		var_value->setText("");
		c_name->setText("");
		c_author->setText("");
		c_web->setText("");
		c_email->setText("");
		c_autoupdate->setText("");
		c_ver->setText("");

	if(remoteObj==NULL)
	{
		hide();
	}
	else
	{
		// load all plugin data
		connect(this, SIGNAL(GetNamedValue(const QString &, QString &)), remoteObj, SLOT(GetNamedValue(const QString &, QString &)));
		connect(this, SIGNAL(GetNamesList(QStringList &)), remoteObj, SLOT(GetNamesList(QStringList &)));
		connect(this, SIGNAL(GetNamedDecription(const QString &, QString &)), remoteObj, SLOT(GetNamedDecription(const QString &, QString &)));
		connect(this, SIGNAL(GetNamedType(const QString &, QString &)), remoteObj, SLOT(GetNamedType(const QString &, QString &)));
		connect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));
		
		QString buf;
		//
		buf="";
		emit GetNamedValue("name", buf);
		c_name->setText(buf);
		//
		buf="";
		emit GetNamedValue("author", buf);
		c_author->setText(buf);
		//
		buf="";
		emit GetNamedValue("web", buf);
		c_web->setText(buf);
		//
		buf="";
		emit GetNamedValue("email", buf);
		c_email->setText(buf);
		//
		buf="";
		emit GetNamedValue("autoupdate", buf);
		c_autoupdate->setText(buf);
		//
		buf="";
		emit GetNamedValue("ver", buf);
		c_ver->setText(buf);

		var_description->setText("");
		var_value->setText("");
		
		
		QStringList li;
		GetNamesList(li);
		
		list_names->clear();
		
		for(int i=0;i<li.count();i++)
		{
			//QListWidgetItem *it=new QListWidgetItem(li[i], list_names);
			//list_names->addItem(it);
			list_names->addItem(li[i]);
		}


		disconnect(this, SIGNAL(GetNamedValue(const QString &, QString &)), remoteObj, SLOT(GetNamedValue(const QString &, QString &)));
		disconnect(this, SIGNAL(GetNamesList(QStringList &)), remoteObj, SLOT(GetNamesList(QStringList &)));
		disconnect(this, SIGNAL(GetNamedDecription(const QString &, QString &)), remoteObj, SLOT(GetNamedDecription(const QString &, QString &)));
		disconnect(this, SIGNAL(GetNamedType(const QString &, QString &)), remoteObj, SLOT(GetNamedType(const QString &, QString &)));
		disconnect(this, SIGNAL(WriteNamedValue(const QString &,const QString &)), remoteObj, SLOT(WriteNamedValue(const QString &,const QString &)));
		
		show();
	}
}
