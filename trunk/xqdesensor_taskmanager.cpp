//
// C++ Implementation: xqdesensor_taskmanager
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QMimeData>
#include <QMetaType>
#include <QtDebug>
#include <QProcess>
#include <QPixmap>
#include <QTimer>
#include <QMenu>
#include <QList>
#include <QTime>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>

#include "xqde.h"
#include "xqdesensor_taskmanager.h"
#include "xqdebasket.h"
#include "netwm_def.h"
#include "xqdeicon.h"
#include "xqdeenvironment.h"


//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xdamage.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>



const int TSKPOLLINGRATE=5000;
const int WINPOLLINGRATE=1000;

XQDESensor_TaskManager *TaskManager;
Pixmap m_windowPixmap;

/*
static unsigned long windows_properties[ 2 ] = {
				     NET::ClientList |
			   	     NET::ClientListStacking |
				     NET::NumberOfDesktops |
				     NET::DesktopGeometry |
				     NET::CurrentDesktop |
				     NET::DesktopNames |
				     NET::ActiveWindow |
				     NET::WorkArea |
				     NET::KDESystemTrayWindows,
                                     NET::WM2ShowingDesktop };

static unsigned long desktop_properties[ 2 ] = { 
				     NET::NumberOfDesktops |
				     NET::DesktopGeometry |
				     NET::CurrentDesktop |
				     NET::DesktopNames |
				     NET::ActiveWindow |
				     NET::WorkArea |
				     NET::KDESystemTrayWindows,
                                     NET::WM2ShowingDesktop };
//, , , PROTOCOLS2, ACTIONS,
*/
static unsigned long win_properties_mini[]=
{
NET::WMState | NET::WMWindowType,
0 
};
static unsigned long win_properties_trans[]=
{
NET::WMState,
NET::WM2TransientFor
};

static unsigned long win_properties_name[]=
{
NET::WMName
| NET::WMPid
| NET::WMVisibleName
| NET::WMIconName
| NET::WMVisibleIconName
| NET::WMIcon,
NET::WM2WindowClass
};


static unsigned long win_properties[]=
{
NET::AllTypesMask,
NET::AllTypesMask
};
static unsigned long full_properties[] =
{
NET::AllTypesMask,
NET::AllTypesMask,
NET::AllTypesMask,
NET::AllTypesMask
};


void MakeWindowOnBottom(void *w)
{
        NETWinInfo info(qt_xdisplay(), (Window)w, qt_xrootwin(),NET::WMState);
        info.setState(
                NET::Override |
                NET::Dock |
                NET::KeepBelow |
                NET::SkipTaskbar |
                NET::SkipPager |
                NET::Sticky,
                NET::Override |
                NET::Dock |
                NET::KeepBelow |
                NET::SkipTaskbar |
                NET::SkipPager |
                NET::Sticky
        );
        info.setWindowType( NET::Dock ); // don't show dock on exposé (10.04.09)
        info.setDesktop( NETWinInfo::OnAllDesktops);
}

void MakeWindowOnTopPillow(void *w)
{
        NETWinInfo info(qt_xdisplay(), (Window)w, qt_xrootwin(),NET::WMWindowType);
        info.setWindowType(NET::Tool);
}

void MakeWindowOnTop(void *w)
{
        NETWinInfo info(qt_xdisplay(), (Window)w, qt_xrootwin(),NET::WMState);
        info.setState(
                NET::Override |
                NET::Dock |
                NET::StaysOnTop |
                NET::KeepAbove |
                NET::SkipTaskbar |
                NET::SkipPager |
                NET::Sticky,
                NET::Override |
                NET::Dock |
                NET::StaysOnTop |
                NET::KeepAbove |
                NET::SkipTaskbar |
                NET::SkipPager |
                NET::Sticky
        );
        // OnTop restore windows type (10.04.09)
        // Usando Dock resta sopra la finestra
        info.setWindowType( NET::Normal );
        info.setDesktop( NETWinInfo::OnAllDesktops);
}


/*
static unsigned long full_properties[PROPERTIES_SIZE] = {
	// PROTOCOLS
	NET::ClientList |
	NET::ClientListStacking |
	NET::NumberOfDesktops |
	NET::DesktopGeometry |
	NET::DesktopViewport |
	NET::CurrentDesktop |
	NET::DesktopNames |
	NET::ActiveWindow |
	NET::WorkArea |
	NET::SupportingWMCheck |
	NET::VirtualRoots |
	NET::KDESystemTrayWindows |
	NET::CloseWindow |
	NET::WMMoveResize |
	NET::WMName |
	NET::WMVisibleName |
	NET::WMDesktop |
	NET::WMWindowType |
	NET::WMState |
	NET::WMStrut |
	NET::WMIconGeometry |
	NET::WMIcon |
	NET::WMPid |
	NET::WMHandledIcons |
	NET::WMPing |
	NET::WMKDESystemTrayWinFor |
	NET::XAWMState |
        NET::WMFrameExtents |
	NET::WMIconName |
	NET::WMVisibleIconName |
	NET::WMGeometry
,
//WINDOW_TYPES
	NET::NormalMask | 
	NET::DesktopMask |
	NET::DockMask |
	NET::ToolbarMask |
	NET::MenuMask |
	NET::DialogMask |
	NET::OverrideMask |
        NET::TopMenuMask |
	NET::UtilityMask |
	NET::SplashMask
NET::AllTypesMask
,
// STATES
NET::AllTypesMask
,
0	// PROTOCOLS2
,
0 //ACTIONS
,
        NET::WM2UserTime |
        NET::WM2StartupId |
        NET::WM2TransientFor |
        NET::WM2GroupLeader |
        NET::WM2AllowedActions |
        NET::WM2RestackWindow |
        NET::WM2MoveResizeWindow |
        NET::WM2ExtendedStrut |
        NET::WM2TakeActivity |
        NET::WM2KDETemporaryRules |
        NET::WM2WindowRole |
        NET::WM2ClientMachine |
        NET::WM2WindowClass |
        NET::WM2ShowingDesktop
	};
*/


//static
//const int minSize = 8;
//
//static
//bool operator< ( const QRect& r1, const QRect& r2 )
//{
//    return r1.width() * r1.height() < r2.width() * r2.height();
//}
//
//// Recursively iterates over the window w and its children, thereby building
//// a tree of window descriptors. Windows in non-viewable state or with height
//// or width smaller than minSize will be ignored.
//static
//void getWindowsRecursive( std::vector<QRect>& windows, Window w,
//                          int rx = 0, int ry = 0, int depth = 0 )
//{
//    XWindowAttributes atts;
//    XGetWindowAttributes( QX11Info::display(), w, &atts );
//    if ( atts.map_state == IsViewable &&
//         atts.width >= minSize && atts.height >= minSize ) {
//        int x = 0, y = 0;
//        if ( depth ) {
//            x = atts.x + rx;
//            y = atts.y + ry;
//        }
//
//        QRect r( x, y, atts.width, atts.height );
//        if ( std::find( windows.begin(), windows.end(), r ) == windows.end() ) {
//            windows.push_back( r );
//        }
//
//        Window root, parent;
//        Window* children;
//        unsigned int nchildren;
//
//        if( XQueryTree( QX11Info::display(), w, &root, &parent, &children, &nchildren ) != 0 ) {
//            for( unsigned int i = 0; i < nchildren; ++i ) {
//                getWindowsRecursive( windows, children[ i ], x, y, depth + 1 );
//            }
//            if( children != NULL )
//                XFree( children );
//        }
//    }
//    if ( depth == 0 )
//        std::sort( windows.begin(), windows.end() );
//}
//
//static
//Window findRealWindow( Window w, int depth = 0 )
//{
//    if( depth > 5 )
//        return None;
//    static Atom wm_state = XInternAtom( QX11Info::display(), "WM_STATE", False );
//    Atom type;
//    int format;
//    unsigned long nitems, after;
//    unsigned char* prop;
//    if( XGetWindowProperty( QX11Info::display(), w, wm_state, 0, 0, False, AnyPropertyType,
//        &type, &format, &nitems, &after, &prop ) == Success ) {
//        if( prop != NULL )
//            XFree( prop );
//        if( type != None )
//            return w;
//    }
//    Window root, parent;
//    Window* children;
//    unsigned int nchildren;
//    Window ret = None;
//    if( XQueryTree( QX11Info::display(), w, &root, &parent, &children, &nchildren ) != 0 ) {
//        for( unsigned int i = 0;
//             i < nchildren && ret == None;
//             ++i )
//            ret = findRealWindow( children[ i ], depth + 1 );
//        if( children != NULL )
//            XFree( children );
//    }
//    return ret;
//}
//
//static
//Window windowUnderCursor( bool includeDecorations = true )
//{
//    Window root;
//    Window child;
//    uint mask;
//    int rootX, rootY, winX, winY;
//    XGrabServer( QX11Info::display() );
//    XQueryPointer( QX11Info::display(), QX11Info::appRootWindow(), &root, &child,
//                   &rootX, &rootY, &winX, &winY, &mask );
//    if( child == None )
//        child = QX11Info::appRootWindow();
//    if( !includeDecorations ) {
//        Window real_child = findRealWindow( child );
//        if( real_child != None ) // test just in case
//            child = real_child;
//    }
//    return child;
//}
//
//static
//QPixmap grabWindow( Window child, int x, int y, uint w, uint h, uint border,
//                    QString *title=0 )
//{
//    QPixmap pm( QPixmap::grabWindow( QX11Info::appRootWindow(), x, y, w, h ) );
//
////    KWindowInfo winInfo( findRealWindow(child), NET::WMVisibleName, NET::WM2WindowClass );
////    if ( title )
////        (*title) = winInfo.visibleName();
////    if ( windowClass )
////        (*windowClass) = winInfo.windowClassName();
//
////#ifdef HAVE_X11_EXTENSIONS_SHAPE_H
//    int tmp1, tmp2;
//    //Check whether the extension is available
//    if ( XShapeQueryExtension( QX11Info::display(), &tmp1, &tmp2 ) ) {
////        QBitmap mask(w,h);
//        //As the first step, get the mask from XShape.
//        int count, order;
//        XRectangle* rects = XShapeGetRectangles( QX11Info::display(), child,
//                                                 ShapeBounding, &count, &order );
//        //The ShapeBounding region is the outermost shape of the window;
//        //ShapeBounding - ShapeClipping is defined to be the border.
//        //Since the border area is part of the window, we use bounding
//        // to limit our work region
//        if (rects) {
//            //Create a QRegion from the rectangles describing the bounding mask.
//            QRegion contents;
//            for ( int pos = 0; pos < count; pos++ )
//                contents += QRegion( rects[pos].x, rects[pos].y,
//                                     rects[pos].width, rects[pos].height );
//            XFree( rects );
//
//            //Create the bounding box.
//            QRegion bbox( 0, 0, w, h );
//
//            if( border > 0 ) {
//                contents.translate( border, border );
//                contents += QRegion( 0, 0, border, h );
//                contents += QRegion( 0, 0, w, border );
//                contents += QRegion( 0, h - border, w, border );
//                contents += QRegion( w - border, 0, border, h );
//            }
//
//            //Get the masked away area.
//            QRegion maskedAway = bbox - contents;
//            QVector<QRect> maskedAwayRects = maskedAway.rects();
//
////            //Construct a bitmap mask from the rectangles
////            QPainter p(&mask);
////            p.fillRect(0, 0, w, h, Qt::color1);
////            for (int pos = 0; pos < maskedAwayRects.count(); pos++)
////                    p.fillRect(maskedAwayRects[pos], Qt::color0);
////            p.end();
//
//            //pm.setMask(mask);
//        }
//    }
////#endif
//
//    return pm;
//}


