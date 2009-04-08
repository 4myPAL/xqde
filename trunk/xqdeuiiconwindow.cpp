//
// C++ Implementation: $MODULE$
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVariant>

#include "xqdebasket.h"
#include "xqdeuiiconwindow.h"
#include "xqdeicon.h"
#include "xqdeaction.h"

XQDEUIIconWindow::XQDEUIIconWindow()
    : QDialog()
{
	setupUi( this );
        //connect( pbAdd, SIGNAL(clicked()), this, SLOT(addClicked()) );
        connect( addsl, SIGNAL(clicked()), this, SLOT(addClicked()) );
        connect( delsl, SIGNAL(clicked()), this, SLOT(delClicked()) );
        connect( bSaveAsTemplate, SIGNAL(clicked()), this, SLOT(SaveAsTemplate()) );
}

XQDEUIIconWindow::~XQDEUIIconWindow()
{
}

void XQDEUIIconWindow::SaveAsTemplate()
{
}
void XQDEUIIconWindow::accept()
{
	if(Basket->items.indexOf(localme)<0)return;
	// apply new configuration to icon...
	localme->setLogic(uniquename->text());
	if(keepindock->checkState())localme->storeOnExit=1;
	else localme->storeOnExit=0;
	if(enablepreview->checkState())localme->enablePreview=1;
	else localme->enablePreview=0;
	if(groupwindows->checkState())localme->groupWindows=1;
	else localme->groupWindows=0;


	XQDEAction *ac=localme->actions->value("XQDE_USER_ACTION_CLICKSX");
	ac->Action=useractionclicksx->text();
	localme->xSetIcon( defaulticon->text());
	localme->slotsSensor->clear();

	for(int i=0;i<slotsSensor->count();i++)
	{
		XQDESlotSensor *as=new XQDESlotSensor;
		as->Slot=slotsSensor->item(i)->text();
		localme->slotsSensor->append(as);

	}
	localme->xReset();
	Basket->FreezeSave("");
	QDialog::accept();
}

void XQDEUIIconWindow::addClicked()
{
	if(sl->text().length()>1)
	{
		slotsSensor->insertItem(0,sl->text());
	}
}

void XQDEUIIconWindow::delClicked()
{
	if(slotsSensor->currentRow()>=0)slotsSensor->takeItem(slotsSensor->currentRow());
}

void XQDEUIIconWindow::setObject(XQDEIcon *me)
{
	localme=me;
	uniquename->setText(me->logic());
	if(me->storeOnExit)keepindock->setChecked(true);
	else keepindock->setChecked(false);
	if(me->enablePreview)enablepreview->setChecked(true);
	else enablepreview->setChecked(false);
	if(me->groupWindows)groupwindows->setChecked(true);
	else groupwindows->setChecked(false);

	useractionclicksx->setText(me->actions->value("XQDE_USER_ACTION_CLICKSX")->Action);
	defaulticon->setText(me->icon());
	slotsSensor->clear();
	slotsSensor->insertItems(0,me->slotsSensorList());
}


