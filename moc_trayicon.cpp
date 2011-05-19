/****************************************************************************
** Meta object code from reading C++ file 'trayicon.h'
**
** Created: Tue 17. May 16:42:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "trayicon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trayicon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrayIcon[] =
{

// content:
    5,       // revision
    0,       // classname
    0,    0, // classinfo
    6,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    2,       // signalCount

// signals: signature, parameters, type, tag, flags
    10,    9,    9,    9, 0x05,
    30,    9,    9,    9, 0x05,

// slots: signature, parameters, type, tag, flags
    44,   41,    9,    9, 0x0a,
    76,    9,    9,    9, 0x0a,
    99,    9,    9,    9, 0x08,
    148,    9,    9,    9, 0x08,

    0        // eod
};

static const char qt_meta_stringdata_TrayIcon[] =
{
    "TrayIcon\0\0showUpdate(QString)\0closeAll()\0"
    ",,\0changedV(int,QString,QDateTime)\0"
    "showingUpdate(QString)\0"
    "doubleClicked(QSystemTrayIcon::ActivationReason)\0"
    "notificationClicked()\0"
};

const QMetaObject TrayIcon::staticMetaObject =
{
    {
        &QSystemTrayIcon::staticMetaObject, qt_meta_stringdata_TrayIcon,
        qt_meta_data_TrayIcon, 0
    }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrayIcon::getStaticMetaObject()
{
    return staticMetaObject;
}
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrayIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrayIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrayIcon))
        return static_cast<void*>(const_cast< TrayIcon*>(this));
    return QSystemTrayIcon::qt_metacast(_clname);
}

int TrayIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSystemTrayIcon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        switch (_id)
        {
        case 0:
            showUpdate((*reinterpret_cast< const QString(*)>(_a[1])));
            break;
        case 1:
            closeAll();
            break;
        case 2:
            changedV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 3:
            showingUpdate((*reinterpret_cast< const QString(*)>(_a[1])));
            break;
        case 4:
            doubleClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1])));
            break;
        case 5:
            notificationClicked();
            break;
        default:
            ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TrayIcon::showUpdate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrayIcon::closeAll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