QPixmap thumbnail(Window m_frameId, int maxDimension)
{

//    if (!m_windowPixmap)
//    {
//        qWarning("thumbnail return pixmap");
//        return QPixmap();
//    }
//
//        Display *dpy = qt_xdisplay();
//
//    XWindowAttributes winAttr;
//    XGetWindowAttributes(dpy, m_frameId, &winAttr);
////    XserverRegion region = XFixesCreateRegionFromWindow(dpy, m_frameId,
////                                                        WindowRegionBounding);
////
//
//        QPixmap thumbnail = QPixmap::grabWindow(m_frameId);
//
//        if (thumbnail.isNull())
//        {
//            return QPixmap();
//        }
//
//        QPixmap pixmap(maxDimension, maxDimension);
//        pixmap.fill(Qt::transparent);
//
//        if (thumbnail.width() > thumbnail.height())
//        {
//            thumbnail = thumbnail.scaledToWidth(maxDimension, Qt::SmoothTransformation);
//        }
//        else
//        {
//            thumbnail = thumbnail.scaledToHeight(maxDimension, Qt::SmoothTransformation);
//        }

//
//
//    /******************************/
//
// int revert;
//
//    Display *dpy = qt_xdisplay();
//
//    // We need to find out some things about the window, such as it's size,
//    // it's position on the screen, and the format of the pixel data
//    XWindowAttributes attr;
//    qWarning("XGetInputFocus");
//    XGetInputFocus(dpy, &m_frameId, &revert);
//    qWarning("XGetWindowAttributes");
//    XGetWindowAttributes(dpy, m_frameId, &attr);
//
//    XRenderPictFormat *format = XRenderFindVisualFormat(dpy, attr.visual);
//    bool hasAlpha             = (format->type == PictTypeDirect &&
//                                 format->direct.alphaMask);
//    int x                     = attr.x;
//    int y                     = attr.y;
//    int width                 = attr.width;
//    int height                = attr.height;
//
//    // Create a Render picture so we can reference the window contents.
//    // We need to set the subwindow mode to IncludeInferiors, otherwise child
//    // widgets in the window won't be included when we draw it, which is not
//    // what we want.
//    XRenderPictureAttributes pa;
//    pa.subwindow_mode = IncludeInferiors; // Don't clip child widgets
//
//    qWarning("XRenderCreatePicture");
//    Picture picture = XRenderCreatePicture(dpy, m_windowPixmap, format, CPSubwindowMode, &pa);
//    // Create a copy of the bounding region for the window
//    qWarning("Create XserverRegion");
//    XserverRegion region = XFixesCreateRegionFromWindow(dpy, m_frameId,WindowRegionBounding);
//    qWarning("XFixesSetPictureClipRegion");
//    XFixesSetPictureClipRegion(dpy, picture, 0, 0, region);
//    qWarning("XFixesDestroyRegion");
//    XFixesDestroyRegion(dpy, region);
//
//    double factor;
//    if (width > height)
//    {
//        factor = (double)maxDimension / (double)width;
//    }
//    else
//    {
//        factor = (double)maxDimension / (double)height;
//    }
//    int thumbnailWidth = width * factor;
//    int thumbnailHeight = height * factor;
//
//    QPixmap thumbnail(thumbnailWidth, thumbnailHeight);
//    thumbnail.fill(Qt::transparent);
//#if 0
//    QPixmap full(width, height);
//    full.fill(QApplication::palette().active().background());
//
//    XRenderComposite(dpy,
//                     hasAlpha ? PictOpOver : PictOpSrc,
//                     picture, // src
//                     None, // mask
//                     full.x11RenderHandle(), // dst
//                     0, 0, // src offset
//                     0, 0, // mask offset
//                     0, 0, // dst offset
//                     width, height);
//
//    thumbnail.convertFromImage(full.convertToImage().smoothScale(thumbnailWidth,
//                               thumbnailHeight));
//#else
//    // XRENDER scaling
//    qWarning("XRenderSetPictureFilter");
//    XRenderSetPictureFilter( dpy, picture, FilterBilinear, 0, 0 );
//    // Scaling matrix
//    XTransform xform = {{
//        { XDoubleToFixed( 1 ), XDoubleToFixed( 0 ), XDoubleToFixed(      0 ) },
//        { XDoubleToFixed( 0 ), XDoubleToFixed( 1 ), XDoubleToFixed(      0 ) },
//        { XDoubleToFixed( 0 ), XDoubleToFixed( 0 ), XDoubleToFixed( factor ) }
//    }};
//
//    qWarning("XRenderSetPictureTransform");
//    XRenderSetPictureTransform(dpy, picture, &xform);
//    qWarning("XRenderComposite");
//    XRenderComposite(dpy,
//                     hasAlpha ? PictOpOver : PictOpSrc,
//                     picture, // src
//                     None, // mask
//                     thumbnail.x11PictureHandle(), // dst
//                     0, 0, // src offset
//                     0, 0, // mask offset
//                     0, 0, // dst offset
//                     thumbnailWidth, thumbnailHeight);
//#endif
//
//    qWarning("XRenderFreePicture");
//    XRenderFreePicture(dpy, picture);
//


////        ***********************************************   //
////    Composite Help: http://ktown.kde.org/~fredrik/composite_howto.html
//
//    if (!m_windowPixmap)
//    {
//        return QPixmap();
//    }

//    qWarning("Create thumbnail...");
//
//    Display *dpy = qt_xdisplay();
//    int revert;
//
//    //Crash here!!
//    // penso che m_frameId non sia corretto
//    // ho inserito XGetInputFocus per prendere id
//    // della finestra in focus... solo per test
//    XWindowAttributes winAttr;
//    XGetInputFocus(dpy, &m_frameId, &revert);
//    XGetWindowAttributes(dpy, m_frameId, &winAttr);
//    XRenderPictFormat *format = XRenderFindVisualFormat(dpy, winAttr.visual);
//
//    bool hasAlpha = ( format->type == PictTypeDirect && format->direct.alphaMask);
//
//    XRenderPictureAttributes picAttr;
//    picAttr.subwindow_mode = IncludeInferiors; // Don't clip child widgets
//
//    Picture picture = XRenderCreatePicture(dpy, m_windowPixmap, format,
//                                           CPSubwindowMode, &picAttr);
//
//    // Get shaped windows handled correctly.
//    XserverRegion region = XFixesCreateRegionFromWindow(dpy, m_frameId,
//                                                        WindowRegionBounding);
//    XFixesSetPictureClipRegion(dpy, picture, 0, 0, region);
//    XFixesDestroyRegion(dpy, region);
//
//
//    double factor;
//    if (winAttr.width > winAttr.height)
//    {
//        factor = (double)maxDimension / (double)winAttr.width;
//    }
//    else
//    {
//        factor = (double)maxDimension / (double)winAttr.height;
//    }
//    int thumbnailWidth = (int)(winAttr.width * factor);
//    int thumbnailHeight = (int)(winAttr.height * factor);
//
//    QPixmap thumbnail(thumbnailWidth, thumbnailHeight);
//
//    thumbnail.fill(Qt::transparent);
//
//#if 0 // QImage::smoothScale() scaling
//    QPixmap full(winAttr.width, winAttr.height);
//    full.fill(QApplication::palette().active().background());
//
//    bool hasAlpha = format->type == PictTypeDirect && format->direct.alphaMask;
//
//    XRenderComposite(dpy,
//                     hasAlpha ? PictOpOver : PictOpSrc,
//                     picture, // src
//                     None, // mask
//                     full.x11RenderHandle(), // dst
//                     0, 0, // src offset
//                     0, 0, // mask offset
//                     0, 0, // dst offset
//                     winAttr.width, winAttr.height);
//
//    KPixmapIO io;
//    QImage image = io.convertToImage(full);
//    thumbnail = io.convertToPixmap(image.smoothScale(thumbnailWidth,
//                                                     thumbnailHeight));
//#else // XRENDER scaling
//    // Scaling matrix
//    XTransform transformation = {{
//        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(     0) },
//        { XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(     0) },
//        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(factor) }
//    }};
//
//    XRenderSetPictureTransform(dpy, picture, &transformation);
////    XRenderSetPictureFilter(dpy, picture, FilterBest, 0, 0);
//
////    XRenderComposite(dpy,
////                     PictOpOver, // we're filtering, alpha values are probable
////                     picture, // src
////                     None, // mask
////                     thumbnail.x11PictureHandle(), // dst
////                     0, 0, // src offset
////                     0, 0, // mask offset
////                     0, 0, // dst offset
////                     thumbnailWidth, thumbnailHeight);
//
//    XRenderComposite( dpy, hasAlpha ? PictOpOver : PictOpSrc, picture, None,
//                      thumbnail.x11PictureHandle(), 0, 0, 0, 0, 0, 0, thumbnailWidth, thumbnailHeight );
//
//#endif
//    XRenderFreePicture(dpy, picture);
//
//
//    return thumbnail;


////        ***********************************************   //
////    Composite Help: http://ktown.kde.org/~fredrik/composite_howto.html
//
//    if (!m_windowPixmap)
//    {
//        return QPixmap();
//    }
//    // If we're using the raster or OpenGL graphics systems, a QPixmap isn't an X pixmap,
//        // so we have to get the window contents into a QImage and then draw that.
//        Display *dpy = qt_xdisplay();
//
//        // XXX We really should keep a cached copy of the image client side, and only
//        //     update it in response to a damage event.
////        m_frameId = 0x7800022; //only for test
////        m_frameId = findRealWindow(0x140015f, 1);
//        Pixmap pixmap = XCompositeNameWindowPixmap(dpy, m_frameId);
//
//        XWindowAttributes winAttr;
//        XGetWindowAttributes(dpy, m_frameId, &winAttr);
//
//        if ( winAttr.map_state == IsViewable /*&&
//         winAttr.width >= minSize && winAttr.height >= minSize*/ ) ;
//        else return QPixmap();
//
////        double factor;
////        if (winAttr.width > winAttr.height)
////        {
////            factor = (double)maxDimension / (double)winAttr.width;
////        }
////        else
////        {
////            factor = (double)maxDimension / (double)winAttr.height;
////        }
////
////        int thumbnailWidth = (int)(winAttr.width * factor);
////        int thumbnailHeight = (int)(winAttr.height * factor);
////
////        int thumbnailWidth1 = (int)(winAttr.width );
////        int thumbnailHeight2 = (int)(winAttr.height);
//
//        int a = winAttr.width;
//        int b = winAttr.height;
//        XImage *ximage = XGetImage(dpy, pixmap, 0, 0, winAttr.width, winAttr.height, AllPlanes, ZPixmap);
//        XFreePixmap(dpy, pixmap);
//        // We actually check if we get the image from X11 since clientWinId can be any arbiter window (with crazy XWindowAttribute and the pixmap associated is bad)
//        if (!ximage)
//            return QPixmap();
//        // This is safe to do since we only composite ARGB32 windows, and PictStandardARGB32
//        // matches QImage::Format_ARGB32_Premultiplied.
//        QImage image((const uchar*)ximage->data, ximage->width, ximage->height, ximage->bytes_per_line,
//                    QImage::Format_ARGB32_Premultiplied);
//
//        XDestroyImage( ximage );
//        return QPixmap::fromImage ( image, Qt::AutoColor );


//        /* ############## Test ########## */
//
////    KWindowInfo winInfo( findRealWindow(m_frameId), NET::WMVisibleName, NET::WM2WindowClass );
////    QString title = winInfo.visibleName();
////    QString windowClass = winInfo.windowClassName();
////
//    NETWinInfo infoTitle(qt_xdisplay(), findRealWindow(m_frameId), qt_xrootwin(),NET::WMName);
//    const char *title0=infoTitle.name();
//    QString title(QString::fromUtf8(title0,-1));
//
//
//    Window root;
//    int y, x;
//    uint w, h, border, depth;
//    //XGrabServer( QX11Info::display() );
//    Window child = windowUnderCursor( false );
//    XGetGeometry( QX11Info::display(), child, &root, &x, &y, &w, &h, &border, &depth );
//    Window parent;
//    Window* children;
//    unsigned int nchildren;
//    if( XQueryTree( QX11Info::display(), child, &root, &parent,
//                    &children, &nchildren ) != 0 ) {
//        if( children != NULL )
//            XFree( children );
//        int newx, newy;
//        Window dummy;
//        if( XTranslateCoordinates( QX11Info::display(), parent, QX11Info::appRootWindow(),
//            x, y, &newx, &newy, &dummy )) {
//            x = newx;
//            y = newy;
//        }
//    }
//    QPixmap pm( grabWindow( child, x, y, w, h, border, &title ) );
//    //XUngrabServer( QX11Info::display() );
//    return pm;

   // ######## other test ###########33

//    // ######## this WORK!!! ###########
////    Composite Help: http://ktown.kde.org/~fredrik/composite_howto.html
//
//    if (!m_windowPixmap)
//    {
//       return QPixmap();
//    }
//
//    Display *dpy = qt_xdisplay();
//    // We need to find out some things about the window, such as it's size, it's position
//    // on the screen, and the format of the pixel data
//    XWindowAttributes attr;
//
//    QTime t;
//    t.start();
//
//    if( XGetWindowAttributes( dpy, m_frameId, &attr ) == 0)  return QPixmap();
//
//    qDebug("Time elapsed XGetWindowAttributes: %d ms", t.elapsed());
//    t.restart();
//
//    XRenderPictFormat *format = XRenderFindVisualFormat( dpy, attr.visual );
//    bool hasAlpha             = ( format->type == PictTypeDirect && format->direct.alphaMask );
//    int x                     = attr.x;
//    int y                     = attr.y;
//    int width                 = attr.width;
//    int height                = attr.height;
//
//    qDebug("Time elapsed XRenderFindVisualFormat: %d ms", t.elapsed());
//    t.restart();
//
//    // Create a Render picture so we can reference the window contents.
//    // We need to set the subwindow mode to IncludeInferiors, otherwise child widgets
//    // in the window won't be included when we draw it, which is not what we want.
//    XRenderPictureAttributes pa;
//    pa.subwindow_mode = IncludeInferiors; // Don't clip child widgets
//
//    Picture picture = XRenderCreatePicture( dpy, m_frameId, format, CPSubwindowMode, &pa );
//
//    qDebug("Time elapsed XRenderCreatePicture: %d ms", t.elapsed());
//    t.restart();
//
//    //        double factor;
//    //        if (attr.width > attr.height)
//    //        {
//    //            factor = (double)maxDimension / (double)attr.width;
//    //        }
//    //        else
//    //        {
//    //            factor = (double)maxDimension / (double)attr.height;
//    //        }
//    //
//    //        int thumbnailWidth = (int)(attr.width * factor);
//    //        int thumbnailHeight = (int)(attr.height * factor);
//
//    int thumbnailWidth = (int)(attr.width );
//    int thumbnailHeight = (int)(attr.height);
//
//    QPixmap thumbnail(thumbnailWidth, thumbnailHeight);
//    thumbnail.fill(Qt::transparent);
//
//    //XRenderComposite(dpy,
//    //                     PictOpOver, // we're filtering, alpha values are probable
//    //                     picture, // src
//    //                     None, // mask
//    //                     thumbnail.x11PictureHandle(), // dst
//    //                     0, 0, // src offset
//    //                     0, 0, // mask offset
//    //                     0, 0, // dst offset
//    //                     thumbnailWidth, thumbnailHeight);
//
//    XRenderComposite( dpy, hasAlpha ? PictOpOver : PictOpSrc, picture, None,
//		    thumbnail.x11PictureHandle(), 0, 0, 0, 0, 0, 0, thumbnailWidth, thumbnailHeight );
//
//    qDebug("Time elapsed XRenderComposite: %d ms", t.elapsed());
//    t.restart();
//
//    XRenderFreePicture(dpy, picture);
//
//    qDebug("Time elapsed XRenderFreePicture: %d ms", t.elapsed());
//    t.restart();

    
    //    Composite Help: http://ktown.kde.org/~fredrik/composite_howto.html

//    if (!m_windowPixmap)
//    {
//       return QPixmap();
//    }

//    Display *dpy = qt_xdisplay();
    // We need to find out some things about the window, such as it's size, it's position
    // on the screen, and the format of the pixel data
//    XWindowAttributes attr;

    //!! XGetWindowAttributes is a synchronous call (it blocks) !!
//    if( XGetWindowAttributes( dpy, m_frameId, &attr ) == 0)  return QPixmap();

//    XQDEIcon *ic=Basket->getViaData((void *)m_frameId);
//    if(!ic) return QPixmap();
//    QRect size = ic->getAttachedWindowsPosition();
//
//    int x                     = 0;
//    int y                     = 0;
//    int width                 = size.width();
//    int height                = size.height();
//
//    //grap picture
//    QPixmap originalPixmap(QPixmap::grabWindow(m_frameId,x,y,width,height));
//
//    return originalPixmap;

//
//
//    int thumbnailWidth = (int)(attr.width );
//    int thumbnailHeight = (int)(attr.height);
//
//    QPixmap thumbnail(thumbnailWidth, thumbnailHeight);
//    thumbnail.fill(Qt::transparent);
//    QSize thumbnailSize(thumbnailWidth, thumbnailHeight);
//    thumbnail = originalPixmap.scaled(thumbnailSize, Qt::KeepAspectRatio,
//						     Qt::SmoothTransformation);

//    if (!m_windowPixmap)
//    {
//	return QPixmap();
//    }

//    Display *dpy = qt_xdisplay();
//    XWindowAttributes attr;
//    if(XGetWindowAttributes(dpy, m_frameId, &attr) == 0)  return QPixmap();
//    XRenderPictFormat *format = XRenderFindVisualFormat(dpy, attr.visual);
//    bool hasAlpha             = ( format->type == PictTypeDirect && format->direct.alphaMask );
//    int x                     = attr.x;
//    int y                     = attr.y;
//    int width                 = attr.width;
//    int height                = attr.height;
//    XRenderPictureAttributes pa;
//    pa.subwindow_mode = IncludeInferiors; // Don't clip child widgets
//
//    Picture picture = XRenderCreatePicture(dpy, m_frameId,
//					   format, CPSubwindowMode, &pa);
//    XserverRegion region = XFixesCreateRegionFromWindow(dpy,
//							m_frameId, WindowRegionBounding);
//
//    XFixesTranslateRegion(dpy, region, -x, -y);
//    XFixesSetPictureClipRegion(dpy, picture, 0, 0, region);
//    XFixesDestroyRegion(dpy, region);
//    QPixmap dest(width, height);
//    XRenderComposite(dpy, hasAlpha ? PictOpOver : PictOpSrc, picture, None,
//		     dest.x11PictureHandle(), 0, 0, 0, 0, 0, 0, width, height);
//
//    return dest;
//



    QPixmap thumbnail;

    Display *display = QX11Info::display();
    XWindowAttributes attributes;

    XCompositeRedirectWindow(display, m_frameId, CompositeRedirectAutomatic);

    if(XGetWindowAttributes(display, m_frameId, &attributes) == 0) return QPixmap();

    XRenderPictFormat *format = XRenderFindVisualFormat(display, attributes.visual);

    if (format)
    {
	bool hasAlpha  = (format->type == PictTypeDirect && format->direct.alphaMask);
	int x = attributes.x;
	int y = attributes.y;
	int width = attributes.width;
	int height = attributes.height;

	XRenderPictureAttributes pictureAttributes;
	pictureAttributes.subwindow_mode = IncludeInferiors;

	Picture picture = XRenderCreatePicture(display, m_frameId, format, CPSubwindowMode, &pictureAttributes);

//	XserverRegion region = XFixesCreateRegionFromWindow(display, m_frameId, WindowRegionBounding);
//
//	XFixesTranslateRegion(display, region, -x, -y);
//	XFixesSetPictureClipRegion(display, picture, 0, 0, region);
//	XFixesDestroyRegion(display, region);

	XShapeSelectInput(display, m_frameId, ShapeNotifyMask);

	thumbnail = QPixmap(width, height);
	thumbnail.fill(Qt::transparent);

	XRenderComposite(display, (hasAlpha?PictOpOver:PictOpSrc), picture, None, thumbnail.x11PictureHandle(), 0, 0, 0, 0, 0, 0, width, height);
    }

    if (!thumbnail.isNull())
    {
	if (thumbnail.width() > thumbnail.height())
	{
	    thumbnail = thumbnail.scaledToWidth(maxDimension, Qt::SmoothTransformation);
	}
	else
	{
	    thumbnail = thumbnail.scaledToHeight(maxDimension, Qt::SmoothTransformation);
	}
    }

    return thumbnail;
}




