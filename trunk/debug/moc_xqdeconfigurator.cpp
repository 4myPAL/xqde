/****************************************************************************
** Meta object code from reading C++ file 'xqdeconfigurator.h'
**
** Created: Sun Mar 1 12:20:03 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdeconfigurator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdeconfigurator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDEConfigurator[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      27,   17,   17,   17, 0x0a,
      53,   17,   17,   17, 0x0a,
      82,   17,   17,   17, 0x0a,
     114,   17,   17,   17, 0x0a,
     144,   17,   17,   17, 0x0a,
     173,   17,   17,   17, 0x0a,
     206,   17,   17,   17, 0x0a,
     228,   17,   17,   17, 0x0a,
     260,   17,   17,   17, 0x0a,
     292,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDEConfigurator[] = {
    "XQDEConfigurator\0\0xReset()\0"
    "bigsize_valueChanged(int)\0"
    "normalsize_valueChanged(int)\0"
    "dockposition_activated(QString)\0"
    "changeOverTextColor_clicked()\0"
    "changeOverTextFont_clicked()\0"
    "lw_itemClicked(QListWidgetItem*)\0"
    "lw_addWidgetClicked()\0"
    "dockPositionX_valueChanged(int)\0"
    "dockPositionY_valueChanged(int)\0"
    "list_plugin_configureClicked()\0"
};

const QMetaObject XQDEConfigurator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_XQDEConfigurator,
      qt_meta_data_XQDEConfigurator, 0 }
};

const QMetaObject *XQDEConfigurator::metaObject() const
{
    return &staticMetaObject;
}

void *XQDEConfigurator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDEConfigurator))
        return static_cast<void*>(const_cast< XQDEConfigurator*>(this));
    if (!strcmp(_clname, "Ui::XQDEUIConfigurator"))
        return static_cast< Ui::XQDEUIConfigurator*>(const_cast< XQDEConfigurator*>(this));
    return QDialog::qt_metacast(_clname);
}

int XQDEConfigurator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: xReset(); break;
        case 1: bigsize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: normalsize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: dockposition_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: changeOverTextColor_clicked(); break;
        case 5: changeOverTextFont_clicked(); break;
        case 6: lw_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: lw_addWidgetClicked(); break;
        case 8: dockPositionX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: dockPositionY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: list_plugin_configureClicked(); break;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
