//
// C++ Interface: xqdeclass
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDECLASS_H
#define XQDECLASS_H

#include <QObject>

class XQDEConfigurationPair
{
	public:
		inline XQDEConfigurationPair(const QString &k, const QString &v, const QString &d="", const QString t="string")
		{
			Key=k;
			Value=v;
			Description=d;
			Type=t;
		};
		inline XQDEConfigurationPair(){};
		inline void setValue(const QString &v){Value=v;};
		QString Key;
		QString Value;
		QString Description;
		QString Type;
};


/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEClass: public QObject
{
	Q_OBJECT
	public:
	XQDEClass(QObject *);
	~XQDEClass();
// Identification Members
	QList<XQDEConfigurationPair *> ConfigurationData;
	QString ObjectName;
	/*
	QString ObjectName;
	QString ObjectClass;
	QString ObjectInterface;
	QString ObjectXMLInterface;
	QString ObjectType;
	QString ObjectPath;
	int	ObjectStatus;
	
	*/
	QObject *ObjectRoot;
	
	QList<XQDEClass *> ObjectTree;

	protected:
		static QObject *globalXQDERoot;
		static QObject *globalXQDEConfiguration;
		static QObject *globalXQDEEvents;
		static QObject *globalXQDEEngine;
		static QList<QObject *> globalXQDEPlugins;
	signals:
		void sgPluginRegister(QObject *);
		void sgPluginUnRegister(QObject *);
	public slots:
		virtual void FreezeSave(const QString &);
		virtual void FreezeRestore(const QString &);
		virtual void import(const QString &);
		virtual void parseString(const QString &, int, void *);
		// Interface to exchange data with remoteObj
		virtual void GetNamesList(QStringList &);
		virtual QString GetNamedValueString(const QString &);
		virtual void GetNamedValue(const QString &, QString &);
		virtual void GetNamedDecription(const QString &, QString &);
		virtual void GetNamedType(const QString &, QString &);
		virtual void WriteNamedValue(const QString &,const QString &);
};

#endif
