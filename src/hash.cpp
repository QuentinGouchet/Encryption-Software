#include "hash.h"

Hash::Hash() : QDialog() {}

Hash::Hash(int index): QDialog()
{
    setFixedSize(800, 400);
    this->setWindowTitle("Hash");

    labelPlain = new QLabel("Choose file to hash :");
    labelHash = new QLabel("Choose a name for the hash file :");
    labelKey = new QLabel("Enter HMAC key :");

    buttonHash = new QPushButton("Hash");
    buttonCancel = new QPushButton("Cancel");
    buttonBrowse = new QPushButton("Browse");

    lePlain = new QLineEdit(this);
    leHash = new QLineEdit(this);
    leKey = new QLineEdit(this);

    fdPlain = new QFileDialog(this);
    fdPlain->setDirectory("../ressources/");

    gl = new QGridLayout(this);

    gl->addWidget(labelPlain, 0, 0);
    gl->addWidget(lePlain, 0, 1);
    gl->addWidget(buttonBrowse, 0, 2);

    gl->addWidget(labelHash, 1, 0);
    gl->addWidget(leHash, 1, 1);

    gl->addWidget(labelKey, 2, 0);
    gl->addWidget(leKey, 2, 1);

    gl->addWidget(buttonCancel, 3, 1);
    gl->addWidget(buttonHash, 3, 2);

    this->setLayout(gl);

    QObject::connect(buttonCancel,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(buttonBrowse,SIGNAL(clicked()),fdPlain,SLOT(exec()));

    QObject::connect(fdPlain,SIGNAL(fileSelected(QString)),lePlain,SLOT(setText(QString)));

    switch(index){
        case 0:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashSHA1()));
            leKey->setEnabled(false);
            break;
        case 1:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashSHA224()));
            leKey->setEnabled(false);
            break;
        case 2:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashSHA256()));
            leKey->setEnabled(false);
            break;
        case 3:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashSHA384()));
            leKey->setEnabled(false);
            break;
        case 4:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashSHA512()));
            leKey->setEnabled(false);
            break;
        case 5:
            QObject::connect(buttonHash, SIGNAL(clicked()), this, SLOT(hashHmacSHA1()));
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            this->close();
            break;
    }
}

void Hash::hashSHA1() {
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    if(reFileName->exactMatch(leHash->text())){
        sha = new Sha();
        rep = sha->computeSha1(lePlain->text().toLocal8Bit().data(),
                               leHash->text().toLocal8Bit().constData());
        if(rep == 1)
        {
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files");
            mb->setWindowTitle("Message");
            mb->exec();
        }
        else
        {
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else{
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashSHA224() {
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    if(reFileName->exactMatch(leHash->text())){
        sha = new Sha();
        rep = sha->computeSha224(lePlain->text().toLocal8Bit().data(), leHash->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Message");
            mb->exec();
        }
        else if (rep == 0){
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
        else {
            mb = new QMessageBox(this);
            QString text = QString("FAILURE: %1").arg(rep);
            mb->setText(text);
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else {
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashSHA256() {
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    if(reFileName->exactMatch(leHash->text())){
        sha = new Sha();
        rep = sha->computeSha256(lePlain->text().toLocal8Bit().data(), leHash->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Message");
            mb->exec();
        }else{
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else{
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashSHA384() {
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    if(reFileName->exactMatch(leHash->text())){
        sha = new Sha();
        rep = sha->computeSha384(lePlain->text().toLocal8Bit().data(), leHash->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Message");
            mb->exec();
        }else{
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else{
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashSHA512() {
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    if(reFileName->exactMatch(leHash->text())){
        sha = new Sha();
        rep = sha->computeSha512(lePlain->text().toLocal8Bit().data(), leHash->text().toLocal8Bit().constData());
        if(rep == 1){
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Message");
            mb->exec();
        }else{
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else{
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashHmacSHA1()
{
    // La regex accepte uniquement les mots composé de lettres, de chiffres
    // De caractère spéciaux hormis le "." et l'espace (pour éviter de
    // Définir une nouvelle extension.
    reFileName = new QRegExp("([\\w]+)");

    // Let's derive the key given by the password
    fprintf(stdout, "passphrase: %s\n", leKey->text().toLocal8Bit().constData());

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
            return ;
    }

    gcry_md_write(hd, pass, pass_len);

    pass = gcry_md_read(hd, GCRY_MD_SHA256);

    printf("hash_len: %d\n", hash_len);

    fprintf(stdout, "Digest of key: ");
    print.printBuff(pass, hash_len);

    if(reFileName->exactMatch(leHash->text()))
    {
        sha = new Sha();
        rep = sha->computeHmacSha1(lePlain->text().toLocal8Bit().data(), leHash->text().toLocal8Bit().constData(), (const char *) pass);

        if(rep == 1)
        {
            mb = new QMessageBox(this);
            mb->setText("Cannot open one of the given files.");
            mb->setWindowTitle("Message");
            mb->exec();
        }
        else
        {
            mb = new QMessageBox(this);
            mb->setText("Success");
            mb->setWindowTitle("Message");
            mb->exec();
            this->close();
        }
    }
    else
    {
        mb = new QMessageBox(this);
        mb->setText("The given name doesn't respect the given format.");
        mb->setWindowTitle("Message");
        mb->exec();
    }
}

void Hash::hashHmacSHA224()
{

}

void Hash::hashHmacSHA256()
{

}

void Hash::hashHmacSHA384()
{

}

void Hash::hashHmacSHA512()
{

}
