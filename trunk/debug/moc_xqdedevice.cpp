/****************************************************************************
** Meta object code from reading C++ file 'xqdedevice.h'
**
** Created: Fri Feb 27 23:48:36 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdedevice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdedevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEDevice[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x05,
      48,   44,   11,   11, 0x25,
      71,   69,   11,   11, 0x25,
      87,   11,   11,   11, 0x25,
      99,   12,   11,   11, 0x05,
     123,   44,   11,   11, 0x25,
     142,   69,   11,   11, 0x25,
     156,   11,   11,   11, 0x25,

       0        // eod
};

static const char qt_meta_stringdata_XQDEDevice[] = {
    "XQDEDevice\0\0x,y,z\0interrupt(long,long,long)\0"
    "x,y\0interrupt(long,long)\0x\0interrupt(long)\0"
    "interrupt()\0polling(long,long,long)\0"
    "polling(long,long)\0polling(long)\0"
    "polling()\0"
};

const QMetaObject XQDEDevice::staticMetaObject = {
    { &XQDEIO::staticMetaObject, qt_meta_stringdata_XQDEDevice,
      qt_meta_data_XQDEDevice, 0 }
};

const QMetaObject *XQDEDevice::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEDevice))
        return static_cast<void*>(const_cast< XQDEDevice*>(this));
    return XQDEIO::qt_metacast(_clname);
}

int XQDEDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEIO::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: interrupt((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 1: interrupt((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 2: interrupt((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: interrupt(); break;
        case 4: polling((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 5: polling((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 6: polling((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 7: polling(); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void XQDEDevice::interrupt(long _t1, long _t2, long _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, 3, _a);
}

// SIGNAL 4
void XQDEDevice::polling(long _t1, long _t2, long _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, 7, _a);
}
QT_END_MOC_NAMESPACE
