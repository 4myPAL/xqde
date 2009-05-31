////
//// C++ Implementation: xqdesensor_systemtray
////
//// Description:
////
////
//// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2006
////
//// Copyright: See COPYING file that comes with this distribution
////
////
//
//
#include <QByteArray>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QX11EmbedWidget>
#include <QX11EmbedContainer>
#include <QDesktopWidget>
#include <QApplication>

#include "xqdesensor_systemtray.h"
#include "import_netwm.h"
//
//
//#include <xqdesensor_taskmanager.h>
//
//
////XQWidget *contenitore;
////int slitta;
//XQDESensor_SystemTray::XQDESensor_SystemTray(QObject *parent)
// : XQWidget(parent,NULL)
//{
///*
//	contenitore=new XQWidget(NULL,NULL);
//	contenitore->setRect(50,50,320+50,50+64);
//	contenitore->show();
//	slitta=0;
//*/
//	vContainer=new QVBoxLayout(this);
//
//        vContainer->addWidget(new QPushButton("ciao"));
//        setLayout(vContainer);
//}
//
//
//XQDESensor_SystemTray::~XQDESensor_SystemTray()
//{
//    if(vContainer) delete vContainer;
//}
//
//
//void XQDESensor_SystemTray::xReset()
//{
//    // register existing tray windows
//	/*
//    const QValueList<WId> systemTrayWindows = kwin_module->systemTrayWindows();
//    bool existing = false;
//    for (QValueList<WId>::ConstIterator it = systemTrayWindows.begin();
//         it != systemTrayWindows.end(); ++it )
//    {
//        embedWindow(*it, true);
//        existing = true;
//    }
//
//    if (existing)
//    {
//        updateVisibleWins();
//        layoutTray();
//    }
//*/
//
//    // the KWinModule notifies us when tray windows are added or removed
///*
//    connect( kwin_module, SIGNAL( systemTrayWindowAdded(WId) ),
//             this, SLOT( systemTrayWindowAdded(WId) ) );
//    connect( kwin_module, SIGNAL( systemTrayWindowRemoved(WId) ),
//             this, SLOT( updateTrayWindows() ) );
//*/
//    QByteArray screenstr;
//    screenstr.setNum(qt_xscreen());
//    QByteArray trayatom = "_NET_SYSTEM_TRAY_S" + screenstr;
//
//    Display *display = qt_xdisplay();
//
//    net_system_tray_selection = XInternAtom(display, trayatom, false);
//    net_system_tray_opcode = XInternAtom(display, "_NET_SYSTEM_TRAY_OPCODE", false);
//
//    // Acquire system tray
//    XSetSelectionOwner(display,
//                       net_system_tray_selection,
//                       winId(),
//                       CurrentTime);
//
//    WId root = qt_xrootwin();
//
//    if (XGetSelectionOwner (display, net_system_tray_selection) == winId())
//    {
//        XClientMessageEvent xev;
//
//        xev.type = ClientMessage;
//        xev.window = root;
//
//        xev.message_type = XInternAtom (display, "MANAGER", False);
//        xev.format = 32;
//        xev.data.l[0] = CurrentTime;
//        xev.data.l[1] = net_system_tray_selection;
//        xev.data.l[2] = winId();
//        xev.data.l[3] = 0;
//        xev.data.l[4] = 0;
//
//        XSendEvent (display, root, False, StructureNotifyMask, (XEvent *)&xev);
//        qWarning("SystemTray installed!");
//    }
//}
//
//
//void XQDESensor_SystemTray::xRepaint()
//{
//	// TODO:full repaint?
//	//paintBuffer.fill(0x00000000);
//        //qWarning("XQDESensor_SystemTray::xRepaint()");
////	paintBuffer.fill(0x80000000+(unsigned int)winId());
//
//        widgetpaint->begin(&paintBuffer);
//	{
//		//
//		//p.drawImage(0,0,);
//		//
//	}
//        widgetpaint->end();
//}
//
//bool XQDESensor_SystemTray::x11Event( XEvent *e )
//{
//#define SYSTEM_TRAY_REQUEST_DOCK    0
//#define SYSTEM_TRAY_BEGIN_MESSAGE   1
//#define SYSTEM_TRAY_CANCEL_MESSAGE  2
//    if ( e->type == ClientMessage ) {
//        if ( e->xclient.message_type == net_system_tray_opcode &&
//             e->xclient.data.l[1] == SYSTEM_TRAY_REQUEST_DOCK) {
//            //if( isWinManaged( (WId)e->xclient.data.l[2] ) ) // we already manage it
//                //return true;
//           embedWindow( e->xclient.data.l[2], false );
//            return true;
//        }
//    }
//    return XQWidget::x11Event( e ) ;
//}
//
//bool XQDESensor_SystemTray::isWinManaged(WId )
//{
//	return false;
//}
//
//void XQDESensor_SystemTray::layoutTray()
//{
//}
///*
//static int get_parent(WId winid, Window *out_parent)
//{
//    Window root, *children=0;
//    unsigned int nchildren;
//    int st = XQueryTree(qt_xdisplay(), winid, &root, out_parent, &children, &nchildren);
//    if (st && children)
//        XFree(children);
//    return st;
//}
//*/
//void withdrawWindow( Window w )
//    {
//    XWithdrawWindow( qt_xdisplay(), w, qt_xscreen());
//    static Atom wm_state = XInternAtom( qt_xdisplay(), "WM_STATE", False );
//    for(;;)
//        {
//        Atom type;
//        int format;
//        unsigned long length, after;
//        unsigned char *data;
//        int r = XGetWindowProperty( qt_xdisplay(), w, wm_state, 0, 2,
//            False, AnyPropertyType, &type, &format,
//            &length, &after, &data );
//        bool withdrawn = true;
//        if ( r == Success && data && format == 32 )
//            {
//            withdrawn = ( *( long* )data == WithdrawnState );
//            XFree( (char *)data );
//            }
//        if( withdrawn )
//            return; // --->
//        struct timeval tm;
//        tm.tv_sec = 0;
//        tm.tv_usec = 10 * 1000; // 10ms
//        select(0, NULL, NULL, NULL, &tm);
//        }
//    }
//
//void XQDESensor_SystemTray::emb( WId )
//{
//
//}
//
//
//void NoDecor(WId win)
//{
//    Atom AtomWinAttr = XInternAtom(qt_xdisplay(), "_OL_WIN_ATTR" ,    FALSE);
//    Atom AtomDecor   = XInternAtom(qt_xdisplay(), "_OL_DECOR_ADD",    FALSE);
//    Atom   winAttrs[2];
//    Atom   winDecor[3];
//    int numberOfDecorations = 0;
//
//    XChangeProperty(qt_xdisplay(),
//    win,
//    AtomWinAttr,
//    XA_ATOM,
//    32,
//    PropModeReplace,
//    (unsigned char*)winAttrs,
//    1);
//
//    /*
//    ** Tell Open Look to add some decorations to our window
//    */
//    XChangeProperty(qt_xdisplay(),
//    win,
//    AtomDecor,
//    XA_ATOM,
//    32,
//    PropModeReplace,
//    (unsigned char*)winDecor,
//    numberOfDecorations);
//}
//
//#include <qxembed.h>
//void XQDESensor_SystemTray::embedWindow( WId w, bool  )
//{
//	//qWarning("XQDESensor_SystemTray::embedWindow()");
//
//	if(managed_trayWindows.indexOf(w)>=0)
//	{
//		//qWarning("already mapped: %d",(int)w);
//		return;
//	}
////        managed_trayWindows.append(w);
////        static Atom hack_atom = XInternAtom( qt_xdisplay(), "_KDE_SYSTEM_TRAY_EMBEDDING", False );
////        XChangeProperty( qt_xdisplay(), w, hack_atom, hack_atom, 32, PropModeReplace, NULL, 0 );
////        QXEmbed *emb=new QXEmbed(this,"prova");
////        emb->embed(w);
//
////	withdrawWindow( w );
////	//usleep(10000000);
////	QX11EmbedContainer *emb=new QX11EmbedContainer(this);
////	vContainer->addWidget(emb);
////	emb->show();
////	XSync(qt_xdisplay(), False);
////
////	XReparentWindow(qt_xdisplay(), w, winId(), 0, 0);
////
////	//emb->embedInto(w);
////	emb->embedClient ( w);
//
//	static int x=32;
//        static int y=64;
//
////        NETRootInfo rootinfo( qt_xdisplay(), NET::WM2MoveResizeWindow); //NET::WMMoveResize);
////
////        rootinfo.moveResizeWindowRequest(w, NET::TopLeft | 1<<8 |1<<9, x, y-=32, 32, 32);
//
//        NETWinInfo info(qt_xdisplay(), w, qt_xrootwin(),NET::WMState);
//
////        info.setState( NET::Override | NET::StaysOnTop | NET::KeepAbove | NET::SkipTaskbar | NET::SkipPager , NET::Override | NET::StaysOnTop | NET::KeepAbove | NET::SkipTaskbar | NET::SkipPager );
//        info.setDesktop( NETWinInfo::OnAllDesktops);
////        NoDecor(w);
//        XMapWindow(qt_xdisplay(), w);
//	//
//        //XDeleteProperty(qt_xdisplay(), w, hack_atom );
//
//        QX11EmbedContainer *emb=new QX11EmbedContainer(this);
//        emb->show();
//        XSync(qt_xdisplay(), False);
//
//        XReparentWindow(qt_xdisplay(), w, winId(), 0, 0);
//        emb->embedClient ( w);
//        vContainer->addWidget(emb);
//
//        vContainer->addWidget(new QPushButton("icon above?!!"));
//
////        QPixmap icon = thumbnail(w,20)
//
//	update();
////        (01.03.09) udate and repaint to the same thing
////        repaint();
//}
//#ifdef pippo
//
//
//SystemTrayApplet::~SystemTrayApplet()
//{
//    for (TrayEmbedList::const_iterator it = m_hiddenWins.constBegin();
//         it != m_hiddenWins.constEnd();
//         ++it)
//    {
//        delete *it;
//    }
//
//    for (TrayEmbedList::const_iterator it = m_shownWins.constBegin();
//         it != m_shownWins.constEnd();
//         ++it)
//    {
//        delete *it;
//    }
//
//    KGlobal::locale()->removeCatalogue("ksystemtrayapplet");
//}
//
//
//
//void SystemTrayApplet::systemTrayWindowAdded( WId w )
//{
//    if (isWinManaged(w))
//    {
//        // we already manage it
//        return;
//    }
//
//    embedWindow(w, true);
//    updateVisibleWins();
//    layoutTray();
//
//    if (m_showFrame && frameStyle() == NoFrame)
//    {
//        setFrameStyle(Panel|Sunken);
//    }
//}
//
//
//bool SystemTrayApplet::isWinManaged(WId w)
//{
//    TrayEmbedList::const_iterator lastEmb = m_shownWins.end();
//    for (TrayEmbedList::const_iterator emb = m_shownWins.begin(); emb != lastEmb; ++emb)
//    {
//        if ((*emb)->embeddedWinId() == w) // we already manage it
//        {
//            return true;
//        }
//    }
//
//    lastEmb = m_hiddenWins.end();
//    for (TrayEmbedList::const_iterator emb = m_hiddenWins.begin(); emb != lastEmb; ++emb)
//    {
//        if ((*emb)->embeddedWinId() == w) // we already manage it
//        {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//
//
//
//void SystemTrayApplet::updateTrayWindows()
//{
//    TrayEmbedList::iterator emb = m_shownWins.begin();
//    while (emb != m_shownWins.end())
//    {
//        WId wid = (*emb)->embeddedWinId();
//        if ((wid == 0) ||
//            ((*emb)->kdeTray() &&
//             !kwin_module->systemTrayWindows().contains(wid)))
//        {
//            (*emb)->deleteLater();
//            emb = m_shownWins.erase(emb);
//        }
//        else
//        {
//            ++emb;
//        }
//    }
//
//    emb = m_hiddenWins.begin();
//    while (emb != m_hiddenWins.end())
//    {
//        WId wid = (*emb)->embeddedWinId();
//        if ((wid == 0) ||
//            ((*emb)->kdeTray() &&
//             !kwin_module->systemTrayWindows().contains(wid)))
//        {
//            (*emb)->deleteLater();
//            emb = m_hiddenWins.erase(emb);
//        }
//        else
//        {
//            ++emb;
//        }
//    }
//
//    showExpandButton(!m_hiddenWins.isEmpty());
//    updateVisibleWins();
//    layoutTray();
//}
//
//int SystemTrayApplet::maxIconWidth() const
//{
//    int largest = m_iconSize;
//
//    TrayEmbedList::const_iterator lastEmb = m_shownWins.end();
//    for (TrayEmbedList::const_iterator emb = m_shownWins.begin(); emb != lastEmb; ++emb)
//    {
//        if (*emb == 0)
//        {
//            continue;
//        }
//
//        int width = (*emb)->width();
//        if (width > largest)
//        {
//            largest = width;
//        }
//    }
//
//    if (m_showHidden)
//    {
//        lastEmb = m_hiddenWins.end();
//        for (TrayEmbedList::const_iterator emb = m_hiddenWins.begin(); emb != lastEmb; ++emb)
//        {
//            int width = (*emb)->width();
//            if (width > largest)
//            {
//                largest = width;
//            }
//        }
//    }
//
//    return largest;
//}
//
//int SystemTrayApplet::maxIconHeight() const
//{
//    int largest = m_iconSize;
//
//    TrayEmbedList::const_iterator lastEmb = m_shownWins.end();
//    for (TrayEmbedList::const_iterator emb = m_shownWins.begin(); emb != m_shownWins.end(); ++emb)
//    {
//        if (*emb == 0)
//        {
//            continue;
//        }
//
//        int height = (*emb)->height();
//        if (height > largest)
//        {
//            largest = height;
//        }
//    }
//
//    if (m_showHidden)
//    {
//        lastEmb = m_hiddenWins.end();
//        for (TrayEmbedList::const_iterator emb = m_hiddenWins.begin(); emb != m_hiddenWins.end(); ++emb)
//        {
//            if (*emb == 0)
//            {
//                continue;
//            }
//
//            int height = (*emb)->height();
//            if (height > largest)
//            {
//                largest = height;
//            }
//        }
//    }
//
//    return largest;
//}
//
//bool SystemTrayApplet::eventFilter(QObject* watched, QEvent* e)
//{
//    if (watched == m_expandButton)
//    {
//        QPoint p;
//        if (e->type() == QEvent::ContextMenu)
//        {
//            p = static_cast<QContextMenuEvent*>(e)->globalPos();
//        }
//        else if (e->type() == QEvent::MouseButtonPress)
//        {
//            QMouseEvent* me = static_cast<QMouseEvent*>(e);
//            if (me->button() == Qt::RightButton)
//            {
//                p = me->globalPos();
//            }
//        }
//
//        if (!p.isNull())
//        {
//            QPopupMenu* contextMenu = new QPopupMenu(this);
//            contextMenu->insertItem(SmallIcon("configure"), i18n("Configure System Tray..."),
//                                    this, SLOT(configure()));
//
//            contextMenu->exec(static_cast<QContextMenuEvent*>(e)->globalPos());
//
//            delete contextMenu;
//            return true;
//        }
//    }
//
//    return false;
//}
//
//
//
//void SystemTrayApplet::layoutTray()
//{
//    setUpdatesEnabled(false);
//
//    int iconCount = m_shownWins.count();
//
//    if (m_showHidden)
//    {
//        iconCount += m_hiddenWins.count();
//    }
//
//    /* heightWidth = height or width in pixels (depends on orientation())
//     * nbrOfLines = number of rows or cols (depends on orientation())
//     * line = what line to draw an icon in */
//    int i = 0, line, nbrOfLines, heightWidth;
//    bool showExpandButton = m_expandButton && m_expandButton->isVisibleTo(this);
//    delete m_layout;
//    m_layout = new QGridLayout(this, 1, 1, 2, 2);
//
//    // col = column or row, depends on orientation(),
//    // the opposite direction of line
//    int col = 0;
//
//    if (orientation() == Vertical)
//    {
//        int iconWidth = maxIconWidth() + 2; // +2 for the margins that implied by the layout
//        heightWidth = width();
//        // to avoid nbrOfLines=0 we ensure heightWidth >= iconWidth!
//        heightWidth = heightWidth < iconWidth ? iconWidth : heightWidth;
//        nbrOfLines = heightWidth / iconWidth;
//
//        if (showExpandButton)
//        {
//            m_layout->addMultiCellWidget(m_expandButton,
//                                         col, col,
//                                         0, nbrOfLines,
//                                         Qt::AlignHCenter | Qt::AlignVCenter);
//            ++col;
//        }
//
//        if (m_showHidden)
//        {
//            TrayEmbedList::const_iterator lastEmb = m_hiddenWins.end();
//            for (TrayEmbedList::const_iterator emb = m_hiddenWins.begin();
//                 emb != lastEmb; ++emb)
//            {
//                line = i % nbrOfLines;
//                (*emb)->hide();
//                (*emb)->show();
//                m_layout->addWidget(*emb, col, line,
//                                    Qt::AlignHCenter | Qt::AlignVCenter);
//
//                if (line + 1 == nbrOfLines)
//                {
//                    ++col;
//                }
//
//                ++i;
//            }
//        }
//
//        TrayEmbedList::const_iterator lastEmb = m_shownWins.end();
//        for (TrayEmbedList::const_iterator emb = m_shownWins.begin();
//             emb != lastEmb; ++emb)
//        {
//            line = i % nbrOfLines;
//            (*emb)->hide();
//            (*emb)->show();
//            m_layout->addWidget(*emb, col, line,
//                                Qt::AlignHCenter | Qt::AlignVCenter);
//
//            if (line + 1 == nbrOfLines)
//            {
//                ++col;
//            }
//
//            ++i;
//        }
//    }
//    else // horizontal
//    {
//        int iconHeight = maxIconHeight() + 2; // +2 for the margins that implied by the layout
//        heightWidth = height();
//        heightWidth = heightWidth < iconHeight ? iconHeight : heightWidth; // to avoid nbrOfLines=0
//        nbrOfLines = heightWidth / iconHeight;
//
//        if (showExpandButton)
//        {
//            m_layout->addMultiCellWidget(m_expandButton,
//                                         0, nbrOfLines - 1,
//                                         0, 0,
//                                         Qt::AlignHCenter | Qt::AlignVCenter);
//            col = 1;
//        }
//
//        if (m_showHidden)
//        {
//            TrayEmbedList::const_iterator lastEmb = m_hiddenWins.end();
//            for (TrayEmbedList::const_iterator emb = m_hiddenWins.begin(); emb != lastEmb; ++emb)
//            {
//                line = i % nbrOfLines;
//                (*emb)->hide();
//                (*emb)->show();
//                m_layout->addWidget(*emb, line, col,
//                                    Qt::AlignHCenter | Qt::AlignVCenter);
//
//                if (line + 1 == nbrOfLines)
//                {
//                    ++col;
//                }
//
//                ++i;
//            }
//        }
//
//        TrayEmbedList::const_iterator lastEmb = m_shownWins.end();
//        for (TrayEmbedList::const_iterator emb = m_shownWins.begin();
//             emb != lastEmb; ++emb)
//        {
//            line = i % nbrOfLines;
//            (*emb)->hide();
//            (*emb)->show();
//            m_layout->addWidget(*emb, line, col,
//                                Qt::AlignHCenter | Qt::AlignVCenter);
//
//            if (line + 1 == nbrOfLines)
//            {
//                ++col;
//            }
//
//            ++i;
//        }
//    }
//
//    setUpdatesEnabled(true);
//    updateGeometry();
//}
//
//#endif
//


