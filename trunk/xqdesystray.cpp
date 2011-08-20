#include <QtGui>
#include "xqdesystray.h"
#include "xqde.h"

XQDESysTray *SysTray;

XQDESysTray::XQDESysTray(XQDEClass *parent)
    : XQDEClass(parent)
{
    ObjectName="com.XQDE.SysTray";
    ConfigurationData.append(new XQDEConfigurationPair("serverurl",""));
    ConfigurationData.append(new XQDEConfigurationPair("email",""));
    ConfigurationData.append(new XQDEConfigurationPair("author","AlmAck"));
    ConfigurationData.append(new XQDEConfigurationPair("web",""));
    ConfigurationData.append(new XQDEConfigurationPair("version","20091225"));
    ConfigurationData.append(new XQDEConfigurationPair("autoupdate",""));

    createActions();
    createTrayIcon();

    setIcon(QIcon(":/images/xqde_logo.png"));
    trayIcon->show();

}

void XQDESysTray::setIcon(QIcon icon)
{
    trayIcon->setIcon(icon);
}

void XQDESysTray::createActions()
{
//    minimizeAction = new QAction(tr("Mi&nimize"), this);
//    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
//
//    maximizeAction = new QAction(tr("Ma&ximize"), this);
//    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
//
//    restoreAction = new QAction(tr("&Restore"), this);
//    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void XQDESysTray::createTrayIcon()
{
    trayIconMenu = new QMenu();
//    trayIconMenu->addAction(minimizeAction);
//    trayIconMenu->addAction(maximizeAction);
//    trayIconMenu->addAction(restoreAction);
//    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
//
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
