SOURCES += \
    cipher.cpp \
    sign.cpp \
    rabin.cpp \
    mainwindow.cpp \
    main.cpp \
    decipher.cpp \
    generatekey.cpp \
    hash.cpp \
    rsa.cpp \
    verify.cpp \
    elgamal.cpp \
    dsa.cpp \
    util.cpp \
    aes.cpp \
    sha.cpp \
    error.cpp \
    des.cpp

HEADERS += \
    sign.h \
    rabin.h \
    mainwindow.h \
    cipher.h \
    decipher.h \
    generatekey.h \
    hash.h \
    rsa.h \
    verify.h \
    elgamal.h \
    dsa.h \
    util.h \
    aes.h \
    sha.h \
    error.h \
    des.h

LIBS += -lgmp -lgcrypt -lcrypto -Wall

QT += widgets
