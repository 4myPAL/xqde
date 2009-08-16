#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMessageBox>


#include "xqdemain.h"
#include "xqde.h"

#include <X11/extensions/Xrender.h>
//#include <X11/Xlib.h>
//#include <X11/Xatom.h>


Display *dpy;
Colormap colormap;
Visual *visual;

bool testARGB()
{
	bool returned=false;
	char *display = 0;
	dpy = XOpenDisplay( display );
	if ( !dpy ) {
	#ifdef ENABLEDEBUGMSG
		qWarning( "cannot connect to X server ");
	#endif
		return returned;
	}
	int screen = DefaultScreen( dpy );
	colormap = 0;
	visual = 0;
	int event_base, error_base;
	if (  XRenderQueryExtension( dpy, &event_base, &error_base ) )
	{
		int nvi;
		XVisualInfo templ;
		templ.screen  = screen;
		templ.depth   = 32;
		templ.c_class = TrueColor;
		XVisualInfo *xvi = XGetVisualInfo( dpy, VisualScreenMask | VisualDepthMask| VisualClassMask, &templ,&nvi);
		for ( int i = 0; i < nvi; i++ ) {
			XRenderPictFormat *format = XRenderFindVisualFormat( dpy, xvi[i].visual );
			if ( format->type == PictTypeDirect && format->direct.alphaMask ) {
				visual = xvi[i].visual;
				colormap = XCreateColormap( dpy, RootWindow( dpy, screen ), visual, AllocNone );
				returned=true;
				break;
			}
		}
	}
	return returned;
}


void SetNullOnAllPointers();


int main(int argc, char *argv[])
{
        Q_INIT_RESOURCE(libxqdebase);
	XQDEMain *app=NULL;
	SetNullOnAllPointers();
        qDebug("XQDE Version %s This is a alpha testing only!",XQDESRCDATE);
        qDebug("You can mail Stefano to xqde@xiaprojects.com");
        qDebug("Updates can be found on http://xqde.xiaprojects.com");

        if(testARGB()==true){
		qWarning("XQDE Will use Composite Extensions!");
                app = new XQDEMain(dpy,argc,argv, Qt::HANDLE( visual ), Qt::HANDLE( colormap ));
        }
        else{
                qWarning("Error: testARGB() cannot find Composite Extensions");
                app = new XQDEMain(dpy,argc,argv);
        }


        if(app->isAppRunning == true) {
            qDebug() << "The application is alredy running!!";
            return 0;
        }

        if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
        }
        app->setQuitOnLastWindowClosed(false);

        app->setApplicationName("xqde");
        app->setOrganizationDomain ("www.xiaprojects.com");
        app->setOrganizationName("XIA Projects 2009");

        //Loading a interface translation, ex: "xqde_it.qm"
        QTranslator appTranslator;
        QString translationFile = ":/translations/xqde_" + QLocale::system().name();
        appTranslator.load(translationFile);
        app->installTranslator(&appTranslator);
        qDebug()<<"Loaded language is: "<<translationFile;

	app->xReset();
	return app->exec();
}