void XRenderResizeImageGood(QPixmap &Source,QPixmap &thumbnail,int maxDimension)
{
    thumbnail=QPixmap(maxDimension, maxDimension);
    double factor;
    factor = (double)maxDimension / (double)Source.width();

    thumbnail.fill(QColor(255,255,255,0));
        //thumbnail.fill(0x00000000);

    // Scaling matrix
    XTransform transformation = {{
        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(     0) },
        { XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(     0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(factor) }
    }};

    XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(), FilterBest, 0, 0);
        XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(),FilterBilinear, 0, 0 );
    XRenderSetPictureTransform(qt_xdisplay(), Source.x11PictureHandle(), &transformation);
    XRenderComposite(qt_xdisplay(),
                     PictOpOver, // we're filtering, alpha values are probable
                                         //PictOpSrc, // we're filtering, alpha values are probable
                     Source.x11PictureHandle(), // src
                     None, // mask
                     thumbnail.x11PictureHandle(), // dst
                     0, 0, // src offset
                     0, 0, // mask offset
                     0, 0, // dst offset
                     maxDimension, maxDimension);

    //New (25.09.02) using Qt
//    thumbnail = Source.scaledToWidth(maxDimension, Qt::SmoothTransformation);
}


void XRenderResizeImage(QPixmap &Source,QPixmap &thumbnail,int mx, int my)
{
    thumbnail=QPixmap(mx, my);
    double factorx;
    double factory;
    factorx = (double)1 / ((double)mx/ (double)Source.width()) ;
    factory = (double)1 / ((double)my/ (double)Source.height());

    thumbnail.fill(QColor(255,255,255,0));

    // Scaling matrix
    XTransform transformation = {{
        { XDoubleToFixed(factorx), XDoubleToFixed(0), XDoubleToFixed(    0) },
        { XDoubleToFixed(0), XDoubleToFixed(factory), XDoubleToFixed(    0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(1) }
    }};

    //XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(), FilterBest, 0, 0);
        //XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(),FilterBilinear, 0, 0 );
    XRenderSetPictureTransform(qt_xdisplay(), Source.x11PictureHandle(), &transformation);
    XRenderComposite(qt_xdisplay(),
                     PictOpOver, // we're filtering, alpha values are probable
                                         //PictOpSrc, // we're filtering, alpha values are probable
                     Source.x11PictureHandle(), // src
                     None, // mask
                     thumbnail.x11PictureHandle(), // dst
                     0, 0, // src offset
                     0, 0, // mask offset
                     0, 0, // dst offset
                     mx,my);

    //New (25.09.02) using Qt
//    thumbnail = Source.scaled(mx,my, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}

void XRenderResizeImage(QPixmap &Source,QPixmap &thumbnail,int maxDimension)
{
    thumbnail=QPixmap(maxDimension, maxDimension);
    double factor;
    factor = (double)maxDimension / (double)Source.width();

    thumbnail.fill(QColor(255,255,255,0));
        //thumbnail.fill(0x00000000);

    // Scaling matrix
    XTransform transformation = {{
        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(     0) },
        { XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(     0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(factor) }
    }};

    //XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(), FilterBest, 0, 0);
        //XRenderSetPictureFilter(qt_xdisplay(), Source.x11PictureHandle(),FilterBilinear, 0, 0 );
    XRenderSetPictureTransform(qt_xdisplay(), Source.x11PictureHandle(), &transformation);
    XRenderComposite(qt_xdisplay(),
                     PictOpOver, // we're filtering, alpha values are probable
                                         //PictOpSrc, // we're filtering, alpha values are probable
                     Source.x11PictureHandle(), // src
                     None, // mask
                     thumbnail.x11PictureHandle(), // dst
                     0, 0, // src offset
                     0, 0, // mask offset
                     0, 0, // dst offset
                     maxDimension, maxDimension);

    //New (25.09.02) using Qt
//    thumbnail = Source.scaledToWidth(maxDimension, Qt::FastTransformation);
}


void updateWindowPixmap(Window m_frameId)
{
        //ToDo ricerca problema questa funzione blocca il programma
///*
//    if (!TaskManager::xCompositeEnabled() || !isOnCurrentDesktop() ||
//        isMinimized())
//    {
//        return;
//    }
//*/
//    if (m_windowPixmap)
//    {
//	qDebug("XFreePixmap");
//	XFreePixmap(qt_xdisplay(), m_windowPixmap);
//    }
//
//    //Bug fix: when no windows is active set m_windowPixmap = 0;
//    qDebug("Window m_frameId: %d",m_frameId);
//    if (m_frameId != 0){
//	m_windowPixmap = XCompositeNameWindowPixmap(qt_xdisplay(), m_frameId);
////	Preventing the backing pixmap from being freed when the window is hidden/destroyed
////	XSelectInput( qt_xdisplay(), m_frameId, StructureNotifyMask );
//    }
//    else m_windowPixmap = NULL;

}

XQDESensor_TaskManager::XQDESensor_TaskManager(XQDEClass *parent)
    : XQDEClass(parent),
    NETRootInfo4( qt_xdisplay(),//int _what
                                   /* 1 >= 0 ?
                                     windows_properties : desktop_properties,
*/
full_properties, sizeof(full_properties)/sizeof(unsigned long), -1, false)
{
	m_windowPixmap=0;

	ObjectName="com.XQDE.TaskManager";
        ConfigurationData.append(new XQDEConfigurationPair("serverurl",""));
        ConfigurationData.append(new XQDEConfigurationPair("email","xqde@xiaprojects.com"));
        ConfigurationData.append(new XQDEConfigurationPair("author","Stefano Zingarini"));
        ConfigurationData.append(new XQDEConfigurationPair("web","http://xqde.xiaprojects.com"));
        ConfigurationData.append(new XQDEConfigurationPair("version","20090712"));
        ConfigurationData.append(new XQDEConfigurationPair("autoupdate","http://xqde.xiaprojects.com/todo.php"));

	int damage_error; // The event base is important here
	XDamageQueryExtension(QX11Info::display(), &m_damageEvent, &damage_error);
}

XQDESensor_TaskManager::~XQDESensor_TaskManager()
{
}


void XQDESensor_TaskManager::setGeometry( void *cw,int x,int y,int z)
{
	NETRect r;
	r.pos.x=x;
	r.pos.y=y;
	r.size.width=z;
	r.size.height=z;
        Window window=(Window)cw;
        NETWinInfo info(qt_xdisplay(), window, qt_xrootwin(),win_properties,sizeof(win_properties)/sizeof(unsigned long));
	info.setIconGeometry(r);
}

void XQDESensor_TaskManager::slotupdateThumbnail()
{
	updateThisThumbnail(lastActiveWindow);
}

QImage GetWMIcon(WId win, int width, int height)
{
	NETWinInfo info( qt_xdisplay(), win, qt_xrootwin(), NET::WMIcon );
	NETIcon ni = info.icon( width , height);
	if ( ni.data && ni.size.width > 0 && ni.size.height > 0 ) {
	  QImage img( (uchar*) ni.data, (int) ni.size.width, (int) ni.size.height, QImage::Format_ARGB32 );
	  if ( width > 0 && height > 0 &&img.size() != QSize( width, height ) && !img.isNull())
	      img = img.scaled(width, height,Qt::KeepAspectRatio , Qt::SmoothTransformation);
	  if ( !img.isNull() )
	      return img;
	}
	return QImage();
}

void XQDESensor_TaskManager::updateThisThumbnail(Window lastActiveWindow)
{
	timer_slotupdateThumbnail->stop();

        //ricava immagine screen..
        //Bug FIX (10.04.09): disabilitata la funzione "updateWindowPixmap", con kwin non trova immagine finestra!
//        updateWindowPixmap(lastActiveWindow);
//        QImage pi=thumbnail(lastActiveWindow,DesktopEnvironment->GUI.sizeIconsMax).toImage();

	XQDEIcon *ic=Basket->getViaData((void *)lastActiveWindow,this);
	if(!ic)return;
	int needToSendSignal=0;
	if(ic->enablePreview>0)
	{
//	    updateWindowPixmap(lastActiveWindow);
	    QImage pi=thumbnail(lastActiveWindow,DesktopEnvironment->GUI.sizeIconsMax).toImage();

	    ic->xSetIcon(pi);
	    needToSendSignal++;
		
	}

	NETWinInfo infoTitle(qt_xdisplay(), lastActiveWindow, qt_xrootwin(),NET::WMName);
	const char *vs=infoTitle.name();
	if(vs!=0)
	{
		ic->xSetTitle(QString::fromUtf8(vs,-1));
	}


	if(ic->enableIconFromWindow>0)
	{
//		NETWinInfo infoIcon(qt_xdisplay(), lastActiveWindow, qt_xrootwin(),NET::WMIcon);
//		//qWarning("about P4_%d_",(int)lastActiveWindow);
//		NETIcon taskIcon=infoIcon.icon(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
//		QImage taskQIcon;
//		//qWarning("about P5_%d_",(int)lastActiveWindow);
//		if(taskIcon.data!=0)
//		{
//		//qWarning("about P5A_%d_",(int)lastActiveWindow);
//			taskQIcon=QImage(taskIcon.size.width,taskIcon.size.height,QImage::Format_ARGB32);
//			taskQIcon.fill(Qt::transparent);
//			memcpy(	(unsigned char *)taskQIcon.bits(),
//				taskIcon.data,taskIcon.size.width*taskIcon.size.height*(1+1+1+1));
//		//qWarning("about P5B_%d_",(int)lastActiveWindow);
//                ic->xSetIconWM( taskQIcon);
		
//		NETWinInfo info( qt_xdisplay(), lastActiveWindow, qt_xrootwin(), NET::WMIcon );
//		NETIcon ni = info.icon( DesktopEnvironment->GUI.sizeIconsMax , DesktopEnvironment->GUI.sizeIconsMax);
//		if ( ni.data && ni.size.width > 0 && ni.size.height > 0 ) {
//		  QImage img( (uchar*) ni.data, (int) ni.size.width, (int) ni.size.height, QImage::Format_ARGB32 );
//		  if ( DesktopEnvironment->GUI.sizeIconsMax > 0 && DesktopEnvironment->GUI.sizeIconsMax > 0 &&img.size() != QSize( DesktopEnvironment->GUI.sizeIconsMax, DesktopEnvironment->GUI.sizeIconsMax ) && !img.isNull())
//		      img = img.scaled(DesktopEnvironment->GUI.sizeIconsMax , DesktopEnvironment->GUI.sizeIconsMax,Qt::KeepAspectRatio , Qt::SmoothTransformation);
//		  if ( !img.isNull() )
//		      ic->xSetIconWM(img);
//		      needToSendSignal++;
//		}

		QImage taskQIcon = GetWMIcon(lastActiveWindow, DesktopEnvironment->GUI.sizeIconsMax , DesktopEnvironment->GUI.sizeIconsMax );
		if(!taskQIcon.isNull())	{
		ic->xSetIconWM(taskQIcon);

//		ic->xSetIconWM(taskQIcon);
//
//
		needToSendSignal++;
	    }
//		}
        }
	if(needToSendSignal>0)
	{
		ic->xReset();
		Basket->sgeBasket_As_Changed(2, ic, NULL);
	}
}

int PIDisRunning(long p)
{
	struct stat buf;
	char path[512];
	sprintf(path,"/proc/%ld",p);
	
	int ret=stat(path,&buf);
	
	if(ret==0)
	{
		return 1;
	}
	return 0;
}


void XQDESensor_TaskManager::postAddClient(Window window)
{
	qDebug("now adding windows! _%x_",(int)window);
	XSync(qt_xdisplay(), False);

	Atom type_ret;
	int format_ret;
	unsigned long nitems_ret, unused;
	unsigned char *data_ret;

	if (XGetWindowProperty(qt_xdisplay(), window, XInternAtom(qt_xdisplay(),"_NET_WM_STATE", false), 0l, 2048l,
			       False, XA_ATOM, &type_ret, &format_ret,
                               &nitems_ret, &unused, &data_ret)   == Success) {
		//qWarning("now adding windows! _%x_ TEST OK",(int)window);
	}
	else
	{
		//qWarning("now adding windows! _%x_ TEST failed",(int)window);
		return;
	}


	NETWinInfo infoTest(qt_xdisplay(), window, qt_xrootwin(),win_properties_mini,sizeof(win_properties_mini)/sizeof(unsigned long));
	unsigned long st=infoTest.state();
	unsigned long ty=infoTest.windowType();
	qDebug("now adding state_%ldd_type_%ld_",st,ty);

	if(ty & NET::Unknown)
	{
		qDebug("NET::Unknown");
		return;
	}
	if(ty & NET::Override)
	{
		qDebug("NET::Override");
		return;
	}
	if(ty & NET::Desktop)
	{
		qDebug("NET::Desktop");
		return;
	}
	if(ty & NET::Dock)
	{
		qDebug("NET::Dock");
		return;
	}
	if(ty & NET::Menu)
	{
		qDebug("NET::Menu");
		return;
	}
	if(ty & NET::TopMenu)
	{
		qDebug("NET::TopMenu");
		return;
	}
	if(ty & NET::Utility)
	{
		qDebug("NET::Utility");
		return;
	}
	if(ty & NET::Splash)
	{
		qDebug("NET::Splash");
		return;
	}

//	if(st & NET::Override)
//	{
//		qDebug("NET::Override");
//		return;
//	}
//	if(st & NET::Dock)
//	{
//		qDebug("NET::Dock");
//		return;
//	}
	if(st & NET::SkipTaskbar)
	{
		qDebug("NET::SkipTaskbar");
		return;
	}
	if(st & NET::SkipPager)
	{
		qDebug("NET::SkipPager");
		return;
	}
	if(st & NET::KeepBelow)
	{
		qDebug("NET::KeepBelow");
		return;
	}
	qDebug("ST=%ld",st);
	qDebug("Looking for transient...");
	//test if this window is not a transient, meanu for ex. a menu popup
	NETWinInfo infoTest2(qt_xdisplay(), window, qt_xrootwin(),win_properties_trans,sizeof(win_properties_trans)/sizeof(unsigned long));

	if(infoTest2.transientFor()!=0)
	{
		qDebug("is Transient for other windows...");
		return;
	}

        //qWarning("about _%d_",(int)window);
	NETWinInfo info(qt_xdisplay(), window, qt_xrootwin(),win_properties_name,sizeof(win_properties_name)/sizeof(unsigned long));
        //qWarning("about P1_%d_",(int)window);
	//if(info==0)return;
	if(info.windowClassName()==0)return;
        //qWarning("about P2_%d_",(int)window);
	if(strcmp(info.windowClassName(),XQDESTRING)==0)return;
        //qWarning("about P3_%d_",(int)window);

	// BufferStrings to avoid crash
	QString windowClassName=QString::fromUtf8(info.windowClassName());
	QString windowClassClass=QString::fromUtf8(info.windowClassClass());
	//froAscii(), fromLatin1(), fromUtf8(), and fromLocal8Bit()
	QString title=QString::fromUtf8(info.name(),-1);
	//get the Icon of the active window
	QImage taskQIcon = GetWMIcon(window, DesktopEnvironment->GUI.sizeIconsMax , DesktopEnvironment->GUI.sizeIconsMax );

	int WindowPid=info.pid();
	

        qWarning("safe position gained! %d (pid %d)",(int)window, WindowPid);
	// now the window can be closed!
	

	if(DesktopEnvironment->GUI.task_GroupByPID)
	{
		// first we test for pid (wow what great idea aahhahahha)
		XQDEIcon *iconPidded=Basket->getViaPID(WindowPid);
		if(iconPidded!=NULL)
		{
				iconPidded->clientsData()->append((void *)window);
				Basket->sgeBasket_As_Changed(5,iconPidded,(void *)window);
				//prepare the new icon to X11 damage events
				prepareDamage(iconPidded, window);
				return;
		}
		else
		{
		}
	}
	
	if(DesktopEnvironment->GUI.task_GroupSimilarWindows)
	{
		// check for existing basket:
		{
		// elsewhere
		for(int i=0;i<Basket->items.size();i++)
		{
			XQDEIcon *icon=Basket->items.at(i);
			
			if(windowClassName.indexOf(icon->logic())>=0)
			{
				// match
				icon->clientsData()->append((void *)window);
				icon->pidsData()->append((void *)WindowPid);
				Basket->sgeBasket_As_Changed(5,icon,(void *)window);
				//prepare the icon to X11 damage events
				prepareDamage(icon, window);
				return;
			}
		}
		}
	}
	// now we test if there is the first window of a "static" icon
		// check for existing basket:
        //Feature: add the possibility to skip the task grouping
        for(int i=0;i<Basket->items.size();i++)
        {
            XQDEIcon *icon=Basket->items.at(i);
            if((windowClassName.indexOf(icon->logic())>=0 ) &&
                (icon->clientsData()->size()<1 || icon->groupWindows>0)) {
                    // match
                    //qWarning("First window of static icon:%d [%d]",i,(int)window);
                    icon->clientsData()->append((void *)window);
                    XQDEIcon *iconPidded=Basket->getViaPID(WindowPid);
                    if(iconPidded==NULL)icon->pidsData()->append((void *)WindowPid);

                    icon->xSetTitle(title);
                    // ok than? we need to attach the userAction!!!
                    disconnect (icon,SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)),this,SLOT(userAction(int,int,int,void *,XQDEIcon *)));
                    connect (icon,SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)),this,SLOT(userAction(int,int,int,void *,XQDEIcon *)));
                    disconnect(icon,SIGNAL(setGeometry(void *,int,int,int)),this,SLOT(setGeometry(void *,int,int,int)));
                    connect(icon,SIGNAL(setGeometry(void *,int,int,int)),SLOT(setGeometry(void *,int,int,int)));


                    disconnect(icon,SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)),this,SLOT(userAction(int,int,int,void *,XQDEIcon *)));
                    connect(icon,SIGNAL(sguserAction(int,int,int,void *,XQDEIcon *)),this,SLOT(userAction(int,int,int,void *,XQDEIcon *)));

                    disconnect(icon,SIGNAL(fillPopup(QMenu *,XQDEIcon *)),this,SLOT(fillPopup(QMenu *,XQDEIcon *)));
                    connect(icon,SIGNAL(fillPopup(QMenu *,XQDEIcon *)),this,SLOT(fillPopup(QMenu *,XQDEIcon *)));

                    setGeometry((void *)window,icon->iconGeometry.x+MainWindow->x(),icon->iconGeometry.y+MainWindow->y(),icon->iconGeometry.z);

                    Basket->sgeBasket_As_Changed(5,icon,(void *)window);

		    //prepare the icon to X11 damage events
		    prepareDamage(icon, window);
                    return;
            }
        }

	XQDEIcon *addedIcon=0;
	// check for existing template:
	addedIcon=Basket->findTemplate(title,windowClassName,this);

