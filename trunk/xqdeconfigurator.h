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
#include <QStringListModel>

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

    void icon_path_add_clicked();
    void icon_path_remove_clicked();
    void icon_path_up_clicked();
    void icon_path_down_clicked();

    void background_theme_activated(int);
    void space_valueChanged(int);

    void ani_new_activated(int);
    void ani_remove_activated(int);
    void ani_lanch_activated(int);

protected:
    class XQDERoot *prr;
    QStringListModel *IconPathListmodel;
};

extern QWidget *GlobalConfigurator;

#endif
