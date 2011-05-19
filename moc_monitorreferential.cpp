/****************************************************************************
** Meta object code from reading C++ file 'monitorreferential.h'
**
** Created: Thu 12. May 10:02:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "monitorreferential.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitorreferential.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MonitorReferential[] =
{

// content:
    5,       // revision
    0,       // classname
    0,    0, // classinfo
    19,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    8,       // signalCount

// signals: signature, parameters, type, tag, flags
    23,   20,   19,   19, 0x05,
    62,   19,   19,   19, 0x05,
    79,   20,   19,   19, 0x05,
    111,   19,   19,   19, 0x05,
    127,   19,   19,   19, 0x05,
    141,  139,   19,   19, 0x05,
    164,  139,   19,   19, 0x05,
    187,  139,   19,   19, 0x05,

// slots: signature, parameters, type, tag, flags
    208,   20,   19,   19, 0x0a,
    247,   19,   19,   19, 0x0a,
    264,   19,   19,   19, 0x0a,
    286,  139,   19,   19, 0x0a,
    310,   19,   19,   19, 0x0a,
    331,   19,   19,   19, 0x0a,
    351,   19,   19,   19, 0x0a,
    359,   19,   19,   19, 0x0a,
    366,   19,   19,   19, 0x0a,
    377,   19,   19,   19, 0x0a,
    384,   19,   19,   19, 0x0a,

    0        // eod
};

static const char qt_meta_stringdata_MonitorReferential[] =
{
    "MonitorReferential\0\0,,\0"
    "addSiteV(QString,QByteArray,QDateTime)\0"
    "removeSiteV(int)\0changedV(int,QString,QDateTime)\0"
    "unchangedV(int)\0errorV(int)\0,\0"
    "setTitleV(int,QString)\0setFaviconV(int,QIcon)\0"
    "setUrlV(int,QString)\0"
    "addSiteM(QString,QByteArray,QDateTime)\0"
    "removeSiteM(int)\0updateFrequencyM(int)\0"
    "updateUrlM(int,QString)\0startMonitoring(int)\0"
    "stopMonitoring(int)\0start()\0stop()\0"
    "checkNow()\0save()\0load()\0"
};

const QMetaObject MonitorReferential::staticMetaObject =
{
    {
        &QSettings::staticMetaObject, qt_meta_stringdata_MonitorReferential,
        qt_meta_data_MonitorReferential, 0
    }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MonitorReferential::getStaticMetaObject()
{
    return staticMetaObject;
}
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MonitorReferential::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MonitorReferential::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MonitorReferential))
        return static_cast<void*>(const_cast< MonitorReferential*>(this));
    return QSettings::qt_metacast(_clname);
}

int MonitorReferential::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSettings::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        switch (_id)
        {
        case 0:
            addSiteV((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 1:
            removeSiteV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 2:
            changedV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 3:
            unchangedV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 4:
            errorV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 5:
            setTitleV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 6:
            setFaviconV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QIcon(*)>(_a[2])));
            break;
        case 7:
            setUrlV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 8:
            addSiteM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 9:
            removeSiteM((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 10:
            updateFrequencyM((*reinterpret_cast< const int(*)>(_a[1])));
            break;
        case 11:
            updateUrlM((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 12:
            startMonitoring((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 13:
            stopMonitoring((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 14:
            start();
            break;
        case 15:
            stop();
            break;
        case 16:
            checkNow();
            break;
        case 17:
            save();
            break;
        case 18:
            load();
            break;
        default:
            ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MonitorReferential::addSiteV(const QString & _t1, const QByteArray & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MonitorReferential::removeSiteV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MonitorReferential::changedV(int _t1, const QString & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MonitorReferential::unchangedV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MonitorReferential::errorV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MonitorReferential::setTitleV(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MonitorReferential::setFaviconV(int _t1, const QIcon & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MonitorReferential::setUrlV(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
