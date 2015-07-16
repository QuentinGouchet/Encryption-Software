#include "error.h"

Error::Error() {}

Error::error_code errors[] = {
    {0x10, "Error NULL pointer"},
    {0x11, "Cannot open file"},

    {0x21, "Error wirg sprintf function"},
    {0x22, "Error with fprintf function"},

    {0x30, "Error with SHA_Init function"},
    {0x31, "Error with SHA_Update function"},
    {0x32, "Error with SHA_Final function"},
    {0x33, "Error with EVP_CIPHER_CTX_new function"},
    {0x34, "Error with EVP_EncryptInit_ex function"},
    {0x35, "Error with EVP_EncryptUpdate function"},
    {0x36, "Error with EVP_Encrypt_Final function"},

    {0x40, "Error with ftell function"},
    {0x41, "Error with fseek function"},
    {0x42, "Error with fread function"}
};

