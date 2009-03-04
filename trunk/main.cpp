#include <QLocale>
#include <QTranslator>

#include <xqdemain.h>
#include <xqde.h>
//#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>
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
	XQDEMain *app=NULL;
	SetNullOnAllPointers();
	qWarning("XQDE Version %s This is a alpha testing only!",XQDESRCDATE);
	qWarning("You can mail Stefano to xqde@xiaprojects.com");
	qWarning("Updates can be found on http://xqde.xiaprojects.com");

	if(testARGB()==true){
		qWarning("XQDE Will use Composite Extensions!");
		app = new XQDEMain(dpy,argc,argv, Qt::HANDLE( visual ), Qt::HANDLE( colormap ));
	}
	else{
		qWarning("Error: testARGB() cannot find Composite Extensions");
		app = new XQDEMain(dpy,argc,argv);
	}
	QCoreApplication::setApplicationName("xqde");
	//app->setName("xqde");
	QCoreApplication::setOrganizationDomain ("www.xiaprojects.com");
        QCoreApplication::setOrganizationName("XIA Projects 2009");

        //Load translation, ex. file: trans_Italian.ts
        QTranslator translator;
        QString translationFile = QLocale::languageToString(QLocale::system().language());
        translationFile = ":/trans_"+translationFile+".ts";
        translator.load(translationFile);
        app.installTranslator(&translator);

	app->xReset();
	return app->exec();
}
