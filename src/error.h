#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

class Error
{
public:
    Error();

    typedef struct error_code {
        int error;
        const char *msg;
    }error_code;

    error_code errors[];
};



#endif // ERROR_H
