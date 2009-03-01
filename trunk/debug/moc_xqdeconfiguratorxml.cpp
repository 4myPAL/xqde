/****************************************************************************
** Meta object code from reading C++ file 'xqdeconfiguratorxml.h'
**
** Created: Fri Feb 27 23:48:45 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeconfiguratorxml.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeconfiguratorxml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEConfiguratorXML[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      50,   48,   20,   20, 0x05,
      82,   48,   20,   20, 0x05,
     119,   48,   20,   20, 0x05,
     150,   48,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     193,  183,   20,   20, 0x0a,
     235,  232,   20,   20, 0x0a,
     271,  268,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEConfiguratorXML[] = {
    "XQDEConfiguratorXML\0\0GetNamesList(QStringList&)\0"
    ",\0GetNamedValue(QString,QString&)\0"
    "GetNamedDecription(QString,QString&)\0"
    "GetNamedType(QString,QString&)\0"
    "WriteNamedValue(QString,QString)\0"
    "remoteObj\0configureThisComponentViaXML(QObject*)\0"
    "lw\0ln_itemClicked(QListWidgetItem*)\0"
    "tt\0value_textChanged(QString)\0"
};

const QMetaObject XQDEConfiguratorXML::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_XQDEConfiguratorXML,
      qt_meta_data_XQDEConfiguratorXML, 0 }
};

const QMetaObject *XQDEConfiguratorXML::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEConfiguratorXML::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEConfiguratorXML))
        return static_cast<void*>(const_cast< XQDEConfiguratorXML*>(this));
    if (!strcmp(_clname, "Ui::XQDEUIConfiguratorXML"))
        return static_cast< Ui::XQDEUIConfiguratorXML*>(const_cast< XQDEConfiguratorXML*>(this));
    return QDialog::qt_metacast(_clname);
}

int XQDEConfiguratorXML::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: GetNamesList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: GetNamedValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: GetNamedDecription((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: GetNamedType((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: WriteNamedValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: configureThisComponentViaXML((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 6: ln_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: value_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void XQDEConfiguratorXML::GetNamesList(QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XQDEConfiguratorXML::GetNamedValue(const QString & _t1, QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XQDEConfiguratorXML::GetNamedDecription(const QString & _t1, QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XQDEConfiguratorXML::GetNamedType(const QString & _t1, QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XQDEConfiguratorXML::WriteNamedValue(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
