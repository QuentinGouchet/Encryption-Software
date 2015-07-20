#include "aes.h"

AES::AES(){}

#ifdef __cplusplus
extern "C" {
#endif

int AES::generateKey(unsigned int nbits, const char *root_keys)
{
    FILE* keyFile;

    char pathKey[100];
    unsigned char *buff = NULL;
    unsigned i;
    int err = 0;

    // Making sure that the security strength is *at least* nbits
    unsigned nbytes = (nbits%8==0)?(nbits/8):(nbits/8+1);

    if(!sprintf(pathKey, "../ressources/%s.key", root_keys)) {
        err = 1;
        goto out;
    }

    buff = (unsigned char *) gcry_malloc(nbytes*sizeof(char*));

    gcry_randomize(buff, nbytes, GCRY_STRONG_RANDOM);

    if((keyFile = fopen(pathKey, "w")) == NULL)
    {
        err = 1;
        goto out;
    }
    else
    {
        for(i=0; i<nbytes; i++)
            fprintf(keyFile, "%02x", buff[i]);
        fprintf(keyFile, "\n");
    }

    out:
        if(keyFile)
            fclose(keyFile);
        if(buff)
            gcry_free(buff);

    return err;
}

int AES::aes_cbc_128_encrypt(const char *plaintextPath, const char *key,
                     const char *cipherPath, const char *iv)
{
    FILE *plaintextFile = NULL;
    FILE *ciphertextFile = NULL;

    int blklen = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES);

    unsigned char *fileContent = NULL;
    unsigned char *ciphertext = NULL;

    char pathCipherFile[50];

    long fsize = 0;
    int plaintext_len, ciphertext_len, i;

    gcry_cipher_hd_t hd = NULL;
    gcry_error_t err = 0;

    Util print;

    printf("iv: ");
    print.printBuff((unsigned char *)iv, blklen);
    printf("key: ");
    print.printBuff((unsigned char *)key, blklen);

    if((plaintextFile = fopen(plaintextPath, "r")) == NULL)
    {
        err = 1;
        fprintf(stderr, "fopen() failure on plaintext file\n");
        goto out;
    }

    if(fseek(plaintextFile, 0, SEEK_END))
    {
        err = 1;
        fprintf(stderr, "fseek() failure on plaintext file\n");
        goto out;
    }

    if((fsize = ftell(plaintextFile)) == -1L)
    {
        err = 1;
        fprintf(stderr, "ftell() failure on plaintext file\n");
        goto out;
    }

    plaintext_len = fsize-1;
    ciphertext_len = (plaintext_len % blklen == 0) ? plaintext_len + blklen :
                     plaintext_len + (blklen - (plaintext_len % blklen));
    fprintf(stdout, "ciphertext: %d\n", ciphertext_len);

    if(fseek(plaintextFile, 0, SEEK_SET))
    {
        err = 1;
        fprintf(stderr, "fseek() failure on plaintext file\n");
        goto out;
    }

    fileContent = (unsigned char *) gcry_malloc_secure(sizeof(unsigned char)*ciphertext_len);
    if(fileContent == NULL)
    {
        err = 1;
        fprintf(stderr, "Could not allocate memory!\n");
        goto out;
    }

    if(fread(fileContent, 1, plaintext_len, plaintextFile) != plaintext_len)
    {
        err = 1;
        fprintf(stderr, "fread() failure on plaintext file\n");
        goto out;
    }

    fileContent[plaintext_len] = 0x10;

    fprintf(stdout, "FileContent: ");
    print.printBuff(fileContent, ciphertext_len);

    err = gcry_cipher_open(&hd, GCRY_CIPHER_AES, GCRY_CIPHER_MODE_CBC, 0);
    if(err)
    {
        err = 1;
        fprintf(stderr, "gcry_cipher_open() error\n");
        goto out;
    }

    err = gcry_cipher_setkey(hd, key, blklen);
    if(err)
    {
        err = 1;
        fprintf(stderr, "gcry_cipher_setkey() error\n");
        goto out;
    }

    err = gcry_cipher_setiv(hd, iv, blklen);

    if(err)
     {
        err = 1;
        fprintf(stderr, "gcry_cipher_setkey() error\n");
        goto out;
    }

    ciphertext_len = plaintext_len + (blklen - (plaintext_len % blklen));

    fprintf(stdout, "plainlen: %d\n", plaintext_len);

    err = gcry_cipher_encrypt(hd, fileContent, ciphertext_len, NULL, 0);

    fprintf(stdout, "FileContent: ");
    print.printBuff(fileContent, ciphertext_len);

    if(err)
    {
        err = 1;
        fprintf (stderr, "Failure: %s/%s\n",
                            gcry_strsource (err),
                            gcry_strerror (err));
        goto out;
    }

    sprintf(pathCipherFile, "../ressources/%s.cipher", cipherPath);

    if((ciphertextFile = fopen(pathCipherFile, "w")) == NULL)
    {
        err = 1;
        fprintf(stderr, "fopen() error on ciphertext file\n");
        goto out;
    }

    printf("%s\n", pathCipherFile);

    if(!fwrite)
    {
        err = 1;
        fprintf(stderr, "Could not write into cipher file\n");
        goto out;
    }

    //fprintf(ciphertextFile, "%s", ciphertext);

    //memcpy((void *) fileContent, "00000", 5);

    //fprintf(stdout, "%s\n", fileContent);

    //err = gcry_cipher_decrypt(hd, fileContent, ciphertext_len, ciphertext, ciphertext_len);

    //fprintf(stdout, "%s\n", fileContent);

    if(!err)
        fprintf(stdout, "Encryption successful\n");

    out:
        if(hd)
            gcry_cipher_close(hd);
        if(plaintextFile)
            fclose(plaintextFile);
        if(ciphertextFile)
            fclose(ciphertextFile);
        if(fileContent)
            gcry_free(fileContent);
        return err;
}

