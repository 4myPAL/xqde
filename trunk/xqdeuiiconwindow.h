//
// C++ Interface: $MODULE$
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEUIICONWINDOW_H
#define XQDEUIICONWINDOW_H
#include <QDialog>

#include "ui_XQDEUIIcon.h"

class XQDEUIIconWindow: public QDialog, Ui::XQDEUIIcon
{
Q_OBJECT
public:
    XQDEUIIconWindow();
    ~XQDEUIIconWindow();
void setObject(class XQDEIcon *me);
void accept();
	
protected:
	class XQDEIcon *localme;
public slots:
	void addClicked();
	void delClicked();
	void SaveAsTemplate();
};

#endif
/*

#include "ui_form.h"

class FormImpl : public Form
{
  Q_OBJECT

public:
  FormImpl() : QDialog()
  {
    setupUi( this );

    connect( pbAdd, SIGNAL(clicked()), this, SLOT(addClicked()) );
  }

private slots:
  void addClicked();
};
*/
