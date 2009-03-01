//
// C++ Interface: xqdeicon
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEICON_H
#define XQDEICON_H

#include <xqde.h>

#include <xqwidget.h>
#include <xqdeslotsensor.h>
//#include <QImage>
//#include <QList>

#ifndef RESIZEVIAXRENDER
	
#else
	#include <QPixmap>
	void XRenderResizeImage(QPixmap &Source,QPixmap &Dest,int maxDimension);
#endif


class QMenu;
template <typename T> class QList;
extern class XQDEEnvironment *DesktopEnvironment;

struct XQDEIconRect
{
	int x,y,z;
};

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEIcon: public XQWidget
{
Q_OBJECT
public:
// extra vars violates object programming paradigms
	int animationsNextFrameCounter;


// methods
    XQDEIcon(QString logicName,QObject * p=0, void *cData=0,QImage *defaultImg=0, QString strTitle=0, QString defaulticon=0);
    ~XQDEIcon();
	void xRepaintDetached();
	void xRepaintSmall();
	void applyEffects();
	void redoEffects();
	void xSetZoom(int newZoom);
	void xSetSmoothZoom(int newZoom);
	void setLogic(const QString &nl);
	QObject *sensor();
	int isRunning();
	int imageCachedMiniDirty;
	int imageCachedDirty;
	int isReflectionEnabled;
	XQDEIconRect detachedRect;

	QStringList slotsSensorList();
	QString logic();
	QString icon();
	QString title();
#ifndef RESIZEVIAXRENDER
	QImage *imageClean();
	QImage *image();
#else
	QPixmap *imageClean();
	QPixmap *image();
#endif
#ifndef RESIZEVIAXRENDER
void xSetImage(QImage &i);
#else
void xSetImage(QPixmap &i);
#endif
	QList <void *> *clientsData();
	QList <void *> *pidsData();
	void *clientData();
	void setIconGeometry(int x,int y,int z);



	// hi speed access to help drawing
	XQDEIconRect iconGeometry;
	XQDEIconRect imageCachedRect;
	XQDEIconRect imageCachedArrowRect;
	XQDEIconRect imageHotSpot;
	class XQText *overText;
#ifndef RESIZEVIAXRENDER
	QImage imageCachedArrow;
	QImage imageCached;
	QImage imageCachedReflection;
	QImage imageCachedMini;
#else
	QPixmap imageCachedArrowPixmap;
	QPixmap imageCachedArrow;
	QPixmap imageCached;
	QPixmap imageCachedReflection;
	QPixmap imageCachedMini;
	//QPixmap localImagePixmap;
#endif
	int enableIconFromWindow;
	int forceRunning;
	int storeOnExit;
	int enablePreview;
	int groupWindows;
	class QList <class XQDEAnimation *>*animations;
	class QList <XQDESlotSensor *>*slotsSensor;
	class QMap <QString,class XQDEAction *>*actions;
public slots:
	void xSetIconWM(QImage &);
	void xUpdateBroadcast();
	void xReset();
	void xSetIcon(const QString &);
	void xSetParent(QObject *);
	void xSetIcon(QImage &);
	void xSetTitle(const QString &);
	void xGetImage(QImage &);
	void userAction(int,int,int);
	void userActionDefault(int,int,int);
	void menu_setKeepInDock();
	void menu_setRemoveOnExit();
	void menu_newWindow();
	void xConfigure();
	void xConfigurator();
protected:

#ifndef RESIZEVIAXRENDER
	QImage localImage;
	QImage localImageWidthEffects;
	QImage localImageWidthEffectsReflection;
#else
	QPixmap localImage;
	QPixmap localImageWidthEffects;
	QPixmap localImageWidthEffectsReflection;
#endif

	class QWidget *ExternalConfigurator;
	QObject *localParent;
	QList <void *>*ClientData;
	QList <void *>*PIDData;
	QString localIcon;
	QString localTitle;
	QString imageArrow;
	QImage imageArrowImage;
	QImage localThumbnail;
	QImage localIconImage;
	QImage localIconImageWM;
	QImage localIconImage_DrawBuffer;
	QString localLogicName;
	void xRepaint();
	QMenu *ContextPopupMenu;
	void localfillPopup(QMenu *,XQDEIcon *);
signals:
	void sguserAction(int,int,int,void *, XQDEIcon *);
	void setGeometry(void *,int,int,int);
	void fillPopup(QMenu *,XQDEIcon *);
};

#endif