//        for(int i=0;i<Basket->templates.size();i++)
//        {
//                XQDEIcon *icon=Basket->templates.at(i);
//                if(windowClassName.indexOf(icon->logic()) >= 0) addedIcon=Basket->clone(icon,this);
//        }

	if(addedIcon==0)
	{
		addedIcon=Basket->AddtoBasket(
		this,(void *)window,
		windowClassName,
		windowClassClass,
		title,
		&taskQIcon);
		
	}
	else
	{
		addedIcon->clientsData()->append((void *)window);

		addedIcon->xSetTitle(title);
		addedIcon->xReset();
		Basket->items.append(addedIcon);
		Basket->sgeBasket_As_Changed(1, addedIcon, NULL);
	}

	// new taskmanagement width pids
	XQDEIcon *iconPidded=Basket->getViaPID(WindowPid);
	if(iconPidded==NULL)addedIcon->pidsData()->append((void *)WindowPid);
	
//	bool hadconnected=connect(addedIcon,SIGNAL(setGeometry(void *,int,int,int)),SLOT(setGeometry(void *,int,int,int)));
	//qWarning("New added icon is %ld and %d",(long)addedIcon,hadconnected);
	
	addedIcon->xSetParent(this);
	timer_slotPollingPID->start(TSKPOLLINGRATE);

	//prepare the new icon to X11 damage events
	prepareDamage(addedIcon, window);

	/*
	// debug WMData
	//qWarning("*** New windows has being added: %d***",(int)window);
	//qWarning("*allowedActions:%d",info.allowedActions());
	//qWarning("*desktop:%d",info.desktop());
	//qWarning("*handledIcons:%d",info.handledIcons());
	//qWarning("*hasNETSupport:%d",info.hasNETSupport());
	//qWarning("*iconName:%s",info.iconName());
	//qWarning("*mappingState:%d",info.mappingState());
	//qWarning("*name:%s",info.name());
	//qWarning("*pid:%d",info.pid());
	//qWarning("*startupId:%d",info.startupId());
	//qWarning("*state:%d",info.state());
	//qWarning("*strut:%d",info.strut());
	//qWarning("*visibleIconName:%s",info.visibleIconName());
	//qWarning("*visibleName:%s",info.visibleName());
	//qWarning("*windowClassClass:%s",info.windowClassClass());
	//qWarning("*windowClassName:%s",info.windowClassName());
	//qWarning("*windowRole:%d",info.windowRole());
	//qWarning("*wmName:%s",wmName());
	//qWarning("*activeWindow:%d",activeWindow());
	//qWarning("*currentDesktop:%d",currentDesktop());
	//qWarning("*numberOfDesktops:%d",numberOfDesktops());
	//qWarning("*virtualRootsCount:%d",virtualRootsCount());
	//qWarning("*virtualRoots:%d",(int)virtualRoots());
	//qWarning("*desktopName:%s",desktopName(currentDesktop()));
	//qWarning("*screenNumber:%d",screenNumber());
	//qWarning("*desktopViewport:%dx%d",desktopViewport(currentDesktop()).x,desktopViewport(currentDesktop()).y);
	char* c = 0;
	if ( XFetchName( qt_xdisplay(), window, &c ) != 0 )
	{
		//qWarning("#XFetchName %s",c);
		XFree( c );
	}
	XClassHint hint;
	if( XGetClassHint( qt_xdisplay(), window, &hint )) {
	//qWarning("#XGetClassHint [%s][%s]",
		hint.res_class,
		hint.res_name);
	}
	*/
}

