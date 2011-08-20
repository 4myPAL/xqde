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

#include <QFontDialog>
#include <QColorDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QDrag>
#include <QMimeData>
#include <QDesktopWidget>
//#include <QStringListModel>
#include <QFileDialog>

#include "xqdeproxy.h"
#include "xqdebasket.h"
#include "xqderoot.h"
#include "xqdeconfigurator.h"
#include "xqdeenvironment.h"
#include "xqwfirsthand.h"
#include "xqdeanimation.h"

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

	//Design panel
	connect(bigsize, SIGNAL(valueChanged(int)),SLOT(bigsize_valueChanged(int)));
	connect(normalsize, SIGNAL(valueChanged(int)),SLOT(normalsize_valueChanged(int)));
	connect(dockposition, SIGNAL(activated( const QString &)),SLOT(dockposition_activated( const QString &)));
	connect(dockPositionX, SIGNAL(valueChanged(int)),SLOT(dockPositionX_valueChanged(int)));
	connect(dockPositionY, SIGNAL(valueChanged(int)),SLOT(dockPositionY_valueChanged(int)));	
	connect(changeOverTextFont, SIGNAL(clicked()),SLOT(changeOverTextFont_clicked()));
	connect(changeOverTextColor, SIGNAL(clicked()),SLOT(changeOverTextColor_clicked()));
	connect(space, SIGNAL(valueChanged(int)),SLOT(space_valueChanged(int)));

	//Theme panel
	//IconPathsListView
	connect(icon_path_add, SIGNAL(clicked()),SLOT(icon_path_add_clicked()));
	connect(icon_path_remove, SIGNAL(clicked()),SLOT(icon_path_remove_clicked()));
	connect(icon_path_up, SIGNAL(clicked()),SLOT(icon_path_up_clicked()));
	connect(icon_path_down, SIGNAL(clicked()),SLOT(icon_path_down_clicked()));

	//Animations
	connect(ani_new, SIGNAL(activated(int)),SLOT(ani_new_activated(int)));
	connect(ani_remove, SIGNAL(activated(int)),SLOT(ani_remove_activated(int)));
	connect(ani_lanch, SIGNAL(activated(int)),SLOT(ani_lanch_activated(int)));

	//background
	connect(background_theme, SIGNAL(activated(int)),SLOT(background_theme_activated(int)));

	connect(listWidgets, SIGNAL(itemClicked(QListWidgetItem *)),SLOT(lw_itemClicked(QListWidgetItem *)));
	connect(lw_addWidget, SIGNAL(clicked()),SLOT(lw_addWidgetClicked()));
	connect(list_plugin_configure, SIGNAL(clicked()),SLOT(list_plugin_configureClicked()));
}

XQDEConfigurator::~XQDEConfigurator()
{
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
	space->setValue(DesktopEnvironment->GUI.spaceIcons);
	
	dockposition->setCurrentIndex(DesktopEnvironment->GUI.dockAlign);
	
	
	dockPositionX->setRange(-QApplication::desktop()->availableGeometry().width(),+QApplication::desktop()->availableGeometry().width());
	dockPositionX->setValue(DesktopEnvironment->GUI.dockAlignDisplaceX);
	
	dockPositionY->setRange(-QApplication::desktop()->availableGeometry().height(),+QApplication::desktop()->availableGeometry().height());
	dockPositionY->setValue(DesktopEnvironment->GUI.dockAlignDisplaceY);
	
	
        listWidgets->clear();
        //ToDo rendere il caricamento dei plugin automatico
	QListWidgetItem *it=new QListWidgetItem("Analog_Clock", listWidgets);
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

	//Find Themes Name and populate the list
	background_theme->addItems(DesktopEnvironment->Theme.findThemesName());
//	background_theme->setCurrentIndex(DesktopEnvironment->Theme.Theme);

	//Prepare model for IconPathList
	IconPathListmodel = new QStringListModel();
	IconPathListmodel->setStringList(*DesktopEnvironment->Theme.IconsPaths);

	IconPathList->setModel(IconPathListmodel);
	IconPathList->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

	//Find Animations Types and populate the list and select item
	ani_new->addItems(((XQDEAnimation *)MainWindow)->getAnimationTypes());
	ani_new->setCurrentIndex(DesktopEnvironment->UserProfile.animation_new-1);
	ani_remove->addItems(((XQDEAnimation *)MainWindow)->getAnimationTypes());
	ani_remove->setCurrentIndex(DesktopEnvironment->UserProfile.animation_remove-1);
	ani_lanch->addItems(((XQDEAnimation *)MainWindow)->getAnimationTypes());
	ani_lanch->setCurrentIndex(DesktopEnvironment->UserProfile.animation_lanch-1);

	//ToDo implemten other dock effects
	ani_dock->addItem("parabolic");

}

