//
// C++ Implementation: xqdepuzzle
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "xqdepuzzle.h"
#include <QListWidget>
#include <QIcon>
#include <QVBoxLayout>
#include <QPushButton>


XQDEPuzzle::XQDEPuzzle(QObject *lroot, QWidget *parent)
 :XQWidget(lroot,parent)
{
	//setAutoFillBackground(false);
	//setBackgroundRole(QPalette::NoRole);
	//setAttribute(Qt::WA_NoBackground);
	//move(50,250);
}

void XQDEPuzzle::import(const QString &)
{
	// we load a xml to add standar QT widgets
	QVBoxLayout *layout = new QVBoxLayout;

	QListWidget *v=new QListWidget();


	v->setViewMode(QListView::IconMode);

	XQDEWidgetsManaged.append(v);
	QIcon ic(QPixmap(":images/xqde_logo.png"));
	QString is="ciao";
	QListWidgetItem *i=new QListWidgetItem(ic,is,v);
	v->addItem(i);
	v->setIconSize(QSize(128,128));
	layout->addWidget(v);
	layout->addWidget(new QPushButton("ciao2"));
	setLayout(layout);
}


XQDEPuzzle::~XQDEPuzzle()
{
}


