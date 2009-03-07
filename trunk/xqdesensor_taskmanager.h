//
// C++ Interface: xqdesensor_taskmanager
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESENSOR_TASKMANAGER_H
#define XQDESENSOR_TASKMANAGER_H

#include "xqdeclass.h"
#include "import_netwm.h"


class QTimer;
class QMenu;
class XQDEIcon;
	
/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDESensor_TaskManager : public XQDEClass,public NETRootInfo4
{
Q_OBJECT
public:
        XQDESensor_TaskManager(XQDEClass *parent = 0);
        ~XQDESensor_TaskManager();
	virtual void xReset();
        void Helper_ActiveOrMinimizeWindow(Window window);
public slots:
        // User Events
	void userAction(int,int,int,void *,XQDEIcon *);
	void setGeometry(void *,int,int,int);
	void slotAddClient();
	void slotupdateStackingOrder();
	void slotupdateThumbnail();
	void fillPopup(QMenu *,XQDEIcon *);
	void triggered(QAction *);
	void triggeredKill(QAction *);
	void slotPollingPID();
        bool x11EventFilter( XEvent *ev );

protected:
	void Helper_RollDown(XQDEIcon *ic);
	void Helper_RollUp(XQDEIcon *ic);
	void updateThisThumbnail(Window);
	//XQDESensor_PidManager *pidManager;
        void updateIcon(XQDEIcon *ip, Window window);
        QTimer *timer_slotAddClient;
        QTimer *timer_slotupdateStackingOrder;
        QTimer *timer_slotupdateThumbnail;
        QTimer *timer_slotPollingPID;
        void postAddClient(Window window);

        virtual void updateStackingOrder();
        virtual void addClient(Window window);
        virtual void removeClient(Window window);
        virtual void addSystemTrayWin(Window window)
        {
                #ifdef ENABLEDEBUGMSG
                        qWarning("addSystemTrayWin");
                #endif
                Q_UNUSED(window);
        }
        virtual void removeSystemTrayWin(Window window) {
                #ifdef ENABLEDEBUGMSG
                qWarning("removeSystemTrayWin");
                #endif
                Q_UNUSED(window);
                }
        virtual void changeNumberOfDesktops(int numberOfDesktops) {
                #ifdef ENABLEDEBUGMSG
                qWarning("changeNumberOfDesktops");
                #endif
                Q_UNUSED(numberOfDesktops); }
        virtual void changeDesktopGeometry(int desktop, const NETSize &geom) {
                #ifdef ENABLEDEBUGMSG
                qWarning("changeDesktopGeometry");
                #endif
                Q_UNUSED(desktop); Q_UNUSED(geom); }
        virtual void changeDesktopViewport(int desktop, const NETPoint &viewport){
                #ifdef ENABLEDEBUGMSG
                qWarning("changeDesktopViewport");
                #endif
                Q_UNUSED(desktop); Q_UNUSED(viewport); }
        virtual void changeCurrentDesktop(int desktop){
                #ifdef ENABLEDEBUGMSG
                qWarning("changeCurrentDesktop");
                #endif
                Q_UNUSED(desktop); }
        virtual void changeActiveWindow(Window window){
                #ifdef ENABLEDEBUGMSG
                qWarning("changeActiveWindow");
                #endif
                Q_UNUSED(window); }
        virtual void closeWindow(Window window){
                #ifdef ENABLEDEBUGMSG
                qWarning("closeWindow");
                #endif
                Q_UNUSED(window);

                }
        virtual void moveResize(Window window, int x_root, int y_root,unsigned long direction) {
                #ifdef ENABLEDEBUGMSG
                qWarning("moveResize");
                #endif
                Q_UNUSED(window); Q_UNUSED(x_root); Q_UNUSED(y_root); Q_UNUSED(direction);
                }

        QList<WId> windows;
        QList<WId> windowsMinimized;
        //QList<WId> stackingOrder;
        //QList<WId> systemTrayWindows;

        Window lastActiveWindow;
        QList<WId> pendingWindows;
        //QList<WId> pollingPIDs;
};

extern XQDESensor_TaskManager *TaskManager;

#endif
