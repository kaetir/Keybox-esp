#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include <stdio.h>
#include <string.h>
#include <sys/lock.h>

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/aes.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/aes.h"
#endif

void pwd_crypt(char* plainText, char* key, unsigned char* outputBuffer);

void pwd_decrypt(unsigned char* chipherText, char* key, unsigned char* outputBuffer);

void setup_AES();

void hash_data(char* payload, int payloadLength, unsigned char* outputBuffer);

void setup_hash();