////////////////////////////////////////
// Source code based on antico(g_cigala@virgilio.it) source code

/* defined in the systray spec */
#define SYSTEM_TRAY_REQUEST_DOCK 0
#define SYSTEM_TRAY_BEGIN_MESSAGE 1
#define SYSTEM_TRAY_CANCEL_MESSAGE 2



QImage get_icon(Window c_win)
{
    Atom type_ret = None;
    unsigned char *data = 0;
    int format = 0;
    unsigned long n = 0;
    unsigned long extra = 0;
    int width = 0;
    int height = 0;
    QImage img;

    Atom _net_wm_icon = XInternAtom(QX11Info::display(), "_NET_WM_ICON", False);

    if (XGetWindowProperty(QX11Info::display(), c_win, _net_wm_icon, 0, 1, False,
                           XA_CARDINAL, &type_ret, &format, &n, &extra, (unsigned char **)&data) == Success && data)
    {
        width = data[0];
//        qDebug() << "Icon width:" << width;
        XFree(data);
    }
    if (XGetWindowProperty(QX11Info::display(), c_win, _net_wm_icon, 1, 1, False,
                           XA_CARDINAL, &type_ret, &format, &n, &extra, (unsigned char **)&data) == Success && data)
    {
        height = data[0];
//        qDebug() << "Icon height:" << height;
        XFree(data);
    }
    if (XGetWindowProperty(QX11Info::display(), c_win, _net_wm_icon, 2, width*height, False,
                           XA_CARDINAL, &type_ret, &format, &n, &extra, (unsigned char **)&data) == Success && data)
    {
        QImage img(data, width, height, QImage::Format_ARGB32);
        XFree(data);
    }
    else // if no icon is found
    {

    }
    return img;
}