int AES::aes_cbc_128_decrypt(const char *plaintextPath, const char *key,
                     const char *cipherPath, const char *iv)
{
    FILE *plaintextFile = NULL;
    FILE *ciphertextFile = NULL;

    int blklen = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES);

    unsigned char *fileContent = NULL;
    unsigned char *ciphertext = NULL;

    char pathCipherFile[50];

    long fsize = 0;
    int plaintext_len, ciphertext_len, i;

    gcry_cipher_hd_t hd = NULL;
    gcry_error_t err = 0;

    Util print;

    printf("iv: ");
    print.printBuff((unsigned char *)iv, blklen);
    printf("key: ");
    print.printBuff((unsigned char *)key, blklen);

    if((plaintextFile = fopen(plaintextPath, "r")) == NULL)
    {
        err = 1;
        fprintf(stderr, "fopen() failure on plaintext file\n");
        goto out;
    }

    if(fseek(plaintextFile, 0, SEEK_END))
    {
        err = 1;
        fprintf(stderr, "fseek() failure on plaintext file\n");
        goto out;
    }

    if((fsize = ftell(plaintextFile)) == -1L)
    {
        err = 1;
        fprintf(stderr, "ftell() failure on plaintext file\n");
        goto out;
    }

    plaintext_len = fsize-1;
    ciphertext_len = (plaintext_len % blklen == 0) ? plaintext_len + blklen :
                     plaintext_len + (blklen - (plaintext_len % blklen));
    fprintf(stdout, "ciphertext: %d\n", ciphertext_len);

    if(fseek(plaintextFile, 0, SEEK_SET))
    {
        err = 1;
        fprintf(stderr, "fseek() failure on plaintext file\n");
        goto out;
    }

    fileContent = (unsigned char *) gcry_malloc_secure(sizeof(unsigned char)*ciphertext_len);
    if(fileContent == NULL)
    {
        err = 1;
        fprintf(stderr, "Could not allocate memory!\n");
        goto out;
    }

    if(fread(fileContent, 1, plaintext_len, plaintextFile) != plaintext_len)
    {
        err = 1;
        fprintf(stderr, "fread() failure on plaintext file\n");
        goto out;
    }

    fileContent[plaintext_len] = 0x10;

    fprintf(stdout, "FileContent: ");
    print.printBuff(fileContent, ciphertext_len);

    err = gcry_cipher_open(&hd, GCRY_CIPHER_AES, GCRY_CIPHER_MODE_CBC, 0);
    if(err)
    {
        err = 1;
        fprintf(stderr, "gcry_cipher_open() error\n");
        goto out;
    }

    err = gcry_cipher_setkey(hd, key, blklen);
    if(err)
    {
        err = 1;
        fprintf(stderr, "gcry_cipher_setkey() error\n");
        goto out;
    }

    err = gcry_cipher_setiv(hd, iv, blklen);

    if(err)
     {
        err = 1;
        fprintf(stderr, "gcry_cipher_setkey() error\n");
        goto out;
    }

    ciphertext_len = plaintext_len + (blklen - (plaintext_len % blklen));

    fprintf(stdout, "plainlen: %d\n", plaintext_len);

    err = gcry_cipher_decrypt(hd, fileContent, ciphertext_len, NULL, 0);

    fprintf(stdout, "FileContent: ");
    print.printBuff(fileContent, ciphertext_len);

    if(err)
    {
        err = 1;
        fprintf (stderr, "Failure: %s/%s\n",
                            gcry_strsource (err),
                            gcry_strerror (err));
        goto out;
    }

    sprintf(pathCipherFile, "../ressources/%s.cipher", cipherPath);

    if((ciphertextFile = fopen(pathCipherFile, "w")) == NULL)
    {
        err = 1;
        fprintf(stderr, "fopen() error on ciphertext file\n");
        goto out;
    }

    printf("%s\n", pathCipherFile);

    if(!fwrite)
    {
        err = 1;
        fprintf(stderr, "Could not write into cipher file\n");
        goto out;
    }

    //fprintf(ciphertextFile, "%s", ciphertext);

    //memcpy((void *) fileContent, "00000", 5);

    //fprintf(stdout, "%s\n", fileContent);

    //err = gcry_cipher_decrypt(hd, fileContent, ciphertext_len, ciphertext, ciphertext_len);

    //fprintf(stdout, "%s\n", fileContent);

    if(!err)
        fprintf(stdout, "Decryption successful\n");

    out:
        if(hd)
            gcry_cipher_close(hd);
        if(plaintextFile)
            fclose(plaintextFile);
        if(ciphertextFile)
            fclose(ciphertextFile);
        if(fileContent)
            gcry_free(fileContent);
        return err;
}

#ifdef __cplusplus
}
#endif
