#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include "PwdCypher.h"

void pwd_crypt(char* plainText, char* key, unsigned char* outputBuffer)
{

    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key, strlen(key) * 8);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
    mbedtls_aes_free(&aes);
}

void pwd_decrypt(unsigned char* chipherText, char* key, unsigned char* outputBuffer)
{

    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, (const unsigned char*)key, strlen(key) * 8);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
    mbedtls_aes_free(&aes);
}

void hash_data(char* payload, int payloadLength, unsigned char* outputBuffer)
{

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char*)payload, payloadLength);
    mbedtls_md_finish(&ctx, outputBuffer);
    mbedtls_md_free(&ctx);
}
