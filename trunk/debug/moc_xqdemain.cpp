/****************************************************************************
** Meta object code from reading C++ file 'xqdemain.h'
**
** Created: Fri Feb 27 23:48:34 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdemain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdemain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEMain[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEMain[] = {
    "XQDEMain\0\0,,\0Basket_As_Changed(int,XQDEIcon*,void*)\0"
};

const QMetaObject XQDEMain::staticMetaObject = {
    { &XQUniqueApplication::staticMetaObject, qt_meta_stringdata_XQDEMain,
      qt_meta_data_XQDEMain, 0 }
};

const QMetaObject *XQDEMain::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEMain))
        return static_cast<void*>(const_cast< XQDEMain*>(this));
    return XQUniqueApplication::qt_metacast(_clname);
}

int XQDEMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQUniqueApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Basket_As_Changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< XQDEIcon*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
