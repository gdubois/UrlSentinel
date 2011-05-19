/****************************************************************************
** Meta object code from reading C++ file 'site.h'
**
** Created: Thu 12. May 10:02:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "site.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'site.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Site[] =
{

// content:
    5,       // revision
    0,       // classname
    0,    0, // classinfo
    12,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    6,       // signalCount

// signals: signature, parameters, type, tag, flags
    9,    6,    5,    5, 0x05,
    47,    5,    5,    5, 0x05,
    62,    5,    5,    5, 0x05,
    75,   73,    5,    5, 0x05,
    99,   73,    5,    5, 0x05,
    121,   73,    5,    5, 0x05,

// slots: signature, parameters, type, tag, flags
    143,    5,    5,    5, 0x0a,
    159,    5,    5,    5, 0x0a,
    168,    5,    5,    5, 0x08,
    182,    5,    5,    5, 0x08,
    212,    5,    5,    5, 0x08,
    230,    5,    5,    5, 0x08,

    0        // eod
};

static const char qt_meta_stringdata_Site[] =
{
    "Site\0\0,,\0contentChanged(int,QString,QDateTime)\0"
    "unchanged(int)\0error(int)\0,\0"
    "urlChanged(int,QString)\0setTitle(int,QString)\0"
    "setFavicon(int,QIcon)\0setUrl(QString)\0"
    "update()\0statusError()\0"
    "contentDownloaded(QByteArray)\0"
    "newTitle(QString)\0newIcon(QIcon)\0"
};

const QMetaObject Site::staticMetaObject =
{
    {
        &QObject::staticMetaObject, qt_meta_stringdata_Site,
        qt_meta_data_Site, 0
    }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Site::getStaticMetaObject()
{
    return staticMetaObject;
}
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Site::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Site::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Site))
        return static_cast<void*>(const_cast< Site*>(this));
    return QObject::qt_metacast(_clname);
}

int Site::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        switch (_id)
        {
        case 0:
            contentChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 1:
            unchanged((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 2:
            error((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 3:
            urlChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 4:
            setTitle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 5:
            setFavicon((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QIcon(*)>(_a[2])));
            break;
        case 6:
            setUrl((*reinterpret_cast< const QString(*)>(_a[1])));
            break;
        case 7:
            update();
            break;
        case 8:
            statusError();
            break;
        case 9:
            contentDownloaded((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            break;
        case 10:
            newTitle((*reinterpret_cast< const QString(*)>(_a[1])));
            break;
        case 11:
            newIcon((*reinterpret_cast< const QIcon(*)>(_a[1])));
            break;
        default:
            ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Site::contentChanged(int _t1, const QString & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Site::unchanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Site::error(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Site::urlChanged(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Site::setTitle(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Site::setFavicon(int _t1, const QIcon & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
