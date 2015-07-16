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

    QPushButton *buttonCancel;
    QPushButton *buttonBrowse;
    QPushButton *buttonHash;

    QLineEdit *lePlain;
    QLineEdit *leHash;

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

};
#endif // HASH_H
