/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu 12. May 10:02:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] =
{

// content:
    5,       // revision
    0,       // classname
    0,    0, // classinfo
    16,   14, // methods
    0,    0, // properties
    0,    0, // enums/sets
    0,    0, // constructors
    0,       // flags
    15,       // signalCount

// signals: signature, parameters, type, tag, flags
    12,   11,   11,   11, 0x05,
    34,   32,   11,   11, 0x05,
    62,   59,   11,   11, 0x05,
    101,   11,   11,   11, 0x05,
    118,   11,   11,   11, 0x05,
    139,   11,   11,   11, 0x05,
    159,   11,   11,   11, 0x05,
    171,   59,   11,   11, 0x05,
    210,   11,   11,   11, 0x05,
    227,   59,   11,   11, 0x05,
    259,   11,   11,   11, 0x05,
    275,   11,   11,   11, 0x05,
    287,   32,   11,   11, 0x05,
    310,   32,   11,   11, 0x05,
    333,   32,   11,   11, 0x05,

// slots: signature, parameters, type, tag, flags
    354,   11,   11,   11, 0x0a,

    0        // eod
};

static const char qt_meta_stringdata_MainWindow[] =
{
    "MainWindow\0\0showUpdate(QString)\0,\0"
    "urlChangedM(int,QString)\0,,\0"
    "addSiteM(QString,QByteArray,QDateTime)\0"
    "removeSiteM(int)\0startMonitoring(int)\0"
    "stopMonitoring(int)\0checkNowM()\0"
    "addSiteV(QString,QByteArray,QDateTime)\0"
    "removeSiteV(int)\0changedV(int,QString,QDateTime)\0"
    "unchangedV(int)\0errorV(int)\0"
    "setTitleV(int,QString)\0setFaviconV(int,QIcon)\0"
    "setUrlV(int,QString)\0doClose()\0"
};

const QMetaObject MainWindow::staticMetaObject =
{
    {
        &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
        qt_meta_data_MainWindow, 0
    }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject()
{
    return staticMetaObject;
}
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
            urlChangedM((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 2:
            addSiteM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 3:
            removeSiteM((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 4:
            startMonitoring((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 5:
            stopMonitoring((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 6:
            checkNowM();
            break;
        case 7:
            addSiteV((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 8:
            removeSiteV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 9:
            changedV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QDateTime(*)>(_a[3])));
            break;
        case 10:
            unchangedV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 11:
            errorV((*reinterpret_cast< int(*)>(_a[1])));
            break;
        case 12:
            setTitleV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 13:
            setFaviconV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QIcon(*)>(_a[2])));
            break;
        case 14:
            setUrlV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            break;
        case 15:
            doClose();
            break;
        default:
            ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showUpdate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::urlChangedM(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::addSiteM(const QString & _t1, const QByteArray & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::removeSiteM(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::startMonitoring(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::stopMonitoring(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::checkNowM()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void MainWindow::addSiteV(const QString & _t1, const QByteArray & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::removeSiteV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::changedV(int _t1, const QString & _t2, const QDateTime & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::unchangedV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::errorV(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::setTitleV(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::setFaviconV(int _t1, const QIcon & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::setUrlV(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_END_MOC_NAMESPACE
