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
#include "xqdeconfigurator.h"

#include <xqdeenvironment.h>
#include <xqwfirsthand.h>
#include <QFontDialog>
#include <QColorDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QDrag>
#include <QMimeData>
#include <QDesktopWidget>
#include <xqdeproxy.h>
#include <xqdebasket.h>
#include <xqderoot.h>

QWidget *GlobalConfigurator;


XQDEConfigurator::XQDEConfigurator(XQDERoot *pr) : QDialog()
{
	prr=pr;
	qWarning("XQDEConfigurator::XQDEConfigurator() : QDialog()");
	if(GlobalConfigurator!=NULL)
	{
		qWarning("XQDEConfigurator::XQDEConfigurator() : QDialog() Warning already existent GlobalConfigurator!!!!");
		GlobalConfigurator->show();
	}
	else GlobalConfigurator=this;
	qWarning("XQDEConfigurator::XQDEConfigurator() : QDialog() setupUi(this);");
	setupUi(this);
	qWarning("XQDEConfigurator::XQDEConfigurator() : QDialog() setupUi(this); end");

	connect(bigsize, SIGNAL(valueChanged(int)),SLOT(bigsize_valueChanged(int)));
	connect(normalsize, SIGNAL(valueChanged(int)),SLOT(normalsize_valueChanged(int)));
	connect(dockposition, SIGNAL(activated( const QString &)),SLOT(dockposition_activated( const QString &)));
	connect(dockPositionX, SIGNAL(valueChanged(int)),SLOT(dockPositionX_valueChanged(int)));
	connect(dockPositionY, SIGNAL(valueChanged(int)),SLOT(dockPositionY_valueChanged(int)));
	
	connect(changeOverTextFont, SIGNAL(clicked()),SLOT(changeOverTextFont_clicked()));
	connect(changeOverTextColor, SIGNAL(clicked()),SLOT(changeOverTextColor_clicked()));
	connect(listWidgets, SIGNAL(itemClicked(QListWidgetItem *)),SLOT(lw_itemClicked(QListWidgetItem *)));
	connect(lw_addWidget, SIGNAL(clicked()),SLOT(lw_addWidgetClicked()));
	connect(list_plugin_configure, SIGNAL(clicked()),SLOT(list_plugin_configureClicked()));
	
}
void XQDEConfigurator::list_plugin_configureClicked()
{
	qWarning("void XQDEConfigurator::list_plugin_configureClicked()");
	if(list_plugin->currentItem())
	{
		qWarning("void XQDEConfigurator::list_plugin_configureClicked() running configuration");
		QObject *xci=prr->byName(list_plugin->currentItem()->text());
		if(xci)DesktopEnvironment->UserProfile.configureComponent(xci);
	}
}
void XQDEConfigurator::xReset()
{

	qWarning("void XQDEConfigurator::xReset()");
	bigsize->setValue(DesktopEnvironment->GUI.sizeIconsMax);
	normalsize->setValue(DesktopEnvironment->GUI.sizeIconsNormal);
	
	dockposition->setCurrentIndex(DesktopEnvironment->GUI.dockAlign);
	
	
	dockPositionX->setRange(-QApplication::desktop()->availableGeometry().width(),+QApplication::desktop()->availableGeometry().width());
	dockPositionX->setValue(DesktopEnvironment->GUI.dockAlignDisplaceX);
	
	dockPositionY->setRange(-QApplication::desktop()->availableGeometry().height(),+QApplication::desktop()->availableGeometry().height());
	dockPositionY->setValue(DesktopEnvironment->GUI.dockAlignDisplaceY);
	
	
        listWidgets->clear();
        //ToDo rendere il caricamento dei plugin automatico
        QListWidgetItem *it=new QListWidgetItem("Analog Clock", listWidgets);
        it->setIcon(QIcon(DesktopEnvironment->Theme.findImage("Analog Clock")));
        listWidgets->addItem(it);


	if(prr)
	{
		qWarning("void XQDEConfigurator::xReset() root is ok");
		list_plugin->clear();
		for(int i=0;i<prr->Plugins()->count();i++)
		{
			XQDEClass *xci=(XQDEClass *)prr->Plugins()->at(i);
			qWarning("void XQDEConfigurator::xReset() adding plugin: %s",xci->ObjectName.toUtf8().constData());
			QListWidgetItem *it=new QListWidgetItem(xci->ObjectName, list_plugin);
			list_plugin->addItem(it);
		}
	}
}

void XQDEConfigurator::lw_addWidgetClicked()
{
	qWarning("void XQDEConfigurator::lw_addWidgetClicked()");
	
	QString pt=classNameWidget->text();
	//const char *ptc=pt.toUtf8().constData();
	//qWarning("%s",ptc);
	
	void *ClassWidget=proxy->newInstanceOf(pt);
	if(ClassWidget!=0)
	{
		Basket->AddtoBasketWidget((QObject *) ClassWidget,(void *)0,(class XQDEPlugin *)ClassWidget,pt);
		qWarning("[%ld] added!",(long)ClassWidget);
	}
	else
	{
		qWarning("[%ld] NOT added",(long)ClassWidget);
		}

	
}

