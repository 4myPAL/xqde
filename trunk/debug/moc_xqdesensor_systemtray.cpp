/****************************************************************************
** Meta object code from reading C++ file 'xqdesensor_systemtray.h'
**
** Created: Fri Feb 27 23:48:36 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdesensor_systemtray.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdesensor_systemtray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDESensor_SystemTray[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_XQDESensor_SystemTray[] = {
    "XQDESensor_SystemTray\0"
};

const QMetaObject XQDESensor_SystemTray::staticMetaObject = {
    { &XQWidget::staticMetaObject, qt_meta_stringdata_XQDESensor_SystemTray,
      qt_meta_data_XQDESensor_SystemTray, 0 }
};

const QMetaObject *XQDESensor_SystemTray::metaObject() const
{
    return &staticMetaObject;
}

void *XQDESensor_SystemTray::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDESensor_SystemTray))
        return static_cast<void*>(const_cast< XQDESensor_SystemTray*>(this));
    return XQWidget::qt_metacast(_clname);
}

int XQDESensor_SystemTray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