XQDESensor_SystemTray::XQDESensor_SystemTray(QWidget *parent) : XQWidget(parent,NULL)
{
    layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignRight);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(1);
    setLayout(layout);

    // Freedesktop.org System Tray support
    char name[20] = {0};
    qsnprintf(name, 20, "_NET_SYSTEM_TRAY_S%d", DefaultScreen(QX11Info::display()));
    net_selection_atom = XInternAtom(QX11Info::display(), name, False);
    net_opcode_atom = XInternAtom(QX11Info::display(), "_NET_SYSTEM_TRAY_OPCODE", False);
    net_manager_atom = XInternAtom(QX11Info::display(), "MANAGER", False);
    net_message_data_atom = XInternAtom(QX11Info::display(), "_NET_SYSTEM_TRAY_MESSAGE_DATA", False);

    XSetSelectionOwner(QX11Info::display(), net_selection_atom, winId(), CurrentTime);

    if (XGetSelectionOwner(QX11Info::display(), net_selection_atom) == winId())
    {
        qDebug("Setting the selection owner");
        XClientMessageEvent xev;

        xev.type = ClientMessage;
        xev.window = QApplication::desktop()->winId();
        xev.message_type = net_manager_atom;
        xev.format = 32;
        xev.data.l[0] = CurrentTime;
        xev.data.l[1] = net_selection_atom;
        xev.data.l[2] = winId();
        xev.data.l[3] = 0; /* manager specific data */
        xev.data.l[4] = 0; /* manager specific data */

        XSendEvent(QX11Info::display(), QApplication::desktop()->winId(), False, StructureNotifyMask, (XEvent *)&xev);
    }
}

