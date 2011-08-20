//
// C++ Implementation: xqdewindowmanagerinterface
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QX11Info>

#include "xqdewindowmanagerinterface.h"

#define qt_xdisplay() QX11Info::display ()
#define qt_xrootwin() QX11Info::appRootWindow()

// ToDo convert all to the class QDesktopWidget
XQDEWindowManagerInterface *WindowManagerInterface;

XQDEWindowManagerInterface::XQDEWindowManagerInterface(XQDEClass *parent)
 : XQDEClass(parent)
{
    ObjectName="com.XQDE.WindowsMangerInterface";
    ConfigurationData.append(new XQDEConfigurationPair("serverurl","http://xqde.xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("email","xqde@xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("author","Stefano Zingarini"));
    ConfigurationData.append(new XQDEConfigurationPair("web","http://xqde.xiaprojects.com"));
    ConfigurationData.append(new XQDEConfigurationPair("version",""));
    ConfigurationData.append(new XQDEConfigurationPair("autoupdate",""));
}


XQDEWindowManagerInterface::~XQDEWindowManagerInterface()
{
}


void XQDEWindowManagerInterface::setOnAllDesktops( WId win, bool b )
{
    NETWinInfo info( qt_xdisplay(), win, qt_xrootwin(), NET::WMDesktop );
    if ( b )
        info.setDesktop( NETWinInfo::OnAllDesktops );
    else if ( info.desktop()  == NETWinInfo::OnAllDesktops ) {
        NETRootInfo rinfo( qt_xdisplay(), NET::CurrentDesktop );
        info.setDesktop( rinfo.currentDesktop() );
    }
}

