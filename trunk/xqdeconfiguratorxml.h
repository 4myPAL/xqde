//
// C++ Interface: xqdeconfiguratorxml
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDECONFIGURATORXML_H
#define XQDECONFIGURATORXML_H

#include <QDialog>

#include "ui_XQDEUIConfiguratorXML.h"

class XQDEConfiguratorXML: public QDialog, Ui::XQDEUIConfiguratorXML
{
Q_OBJECT
public:
    XQDEConfiguratorXML();
    ~XQDEConfiguratorXML();
public slots:
	void configureThisComponentViaXML(QObject *remoteObj);
	void ln_itemClicked(QListWidgetItem *lw);
	void value_textChanged(const QString &tt);
signals:
	// Interface to exchange data with remoteObj
	void GetNamesList(QStringList &);
	void GetNamedValue(const QString &, QString &);
	void GetNamedDecription(const QString &, QString &);
	void GetNamedType(const QString &, QString &);
	void WriteNamedValue(const QString &,const QString &);

protected:
		QObject *lastRemoteObj;
	QString lastKeyName;
};

#endif
