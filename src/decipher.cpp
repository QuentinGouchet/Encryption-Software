#include "decipher.h"

Decipher::Decipher() : QDialog() {}

/*
    0 - RSA
    1 - RSA-CRT
    2 - EL GAMAL
    3 - RABIN
*/

Decipher::Decipher(int index, int public_cipher): QDialog()
{
    setFixedSize(800, 400);
    this->setWindowTitle("Decipher");

    labelCipher = new QLabel("Choose file to decipher :",this);
    labelPlain = new QLabel("Choose where to create output file :",this);
    if(public_cipher)
        labelKey = new QLabel("Choose which key to use :",this);
    else
        labelKey = new QLabel("Type in your passphrase :", this);
    labelMode = new QLabel("Block chaining mode and size :");
    //labelIv = new QLabel("Enter IV :", this);

    buttonBrowseCipher = new QPushButton("Browse", this);
    if(public_cipher)
        buttonBrowseKey = new QPushButton("Browse", this);
    buttonCancel = new QPushButton("Cancel", this);
    buttonCompute = new QPushButton("Compute", this);

    QStringList listMode(QStringList() << "CBC");
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

    //leIv = new QLineEdit(this);

    fdCipher = new QFileDialog(this);
    fdKey = new QFileDialog(this);

    fdCipher->setDirectory("../ressources/");
    fdKey->setDirectory("../ressources/");

    QStringList listFilters;

    if(public_cipher)
        listFilters << "*.puKey" << "*";
    else
        listFilters << "*.key" << "*";

    fdCipher->setNameFilter("*.cipher");
    fdKey->setNameFilter("*.prKey");

    fdKey->setNameFilters(listFilters);

    gl = new QGridLayout(this);

    gl->addWidget(labelCipher, 0, 0);
    gl->addWidget(leCipher, 0, 1);
    gl->addWidget(buttonBrowseCipher, 0, 2);

    gl->addWidget(labelKey, 1, 0);
    gl->addWidget(leKey, 1, 1);

    if(public_cipher)
        gl->addWidget(buttonBrowseKey, 1, 2);

    gl->addWidget(labelMode, 2, 0);
    gl->addWidget(comboMode, 2, 1);
    gl->addWidget(comboSize, 2, 2);

    /*gl->addWidget(labelIv, 3, 0);
    gl->addWidget(leIv, 3, 1);*/

    gl->addWidget(labelPlain, 4, 0);
    gl->addWidget(lePlain, 4, 1);

    gl->addWidget(buttonCancel, 5, 1);
    gl->addWidget(buttonCompute, 5, 2);

    this->setLayout(gl);

    QObject::connect(buttonCancel,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(buttonBrowseCipher, SIGNAL(clicked()), fdCipher, SLOT(exec()));

    if(public_cipher)
        QObject::connect(buttonBrowseKey, SIGNAL(clicked()), fdKey, SLOT(exec()));

    QObject::connect(fdCipher, SIGNAL(fileSelected(QString)), leCipher, SLOT(setText(QString)));
    QObject::connect(fdKey, SIGNAL(fileSelected(QString)), leKey, SLOT(setText(QString)));

    switch(index){
        case 0:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSA()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 1:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSACRT()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 2:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeElGamal()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 3:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRabin()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 4:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSAOAEP()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 5:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeAES()));
            break;
        case 6:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeDES()));
            break;
        default:
            this->close();
            break;
    }
}

