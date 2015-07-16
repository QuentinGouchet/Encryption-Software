#ifndef DSA_H
#define DSA_H

#include "stdio.h"
#include "time.h"
#include "gmp.h"
#include "stdlib.h"

class DSA2
{

public:
    DSA2();
    int generateKey(const char*);
    int sign(const char*, const char*, const char*, const char*);
    int verify(const char*, const char*, const char*);
};

#endif // DSA_H
