#ifndef DES_H
#define DES_H

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

class DES
{

public:
    DES();
    int des3_cbc_encrypt(const char *, const char *, const char *, const char *);
    int des3_cbc_decrypt(const char *, const char *, const char *, const char *);
};

#endif // DES_H
