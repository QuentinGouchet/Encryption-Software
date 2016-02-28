#ifndef AES_H
#define AES_H

#include <linux/random.h>
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <gcrypt.h>
#include "error.h"
#include "util.h"

class AES
{

public:
    AES();
    int generateKey(unsigned int, const char *);
    int aes_cbc_128_encrypt(const char *, const char *, const char *, const char *);
    int aes_cbc_128_decrypt(const char *, const char *, const char *);
    int aes_cbc_256_encrypt(const char *, const char *, const char *, const char *);
    int aes_cbc_256_decrypt(const char *, const char *, const char *, const char *);
};

#endif // AES_H
