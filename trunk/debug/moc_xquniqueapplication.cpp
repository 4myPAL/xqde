/****************************************************************************
** Meta object code from reading C++ file 'xquniqueapplication.h'
**
** Created: Fri Feb 27 23:48:35 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xquniqueapplication.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xquniqueapplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQUniqueApplication[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQUniqueApplication[] = {
    "XQUniqueApplication\0\0prova()\0"
};

const QMetaObject XQUniqueApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_XQUniqueApplication,
      qt_meta_data_XQUniqueApplication, 0 }
};

const QMetaObject *XQUniqueApplication::metaObject() const
{
    return &staticMetaObject;
}

void *XQUniqueApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQUniqueApplication))
        return static_cast<void*>(const_cast< XQUniqueApplication*>(this));
    return QApplication::qt_metacast(_clname);
}

int XQUniqueApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: prova(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
