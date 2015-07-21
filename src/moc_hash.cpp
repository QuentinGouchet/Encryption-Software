/****************************************************************************
** Meta object code from reading C++ file 'hash.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "hash.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hash.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Hash_t {
    QByteArrayData data[12];
    char stringdata[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Hash_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Hash_t qt_meta_stringdata_Hash = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Hash"
QT_MOC_LITERAL(1, 5, 8), // "hashSHA1"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 10), // "hashSHA224"
QT_MOC_LITERAL(4, 26, 10), // "hashSHA256"
QT_MOC_LITERAL(5, 37, 10), // "hashSHA384"
QT_MOC_LITERAL(6, 48, 10), // "hashSHA512"
QT_MOC_LITERAL(7, 59, 12), // "hashHmacSHA1"
QT_MOC_LITERAL(8, 72, 14), // "hashHmacSHA224"
QT_MOC_LITERAL(9, 87, 14), // "hashHmacSHA256"
QT_MOC_LITERAL(10, 102, 14), // "hashHmacSHA384"
QT_MOC_LITERAL(11, 117, 14) // "hashHmacSHA512"

    },
    "Hash\0hashSHA1\0\0hashSHA224\0hashSHA256\0"
    "hashSHA384\0hashSHA512\0hashHmacSHA1\0"
    "hashHmacSHA224\0hashHmacSHA256\0"
    "hashHmacSHA384\0hashHmacSHA512"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Hash[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Hash::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Hash *_t = static_cast<Hash *>(_o);
        switch (_id) {
        case 0: _t->hashSHA1(); break;
        case 1: _t->hashSHA224(); break;
        case 2: _t->hashSHA256(); break;
        case 3: _t->hashSHA384(); break;
        case 4: _t->hashSHA512(); break;
        case 5: _t->hashHmacSHA1(); break;
        case 6: _t->hashHmacSHA224(); break;
        case 7: _t->hashHmacSHA256(); break;
        case 8: _t->hashHmacSHA384(); break;
        case 9: _t->hashHmacSHA512(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Hash::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Hash.data,
      qt_meta_data_Hash,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Hash::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Hash::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Hash.stringdata))
        return static_cast<void*>(const_cast< Hash*>(this));
    return QDialog::qt_metacast(_clname);
}

int Hash::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
