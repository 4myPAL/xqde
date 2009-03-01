/****************************************************************************
** Meta object code from reading C++ file 'xqdebasket.h'
**
** Created: Fri Feb 27 23:48:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdebasket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdebasket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEBasket[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_XQDEBasket[] = {
    "XQDEBasket\0\0,,\0Basket_As_Changed(int,XQDEIcon*,void*)\0"
};

const QMetaObject XQDEBasket::staticMetaObject = {
    { &XQDEClass::staticMetaObject, qt_meta_stringdata_XQDEBasket,
      qt_meta_data_XQDEBasket, 0 }
};

const QMetaObject *XQDEBasket::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEBasket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEBasket))
        return static_cast<void*>(const_cast< XQDEBasket*>(this));
    return XQDEClass::qt_metacast(_clname);
}

int XQDEBasket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEClass::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void XQDEBasket::Basket_As_Changed(int _t1, XQDEIcon * _t2, void * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
