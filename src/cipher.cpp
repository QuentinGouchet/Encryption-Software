#include "cipher.h"

Cipher::Cipher(): QDialog() {}

/*
    0 - "RSA"
    1 - "EL GAMAL"
    2 - "RABIN"
    3 - "RSA-OAEP"
    4 - "AES-CBC-128"
*/

void Cipher::hideIvBox()
{
    if(leIv->isEnabled())
        leIv->setEnabled(false);
    else
        leIv->setEnabled(true);
}

Cipher::Cipher(int index, int public_cipher): QDialog()
{
    setFixedSize(800, 400);
    this->setWindowTitle("Cipher");

    labelPlain = new QLabel("Choose file to cipher :",this);
    labelCipher = new QLabel("Name the output file :",this);    
    if(public_cipher)
        labelKey = new QLabel("Choose which key to use :",this);
    else
        labelKey = new QLabel("Type in your passphrase :", this);
    labelMode = new QLabel("Block chaining mode and size :");
    labelIv = new QLabel("Enter IV :", this);

    buttonBrowsePlain = new QPushButton("Browse", this);
    if(public_cipher)
        buttonBrowseKey = new QPushButton("Browse", this);
    buttonCancel = new QPushButton("Cancel", this);
    buttonCompute = new QPushButton("Compute", this);

    //QStringList listMode(QStringList() << "CBC");
    QStringList listSize(QStringList() << "128" << "256");

    if(index == 4)
    {
        comboSize->addItem("128", GCRY_CIPHER_AES);
        comboSize->addItem("256", GCRY_CIPHER_AES256);
    }

    comboMode = new QComboBox(this);
    //comboMode->addItems(listMode);

    comboMode->addItem("CBC", GCRY_CIPHER_MODE_CBC);

    comboSize = new QComboBox(this);
    comboSize->addItems(listSize);

    lePlain = new QLineEdit(this);
    leCipher = new QLineEdit(this);
    leKey = new QLineEdit(this);

    // EchoMode(1) sets a password type of echo
    if(!public_cipher)
        leKey->setEchoMode(QLineEdit::Password);

    leIv = new QLineEdit(this);
    leIv->setEnabled(false);

    radioIv = new QRadioButton(tr("Manually enter IV"));

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

    // index == 4 is AES; we want a 128 bits IV only
    if(index == 4)
        leIv->setMaxLength(gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES));
    // index = 5 3DES, IV is 64 bits
    else if(index == 5)
        leIv->setMaxLength(gcry_cipher_get_algo_blklen(GCRY_CIPHER_3DES));

    gl->addWidget(leIv, 3, 1);
    gl->addWidget(radioIv, 3, 2);

    gl->addWidget(labelCipher, 4, 0);
    gl->addWidget(leCipher, 4, 1);

    gl->addWidget(buttonCancel, 5, 1);
    gl->addWidget(buttonCompute, 5, 2);

    this->setLayout(gl);

    QObject::connect(radioIv,SIGNAL(clicked()), this, SLOT(hideIvBox()));

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
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 1:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeElGamal()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 2:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRabin()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 3:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeRSAOAEP()));
            comboMode->setEnabled(false);
            comboSize->setEnabled(false);
            leIv->setEnabled(false);
            break;
        case 4:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeAES()));
            break;
        case 5:
            QObject::connect(buttonCompute, SIGNAL(clicked()), this, SLOT(computeDES()));
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
         Util print;
    //rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("([\\w]+)");
    // Next line is not needed since we derive the key from the passphrase
    // reKey = new QRegExp("^[\\w|/]+\\.(key)$");

    reIv = new QRegExp("[a-fA-F0-9]+");

    // Let's derive the key given by the password
    if( (leKey->text().isEmpty() || lePlain->text().isEmpty() || leCipher->text().isEmpty() || leIv->text().size() != 16 && radioIv->isChecked()) )
    {
        mb = new QMessageBox(this);
        mb->setWindowTitle("Information");
        mb->setText("One field is still empty!");
        mb->exec();
        return ;
    }

    int keylen = comboSize->currentText().toLocal8Bit().toInt()/8;
    int pass_len = leKey->text().length();

    // Here check whether radioIv is checked and if not randomly generate IV and store in the file
    unsigned char *iv = NULL;
    int blklen = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES);

    if(!radioIv->isChecked())
    {
        iv = (unsigned char *) gcry_calloc(blklen, sizeof(unsigned char));
        gcry_randomize(iv, blklen, GCRY_STRONG_RANDOM);
    }
    else
        iv = (unsigned char *) leIv->text().toLocal8Bit().constData();

    int hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA256);

    unsigned char *pass = (unsigned char *) gcry_calloc(sizeof(unsigned char), hash_len);
    strcpy( (char *) pass, leKey->text().toLocal8Bit().constData());

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

    if(pass)
        gcry_free(pass);

    pass = gcry_md_read(hd, GCRY_MD_SHA256);

    /*
        Dans un soucis de contrôle minimaliste des entrées, nous vérifions, avant toutes opérations, que les
        QLineEdit contienne bien une extension .in pour le fichier d'entrée, une extension .out pour le fi-
        chier de sortie et une extension .key pour le fichier de clé
    */
    if(!reIv->exactMatch(leIv->text()) && radioIv->isChecked())
    {
      mb = new QMessageBox(this);
      mb->setText("The IV field is incorrect");
      mb->setWindowTitle("Information");
      mb->exec();
    return ;
    }

    if(reCipher->exactMatch(leCipher->text()))
    {
        aes = new AES();

        if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC") ||
                strcmp(comboSize->currentText().toLocal8Bit().constData(), "128")))
        {
            printf("AES-128-CBC encryption\n");
            rep = aes->aes_encrypt(lePlain->text().toLocal8Bit().constData(),
                                   leCipher->text().toLocal8Bit().constData(),
                                   GCRY_CIPHER_AES, comboMode->currentData().toInt(),
                                   (const char *) pass, (const char*) iv);
        }
        else if(!(strcmp(comboMode->currentText().toLocal8Bit().constData(), "CBC") ||
                  strcmp(comboSize->currentText().toLocal8Bit().constData(), "256")))
        {
            printf("AES-256-CBC encryption\n");
            rep = aes->aes_cbc_256_encrypt(lePlain->text().toLocal8Bit().constData(),
                                           leCipher->text().toLocal8Bit().constData(),
                                           (const char *) pass, (const char *) iv);
        }

        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Symmetric encryption error");
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
    // why is gcry_free(pass) failing?

    out:
    memset(pass, 0, hash_len);
    memset(iv, 0, blklen);

    leKey->clear();
    leIv->clear();

    if(hd)
        gcry_md_close(hd);

    if(iv && !radioIv->isChecked())
        gcry_free(iv);

    return ;
}

void Cipher::computeDES()
{
    //rePlain = new QRegExp("^[\\w|/]+\\.(plain)$");
    reCipher = new QRegExp("([\\w]+)");
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
            printf("DES3 encryption\n");
            rep = des->des3_cbc_encrypt(lePlain->text().toLocal8Bit().constData(),
                               (const char *) pass,
                               leCipher->text().toLocal8Bit().constData(),
                               leIv->text().toLocal8Bit().constData());
        }

        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Symmetric encryption error");
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