void Decipher::computeRSACRT(){
    rePlain = new QRegExp("^[\\w]+$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    rePrKey = new QRegExp("^[\\w|/]+\\.(prKey)$");
    /*  Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && rePrKey->exactMatch(leKey->text())){
        rsa = new RSA2();
        rep = rsa->decryptCRT(leCipher->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), lePlain->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
            mb->exec();

        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);
            mb->setText("The given name doesn't respect the given format.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given cipher file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given private key file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
}

void Decipher::computeElGamal(){
    rePlain = new QRegExp("^[\\w]+$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    rePrKey = new QRegExp("^[\\w|/]+\\.(prKey)$");
    /*  Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && rePrKey->exactMatch(leKey->text())){
        elGamal = new ElGamal();
        rep = elGamal->decipherElGamal(leCipher->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), lePlain->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("the given name doesn't respect the given format");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given cipher file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given private key file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("The given private key file is wrong.");
            mb->exec();
            this->close();
        }
    }
}

void Decipher::computeRabin(){
    rePlain = new QRegExp("^[\\w]+$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    rePrKey = new QRegExp("^[\\w|/]+\\.(prKey)$");
    /*  Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && rePrKey->exactMatch(leKey->text())){
        rabin = new Rabin();
        rep = rabin->decrypt_Rabin(leCipher->text().toLocal8Bit().constData(),lePlain->text().toLocal8Bit().constData(),leKey->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("the given name doesn't respect the given format");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given cipher file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given private key file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
}

void Decipher::computeRSA() {
    rePlain = new QRegExp("^[\\w]+$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    rePrKey = new QRegExp("^[\\w|/]+\\.(prKey)$");

    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && rePrKey->exactMatch(leKey->text())){
        rsa = new RSA2();
        rep = rsa->decrypt(leCipher->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), lePlain->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
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
            mb->setText("The given name doesn't respect the given format.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given cipher file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given private key file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
}

void Decipher::computeRSAOAEP(){
    rePlain = new QRegExp("^[\\w]+$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    rePrKey = new QRegExp("^[\\w|/]+\\.(prKey)$");

    if(rePlain->exactMatch(lePlain->text()) && reCipher->exactMatch(leCipher->text()) && rePrKey->exactMatch(leKey->text())){
        rsa = new RSA2();
        rep = rsa->decryptOAEP(leCipher->text().toLocal8Bit().constData(), leKey->text().toLocal8Bit().constData(), lePlain->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();

        }else{
            mb = new QMessageBox(this);
            mb->setWindowTitle("Information");
            mb->setText("Success");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }
    else{
        if(!rePlain->exactMatch(lePlain->text())){
            mb = new QMessageBox(this);
            mb->setText("The given name doesn't respect the given format.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!reCipher->exactMatch(leCipher->text())){
            mb = new QMessageBox(this);
            mb->setText("The given cipher file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
        else if(!rePrKey->exactMatch(leKey->text())){
            mb = new QMessageBox(this);
            mb->setText("The given private key file is wrong.");
            mb->setWindowTitle("Information");
            mb->exec();
            this->close();
        }
    }   
}

void Decipher::computeAES()
{
    //rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    // Next line is not needed since we derive the key from the passphrase
    // reKey = new QRegExp("^[\\w|/]+\\.(key)$");

    // Let's derive the key given by the password
    fprintf(stdout, "passphrase: %s\n", leKey->text().toLocal8Bit().constData());
    fprintf(stdout, "size in bytes: %d\n", comboSize->currentText().toInt()/8);

    int keylen = comboSize->currentText().toLocal8Bit().toInt()/8;
    int pass_len = leKey->text().length();

    fprintf(stdout, "size of pass: %d\n", pass_len);

    Util print;

    int hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA256);

    unsigned char *pass = (unsigned char *) gcry_malloc_secure(sizeof(unsigned char)*hash_len);
    strcpy( (char *) pass, leKey->text().toLocal8Bit().constData());

    fprintf(stdout, "pass: ");
    print.printBuff(pass, hash_len);

    gcry_error_t err = 0;
    gcry_md_hd_t hd = NULL;

    if(err = gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE))
    {
            fprintf (stderr, "Failure to open MD_SHA256: %s/%s\n",
                                gcry_strsource (err),
                                gcry_strerror (err));
            goto out;
    }

    gcry_md_write(hd, pass, pass_len);

    pass = gcry_md_read(hd, GCRY_MD_SHA256);

    printf("hash_len: %d\n", hash_len);

    fprintf(stdout, "Digest of key: ");
    print.printBuff(pass, hash_len);

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text()))
    {
        aes = new AES();

        if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC") ||
                strcmp(comboSize->currentText().toLocal8Bit().constData(), "128")))
        {
            printf("AES-128-CBC decryption\n");
            rep = aes->aes_cbc_128_decrypt(leCipher->text().toLocal8Bit().constData(),
                                           lePlain->text().toLocal8Bit().constData(),
                                           (const char *) pass);
        }
        else if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC") ||
                  strcmp(comboSize->currentText().toLocal8Bit().constData(), "256")))
        {
            printf("AES256 decryption\n");
            rep = aes->aes_cbc_256_decrypt(leCipher->text().toLocal8Bit().constData(),
                               (const char *) pass,
                               lePlain->text().toLocal8Bit().constData(),
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
        else if(!reKey->exactMatch(leKey->text())){
          mb = new QMessageBox(this);
          mb->setText("The given key is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }*/
        if(!reCipher->exactMatch(leCipher->text())){
          mb = new QMessageBox(this);
          mb->setText("The given name doesn't respect the given format.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
    }

    // not actually needed, it is done by derivePassphrase
    out:
        if(hd)
            gcry_md_close(hd);
}

void Decipher::computeDES()
{
    //rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("^[\\w|/]+\\.(cipher)$");
    // Next line is not needed since we derive the key from the passphrase
    // reKey = new QRegExp("^[\\w|/]+\\.(key)$");

    // Let's derive the key given by the password
    fprintf(stdout, "passphrase: %s\n", leKey->text().toLocal8Bit().constData());
    fprintf(stdout, "size in bytes: %d\n", comboSize->currentText().toInt()/8);

    int keylen = comboSize->currentText().toLocal8Bit().toInt()/8;
    int pass_len = leKey->text().length();

    fprintf(stdout, "size of pass: %d\n", pass_len);

    Util print;

    int hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA256);

    unsigned char *pass = (unsigned char *) gcry_malloc_secure(sizeof(unsigned char)*hash_len);
    strcpy( (char *) pass, leKey->text().toLocal8Bit().constData());

    fprintf(stdout, "pass: ");
    print.printBuff(pass, hash_len);

    gcry_error_t err = 0;
    gcry_md_hd_t hd = NULL;

    if(err = gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE))
    {
            fprintf (stderr, "Failure to open MD_SHA256: %s/%s\n",
                                gcry_strsource (err),
                                gcry_strerror (err));
            goto out;
    }

    gcry_md_write(hd, pass, pass_len);

    pass = gcry_md_read(hd, GCRY_MD_SHA256);

    printf("hash_len: %d\n", hash_len);

    fprintf(stdout, "Digest of key: ");
    print.printBuff(pass, hash_len);

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(reCipher->exactMatch(leCipher->text()))
    {
        des = new DES();

        if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC")))
        {
            printf("DES3 decryption\n");
            rep = des->des3_cbc_decrypt(leCipher->text().toLocal8Bit().constData(),
                               (const char *) pass,
                               lePlain->text().toLocal8Bit().constData(),
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
        else if(!reKey->exactMatch(leKey->text())){
          mb = new QMessageBox(this);
          mb->setText("The given key is wrong.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }*/
        if(!reCipher->exactMatch(leCipher->text())){
          mb = new QMessageBox(this);
          mb->setText("The given name doesn't respect the given format.");
          mb->setWindowTitle("Information");
          mb->exec();
          this->close();
        }
    }

    // not actually needed, it is done by derivePassphrase
    out:
        if(hd)
            gcry_md_close(hd);
}
