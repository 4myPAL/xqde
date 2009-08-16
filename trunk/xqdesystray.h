#ifndef XQDESYSTRAY_H
#define XQDESYSTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>

#include "xqdeclass.h"


class XQDESysTray : public QObject
{
public:
    XQDESysTray(XQDEClass *parent = 0);

private:
    void setIcon(QIcon icon);
    void createActions();
    void createTrayIcon();


    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

extern XQDESysTray *SysTray;

#endif // XQDESYSTRAY_H
