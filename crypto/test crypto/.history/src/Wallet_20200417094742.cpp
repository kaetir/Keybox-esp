#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
#include <Arduino.h>

void Wallet::createWallet(std::string masterUser, std::string masterWord)
{
    /* 
        In order to use AES we need char* but for easier manipulation
        we will manipulate string so the manipulation folowing.
    */

    // creation of the pointers necessary
    char* ca = new char[masterWord.size() + 1];
    std::copy(masterWord.begin(), masterWord.end(), ca);
    ca[masterWord.size()] = '\0';
    unsigned char shaResult[32];
    // creation of the hash

    hash_data(ca, masterWord.size(), shaResult);

    Serial.println((char*)shaResult);
    // way to stock the hash in an inderect way
    std::string mainkey_rng;
    std::string::size_type len = 32;

    mainkey_rng = generate_random_string(32);

    int n = mainkey_rng.length();

    // declaring character array
    char rkey[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(rkey, mainkey_rng.c_str());
    unsigned char main[32];

    char* S1 = reinterpret_cast<char*>(shaResult);

    pwd_crypt(S1, rkey, main);

    std::string mainkey(reinterpret_cast<const char*>(shaResult), 32);
    unsigned char check[32];

    char* key = (char*)"concombre";
    pwd_crypt(rkey, key, check);
    std::string checkkey(reinterpret_cast<const char*>(check), 32);
    unsigned char S2[32];
    pwd_decrypt(main, rkey, S2);
    Serial.println((char*)S1);
    Serial.println((char*)S2);
    this->mainkeys.push_back(mainkey);
    this->mainkeys.push_back(checkkey);
}

bool Wallet::checkValid(std::string masterWord)
{

    char* ca = new char[masterWord.size() + 1];
    std::copy(masterWord.begin(), masterWord.end(), ca);
    ca[masterWord.size()] = '\0';
    unsigned char shaResult[32];
    // creation of the hash
    hash_data(ca, masterWord.size(), shaResult);
    char* main = new char[this->mainkeys[0].size() + 1];
    std::copy(this->mainkeys[0].begin(), this->mainkeys[0].end(), main);
    std::string checkkey(reinterpret_cast<const char*>(shaResult), 32);
    main[this->mainkeys[0].size()] = '\0';
    unsigned char rkey[32];
    pwd_decrypt(shaResult, main, rkey);
    std::string mainkey(reinterpret_cast<const char*>(main), 32);
    char* check = new char[this->mainkeys[0].size() + 1];
    std::copy(this->mainkeys[1].begin(), this->mainkeys[1].end(), check);
    check[this->mainkeys[0].size()] = '\0';
    unsigned char key[32];
    char* test = (char*)"concombre";
    unsigned char* keyT = (unsigned char*)(test);
    pwd_decrypt(rkey, check, key);

    if (this->mainkeys[0] == checkkey) {
        std::string sName(reinterpret_cast<char*>(shaResult));
        this->hashWord = sName;
        this->lock = false;
        return true;
    }

    return false;
}

bool Wallet::addAccount(std::string username, std::string pwd)
{
    /*
        This method is used to add an account in a wallet class
    */
    if (this->lock == false) {
        if (username == "" || pwd == "") {
            return false;
        }
        Account acc;

        // in order to manipulate string outside wallet we need to transform a string in a char
        char* key = this->stringToChar(this->hashWord);
        char* pwdchar = = this->stringToChar(pwd);
        strcpy(key, this->hashWord.c_str());
        unsigned char cipherTextOutput[32];
        unsigned char decipheredTextOutput[32];

        pwd_crypt(pwdchar, key, cipherTextOutput);
        pwd_decrypt(cipherTextOutput, key, decipheredTextOutput);
        acc.initAccount(username, pwd);
        this->strongbox.push_back(acc);
        if (l + 1 == this->strongbox.size()) {
            return true;
        }
        return false;
    }
    return false;
}

void Wallet::locked()
{
    this->hashWord = "";
    this->lock = true;
}

bool unlock();

std::vector<std::string> Wallet::getUsers()
{
    std::vector<std::string> users;
    for (auto& acc : this->strongbox) {
        users.push_back(acc.getUsername());
    }
    return users;
}

std::vector<std::string> Wallet::getPwd()
{
    std::vector<std::string> pwds;
    for (auto& acc : this->strongbox) {
        pwds.push_back(acc.getPwd());
    }
    return pwds;
}

char* Wallet::stringToChar(std::string strin)
{
    int n = strin.length();
    char chr[n + 1];
    strcpy(chr, strin.c_str());
    return chr;
}