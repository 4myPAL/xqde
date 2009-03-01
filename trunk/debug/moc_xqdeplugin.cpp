/****************************************************************************
** Meta object code from reading C++ file 'xqdeplugin.h'
**
** Created: Fri Feb 27 23:48:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEPlugin[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      32,   11,   11,   11, 0x05,
      51,   11,   11,   11, 0x05,
      69,   11,   11,   11, 0x05,
      90,   11,   11,   11, 0x05,
      99,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,  118,   11,   11, 0x0a,
     140,   11,   11,   11, 0x0a,
     152,   11,   11,   11, 0x0a,
     171,   11,   11,   11, 0x0a,
     190,  188,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEPlugin[] = {
    "XQDEPlugin\0\0xSetIconWM(QImage&)\0"
    "xSetTitle(QString)\0xSetIcon(QString)\0"
    "xSetParent(QObject*)\0xReset()\0"
    "xUpdateBroadcast()\0newI\0attach(QObject*)\0"
    "Configure()\0restore(QDomNode*)\0"
    "store(QDomNode*)\0,\0ConfigurationChanged(void*,int)\0"
};

const QMetaObject XQDEPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XQDEPlugin,
      qt_meta_data_XQDEPlugin, 0 }
};

const QMetaObject *XQDEPlugin::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEPlugin))
        return static_cast<void*>(const_cast< XQDEPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int XQDEPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: xSetIconWM((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: xSetTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: xSetIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: xSetParent((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 4: xReset(); break;
        case 5: xUpdateBroadcast(); break;
        case 6: attach((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: Configure(); break;
        case 8: restore((*reinterpret_cast< QDomNode*(*)>(_a[1]))); break;
        case 9: store((*reinterpret_cast< QDomNode*(*)>(_a[1]))); break;
        case 10: ConfigurationChanged((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void XQDEPlugin::xSetIconWM(QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEPlugin::xSetTitle(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XQDEPlugin::xSetIcon(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XQDEPlugin::xSetParent(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XQDEPlugin::xReset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void XQDEPlugin::xUpdateBroadcast()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