void XQDEConfigurator::lw_addWidgetClicked()
{
	qWarning("void XQDEConfigurator::lw_addWidgetClicked()");
	
	QString pt=classNameWidget->text();
	//const char *ptc=pt.toUtf8().constData();
	//qWarning("%s",ptc);
	
//	foreach(XQDEPlugin *widget, XQDEMain::widgets);


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
	qWarning("void XQDEConfigurator::lw_itemClicked(QListWidgetItem *i)");
	if(i==NULL)
	{
		classNameWidget->setText("");
	}
	QString plainText = i->text();
	classNameWidget->setText(plainText);


//
//QMimeData *mimeData = new QMimeData;
//mimeData->setText(plainText);
//QDrag *drag = new QDrag(this);
//drag->setMimeData(mimeData);
//drag->start(Qt::CopyAction | Qt::MoveAction);
//
//


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

     }
     else {
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

     }
    else {
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

void XQDEConfigurator::background_theme_activated(int nv)
{
    qDebug("theme changed now is: %s", background_theme->itemText(nv).toAscii().data());

    DesktopEnvironment->Theme.Theme = background_theme->itemText(nv).toAscii().data();

    //reload all images from theme
    DesktopEnvironment->Theme.xReset();
    //overiite existing image template with the new one
    ((XQWFirstHand *)MainWindow)->xReset();
    //Repaint all dock and save changes on xml file
    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::space_valueChanged(int nv)
{
	DesktopEnvironment->GUI.spaceIcons=nv;
	((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::icon_path_add_clicked ()
{
    int row = IconPathListmodel->rowCount(); //last row

    QString directory = QFileDialog::getExistingDirectory(this,
				    tr("Find Icon Path"), QDir::currentPath());

    if (!directory.isEmpty()) {
	IconPathListmodel->insertRows(row,1);
	QModelIndex index = IconPathListmodel->index(row);
	IconPathListmodel->setData(index, directory);

	IconPathList->setCurrentIndex(index);

	DesktopEnvironment->Theme.IconsPaths->append(directory);

	((XQWFirstHand *)MainWindow)->xConfigurationChanged();
	}
}

void XQDEConfigurator::icon_path_remove_clicked ()
{
    int row = IconPathList->currentIndex().row();
    if (row < 0) return;
    IconPathListmodel->removeRows(IconPathList->currentIndex().row(),1);

    DesktopEnvironment->Theme.IconsPaths->removeAt(IconPathList->currentIndex().row()+1);

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::icon_path_up_clicked ()
{
    int row = IconPathList->currentIndex().row();
    if(row == 0) return;
    QVariant dataBefore = IconPathListmodel->data(IconPathList->currentIndex().sibling(row-1,0),0);
    QVariant dataAfter = IconPathListmodel->data(IconPathList->currentIndex().sibling(row,0),0);
    IconPathListmodel->setData(IconPathList->currentIndex().sibling(row-1,0), dataAfter);
    IconPathListmodel->setData(IconPathList->currentIndex().sibling(row,0), dataBefore);

    IconPathList->currentIndex().sibling(row-1,0);
    IconPathList->setCurrentIndex(IconPathListmodel->index(row-1));

    DesktopEnvironment->Theme.IconsPaths->clear();
    for(int i=0; i < IconPathListmodel->rowCount(); i++)
	DesktopEnvironment->Theme.IconsPaths->append(IconPathListmodel->data(IconPathList->currentIndex().sibling(i,0),0).toString().toAscii());

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::icon_path_down_clicked ()
{
    int row = IconPathList->currentIndex().row();
    if(row >= IconPathListmodel->rowCount()-1) return;
    QVariant dataBefore = IconPathListmodel->data(IconPathList->currentIndex().sibling(row+1,0),0);
    QVariant dataAfter = IconPathListmodel->data(IconPathList->currentIndex().sibling(row,0),0);
    IconPathListmodel->setData(IconPathList->currentIndex().sibling(row+1,0), dataAfter);
    IconPathListmodel->setData(IconPathList->currentIndex().sibling(row,0), dataBefore);

    IconPathList->currentIndex().sibling(row+1,0);
    IconPathList->setCurrentIndex(IconPathListmodel->index(row+1));

    DesktopEnvironment->Theme.IconsPaths->clear();
    for(int i=0; i < IconPathListmodel->rowCount(); i++)
	DesktopEnvironment->Theme.IconsPaths->append(IconPathListmodel->data(IconPathList->currentIndex().sibling(i,0),0).toString().toAscii());

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::ani_new_activated(int nv){

    DesktopEnvironment->UserProfile.animation_new = nv;

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::ani_remove_activated(int nv){

    DesktopEnvironment->UserProfile.animation_remove = nv+1;

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}

void XQDEConfigurator::ani_lanch_activated(int nv){

    DesktopEnvironment->UserProfile.animation_lanch = nv+1;

    ((XQWFirstHand *)MainWindow)->xConfigurationChanged();
}