XQDESensor_SystemTray::~XQDESensor_SystemTray()
{
    delete layout;
}

void XQDESensor_SystemTray::add_sysicon(Window win_id)
{
//    QImage sysTrayIcon = get_icon(win_id);
    //ToDo create now the widget to add in the dock
//    layout->addWidget(sysTrayIcon);
//    qDebug() <<"Frame added to System Tray." << "Frame name:" << frm->cl_name() << "Frame Id:" << frm->winId() << "Client Id:" << frm->cl_win();
//    connect(s_icon, SIGNAL(destroy_sys(Sysicon *)), this, SLOT(remove(Sysicon *)));
}

void XQDESensor_SystemTray::add_embed(Window win_id)
{
    emb_cont = new QX11EmbedContainer(this);
    emb_cont->setPalette(QPalette(QPalette::Light));
    emb_cont->embedClient(win_id);
    sys_embed.insert(win_id, emb_cont); // save the Client winId/QX11EmbedContainer
//    qDebug("Client added to System Tray.  QX11EmbedContainer id: %d  Client Id: %d",emb_cont->winId() , win_id);
    layout->addWidget(emb_cont);
    emb_cont->setContentsMargins(0, 0, 0, 0);
    emb_cont->setFixedSize(qMin(25, height()), qMin(25, height()));
    XResizeWindow(QX11Info::display(), win_id, emb_cont->width(), emb_cont->height());
    XMapRaised(QX11Info::display(), win_id);

    connect(emb_cont, SIGNAL(clientClosed()), emb_cont, SLOT(close())); // doesn't work ?!?!?!?!?!?!?
}