void XQDEConfigurator::lw_itemClicked(QListWidgetItem *i)
{
	qWarning("void XQDEConfigurator::lw_itemClicked(QListWidgetItem *i)");
	if(i==NULL)
	{
		classNameWidget->setText("");
	}
	QString plainText = i->text();
	classNameWidget->setText(plainText);

	/*

QMimeData *mimeData = new QMimeData;
mimeData->setText(plainText);
QDrag *drag = new QDrag(this);
drag->setMimeData(mimeData);
drag->start(Qt::CopyAction | Qt::MoveAction);
*/
	
	
	
/*
event->pos() - rect().topLeft()
     Qt::DropAction dropAction = drag->start(Qt::CopyAction | Qt::MoveAction);

     if (dropAction == Qt::MoveAction) {
         close();
         update();
     }
*/

}

void XQDEConfigurator::changeOverTextColor_clicked()
{

QColor color=QColorDialog::getColor (QColor(DesktopEnvironment->GUI.desktopFont.FontRed,DesktopEnvironment->GUI.desktopFont.FontGreen,DesktopEnvironment->GUI.desktopFont.FontBlue), this);

 if (color.isValid()) {
     // the user clicked OK and font is set to the font the user selected

DesktopEnvironment->GUI.desktopFont.FontBlue=color.blue();
DesktopEnvironment->GUI.desktopFont.FontGreen=color.green();
DesktopEnvironment->GUI.desktopFont.FontRed=color.red();

((XQWFirstHand *)MainWindow)->xConfigurationChanged();

 } else {
     // the user canceled the dialog; font is set to the initial
     // value, in this case Helvetica [Cronyx], 10
 }


}
void XQDEConfigurator::changeOverTextFont_clicked()
{
bool ok;
 QFont font = QFontDialog::getFont(
                 &ok, QFont(DesktopEnvironment->GUI.desktopFont.FontFamily, DesktopEnvironment->GUI.desktopFont.FontSize), this);
 if (ok) {
            // the user clicked OK and font is set to the font the user selected
            DesktopEnvironment->GUI.desktopFont.FontFamily=font.family();
            DesktopEnvironment->GUI.desktopFont.FontSize=font.pointSize();

            qWarning("void XQDEConfigurator::changeOverTextFont_clicked() %s(%d)",DesktopEnvironment->GUI.desktopFont.FontFamily.toAscii().data(),DesktopEnvironment->GUI.desktopFont.FontSize);
            ((XQWFirstHand *)MainWindow)->xConfigurationChanged();

 } else {
     // the user canceled the dialog; font is set to the initial
     // value, in this case Helvetica [Cronyx], 10
 }
}



void XQDEConfigurator::dockposition_activated( const QString &newPos)
{
	int StringtoIntPos=0;
	if(newPos=="left")StringtoIntPos=2;
	if(newPos=="top")StringtoIntPos=1;
	if(newPos=="right")StringtoIntPos=3;
	if(DesktopEnvironment->GUI.dockAlign!=StringtoIntPos)
	{
		qWarning("void XQDEConfigurator::dockposition_activated(%d) from %ld",StringtoIntPos,DesktopEnvironment->GUI.dockAlign);
		DesktopEnvironment->GUI.dockAlign=StringtoIntPos;
		dockposition->setCurrentIndex(DesktopEnvironment->GUI.dockAlign);
		((XQWFirstHand *)MainWindow)->xConfigurationChanged();
	}
	dockposition->setCurrentIndex(DesktopEnvironment->GUI.dockAlign);
}

XQDEConfigurator::~XQDEConfigurator()
{
}

void XQDEConfigurator::dockPositionX_valueChanged(int nv)
{
	DesktopEnvironment->GUI.dockAlignDisplaceX=nv;
	((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::dockPositionY_valueChanged(int nv)
{
	DesktopEnvironment->GUI.dockAlignDisplaceY=nv;
	((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}


void XQDEConfigurator::normalsize_valueChanged(int nv)
{
if(nv>DesktopEnvironment->GUI.sizeIconsMax)
{
	normalsize->setValue(DesktopEnvironment->GUI.sizeIconsMax-8);
	return;
}

DesktopEnvironment->GUI.sizeIconsNormal=nv;
DesktopEnvironment->GUI.handIconsMax=0; //this will help to recalculate
((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::bigsize_valueChanged(int nv)
{
if(nv<DesktopEnvironment->GUI.sizeIconsNormal)
{
	bigsize->setValue(DesktopEnvironment->GUI.sizeIconsNormal+8);
	return;
}
DesktopEnvironment->GUI.sizeIconsMax=nv;
DesktopEnvironment->GUI.handIconsMax=0; //this will help to recalculate

((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::accept()
{
}
