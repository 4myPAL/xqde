/****************************************************************************
** Meta object code from reading C++ file 'xqdeenvironment.h'
**
** Created: Fri Feb 27 23:48:33 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeenvironment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeenvironment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEEnvironmentTheme[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      69,   67,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_XQDEEnvironmentTheme[] = {
    "XQDEEnvironmentTheme\0\0"
    "XQDEEnvironmentTheme_findImage_miss(QString)\0"
    ",\0XQDEEnvironmentTheme_findResources_miss(QString,QString)\0"
};

const QMetaObject XQDEEnvironmentTheme::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XQDEEnvironmentTheme,
      qt_meta_data_XQDEEnvironmentTheme, 0 }
};

const QMetaObject *XQDEEnvironmentTheme::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEEnvironmentTheme::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEEnvironmentTheme))
        return static_cast<void*>(const_cast< XQDEEnvironmentTheme*>(this));
    return QObject::qt_metacast(_clname);
}

int XQDEEnvironmentTheme::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: XQDEEnvironmentTheme_findImage_miss((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: XQDEEnvironmentTheme_findResources_miss((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void XQDEEnvironmentTheme::XQDEEnvironmentTheme_findImage_miss(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEEnvironmentTheme::XQDEEnvironmentTheme_findResources_miss(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_XQDEEnvironmentUserProfile[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEEnvironmentUserProfile[] = {
    "XQDEEnvironmentUserProfile\0\0"
    "configureThisComponentViaXML(QObject*)\0"
    "configureComponent(QObject*)\0"
};

const QMetaObject XQDEEnvironmentUserProfile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XQDEEnvironmentUserProfile,
      qt_meta_data_XQDEEnvironmentUserProfile, 0 }
};

const QMetaObject *XQDEEnvironmentUserProfile::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEEnvironmentUserProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEEnvironmentUserProfile))
        return static_cast<void*>(const_cast< XQDEEnvironmentUserProfile*>(this));
    return QObject::qt_metacast(_clname);
}

int XQDEEnvironmentUserProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: configureThisComponentViaXML((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: configureComponent((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void XQDEEnvironmentUserProfile::configureThisComponentViaXML(QObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
