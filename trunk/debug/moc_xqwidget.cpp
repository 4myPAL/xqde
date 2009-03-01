/****************************************************************************
** Meta object code from reading C++ file 'xqwidget.h'
**
** Created: Fri Feb 27 23:48:35 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,
      32,   28,    9,    9, 0x0a,
      57,    9,    9,    9, 0x0a,
      77,   74,    9,    9, 0x0a,
     102,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQWidget[] = {
    "XQWidget\0\0,\0setPos(int,int)\0,,,\0"
    "setRect(int,int,int,int)\0paint(QPainter&)\0"
    ",,\0paint(int,int,QPainter&)\0"
    "setFixedSize(int,int)\0"
};

const QMetaObject XQWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_XQWidget,
      qt_meta_data_XQWidget, 0 }
};

const QMetaObject *XQWidget::metaObject() const
{
    return &staticMetaObject;
}

void *XQWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQWidget))
        return static_cast<void*>(const_cast< XQWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int XQWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: paint((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 3: paint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QPainter(*)>(_a[3]))); break;
        case 4: setFixedSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
