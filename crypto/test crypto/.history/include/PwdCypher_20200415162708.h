#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include <stdio.h>
#include <string.h>
#include <sys/lock.h>

void pwd_crypt(char* plainText, char* key, unsigned char* outputBuffer);

void pwd_decrypt(unsigned char* chipherText, char* key, unsigned char* outputBuffer);

void hash_data(char* payload, int payloadLength, unsigned char* outputBuffer);
