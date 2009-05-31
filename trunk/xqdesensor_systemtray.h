//
// C++ Interface: xqdesensor_systemtray
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDESENSOR_SYSTEMTRAY_H
#define XQDESENSOR_SYSTEMTRAY_H

#include <QX11EmbedContainer>
#include <QHash>
#include <QHBoxLayout>
#include <QString>

#include "xqwidget.h"
#include "import_netwm.h"



class QVBoxLayout;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDESensor_SystemTray : public XQWidget
{
//Q_OBJECT
//public:
//	void xRepaint();
//	virtual void xReset();
//	XQDESensor_SystemTray(QObject *parent = 0);
//	~XQDESensor_SystemTray();
//protected:
//	QVBoxLayout *vContainer;
//	Atom net_system_tray_selection;
//	Atom net_system_tray_opcode;
//	bool x11Event( XEvent *e );
//	bool isWinManaged(WId w);
//	void embedWindow( WId w, bool kde_tray );
//	void emb( WId w);
//	void layoutTray();
//	QList<Window >managed_trayWindows;
//};

    Q_OBJECT

public:
    XQDESensor_SystemTray(QWidget *parent=0);
    ~XQDESensor_SystemTray();
    void add_sysicon(Window);
    void add_embed(Window);
//    void remove_sysicon(Window);
    void remove_embedder(Window);

public slots:
//    void remove_sysicon(Sysicon *);

protected:
    virtual bool x11Event (XEvent *);

private:
//    QHash<int, Sysicon *> sys_icons; // mapping frame id with Sysicon (key=frame_win_id, value=Sysicon)
    QHash<int, QX11EmbedContainer *> sys_embed; // mapping Client win_id with QX11EmbedContainer
                                                // (key=client id, value=Container)
    QString sys_pix;
    // System tray properties
    Atom kde_systray_prop;
    Atom net_opcode_atom;
    Atom net_selection_atom;
    Atom net_manager_atom;
    Atom net_message_data_atom;
    QHBoxLayout *layout;
//    Sysicon *s_icon;
    QX11EmbedContainer *emb_cont;
};

#endif
