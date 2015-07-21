#ifndef SHA_H
#define SHA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gcrypt.h>

#include "util.h"

typedef unsigned char u8;
typedef unsigned long long int u16;

class Sha
{

public:
    Sha();
    int computeSha1_dep(const char*, const char*);
    int computeSha1(const char*, const char*);
    int computeSha224(const char *, const char *);
    int computeSha256(const char *, const char *);
    int computeSha384(const char *, const char *);
    int computeSha512(const char *, const char *);
    int computeHmacSha1(const char *, const char *, const char *);
    int computeHmacSha224(const char *, const char *, const char *);
    int computeHmacSha256(const char *, const char *, const char *);
    int computeHmacSha384(const char *, const char *, const char *);
    int computeHmacSha512(const char *, const char *, const char *);

private:
    void print_hex(u8*,int,const char*);
    u16 string_size(char*);
    void compute_sha1(u8*,u8*,unsigned long long int);
    void H(u8*,u8*,u8*,u8*);
    void G(u8*,u8*,u8*,u8*);
    void F(u8*,u8*,u8*,u8*);
    void u8_xor(u8*,u8*,u8*);
    void shift_left(u8*,u8*,u8);
    void add(u8*,u8*,u8*);
    void u8_memcpy(u8*,u8*,u16);
};

#endif // SHA_H