void XQDESensor_TaskManager::prepareDamage(XQDEIcon *iconToDamage, Window window)
{
    XCompositeRedirectSubwindows(QX11Info::display(),
				 window,
				 CompositeRedirectAutomatic);
    XShapeSelectInput(QX11Info::display(), window, ShapeNotifyMask);
    XSelectInput( QX11Info::display(), window, StructureNotifyMask ); //I'm interessed to get resize events for the windows
    Damage damage = XDamageCreate(QX11Info::display(), window, XDamageReportNonEmpty);
    Q_UNUSED(damage);

    XWindowAttributes attr;

    //!! XGetWindowAttributes is a synchronous call (it blocks) !!
    XGetWindowAttributes( QX11Info::display(), window, &attr );

    int x                     = attr.x;
    int y                     = attr.y;
    int width                 = attr.width;
    int height                = attr.height;

    //save the size of the windows to use in the feature
//	QRect m_position = new QRect(x,y,width,height);
    iconToDamage->setAttachedWindowsPosition(QRect(x,y,width,height));
}

void XQDESensor_TaskManager::slotAddClient()
{
	if(pendingWindows.size()<1)
	{
		timer_slotAddClient->stop();
		return;
	}
	Window window=pendingWindows.takeAt(0);

	postAddClient(window);
}

