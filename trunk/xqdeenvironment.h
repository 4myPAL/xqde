//
// C++ Interface: xqdeenvironment
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEENVIRONMENT_H
#define XQDEENVIRONMENT_H

#include "xqdeclass.h"			// ok
//#include <QMap>
//#include <QString>
//#include <QStringList>
class QStringList;
class QDomNode;


struct XSCfgTextFont
{
	int FontRed;
	int FontGreen;
	int FontBlue;
	QString FontFamily;
	int	FontSize;
	QString BackgroundPath;
	int	Bold;
	int	Italic;
	int	OtherBinaryValue;
	int	Weight;
	int	Other;
	QString	Alias;
	int	XPercentageDisplacement;
	int	YPercentageDisplacement;

};

class XQDEEnvironmentTheme : public QObject
	{
		Q_OBJECT
		public:
		XQDEEnvironmentTheme();
		QString findImage(QString loginName);
		QString getPathImagesByTheme(QString ThisTheme, int UserLevel=0);
		QString pathImages;
		QString Theme;
		QString Arrow;
		QStringList *IconsPaths;
		void xReset();
		signals:
		void XQDEEnvironmentTheme_findImage_miss(QString);
		void XQDEEnvironmentTheme_findResources_miss(QString, QString);
		protected:
			void checkDefaultResourcesConsistency();
	};

class XQDEEnvironmentUserProfile:QObject
	{
		Q_OBJECT
		public:
		XQDEEnvironmentUserProfile();
		public slots:
			void configureComponent(QObject *);
		signals:
			void configureThisComponentViaXML(QObject *);
		protected:
			class QWidget *ConfiguratorXML;
	};



class XQDEEnvironmentGUI
	{
		public:
		XQDEEnvironmentGUI();
		long handIconsMax;
		long sizeIconsMax;
		long sizeIconsNormal;
		XSCfgTextFont desktopFont;
		long task_GroupSimilarWindows;
		long updateViaDND;
		long dockAlign;
		void restore(QDomNode *);
		void store(QDomNode *);
		int dockAlignDisplaceX;
		int dockAlignDisplaceY;
		int task_GroupByPID;
	};

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEEnvironment 
{
//Q_OBJECT
public:
    XQDEEnvironment(XQDEClass *parent = 0);

    virtual ~XQDEEnvironment();
	 XQDEEnvironmentUserProfile 	UserProfile;
	 XQDEEnvironmentTheme 		Theme;
	 XQDEEnvironmentGUI		GUI;
int GenericPluginNeedPolled;
/*
	static QMap <QString,long> 		Longs;
	static QMap <QString,QString> 		Strings;
	static QMap <QString,QStringList> 	Lists;
*/

};

extern void GenericPluginNeedPolledEnable();

extern XQDEEnvironment *DesktopEnvironment;

//
class QImage;
QImage *XQDE_ImageRepeat(QImage &,QImage &, int ,int );
QImage *XQDE_ImageEraseRect(QImage &,uint,uint,uint);
QImage *XQDE_ImageSetIntensity(QImage &,double);

/*
#ifndef RESIZEVIAXRENDER
	void XQDE_ImageRotate(QImage &target,const QImage &source, double degree);
#else
	void XQDE_ImageRotate(QPixmap &target,const QPixmap &source, double degree);
#endif
*/
//

void MakeWindowOnTop(void *w);
void MakeWindowOnBottom(void *w);
#endif
