/****************************************************************************
** Meta object code from reading C++ file 'xqdeplugin_analogclock.h'
**
** Created: Sat May 1 18:28:04 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "xqdeplugin_analogclock.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeplugin_analogclock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEPlugin_AnalogClock[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      44,   23,   23,   23, 0x05,
      63,   23,   23,   23, 0x05,
      81,   23,   23,   23, 0x05,
     102,   23,   23,   23, 0x05,
     111,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   23,   23,   23, 0x08,
     156,  151,   23,   23, 0x0a,
     173,   23,   23,   23, 0x0a,
     185,   23,   23,   23, 0x0a,
     204,   23,   23,   23, 0x0a,
     223,  221,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEPlugin_AnalogClock[] = {
    "XQDEPlugin_AnalogClock\0\0xSetIconWM(QImage&)\0"
    "xSetTitle(QString)\0xSetIcon(QString)\0"
    "xSetParent(QObject*)\0xReset()\0"
    "xUpdateBroadcast()\0AnalogClockPolling()\0"
    "newI\0attach(QObject*)\0Configure()\0"
    "restore(QDomNode*)\0store(QDomNode*)\0"
    ",\0ConfigurationChanged(void*,int)\0"
};

const QMetaObject XQDEPlugin_AnalogClock::staticMetaObject = {
    { &XQDEPlugin::staticMetaObject, qt_meta_stringdata_XQDEPlugin_AnalogClock,
      qt_meta_data_XQDEPlugin_AnalogClock, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XQDEPlugin_AnalogClock::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XQDEPlugin_AnalogClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XQDEPlugin_AnalogClock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEPlugin_AnalogClock))
        return static_cast<void*>(const_cast< XQDEPlugin_AnalogClock*>(this));
    return XQDEPlugin::qt_metacast(_clname);
}

int XQDEPlugin_AnalogClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEPlugin::qt_metacall(_c, _id, _a);
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
        case 6: AnalogClockPolling(); break;
        case 7: attach((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 8: Configure(); break;
        case 9: restore((*reinterpret_cast< QDomNode*(*)>(_a[1]))); break;
        case 10: store((*reinterpret_cast< QDomNode*(*)>(_a[1]))); break;
        case 11: ConfigurationChanged((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void XQDEPlugin_AnalogClock::xSetIconWM(QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEPlugin_AnalogClock::xSetTitle(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XQDEPlugin_AnalogClock::xSetIcon(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XQDEPlugin_AnalogClock::xSetParent(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XQDEPlugin_AnalogClock::xReset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void XQDEPlugin_AnalogClock::xUpdateBroadcast()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
