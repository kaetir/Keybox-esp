#include <stdio.h>
#include <string.h>
#include <sys/lock.h>

#include "mbedtls/aes.h"
#include "mbedtls/md.h"

/**
 * @brief  Cipher a data
 * @param plainText the data we want to cipher
 * @param key  the encryption key
 * @param outputBuffer  the output buffer
 */
void pwd_crypt(char* plainText, char* key, unsigned char* outputBuffer);
/**
 * @brief  Secipher a data
 * @param chipherText the data we want to decipher
 * @param key  the encryption key
 * @param outputBuffer  the output buffer
 */
void pwd_decrypt(unsigned char* chipherText, char* key,
                 unsigned char* outputBuffer);
/**
 * @brief  Hash a data
 * @param plainText the data we want to hash
 * @param payloadLength  the lenght of the data
 * @param outputBuffer  the output buffer
 */
void hash_data(char* payload, int payloadLength, unsigned char* outputBuffer);
