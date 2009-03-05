//
// C++ Interface: xqdebasket
//
// Description: 
//
//
// Author: Stefano Zingarini <stefano@xiaprojects.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef XQDEBASKET_H
#define XQDEBASKET_H

#include "xqdeclass.h"
#include "xqdeicon.h"

/*
#include <QWidget>
#include <QList>
#include <QMap>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
*/


class XQDEPlugin;

/**
	@author Stefano Zingarini <stefano@xiaprojects.com>
*/
class XQDEBasket : public XQDEClass
{
Q_OBJECT
public:
    XQDEBasket(XQDEClass *parent = 0);
    ~XQDEBasket();
	QList<XQDEIcon *> items;
	QList<XQDEIcon *> templates;
	XQDEIcon *AddtoBasket(QObject *SensorManager=0,void *cData=0,QString ClassClass="", QString cn="", QString title="", QImage *defaultIcon=0, QString defaultIconFile="");

	XQDEIcon *AddtoBasketWidget(QObject *SensorManager=0,void *cData=0,XQDEPlugin *WidgetClass=0, QString title="");

	XQDEIcon *getViaPID(long);

	void DelFromBasket(XQDEIcon *cData,int WithOutAnimation=0);
	void DelFromBasketViaData(void *,int WithOutAnimation=0);
	void DelFromBasketViaData(void *, QObject *, int WithOutAnimation=0);
	XQDEIcon *getViaData(void *);
	XQDEIcon *getViaData(void *, QObject *);
	void setImageViaData(void *,QImage &);
	void setImageViaData(void *,QImage &, QObject *);
	void setTitleViaData(void *,QString &, QObject *);
	void sgeBasket_As_Changed(int,XQDEIcon*,void*);
	XQDEIcon *getViaLogicName(const QString &);
	void FreezeSave(const QString &);
	void FreezeRestore(const QString &);
	void iconExport(XQDEIcon *, const QString &);
	XQDEIcon *iconImport(const QString &);
	XQDEIcon *clone(XQDEIcon *, QObject  *cloneSender);
	XQDEIcon *findTemplate(QString &, QString &,QObject *cloneSender=0);
signals:
	void Basket_As_Changed(int,XQDEIcon*,void*);
protected:
	void FreezeRestoreLoadFromandStoreTo(class QDir *,QList<XQDEIcon *> *);
//        void dockWindow( Window w, Window owner );
//        void withdrawWindow( Window w );
//        static Atom makeSelectionAtom();
//        QList< Window > pending_windows;
//        QList< Window > tray_windows;
//        QMap< Window, unsigned long > docked_windows;
};
extern XQDEBasket *Basket;
#endif
