/****************************************************************************
** Meta object code from reading C++ file 'xqderoot.h'
**
** Created: Fri Feb 27 23:48:34 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqderoot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqderoot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDERoot[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,    9,    9,    9, 0x0a,
      73,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDERoot[] = {
    "XQDERoot\0\0,\0sgn_GetNamedValue(QString,QString&)\0"
    "PluginRegister(QObject*)\0"
    "PluginUnRegister(QObject*)\0"
};

const QMetaObject XQDERoot::staticMetaObject = {
    { &XQDEClass::staticMetaObject, qt_meta_stringdata_XQDERoot,
      qt_meta_data_XQDERoot, 0 }
};

const QMetaObject *XQDERoot::metaObject() const
{
    return &staticMetaObject;
}

void *XQDERoot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDERoot))
        return static_cast<void*>(const_cast< XQDERoot*>(this));
    return XQDEClass::qt_metacast(_clname);
}

int XQDERoot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sgn_GetNamedValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: PluginRegister((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: PluginUnRegister((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void XQDERoot::sgn_GetNamedValue(const QString & _t1, QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
