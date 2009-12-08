//
// C++ Interface: xqdeconfigurator
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDECONFIGURATOR_H
#define XQDECONFIGURATOR_H

#include <QDialog>

#include "ui_XQDEUIConfigurator.h"

class XQDEConfigurator: public QDialog, Ui::XQDEUIConfigurator
{
    Q_OBJECT
public:
    XQDEConfigurator(class XQDERoot *pr);
    void accept();
    ~XQDEConfigurator();

public slots:
    void xReset();
    void bigsize_valueChanged(int);
    void normalsize_valueChanged(int);
    void dockposition_activated( const QString &);
    void changeOverTextColor_clicked();
    void changeOverTextFont_clicked();
    void lw_itemClicked(QListWidgetItem *);
    void lw_addWidgetClicked();
    void dockPositionX_valueChanged(int);
    void dockPositionY_valueChanged(int);
    void list_plugin_configureClicked();

    void background_theme_activated(int);


protected:
    class XQDERoot *prr;
};

extern QWidget *GlobalConfigurator;

#endif