//void XQDESensor_SystemTray::remove_sysicon(Window win_id) // if Sysicon is on Systray together with equal icon from _NET_SYSTEM_TRAY protocol
//{
//    if (sys_icons.contains(win_id))
//    {
//        s_icon = sys_icons.value(win_id);
//        sys_icons.remove(win_id);
//qDebug("Sysicon remove from Systray cmd.");
//        layout->removeWidget(s_icon);
//        s_icon->close();
//    }
//}

void XQDESensor_SystemTray::remove_embedder(Window win_id)
{
    if (sys_embed.contains(win_id))
    {
        emb_cont = sys_embed.value(win_id);
        sys_embed.remove(win_id);
//        qDebug("QX11EmbedContainer: %d Client: %d remove from Systray cmd." ,emb_cont->winId() ,win_id );
        layout->removeWidget(emb_cont);
        emb_cont->close();
    }
}


bool XQDESensor_SystemTray::x11Event(XEvent *event)
{
    if (event->type == ClientMessage)
    {
    qDebug("Systray::x11Event client message");
        if (event->xclient.message_type == net_opcode_atom && event->xclient.data.l[1] == SYSTEM_TRAY_REQUEST_DOCK)
        {
            qDebug("SYSTEM_TRAY_REQUEST_DOCK");
            add_embed(event->xclient.data.l[2]);
        }
        else if (event->xclient.message_type == net_opcode_atom && event->xclient.data.l[1] == SYSTEM_TRAY_BEGIN_MESSAGE)
        {
            qDebug("SYSTEM_TRAY_BEGIN_MESSAGE");
        }
        else if (event->xclient.message_type == net_opcode_atom && event->xclient.data.l[1] == SYSTEM_TRAY_CANCEL_MESSAGE)
        {
            qDebug("SYSTEM_TRAY_CANCEL_MESSAGE");
        }
        else if (event->xclient.data.l[1] == (signed)net_message_data_atom)
        {
            qDebug("Text message from Dockapp: %s", event->xclient.data.b);
        }
        return true;
    }
    return false;
}

