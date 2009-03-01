/****************************************************************************
** Meta object code from reading C++ file 'xqwfirsthand.h'
**
** Created: Fri Feb 27 23:48:39 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqwfirsthand.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqwfirsthand.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQWFirstHand[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x0a,
      56,   13,   13,   13, 0x0a,
      76,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQWFirstHand[] = {
    "XQWFirstHand\0\0,,\0"
    "Basket_As_Changed(int,XQDEIcon*,void*)\0"
    "slot_mousePolling()\0slot_animationPolling()\0"
};

const QMetaObject XQWFirstHand::staticMetaObject = {
    { &XQWidget::staticMetaObject, qt_meta_stringdata_XQWFirstHand,
      qt_meta_data_XQWFirstHand, 0 }
};

const QMetaObject *XQWFirstHand::metaObject() const
{
    return &staticMetaObject;
}

void *XQWFirstHand::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQWFirstHand))
        return static_cast<void*>(const_cast< XQWFirstHand*>(this));
    return XQWidget::qt_metacast(_clname);
}

int XQWFirstHand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Basket_As_Changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< XQDEIcon*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 1: slot_mousePolling(); break;
        case 2: slot_animationPolling(); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
