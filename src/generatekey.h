#ifndef GENERATEKEY_H
#define GENERATEKEY_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QRegExp>

#include "rsa.h"
#include "rabin.h"
#include "elgamal.h"
#include "dsa.h"
#include "aes.h"

class GenerateKey : public QDialog
{
    Q_OBJECT

public:
    GenerateKey();
    GenerateKey(int);
    unsigned int getLengthKey() const {return lengthKey;}

private:
    int rep;
    unsigned int lengthKey;
    QLabel *labelLengthKey;
    QLabel *labelFileNameKeys;

    QPushButton *buttonCancel;
    QPushButton *buttonGenerate;

    QLineEdit *leLenghtKey;
    QLineEdit *leFileNameKeys;

    QGridLayout *gl;

    QRegExp *reFileName;
    QRegExp *reLenghtKey;

    QMessageBox *mb;

    ElGamal *elGamal;
    Rabin *rabin;
    RSA2 *rsa;
    DSA2 *dsa;
    AES *aes;

public slots:    
    void setLengthKey(QString);
    void generateRSA();
    void generateElGamal();
    void generateRabin();
    void generateDSA();
    void generateAES();

signals:
    void clickedGenerate();
};

#endif // GENERATEKEY_H
