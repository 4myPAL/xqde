#include <QtGui>


#include "libxqdebase.h"
#include "xqdeenvironment.h"
#include "xqtext.h"
#include "import_netwm.h"
#include "xqderuler.h"

//#include <xqwfirsthand_left.h>
#include "xqwfirsthand_bottom.h"
//#include <xqwfirsthand_right.h>
//#include <xqwfirsthand_top.h>



//#include <xqimageautozoom.h>
//#include <xqimage.h>
//#include <xqdepuzzle.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xatom.h>
//
//
//#include <QX11Info>

#define qt_xdisplay() QX11Info::display ()
#define qt_xrootwin() QX11Info::appRootWindow()


void XQDEBase::xReset()
{
	qWarning("XQDEBase::xReset() begin %ld",DesktopEnvironment->GUI.dockAlign);
	//exit(1);
	XQWFirstHand	*firstHand=NULL;
	switch(DesktopEnvironment->GUI.dockAlign)
	{
		case 0:// 0 bottom
			firstHand=new XQWFirstHand_bottom(NULL,NULL);
		break;
		case 1:// 1 top
//			firstHand=new XQWFirstHand_top(NULL,NULL);
		break;
		case 2:// 2 left
//			firstHand=new XQWFirstHand_left(NULL,NULL);
		break;
		case 3:// 3 right
//			firstHand=new XQWFirstHand_right(NULL,NULL);
		break;
	}
	if(firstHand==NULL)
	{
		qWarning("Wrong configuration detected... %ld" ,DesktopEnvironment->GUI.dockAlign);
		exit(1);
	}
		
	firstHand->xReset();
	firstHand->xRepaint();
	firstHand->show();
	XQPillow *mPillow=new XQPillow(firstHand,2);
	mPillow->xReset();
	mPillow->xRepaint();
	qWarning("XQDEBase::xReset() end");	
}


