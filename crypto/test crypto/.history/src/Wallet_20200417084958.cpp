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
    Serial.println("1");

    Serial.println((char*)shaResult);
    // way to stock the hash in an inderect way
    Serial.println("2");
    std::string mainkey_rng;
    std::string::size_type len = 32;

    mainkey_rng = generate_random_string(32);
    Serial.println("3");

    char* rkey = new char[mainkey_rng.size() + 1];
    std::copy(mainkey_rng.begin(), mainkey_rng.end(), ca);
    rkey[mainkey_rng.size()] = '\0';
    Serial.println(mainkey_rng.c_str());
    Serial.println((char*)rkey);
    unsigned char main[32];

    char* S1 = reinterpret_cast<char*>(shaResult);

    pwd_crypt(S1, rkey, main);

    std::string mainkey(reinterpret_cast<const char*>(main), 32);
    unsigned char check[32];
    Serial.println("d");
    Serial.println((char*)main);

    char* key = (char*)"concombre";
    pwd_crypt(rkey, key, check);
    std::string checkkey(reinterpret_cast<const char*>(check), 32);

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
    main[this->mainkeys[0].size()] = '\0';
    unsigned char rkey[32];
    Serial.println("?");
    Serial.println((char*)shaResult);
    pwd_decrypt(shaResult, main, rkey);
    Serial.println("c");
    Serial.println((char*)shaResult);
    std::string mainkey(reinterpret_cast<const char*>(main), 32);
    char* check = new char[this->mainkeys[0].size() + 1];
    std::copy(this->mainkeys[1].begin(), this->mainkeys[1].end(), check);
    check[this->mainkeys[0].size()] = '\0';
    unsigned char key[32];
    char* test = (char*)"concombre";
    unsigned char* keyT = (unsigned char*)(test);
    pwd_decrypt(rkey, check, key);
    if (keyT == key) {
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
    if (username == "" || pwd == "") {
        return false;
    }
    Account acc;
    int l = this->strongbox.size();

    acc.initAccount(username, pwd);
    this->strongbox.push_back(acc);
    if (l + 1 == this->strongbox.size()) {
        return true;
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
