#ifndef DECIPHER_H
#define DECIPHER_H

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
#include "elgamal.h"
#include "rsa.h"
#include "aes.h"
#include "des.h"

class Decipher : public QDialog
{
    Q_OBJECT

public:
    Decipher();
    Decipher(int, int);

private:
    unsigned int rep;
    QPushButton *buttonBrowseCipher;
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

    QFileDialog *fdCipher;
    QFileDialog *fdKey;

    QLineEdit *lePlain;
    QLineEdit *leCipher;
    QLineEdit *leKey;
    QLineEdit *leIv;

    QMessageBox *mb;

    QRegExp *rePlain;
    QRegExp *rePrKey;
    QRegExp *reCipher;

    ElGamal *elGamal;
    Rabin *rabin;
    RSA2 *rsa;
    AES *aes;
    DES *des;

    QGridLayout *gl;

public slots:
    void computeRSA();
    void computeRSACRT();
    void computeRSAOAEP();
    void computeElGamal();
    void computeRabin();
    void computeAES();
    void computeDES();

signals:
    void clickedCompute();
};
#endif // DECIPHER_H