void XQDESensor_TaskManager::slotPollingPID()
{
	timer_slotPollingPID->stop();
	int k=0;
	for(int i=0;i<Basket->items.size();i++)
	{
			XQDEIcon *icon=Basket->items.at(i);
			if(icon==NULL)continue;
				
		if(icon->pidsData()->size()<1)continue;
		if(icon->clientsData()->size()>0)
		{
			k++;
			continue;
		}
			
		for(int pidi=0;pidi<icon->pidsData()->size();pidi++)
		{
			long piddu=(long)icon->pidsData()->at(pidi);
			if(!piddu)continue;
			if(PIDisRunning(piddu)>0)
			{
				k++;
				//qWarning("%ld %ld running",(long)icon,(long)piddu);
			}
			else
			{
				icon->pidsData()->takeAt(pidi);
				//qWarning("%ld %ld not running",(long)icon,(long)piddu);
				pidi--;
			}
		}
		if(icon->pidsData()->size()<1)
		{
			//qWarning("Last pid of %ld has being terminated",(long)icon);
			Basket->DelFromBasket(icon);
			timer_slotPollingPID->start(TSKPOLLINGRATE);
			
			return;
		}
	}
	if(k>0)timer_slotPollingPID->start(TSKPOLLINGRATE);
}

void XQDESensor_TaskManager::xReset()
{
	//pidManager=new XQDESensor_PidManager();
	timer_slotPollingPID=new QTimer(this);
	connect(timer_slotPollingPID,SIGNAL(timeout()),SLOT(slotPollingPID()));
	timer_slotAddClient=new QTimer(this);
	connect(timer_slotAddClient,SIGNAL(timeout()),SLOT(slotAddClient()));
        timer_slotupdateStackingOrder=new QTimer(this);
        connect(timer_slotupdateStackingOrder,SIGNAL(timeout()),SLOT(slotupdateStackingOrder()));
	activate();

        //Todo: don't use the timer but Tracking changes with "damage" X11 function
        timer_slotupdateThumbnail=new QTimer(this);
        connect(timer_slotupdateThumbnail,SIGNAL(timeout()),SLOT(slotupdateThumbnail()));
	activate();

}

