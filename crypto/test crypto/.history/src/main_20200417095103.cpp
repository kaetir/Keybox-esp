#include <Arduino.h>
#include "RandomPwdGenerator.h"
#include "Wallet.h"
#include "PwdCypher.h"
#include <iostream>
#include <string>
using namespace std;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.print("Ok");
    std::string username = "Fire";
    std::string pwd = "azertymaqsdezed";
    Wallet wallet;
    wallet.createWallet(username, pwd);
    if ((wallet.checkValid(pwd) == true)) {
        Serial.print("c'est génial");
    } else {
        Serial.print("c'est nul");
    }
    addAccount(username, string pwd);
}

void setup_AES()
{
    // example of how to use AES

    char* key = (char*)"abcdefghijklmnop";

    char* plainText = (char*)"test";
    unsigned char cipherTextOutput[16];
    unsigned char decipheredTextOutput[16];

    pwd_crypt(plainText, key, cipherTextOutput);
    pwd_decrypt(cipherTextOutput, key, decipheredTextOutput);

    Serial.println("\nOriginal plain text:");
    Serial.println(plainText);

    Serial.println("\nCiphered text:");
    for (int i = 0; i < 16; i++) {

        char str[16];

        sprintf(str, "%02x", (int)cipherTextOutput[i]);
        Serial.print(str);
    }

    Serial.println("\n\nDeciphered text:");
    for (int i = 0; i < 16; i++) {
        Serial.print((char)decipheredTextOutput[i]);
    }
}

void setup_hash()
{
    // exemple of how to hash a data

    char* payload = (char*)"Hello SHA 256!";
    unsigned char shaResult[32];
    int l = strlen(payload);
    hash_data(payload, l, shaResult);

    Serial.print("Hash: ");

    for (int i = 0; i < sizeof(shaResult); i++) {
        char str[16];

        sprintf(str, "%02x", (int)shaResult[i]);
        Serial.print(str);
    }
}

void loop()
{
    /*
    // put your main code here, to run repeatedly:

    std::string username = "Fire";
    std::string pwd = "azertymaqsde";
    Serial.println(10, BIN);
    Wallet wallet;
    wallet.createWallet(username, pwd);
    Serial1.print(wallet.checkValid(pwd));
    Serial.println(10, HEX);
    vTaskDelay(500000000);*/
}