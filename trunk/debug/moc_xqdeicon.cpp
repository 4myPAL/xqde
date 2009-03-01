/****************************************************************************
** Meta object code from reading C++ file 'xqdeicon.h'
**
** Created: Fri Feb 27 23:48:42 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeicon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeicon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEIcon[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,
      61,   57,    9,    9, 0x05,
      94,   92,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     122,    9,    9,    9, 0x0a,
     142,    9,    9,    9, 0x0a,
     161,    9,    9,    9, 0x0a,
     170,    9,    9,    9, 0x0a,
     188,    9,    9,    9, 0x0a,
     209,    9,    9,    9, 0x0a,
     227,    9,    9,    9, 0x0a,
     246,    9,    9,    9, 0x0a,
     268,  265,    9,    9, 0x0a,
     292,  265,    9,    9, 0x0a,
     323,    9,    9,    9, 0x0a,
     344,    9,    9,    9, 0x0a,
     367,    9,    9,    9, 0x0a,
     384,    9,    9,    9, 0x0a,
     397,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEIcon[] = {
    "XQDEIcon\0\0,,,,\0sguserAction(int,int,int,void*,XQDEIcon*)\0"
    ",,,\0setGeometry(void*,int,int,int)\0,\0"
    "fillPopup(QMenu*,XQDEIcon*)\0"
    "xSetIconWM(QImage&)\0xUpdateBroadcast()\0"
    "xReset()\0xSetIcon(QString)\0"
    "xSetParent(QObject*)\0xSetIcon(QImage&)\0"
    "xSetTitle(QString)\0xGetImage(QImage&)\0"
    ",,\0userAction(int,int,int)\0"
    "userActionDefault(int,int,int)\0"
    "menu_setKeepInDock()\0menu_setRemoveOnExit()\0"
    "menu_newWindow()\0xConfigure()\0"
    "xConfigurator()\0"
};

const QMetaObject XQDEIcon::staticMetaObject = {
    { &XQWidget::staticMetaObject, qt_meta_stringdata_XQDEIcon,
      qt_meta_data_XQDEIcon, 0 }
};

const QMetaObject *XQDEIcon::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEIcon))
        return static_cast<void*>(const_cast< XQDEIcon*>(this));
    return XQWidget::qt_metacast(_clname);
}

int XQDEIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sguserAction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< void*(*)>(_a[4])),(*reinterpret_cast< XQDEIcon*(*)>(_a[5]))); break;
        case 1: setGeometry((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: fillPopup((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< XQDEIcon*(*)>(_a[2]))); break;
        case 3: xSetIconWM((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 4: xUpdateBroadcast(); break;
        case 5: xReset(); break;
        case 6: xSetIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: xSetParent((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 8: xSetIcon((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 9: xSetTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: xGetImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 11: userAction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: userActionDefault((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: menu_setKeepInDock(); break;
        case 14: menu_setRemoveOnExit(); break;
        case 15: menu_newWindow(); break;
        case 16: xConfigure(); break;
        case 17: xConfigurator(); break;
        }
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void XQDEIcon::sguserAction(int _t1, int _t2, int _t3, void * _t4, XQDEIcon * _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEIcon::setGeometry(void * _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XQDEIcon::fillPopup(QMenu * _t1, XQDEIcon * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
