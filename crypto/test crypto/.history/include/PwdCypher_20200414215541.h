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

void pwd_crypt();

void pwd_decrypt();

void setup_AES();

void hash_data();

void setup_hash();

void esp_aes_xts_init(esp_aes_xts_context* ctx);

void esp_aes_xts_free(esp_aes_xts_context* ctx);

static int esp_aes_xts_decode_keys(const unsigned char* key,
    unsigned int keybits,
    const unsigned char** key1,
    unsigned int* key1bits,
    const unsigned char** key2,
    unsigned int* key2bits);

int esp_aes_xts_setkey_enc(esp_aes_xts_context* ctx,
    const unsigned char* key,
    unsigned int keybits);

int esp_aes_xts_setkey_dec(esp_aes_xts_context* ctx,
    const unsigned char* key,
    unsigned int keybits);

/* Endianess with 64 bits values */
#ifndef GET_UINT64_LE
#define GET_UINT64_LE(n, b, i)               \
    {                                        \
        (n) = ((uint64_t)(b)[(i) + 7] << 56) \
            | ((uint64_t)(b)[(i) + 6] << 48) \
            | ((uint64_t)(b)[(i) + 5] << 40) \
            | ((uint64_t)(b)[(i) + 4] << 32) \
            | ((uint64_t)(b)[(i) + 3] << 24) \
            | ((uint64_t)(b)[(i) + 2] << 16) \
            | ((uint64_t)(b)[(i) + 1] << 8)  \
            | ((uint64_t)(b)[(i)]);          \
    }
#endif

#ifndef PUT_UINT64_LE
#define PUT_UINT64_LE(n, b, i)                     \
    {                                              \
        (b)[(i) + 7] = (unsigned char)((n) >> 56); \
        (b)[(i) + 6] = (unsigned char)((n) >> 48); \
        (b)[(i) + 5] = (unsigned char)((n) >> 40); \
        (b)[(i) + 4] = (unsigned char)((n) >> 32); \
        (b)[(i) + 3] = (unsigned char)((n) >> 24); \
        (b)[(i) + 2] = (unsigned char)((n) >> 16); \
        (b)[(i) + 1] = (unsigned char)((n) >> 8);  \
        (b)[(i)] = (unsigned char)((n));           \
    }
#endif

/*
 * GF(2^128) multiplication function
 *
 * This function multiplies a field element by x in the polynomial field
 * representation. It uses 64-bit word operations to gain speed but compensates
 * for machine endianess and hence works correctly on both big and little
 * endian machines.
 */
static void esp_gf128mul_x_ble(unsigned char r[16],
    const unsigned char x[16])
{
    uint64_t a, b, ra, rb;

    GET_UINT64_LE(a, x, 0);
    GET_UINT64_LE(b, x, 8);

    ra = (a << 1) ^ 0x0087 >> (8 - ((b >> 63) << 3));
    rb = (a >> 63) | (b << 1);

    PUT_UINT64_LE(ra, r, 0);
    PUT_UINT64_LE(rb, r, 8);
}

/*
 * AES-XTS buffer encryption/decryption
 */
int esp_aes_crypt_xts(esp_aes_xts_context* ctx,
    int mode,
    size_t length,
    const unsigned char data_unit[16],
    const unsigned char* input,
    unsigned char* output);