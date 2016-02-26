/****************************************************************************
** Meta object code from reading C++ file 'decipher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "decipher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decipher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Decipher_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Decipher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Decipher_t qt_meta_stringdata_Decipher = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Decipher"
QT_MOC_LITERAL(1, 9, 14), // "clickedCompute"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "computeRSA"
QT_MOC_LITERAL(4, 36, 13), // "computeRSACRT"
QT_MOC_LITERAL(5, 50, 14), // "computeRSAOAEP"
QT_MOC_LITERAL(6, 65, 14), // "computeElGamal"
QT_MOC_LITERAL(7, 80, 12), // "computeRabin"
QT_MOC_LITERAL(8, 93, 10), // "computeAES"
QT_MOC_LITERAL(9, 104, 10) // "computeDES"

    },
    "Decipher\0clickedCompute\0\0computeRSA\0"
    "computeRSACRT\0computeRSAOAEP\0"
    "computeElGamal\0computeRabin\0computeAES\0"
    "computeDES"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Decipher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Decipher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Decipher *_t = static_cast<Decipher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedCompute(); break;
        case 1: _t->computeRSA(); break;
        case 2: _t->computeRSACRT(); break;
        case 3: _t->computeRSAOAEP(); break;
        case 4: _t->computeElGamal(); break;
        case 5: _t->computeRabin(); break;
        case 6: _t->computeAES(); break;
        case 7: _t->computeDES(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Decipher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Decipher::clickedCompute)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Decipher::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Decipher.data,
      qt_meta_data_Decipher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Decipher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Decipher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Decipher.stringdata0))
        return static_cast<void*>(const_cast< Decipher*>(this));
    return QDialog::qt_metacast(_clname);
}

int Decipher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Decipher::clickedCompute()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
