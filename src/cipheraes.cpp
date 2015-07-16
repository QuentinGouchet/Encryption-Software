#include "cipheraes.h"

CipherAes::CipherAes(): QDialog() {}

CipherAes::CipherAes(int index): QDialog()
{
    setFixedSize(800, 400);
    this->setWindowTitle("AES");

    labelPlain = new QLabel("Choose file to encrypt/decrypt :");
    labelEncrypt = new QLabel("Choose a name for the plaintext/ciphertext file :");

    buttonEncrypt = new QPushButton("Encrypt");
    buttonDecrypt = new QPushButton("Decrypt");

    buttonCancel = new QPushButton("Cancel");
    buttonBrowse = new QPushButton("Browse");

    lePlain = new QLineEdit(this);
    leEncrypt = new QLineEdit(this);

    fdPlain = new QFileDialog(this);
    fdPlain->setDirectory("../ressources/");

    gl = new QGridLayout(this);

    gl->addWidget(labelPlain, 0, 0);
    gl->addWidget(lePlain, 0, 1);
    gl->addWidget(buttonBrowse, 0, 2);

    gl->addWidget(labelEncrypt, 1, 0);
    gl->addWidget(leEncrypt, 1, 1);

    gl->addWidget(buttonDecrypt, 2, 1);
    gl->addWidget(buttonEncrypt, 2, 2);

    gl->addWidget(buttonCancel, 3, 0);

    this->setLayout(gl);

    QObject::connect(buttonCancel,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(buttonBrowse,SIGNAL(clicked()),fdPlain,SLOT(exec()));

    QObject::connect(fdPlain,SIGNAL(fileSelected(QString)),lePlain,SLOT(setText(QString)));

    switch(index){
        case 0:
            QObject::connect(buttonEncrypt, SIGNAL(clicked()), this, SLOT(hashSHA1()));
            break;
        case 1:
            QObject::connect(buttonEncrypt, SIGNAL(clicked()), this, SLOT(hashSHA224()));
            break;
        case 2:
            QObject::connect(buttonEncrypt, SIGNAL(clicked()), this, SLOT(hashSHA256()));
            break;
        case 3:
            QObject::connect(buttonEncrypt, SIGNAL(clicked()), this, SLOT(hashSHA384()));
            break;
        case 4:
            QObject::connect(buttonEncrypt, SIGNAL(clicked()), this, SLOT(hashSHA512()));
            break;
        default:
            this->close();
            break;
    }

}
