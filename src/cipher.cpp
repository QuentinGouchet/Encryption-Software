#include "cipher.h"

Cipher::Cipher(): QDialog() {}

/*
    0 - "RSA"
    1 - "EL GAMAL"
    2 - "RABIN"
    3 - "RSA-OAEP"
    4 - "AES-CBC-128"
*/

int Cipher::derivePassphrase(unsigned char *key, int keylen)
{
    gcry_error_t err = 0;
    gcry_md_hd_t hd = NULL;
    unsigned char *digest = NULL;
    int hash_len;

    if(err = gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE))
    {
            fprintf (stderr, "Failure to open MD_SHA256: %s/%s\n",
                                gcry_strsource (err),
                                gcry_strerror (err));
            return 1;
    }

    hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA256);

    gcry_md_write(hd, key, keylen);
    digest = gcry_md_read(hd, GCRY_MD_SHA256);

    fprintf(stdout, "digest of key: ");
    Util print;
    print.printBuff(digest, hash_len);

    if(hd)
            gcry_md_close(hd);
    if(digest)
            gcry_free(digest);
    if(key)
            gcry_free(key);

    return 0;
}

Cipher::Cipher(int index, int public_cipher): QDialog()
{
    setFixedSize(800, 400);
    this->setWindowTitle("Cipher");

    labelPlain = new QLabel("Choose file to cipher :",this);
    labelCipher = new QLabel("Name the output file :",this);
    labelKey = new QLabel("Choose which key to use :",this);
    labelMode = new QLabel("Block chaining mode :");
    labelIv = new QLabel("Enter IV :", this);

    buttonBrowsePlain = new QPushButton("Browse", this);
    if(public_cipher)
        buttonBrowseKey = new QPushButton("Browse", this);
    buttonCancel = new QPushButton("Cancel", this);
    buttonCompute = new QPushButton("Compute", this);

    QStringList listMode(QStringList() << "ECB" << "CBC");
    QStringList listSize(QStringList() << "128" << "256");

    comboMode = new QComboBox(this);
    comboMode->addItems(listMode);

    comboSize = new QComboBox(this);
    comboSize->addItems(listSize);

    lePlain = new QLineEdit(this);
    leCipher = new QLineEdit(this);

    leKey = new QLineEdit(this);

    // EchoMode(1) sets a password type of echo
    if(!public_cipher)
        leKey->setEchoMode(QLineEdit::Password);

    leIv = new QLineEdit(this);

    fdPlain = new QFileDialog(this);
    fdKey = new QFileDialog(this);

    fdPlain->setDirectory("../ressources/");
    fdKey->setDirectory("../ressources/");

    QStringList listFilters;

    if(public_cipher)
        listFilters << "*.puKey" << "*";
    else
        listFilters << "*.key" << "*";

    fdKey->setNameFilters(listFilters);

    gl = new QGridLayout(this);

    gl->addWidget(labelPlain, 0, 0);
    gl->addWidget(lePlain, 0, 1);
    gl->addWidget(buttonBrowsePlain, 0, 2);

    gl->addWidget(labelKey, 1, 0);
    gl->addWidget(leKey, 1, 1);

    if(public_cipher)
        gl->addWidget(buttonBrowseKey, 1, 2);

    gl->addWidget(labelMode, 2, 0);
    gl->addWidget(comboMode, 2, 1);
    gl->addWidget(comboSize, 2, 2);

    gl->addWidget(labelIv, 3, 0);
    gl->addWidget(leIv, 3, 1);

    gl->addWidget(labelCipher, 4, 0);
    gl->addWidget(leCipher, 4, 1);

    gl->addWidget(buttonCancel, 5, 1);
    gl->addWidget(buttonCompute, 5, 2);

    this->setLayout(gl);

    QObject::connect(buttonCancel,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(buttonBrowsePlain, SIGNAL(clicked()), fdPlain, SLOT(exec()));

    if(public_cipher)
        QObject::connect(buttonBrowseKey, SIGNAL(clicked()), fdKey, SLOT(exec()));

    QObject::connect(fdPlain, SIGNAL(fileSelected(QString)), lePlain, SLOT(setText(QString)));
    QObject::connect(fdKey, SIGNAL(fileSelected(QString)), leKey, SLOT(setText(QString)));

    switch(index){
        case 0:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSA()));
            comboMode->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 1:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeElGamal()));
            comboMode->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 2:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRabin()));
            comboMode->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 3:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSAOAEP()));
            comboMode->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 4:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeAES()));
            break;
        default:
            this->close();
            break;
    }
}

