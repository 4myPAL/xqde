/****************************************************************************
** Meta object code from reading C++ file 'xqdeclass.h'
**
** Created: Fri Feb 27 23:48:33 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeclass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEClass[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      38,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   10,   10,   10, 0x0a,
      87,   10,   10,   10, 0x0a,
     110,   10,   10,   10, 0x0a,
     129,  126,   10,   10, 0x0a,
     160,   10,   10,   10, 0x0a,
     195,   10,  187,   10, 0x0a,
     226,  224,   10,   10, 0x0a,
     258,  224,   10,   10, 0x0a,
     295,  224,   10,   10, 0x0a,
     326,  224,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEClass[] = {
    "XQDEClass\0\0sgPluginRegister(QObject*)\0"
    "sgPluginUnRegister(QObject*)\0"
    "FreezeSave(QString)\0FreezeRestore(QString)\0"
    "import(QString)\0,,\0parseString(QString,int,void*)\0"
    "GetNamesList(QStringList&)\0QString\0"
    "GetNamedValueString(QString)\0,\0"
    "GetNamedValue(QString,QString&)\0"
    "GetNamedDecription(QString,QString&)\0"
    "GetNamedType(QString,QString&)\0"
    "WriteNamedValue(QString,QString)\0"
};

const QMetaObject XQDEClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XQDEClass,
      qt_meta_data_XQDEClass, 0 }
};

const QMetaObject *XQDEClass::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEClass))
        return static_cast<void*>(const_cast< XQDEClass*>(this));
    return QObject::qt_metacast(_clname);
}

int XQDEClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sgPluginRegister((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: sgPluginUnRegister((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: FreezeSave((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: FreezeRestore((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: import((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: parseString((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 6: GetNamesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: { QString _r = GetNamedValueString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: GetNamedValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: GetNamedDecription((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: GetNamedType((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: WriteNamedValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void XQDEClass::sgPluginRegister(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEClass::sgPluginUnRegister(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