void XQDESensor_TaskManager::updateIcon(XQDEIcon *ip, Window window)
{
	NETWinInfo info(qt_xdisplay(), window, qt_xrootwin(),NET::WMName);
	ip->xSetTitle(QString::fromUtf8(info.name(),-1));
}

void XQDESensor_TaskManager::fillPopup(QMenu *m, XQDEIcon *ip)
{
	if(ip->clientData())
	{
		m->addSeparator();
		for(int i=0;i<ip->clientsData()->size();i++)
		{
                        updateIcon(ip, (Window) ip->clientsData()->at(i));
                        QString vTitle=ip->title();
                        if(vTitle.length()<1)vTitle=ip->logic();
                                // ToDo port to ip->localIconImageWM
                        QAction *a=m->addAction(QIcon(DesktopEnvironment->Theme.findImage(ip->icon())),vTitle);
                        if(a)
                        {
                                qulonglong dataint=(qulonglong)(ip->clientsData()->at(i));
                                a->setData(dataint);
                        }
		}
		disconnect(m,SIGNAL(triggered(QAction *)));
		connect(m,SIGNAL(triggered(QAction *)),SLOT(triggered(QAction *)));
	}
	if(ip->pidsData())
	{
		m->addSeparator();
		for(int i=0;i<ip->pidsData()->size();i++)
		{
			QString vTitle=QString("kill %1").arg((long)ip->pidsData()->at(i));
			QAction *a=m->addAction(QIcon(DesktopEnvironment->Theme.findImage("kill")),vTitle);
			if(a)
			{
				qulonglong dataint=(qulonglong)(ip->pidsData()->at(i));
				a->setData(dataint);
			}
		}
		disconnect(m,SIGNAL(triggeredKill(QAction *)));
		connect(m,SIGNAL(triggered(QAction *)),SLOT(triggeredKill(QAction *)));
	}
}

void XQDESensor_TaskManager::triggeredKill(QAction *a)
{	
	QProcess::startDetached(a->text());
}

void XQDESensor_TaskManager::triggered(QAction *a)
{
	Helper_ActiveOrMinimizeWindow((Window)a->data().toLongLong ());
	// now we move to the top of the stack!
	XQDEIcon *ip=Basket->getViaData((void *)a->data().toLongLong (),this);
	if(ip)
	{
		int oldIndex=ip->clientsData()->indexOf((void *)a->data().toLongLong ());
		if(oldIndex>0)ip->clientsData()->move(oldIndex,0);
	}
}


void XQDESensor_TaskManager::Helper_ActiveOrMinimizeWindow(Window window)
{
	NETWinInfo info(qt_xdisplay(), window,qt_xrootwin(),win_properties,sizeof(win_properties)/sizeof(unsigned long));
////qWarning("Helper_ActiveOrMinimizeWindow(Window %d)[%d]=[%d]",(int)window,info.state(),info.state()^NET::Hidden);
	//qWarning("activeWindow()=%d",(int)lastActiveWindow);
	if((info.state() & NET::Hidden  || info.state() & NET::Shaded  || info.mappingState() ==NET::Iconic )|| lastActiveWindow!=window)
	{
		//qWarning("Helper_ActiveOrMinimizeWindow(%d) raise...",(int)window);
/*
		XMapWindow( qt_xdisplay(), window );
		NETRootInfo info( qt_xdisplay(), NET::Supported );
		if( info.isSupported( NET::WM2RestackWindow ))
			info.restackRequest( window, None, Above );
		else
			XRaiseWindow( qt_xdisplay(), window );
*/
        setActiveWindow(window);
	}
	else
	{
		//qWarning("Helper_ActiveOrMinimizeWindow(%d) minimize...",(int)window);
		XIconifyWindow( qt_xdisplay(), window, qt_xscreen() );
	}
}

void XQDESensor_TaskManager::Helper_RollDown(XQDEIcon *ic)
{
	if(!ic)return;
	if(ic->clientsData()->count()<1)return;
	void *w=ic->clientsData()->takeFirst();
	ic->clientsData()->append(w);
	setActiveWindow((Window)ic->clientData());
}

void XQDESensor_TaskManager::Helper_RollUp(XQDEIcon *ic)
{
	if(!ic)return;
	if(ic->clientsData()->count()<1)return;
	void *w=ic->clientsData()->takeLast();
	ic->clientsData()->insert(0,w);
	setActiveWindow((Window)ic->clientData());
}

