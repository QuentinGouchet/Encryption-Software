/****************************************************************************
** Meta object code from reading C++ file 'generatekey.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "generatekey.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generatekey.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GenerateKey_t {
    QByteArrayData data[9];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GenerateKey_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GenerateKey_t qt_meta_stringdata_GenerateKey = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GenerateKey"
QT_MOC_LITERAL(1, 12, 15), // "clickedGenerate"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "setLengthKey"
QT_MOC_LITERAL(4, 42, 11), // "generateRSA"
QT_MOC_LITERAL(5, 54, 15), // "generateElGamal"
QT_MOC_LITERAL(6, 70, 13), // "generateRabin"
QT_MOC_LITERAL(7, 84, 11), // "generateDSA"
QT_MOC_LITERAL(8, 96, 11) // "generateAES"

    },
    "GenerateKey\0clickedGenerate\0\0setLengthKey\0"
    "generateRSA\0generateElGamal\0generateRabin\0"
    "generateDSA\0generateAES"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GenerateKey[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x0a /* Public */,
       4,    0,   53,    2, 0x0a /* Public */,
       5,    0,   54,    2, 0x0a /* Public */,
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GenerateKey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GenerateKey *_t = static_cast<GenerateKey *>(_o);
        switch (_id) {
        case 0: _t->clickedGenerate(); break;
        case 1: _t->setLengthKey((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->generateRSA(); break;
        case 3: _t->generateElGamal(); break;
        case 4: _t->generateRabin(); break;
        case 5: _t->generateDSA(); break;
        case 6: _t->generateAES(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GenerateKey::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GenerateKey::clickedGenerate)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject GenerateKey::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GenerateKey.data,
      qt_meta_data_GenerateKey,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GenerateKey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GenerateKey::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateKey.stringdata))
        return static_cast<void*>(const_cast< GenerateKey*>(this));
    return QDialog::qt_metacast(_clname);
}

int GenerateKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GenerateKey::clickedGenerate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
