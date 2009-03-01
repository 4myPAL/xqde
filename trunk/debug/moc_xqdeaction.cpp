/****************************************************************************
** Meta object code from reading C++ file 'xqdeaction.h'
**
** Created: Fri Feb 27 23:48:44 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeaction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEAction[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEAction[] = {
    "XQDEAction\0\0enableActionAgain()\0"
};

const QMetaObject XQDEAction::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XQDEAction,
      qt_meta_data_XQDEAction, 0 }
};

const QMetaObject *XQDEAction::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEAction))
        return static_cast<void*>(const_cast< XQDEAction*>(this));
    return QObject::qt_metacast(_clname);
}

int XQDEAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableActionAgain(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