void XQDESensor_TaskManager::userAction(int XQDE_USER_ACTION_ENUM,int dx,int dy,void *cData, XQDEIcon *ic)
{
//	qWarning("void XQDESensor_TaskManager::userAction(int %d,int %d,int %d,void *%d)",XQDE_USER_ACTION_ENUM,dx,dy,(int)cData);

	Window window=(Window)cData;
	if(cData==0 && ic!=0)ic->userActionDefault( XQDE_USER_ACTION_ENUM,dx,dy);

	switch(XQDE_USER_ACTION_ENUM)
	{
		case XQDE_USER_ACTION_CLICKSX:
			Helper_ActiveOrMinimizeWindow(window);
		break;
		case XQDE_USER_ACTION_CLICKDX:
			if(ic!=0)ic->userActionDefault( XQDE_USER_ACTION_ENUM,dx,dy);
		break;
		case XQDE_USER_ACTION_CLICKMI:
			if(ic!=0)ic->userActionDefault( XQDE_USER_ACTION_ENUM,dx,dy);
		break;
		case XQDE_USER_ACTION_CLICKRU:
			Helper_RollUp(ic);
		break;
		case XQDE_USER_ACTION_CLICKRD:
			Helper_RollDown(ic);
		break;
		default:
			if(ic!=0)ic->userActionDefault( XQDE_USER_ACTION_ENUM,dx,dy);
		break;
	};
}


void XQDESensor_TaskManager::addClient(Window window)
{
	if(window==qt_xrootwin())return;
	pendingWindows.append(window);
	//qWarning("void XQDESensor_TaskManager::addClient(Window %d)[%d]", (int)window,pendingWindows.size());
}


void XQDESensor_TaskManager::removeClient(Window window)
{
	//qWarning("void XQDESensor_TaskManager::removeClient(%d)",(int)window);
	int idx=pendingWindows.indexOf(window);	
	if(idx>=0)pendingWindows.takeAt(idx);
	idx=windowsMinimized.indexOf(window);
	if(idx>=0)windowsMinimized.takeAt(idx);
	idx=windows.indexOf(window);
	if(idx>=0)
	{
		windows.takeAt(idx);
	}
		//qWarning("removeClient(%d) sending signal",(int)window);
		void *ptoi=Basket->getViaData((void *)window,this);
		while(ptoi!=NULL)
		{
			//qWarning("sending signal... (%ld)",(long)ptoi);
			Basket->DelFromBasketViaData((void *)window,this);
			ptoi=Basket->getViaData((void *)window,this);
		}	
}


void XQDESensor_TaskManager::slotupdateStackingOrder()
{
	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder()");
	timer_slotupdateStackingOrder->stop();

	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder() XSync");
	XSync(qt_xdisplay(), False);
	//int cc=;
	static QImage dummy;
//	Window mwi=MainWindow->winId();
	windows.clear();
	for (int i =0;i<clientListStackingCount();i++)
	{
	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder() %d/%d",i,clientListStackingCount());
	Window window=clientListStacking()[i];
	//qWarning("Window:%ld",(long)window);
	Atom type_ret;
	int format_ret;
	unsigned long nitems_ret, unused;
	unsigned char *data_ret;
	if (XGetWindowProperty(qt_xdisplay(),window, XInternAtom(qt_xdisplay(),"_NET_WM_STATE", false), 0l, 2048l,
			       False, XA_ATOM, &type_ret, &format_ret,
                               &nitems_ret, &unused, &data_ret) == Success) {
		//qWarning("update _%x_ TEST OK",(int)window);
	}
	else
	{
		//qWarning("update _%x_ TEST failed",(int)window);
		continue;
	}

	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder() Step2 %d",clientListStackingCount());

	int iMinW=windowsMinimized.indexOf(window);

		NETWinInfo info(qt_xdisplay(), window, qt_xrootwin(),win_properties_mini,sizeof(win_properties_mini)/sizeof(unsigned long));
		if((info.state() & NET::Hidden  || info.state() & NET::Shaded  || info.mappingState() & NET::Iconic ))
		{
			if(iMinW<0)
			{
				Basket->setImageViaData( (void *)window,dummy,this);
				windowsMinimized.append(window);
			}
		}
		else
		{
			if(iMinW>-1)
			{
				windowsMinimized.takeAt(iMinW);
			}
		}
		windows.append(window);
	}
	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder() Step3 %d",clientListStackingCount());

	for(;pendingWindows.size();)
	{
		Window w=pendingWindows.takeAt(0);
		if(windows.indexOf(w)<0)continue;
		postAddClient(w);
	}
	//qWarning("void XQDESensor_TaskManager::slotupdateStackingOrder() done %d",clientListStackingCount());
}

void XQDESensor_TaskManager::updateStackingOrder()
{
	timer_slotupdateStackingOrder->start(WINPOLLINGRATE);

}

bool XQDESensor_TaskManager::x11EventFilter( XEvent *event )
{
//qWarning("%10d %d",event->xany.window,windows.indexOf( event->xany.window ));

//    XAnyEvent *ae = reinterpret_cast<XAnyEvent*>(event);
//    if (ae->window == lastActiveWindow) {

    if (event->type == m_damageEvent + XDamageNotify) {
	XDamageNotifyEvent *e = reinterpret_cast<XDamageNotifyEvent*>(event);
	XDamageSubtract(QX11Info::display(), e->damage, None, None);
	if(!timer_slotupdateThumbnail->isActive()){
	    lastActiveWindow=activeWindow();
	    timer_slotupdateThumbnail->start(WINPOLLINGRATE);
	}
    }
    else if (event->type == ConfigureNotify) {
	    XConfigureEvent *e = &event->xconfigure;
	    if(e->window == lastActiveWindow){
		XQDEIcon *ic=Basket->getViaData((void *)lastActiveWindow,this);
		if(ic) ic->setAttachedWindowsPosition(QRect(e->x, e->y, e->width, e->height));
	    }
	}
//}


//    qWarning() << event->xany.window << "  :  " << qt_xrootwin();
	if (event->xany.window == qt_xrootwin() ) {
		unsigned long m[ 5 ];
		NETRootInfo::event( event, m, 5 );
//		qWarning() << m[ PROTOCOLS ];


		if (( m[ PROTOCOLS ] & CurrentDesktop ) ) qDebug("CurrentDesktop");
		if (( m[ PROTOCOLS ] & ActiveWindow )  )
                {
		    qDebug("ActiveWindow");
		    Window thisActive=activeWindow();
		    if(MainWindow->winId()!=thisActive)
		    {
                        lastActiveWindow=thisActive;
                        timer_slotupdateThumbnail->start(WINPOLLINGRATE);
		    }

		    updateStackingOrder();
                                //qWarning("ActiveWindow=%d",(int)lastActiveWindow);
                }
		if ( m[ PROTOCOLS ] & DesktopNames )qDebug("DesktopNames");
		if (( m[ PROTOCOLS ] & NumberOfDesktops ) )qDebug("NumberOfDesktops");
		if ( m[ PROTOCOLS ] & WorkArea )qDebug("WorkArea");
		if ( m[ PROTOCOLS ] & ClientListStacking )
		{
			//qWarning("updateStackingOrder");
	    		updateStackingOrder();
			if(( m[ PROTOCOLS2 ] & WM2ShowingDesktop ))qDebug("WM2ShowingDesktop");
		}
	} else  if ( windows.indexOf( event->xany.window ) != -1 ){
		NETWinInfo ni( qt_xdisplay(), event->xany.window, qt_xrootwin(), 0 );
		unsigned long dirty[ 2 ];
		ni.event( event, dirty, 2 );
//qWarning("%10d %10d %10d %10d %10d",event->xany.window, event->type,event->xproperty.atom,dirty[0],dirty[1]);
		if ( event->type ==PropertyNotify ) {
		if( event->xproperty.atom == XA_WM_HINTS )
			dirty[ NETWinInfo::PROTOCOLS ] |= NET::WMIcon; // support for old icons
		else if( event->xproperty.atom == XA_WM_NAME )
			dirty[ NETWinInfo::PROTOCOLS ] |= NET::WMName; // support for old name
		else if( event->xproperty.atom == XA_WM_ICON_NAME )
			dirty[ NETWinInfo::PROTOCOLS ] |= NET::WMIconName; // support for old iconic name
		}
		if ( (dirty[ NETWinInfo::PROTOCOLS ] & NET::WMStrut) != 0 ) {
/*
		if ( possibleStrutWindows.indexOf( event->xany.window ) == -1 )
			possibleStrutWindows.append( event->xany.window );
*/
		}

		if ( dirty[ NETWinInfo::PROTOCOLS ] || dirty[ NETWinInfo::PROTOCOLS2 ] ) {
/*
		for ( QList<KWinModule>::iterator mit=modules.begin (); mit!=modules.end(); ++mit  ) {
			emit mit.windowChanged( event->xany.window );
			emit mit.windowChanged( event->xany.window, dirty );
			emit mit.windowChanged( event->xany.window, dirty[ NETWinInfo::PROTOCOLS ] );
			if ( (dirty[ NETWinInfo::PROTOCOLS ] & NET::WMStrut) != 0 )
			emit mit.strutChanged();
		}
*/
			//qWarning("windowChanged");
		}

	}
/*
        int old_current_desktop = currentDesktop();
        WId old_active_window = activeWindow();
        int old_number_of_desktops = numberOfDesktops();
        bool old_showing_desktop = showingDesktop();
        
	

    }
*/
    return false;
}
