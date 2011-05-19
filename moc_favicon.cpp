/****************************************************************************
** Meta object code from reading C++ file 'favicon.h'
**
** Created: Thu 12. May 10:02:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "favicon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'favicon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Favicon[] =
{

// content:
    5,       // revision
    0,       // classname
    0,    0, // classinfo
    3,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    1,       // signalCount

// signals: signature, parameters, type, tag, flags
    9,    8,    8,    8, 0x05,

// slots: signature, parameters, type, tag, flags
    28,   24,    8,    8, 0x0a,
    44,    8,    8,    8, 0x08,

    0        // eod
};

static const char qt_meta_stringdata_Favicon[] =
{
    "Favicon\0\0newIcon(QIcon)\0url\0setUrl(QString)\0"
    "replyFinished(QNetworkReply*)\0"
};

const QMetaObject Favicon::staticMetaObject =
{
    {
        &QNetworkAccessManager::staticMetaObject, qt_meta_stringdata_Favicon,
        qt_meta_data_Favicon, 0
    }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Favicon::getStaticMetaObject()
{
    return staticMetaObject;
}
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Favicon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Favicon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Favicon))
        return static_cast<void*>(const_cast< Favicon*>(this));
    return QNetworkAccessManager::qt_metacast(_clname);
}

int Favicon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkAccessManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        switch (_id)
        {
        case 0:
            newIcon((*reinterpret_cast< const QIcon(*)>(_a[1])));
            break;
        case 1:
            setUrl((*reinterpret_cast< const QString(*)>(_a[1])));
            break;
        case 2:
            replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1])));
            break;
        default:
            ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Favicon::newIcon(const QIcon & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
