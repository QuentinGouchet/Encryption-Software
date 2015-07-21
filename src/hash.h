#ifndef HASH_H
#define HASH_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExp>
#include <QMessageBox>
#include <QPlainTextEdit>

#include "sha.h"
#include "util.h"

class Hash : public QDialog
{
    Q_OBJECT

public:
    Hash();
    Hash(int);

private:
    int rep;

    QLabel *labelPlain;
    QLabel *labelHash;
    QLabel *labelKey;

    QPushButton *buttonCancel;
    QPushButton *buttonBrowse;
    QPushButton *buttonHash;

    QLineEdit *lePlain;
    QLineEdit *leHash;
    QLineEdit *leKey;

    QFileDialog *fdPlain;

    QRegExp *reFileName;

    QMessageBox *mb;
    QPlainTextEdit *qp;

    QGridLayout *gl;

    Sha *sha;

public slots:
    void hashSHA1();
    void hashSHA224();
    void hashSHA256();
    void hashSHA384();
    void hashSHA512();
    void hashHmacSHA1();
    void hashHmacSHA224();
    void hashHmacSHA256();
    void hashHmacSHA384();
    void hashHmacSHA512();

};
#endif // HASH_H
