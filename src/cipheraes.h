#ifndef CIPHERAES_H
#define CIPHERAES_H

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

#include "aes.h"

class CipherAes : public QDialog
{
    Q_OBJECT

    public:
        CipherAes();
        CipherAes(int);

    private:
        QLabel *labelPlain;
        QLabel *labelEncrypt;
        QPushButton *buttonEncrypt;
        QPushButton *buttonDecrypt;
        QPushButton *buttonCancel;
        QPushButton *buttonBrowse;
        QLineEdit *lePlain;
        QLineEdit *leEncrypt;
        QFileDialog *fdPlain;
        QGridLayout *gl;

};

#endif // CIPHERAES_H
