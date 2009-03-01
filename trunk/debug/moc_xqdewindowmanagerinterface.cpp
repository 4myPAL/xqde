/****************************************************************************
** Meta object code from reading C++ file 'xqdewindowmanagerinterface.h'
**
** Created: Fri Feb 27 23:48:40 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdewindowmanagerinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdewindowmanagerinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEWindowManagerInterface[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      30,   28,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEWindowManagerInterface[] = {
    "XQDEWindowManagerInterface\0\0,\0"
    "setOnAllDesktops(WId,bool)\0"
};

const QMetaObject XQDEWindowManagerInterface::staticMetaObject = {
    { &XQDEClass::staticMetaObject, qt_meta_stringdata_XQDEWindowManagerInterface,
      qt_meta_data_XQDEWindowManagerInterface, 0 }
};

const QMetaObject *XQDEWindowManagerInterface::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEWindowManagerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEWindowManagerInterface))
        return static_cast<void*>(const_cast< XQDEWindowManagerInterface*>(this));
    return XQDEClass::qt_metacast(_clname);
}

int XQDEWindowManagerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setOnAllDesktops((*reinterpret_cast< WId(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
