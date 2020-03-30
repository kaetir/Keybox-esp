#include "mbedtls/aes.h"
#include "mbedtls/md.h"

void pwd_crypt(char * plainText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void pwd_decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void setup_AES() {

  Serial.begin(115200);

  char * key = "abcdefghijklmnop";

  char *plainText = "test";
  unsigned char cipherTextOutput[16];
  unsigned char decipheredTextOutput[16];

  encrypt(plainText, key, cipherTextOutput);
  decrypt(cipherTextOutput, key, decipheredTextOutput);

  Serial.println("\nOriginal plain text:");
  Serial.println(plainText);

  Serial.println("\nCiphered text:");
  for (int i = 0; i < 16; i++) {

    char str[3];

    sprintf(str, "%02x", (int)cipherTextOutput[i]);
    Serial.print(str);
  }

  Serial.println("\n\nDeciphered text:");
  for (int i = 0; i < 16; i++) {
    Serial.print((char)decipheredTextOutput[i]);
  }
}

byte * hash_data(char * payload, char * md_type, unsigned char * outputBuffer){

  mbedtls_md_context_t ctx;
  byte shaResult[32];

  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *) payload, payloadLength);
  mbedtls_md_finish(&ctx, shaResult);
  mbedtls_md_free(&ctx);

  return (shaResult);
}

void setup(){
 
  Serial.begin(115200);
 
  char *payload = "Hello SHA 256!";
  byte shaResult[32];
 
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  const size_t payloadLength = strlen(payload);         
 
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *) payload, payloadLength);
  mbedtls_md_finish(&ctx, shaResult);
  mbedtls_md_free(&ctx);
 
  Serial.print("Hash: ");
 
  for(int i= 0; i< sizeof(shaResult); i++){
      char str[3];
 
      sprintf(str, "%02x", (int)shaResult[i]);
      Serial.print(str);
  }
}
 
void loop(){}