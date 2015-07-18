#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <gmp.h>

typedef struct{
    unsigned char* string;
    unsigned int size;
}buff_t;

class Util
{
    public:
        static buff_t convert(mpz_t,unsigned int);
        void printBuff(unsigned char *, int);
};

#endif // UTIL_H
