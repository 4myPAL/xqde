/****************************************************************************
** Meta object code from reading C++ file 'xqdesensor_taskmanager.h'
**
** Created: Fri Feb 27 23:48:40 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xqdesensor_taskmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqdesensor_taskmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XQDESensor_TaskManager[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      29,   24,   23,   23, 0x0a,
      73,   69,   23,   23, 0x0a,
     104,   23,   23,   23, 0x0a,
     120,   23,   23,   23, 0x0a,
     146,   23,   23,   23, 0x0a,
     170,  168,   23,   23, 0x0a,
     198,   23,   23,   23, 0x0a,
     218,   23,   23,   23, 0x0a,
     242,   23,   23,   23, 0x0a,
     267,  264,  259,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XQDESensor_TaskManager[] = {
    "XQDESensor_TaskManager\0\0,,,,\0"
    "userAction(int,int,int,void*,XQDEIcon*)\0"
    ",,,\0setGeometry(void*,int,int,int)\0"
    "slotAddClient()\0slotupdateStackingOrder()\0"
    "slotupdateThumbnail()\0,\0"
    "fillPopup(QMenu*,XQDEIcon*)\0"
    "triggered(QAction*)\0triggeredKill(QAction*)\0"
    "slotPollingPID()\0bool\0ev\0"
    "x11EventFilter(XEvent*)\0"
};

const QMetaObject XQDESensor_TaskManager::staticMetaObject = {
    { &XQDEClass::staticMetaObject, qt_meta_stringdata_XQDESensor_TaskManager,
      qt_meta_data_XQDESensor_TaskManager, 0 }
};

const QMetaObject *XQDESensor_TaskManager::metaObject() const
{
    return &staticMetaObject;
}

void *XQDESensor_TaskManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XQDESensor_TaskManager))
        return static_cast<void*>(const_cast< XQDESensor_TaskManager*>(this));
    if (!strcmp(_clname, "NETRootInfo4"))
        return static_cast< NETRootInfo4*>(const_cast< XQDESensor_TaskManager*>(this));
    return XQDEClass::qt_metacast(_clname);
}

int XQDESensor_TaskManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = XQDEClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: userAction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< void*(*)>(_a[4])),(*reinterpret_cast< XQDEIcon*(*)>(_a[5]))); break;
        case 1: setGeometry((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: slotAddClient(); break;
        case 3: slotupdateStackingOrder(); break;
        case 4: slotupdateThumbnail(); break;
        case 5: fillPopup((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< XQDEIcon*(*)>(_a[2]))); break;
        case 6: triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: triggeredKill((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 8: slotPollingPID(); break;
        case 9: { bool _r = x11EventFilter((*reinterpret_cast< XEvent*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