XQDEBase::XQDEBase(XQDEClass *p):XQWidget(p,NULL)
{
qWarning("XQDEBase::XQDEBase()");


	return;
/*
	XQDERuler *ruler=new XQDERuler();

	for(int i=0;i<1;i++)
	{
		XQImageAutoZoom *x=NULL;
		x=new XQImageAutoZoom(NULL,NULL);

		int cx=0;
		int cy=0;
		ruler->firstFit(DesktopEnvironment->GUI.sizeIconsMax,cx,cy);
		qWarning("[%d][%d][%d]",(int)DesktopEnvironment->GUI.sizeIconsMax,(int)cx,(int)cy);
		ruler->lock(x,cx,cy,DesktopEnvironment->GUI.sizeIconsMax);

		x->setRect(cx,cy,cx+DesktopEnvironment->GUI.sizeIconsMax,cy+DesktopEnvironment->GUI.sizeIconsMax);
		x->setFixedSize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);

		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/Microphone.png",XQImage_Normal);
		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/orange.png",XQImage_Clicked);

		x->show();
	}





//kapp->installX11EventFilter( this );
//	(void ) kapp->desktop(); //trigger desktop widget creation to select root window events



//	resize(DesktopEnvironment->GUI.sizeIconsMax*5,DesktopEnvironment->GUI.sizeIconsMax*2);
	move(50,150);

	// fill the widgets


	int y=0;
/--*
	for(int i=0;i<2;i++)
	{
		XQImage *x=NULL;
		x=new XQImage(NULL,NULL);
		x->setPos(i*DesktopEnvironment->GUI.sizeIconsMax,y*DesktopEnvironment->GUI.sizeIconsMax);
		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/lime.png");
//		x->resize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
		globalXQDEWidgets.append(x);
		x->show();

	}
	for(int i=0;i<2;i++)
	{
		XQText *x=NULL;
		x=new XQText(NULL,NULL);
		x->xSetFontStyle(&DesktopEnvironment->GUI.desktopFont);
		x->setPos(i*DesktopEnvironment->GUI.sizeIconsMax,y*DesktopEnvironment->GUI.sizeIconsMax);

		x->xSetText(QString("Ciao sono una icona %1").arg(i));
		x->xDrawText();
		//globalXQDEWidgets.append(x);
		x->show();
	}

	for(int i=2;i<5;i++)
	{
		XQImage *x=NULL;
		x=new XQImage(NULL,NULL);
		x->setRect(i*DesktopEnvironment->GUI.sizeIconsMax,y*DesktopEnvironment->GUI.sizeIconsMax,(i+1)*DesktopEnvironment->GUI.sizeIconsMax,(y+1)*DesktopEnvironment->GUI.sizeIconsMax);
		x->setFixedSize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);
		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/lime.png");
		globalXQDEWidgets.append(x);
	}

	y++;
	*---/
qWarning("Numero screens: %d (%d)",QApplication::desktop()->numScreens(),QApplication::desktop()->availableGeometry().width());
	for(int i=0;i<5;i++)
	{
		XQImageAutoZoom *x=NULL;
		x=new XQImageAutoZoom(NULL, QApplication::desktop()->screen());
		x->setRect(i*(DesktopEnvironment->GUI.sizeIconsMax+10),y*DesktopEnvironment->GUI.sizeIconsMax,(i+1)*DesktopEnvironment->GUI.sizeIconsMax,(y+1)*DesktopEnvironment->GUI.sizeIconsMax);
		x->setFixedSize(DesktopEnvironment->GUI.sizeIconsMax,DesktopEnvironment->GUI.sizeIconsMax);

		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/Microphone.png",XQImage_Normal);
		x->setImage("/mnt/documenti/users/stefano/mirror/temi/icone/orange.png",XQImage_Clicked);
		//x->setPos(i*DesktopEnvironment->GUI.sizeIconsMax,y*DesktopEnvironment->GUI.sizeIconsMax);
		//globalXQDEWidgets.append(x);
		//x->repaint();
		x->show();
	}
/--*
	XQDEPuzzle *puzzle=new XQDEPuzzle(NULL,NULL);
	puzzle->import("");
	puzzle->show();
*/
	//puzzle->append();
	//globalXQDEWidgets.append(puzzle);
	/*iBuffer.create(width(),height(),32);
	iBuffer.setAlphaBuffer(false);
	iBuffer.fill(0);
	iBuffer.setAlphaBuffer(true);
	*---/
//  setFocusPolicy( StrongFocus );
//  viewport()->setFocusPolicy( StrongFocus );
	
	//setGeometry( QApplication::desktop()->geometry() );
//NETRootInfo wmNet(qt_xdisplay(),0);
//wmNet.setCurrentDesktop(2);

	qWarning("Desktop widget will be: %dx%d",width(),height());

	iBuffer=QImage(width(),height(),QImage::Format_ARGB32);
	//iBuffer.fill(0xef0012800);
	pBuffer.begin(&iBuffer);
	paint(pBuffer);
	pBuffer.end();
	paintBuffer=iBuffer;
	repaint();
	lower();
	show();

/--*
	unsigned long data[2];
	data[0] = (unsigned long) 1;
	data[1] = (unsigned long) 0; // None; (Werner)
	Atom wm_state = XInternAtom(qt_xdisplay(), "WM_STATE", False);
	XChangeProperty(qt_xdisplay(), winId(), wm_state, wm_state, 32,PropModeReplace, (unsigned char *)data, 2);
*--/

	return;
	

/--*
    TaskList taskList = KDETaskManager->tasks();
    Task* task;
    for (task = taskList.first(); task; task = taskList.next())
    {
    	taskAdded(task);
    }
*--/
*/
}

XQDEBase::~XQDEBase()
{
}

void XQDEBase::paintEvent(QPaintEvent *e)
{
	XQWidget::paintEvent(e);
return;
/*
	QPainter p;
/--*
	p.begin(this);
		p.setCompositionMode(QPainter::CompositionMode_Clear);
		p.setBackground (QBrush(QColor(255,0,0,128)));
		p.eraseRect (0,0,width(),height());
	p.end();
*--/
//return;

	p.begin(this);
	//p.setBackground (QBrush(QColor(255,0,0,128)));
	//p.eraseRect (0,0,width(),height());
//	p.setBackgroundMode(Qt::OpaqueMode);
	p.fillRect(0,0,width(),height(),QBrush(QColor(255,0,0,128)));
	p.drawImage(QPoint(0,0),iBuffer);
	p.end();
*/
}

void XQDEBase::paint(QPainter &p)
{
	for (int i = 0; i < globalXQDEWidgets.size(); ++i)
	{
		globalXQDEWidgets.at(i)->paint(p);
	}
}
