/****************************************************************************
** Meta object code from reading C++ file 'seamcarving.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../seamcarving.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'seamcarving.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SeamCarving_t {
    QByteArrayData data[9];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SeamCarving_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SeamCarving_t qt_meta_stringdata_SeamCarving = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SeamCarving"
QT_MOC_LITERAL(1, 12, 10), // "seamNormal"
QT_MOC_LITERAL(2, 23, 7), // "cv::Mat"
QT_MOC_LITERAL(3, 31, 0), // ""
QT_MOC_LITERAL(4, 32, 3), // "img"
QT_MOC_LITERAL(5, 36, 14), // "cols_to_delete"
QT_MOC_LITERAL(6, 51, 4), // "mode"
QT_MOC_LITERAL(7, 56, 30), // "on_pushButton_save_rem_clicked"
QT_MOC_LITERAL(8, 87, 21) // "on_buttonBox_accepted"

    },
    "SeamCarving\0seamNormal\0cv::Mat\0\0img\0"
    "cols_to_delete\0mode\0on_pushButton_save_rem_clicked\0"
    "on_buttonBox_accepted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SeamCarving[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   29,    3, 0x08 /* Private */,
       7,    0,   36,    3, 0x08 /* Private */,
       8,    0,   37,    3, 0x08 /* Private */,

 // slots: parameters
    0x80000000 | 2, 0x80000000 | 2, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SeamCarving::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SeamCarving *_t = static_cast<SeamCarving *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { cv::Mat _r = _t->seamNormal((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< cv::Mat*>(_a[0]) = _r; }  break;
        case 1: _t->on_pushButton_save_rem_clicked(); break;
        case 2: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    }
}

const QMetaObject SeamCarving::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SeamCarving.data,
      qt_meta_data_SeamCarving,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SeamCarving::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SeamCarving::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SeamCarving.stringdata0))
        return static_cast<void*>(const_cast< SeamCarving*>(this));
    return QDialog::qt_metacast(_clname);
}

int SeamCarving::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
