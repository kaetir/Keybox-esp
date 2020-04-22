#include <Arduino.h>
#include "Wallet.h"
#include <iostream>
#include <string>
#include "FS.h"
#include "SPIFFS.h"
using namespace std;

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

void setup()
{
    // Initialize serial port
    Serial.begin(9600);
    std::string username = "FireWolf";
    std::string pwd = "jenesaisplusquo";
    std::string count = "laposte";
    std::string account = "loupio";
    std::string pwdacc = "jenesaisplusquo";
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
    } else {
        Wallet wallet;
        Wallet temp;
        unsigned char output[32];
        hash_data((char*)"coucou", 6, output);
        for (int i = 0; i < 32; i++) {
            char str[4];

            sprintf(str, "%02x", (int)output[i]);
            Serial.print(str);
        }
        temp.createWallet(username, pwd);
        temp.unlock(pwd);
        temp.addAccount(count, account, pwdacc);
        std::vector<std::vector<std::string>> strongbox2 = temp.getAccounts();
        Serial.println("Account 1");
        for (auto& acc : strongbox2) {
            Serial.println(acc[0].c_str());
            Serial.println(acc[1].c_str());
            Serial.println(acc[2].c_str());
        }
        temp.saveWallet();
        wallet.initWalletJson();
        wallet.unlock(pwd);
        std::vector<std::vector<std::string>> strongbox = wallet.getAccounts();
        Serial.println("Account 2");
        for (auto& acc : strongbox) {
            Serial.println(acc[0].c_str());
            Serial.println(acc[1].c_str());
            Serial.println(acc[2].c_str());
        }
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