void Cipher::computeRSA() {
    reCipher = new QRegExp("([\\w]+)");
    reKey = new QRegExp("^[\\w|/]+\\.(puKey)$");

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text()) && reKey->exactMatch(leKey->text())){
        rsa = new RSA2();
        rep = rsa->encrypt(lePlain->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), leCipher->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Cannot open one of the given files");
            mb->exec();
            this->close();
        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given plain file is wrong.");
            mb->exec();
            this->close();
        }
        else if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given public key is wrong.");
            mb->exec();

        }
        else if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("the given public key is wrong");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given name doesn't respect the given format.");
            mb->exec();
            this->close();
        }
    }
}

void Cipher::computeElGamal() {
    reCipher = new QRegExp("([\\w]+)");
    reKey = new QRegExp("^[\\w|/]+\\.(puKey)$");

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text()) && reKey->exactMatch(leKey->text())){
        elGamal = new ElGamal();
        rep = elGamal->cipherElGamal(lePlain->text().toLocal8Bit().constData(),leKey->text().toLocal8Bit().constData(),leCipher->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Cannot open one of the given files");
            mb->exec();
            this->close();

        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);            
            mb->setWindowTitle("Information");
            mb->setText("The given plain file is wrong.");
            mb->exec();
            this->close();
        }
        else if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given public key is wrong.");
            mb->exec();
            this->close();
        }
        else if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("the given public key is wrong");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given name doesn't respect the given format.");
            mb->exec();
            this->close();
        }
    }
}

void Cipher::computeRabin(){
    reCipher = new QRegExp("([\\w]+)");
    reKey = new QRegExp("^[\\w|/]+\\.(puKey)$");

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text()) && reKey->exactMatch(leKey->text())){
        rabin = new Rabin();
        rep = rabin->encrypt_Rabin(lePlain->text().toLocal8Bit().constData(),leCipher->text().toLocal8Bit().constData(),leKey->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Cannot open one of the given files.");
            mb->exec();
            this->close();

        }else{
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given public key is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!reKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given public key is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given name doesn't respect the format.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
}

void Cipher::computeRSAOAEP(){
    rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("([\\w]+)");
    reKey = new QRegExp("^[\\w|/]+\\.(puKey)$");

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && reKey->exactMatch(leKey->text())){
        rsa = new RSA2();
        rep = rsa->encryptOAEP(lePlain->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), leCipher->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
            mb->setText("Cannot open one of the given files");
            mb->exec();

        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
          mb = new QMessageBox(this);
          mb->setText("The given plain file is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
        else if(!reKey->exactMatch(leKey->text())){
          mb = new QMessageBox(this);
          mb->setText("The given public key is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
          mb = new QMessageBox(this);
          mb->setText("The given name doesn't respect the given format.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
    }
}

void Cipher::computeAES(){
    //rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("([\\w]+)");
    // Next line is not needed since we derive the key from the passphrase
    // reKey = new QRegExp("^[\\w|/]+\\.(key)$");

    // Let's derive the key given by the password
    fprintf(stdout, "passphrase: %s\n", leKey->text().toLocal8Bit().constData());
    fprintf(stdout, "size in bytes: %d\n", comboSize->currentText().toInt()/8);

    int keylen = comboSize->currentText().toLocal8Bit().toInt()/8;

    unsigned char *key = (unsigned char *) gcry_malloc_secure(sizeof(unsigned char)*keylen);

    Cipher derive;
    derive.derivePassphrase(key, keylen);

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text())){
        aes = new AES();

        if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC") ||
                strcmp(comboSize->currentText().toLocal8Bit().constData(), "128")))
        {
            rep = aes->aes_cbc_128(lePlain->text().toLocal8Bit().constData(),
                               (const char *) key,
                               leCipher->text().toLocal8Bit().constData(),
                               leIv->text().toLocal8Bit().constData());
        }

        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Symmetric encryption error.");
            mb->setWindowTitle("Information");
            mb->exec();

        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->exec();
            this->close();
        }
    }
    else{
        /*if(!rePlain->exactMatch(lePlain->text())){
          mb = new QMessageBox(this);
          mb->setText("The given plain file is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
        else*/ if(!reKey->exactMatch(leKey->text())){
          mb = new QMessageBox(this);
          mb->setText("The given key is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
          mb = new QMessageBox(this);
          mb->setText("The given name doesn't respect the given format.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
    }
    // not actually needed, it is done by derivePassphrase
    if(key)
        gcry_free(key);
}
