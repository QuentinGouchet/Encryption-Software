#ifndef CIPHER_H
#define CIPHER_H

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
#include <QComboBox>

#include "rabin.h"
#include "rsa.h"
#include "elgamal.h"
#include "aes.h"

class Cipher : public QDialog
{
    Q_OBJECT

public:
    Cipher();
    Cipher(int);

private:
    int rep;

    QPushButton *buttonBrowsePlain;
    QPushButton *buttonBrowseKey;
    QPushButton *buttonCancel;
    QPushButton *buttonCompute;

    QComboBox *comboMode;
    QComboBox *comboSize;

    QLabel *labelPlain;
    QLabel *labelCipher;
    QLabel *labelKey;
    QLabel *labelMode;
    QLabel *labelIv;

    QFileDialog *fdPlain;
    QFileDialog *fdKey;

    QLineEdit *lePlain;
    QLineEdit *leCipher;
    QLineEdit *leKey;
    QLineEdit *leEnterKey;
    QLineEdit *leIv;

    QRegExp *rePlain;
    QRegExp *reCipher;
    QRegExp *reKey;

    QMessageBox *mb;

    QGridLayout *gl;

    RSA2 *rsa;
    ElGamal *elGamal;
    Rabin *rabin;
    AES *aes;

public slots:
    void computeRSA();
    void computeElGamal();
    void computeRabin();
    void computeRSAOAEP();
    void computeAES();
};
#endif // CIPHER_H
