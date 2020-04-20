#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
#include <Arduino.h>

void Wallet::createWallet(std::string masterUser, std::string pwd)
{
    /* 
        In order to use AES we need char* but for easier manipulation
        we will manipulate string so the manipulation folowing.
    */

    char ca[this->nbit + 1];
    strncpy(ca, pwd.c_str(), this->nbit);
    ca[this->nbit] = '\0';
    unsigned char shaResult[this->nbit];

    hash_data(ca, 32, shaResult);
    std::string pwd2 = pwd;
    int c = 0;
    while (this->nbit > pwd2.length()) {
        pwd2 += pwd2[c];
        c++;
    }
    // creation of the pointers necessary
    int n = 16;
    std::string str1 = pwd2.substr(0, 16);
    std::string str2 = pwd2.substr(16);

    char ca1[n + 1];
    strncpy(ca1, str1.c_str(), n);
    ca1[n] = '\0';

    char ca2[n + 1];
    strncpy(ca2, str2.c_str(), n);
    ca2[n] = '\0';

    // creation of the hash

    // way to stock the hash in an inderect way
    std::string mainkey_rng;

    mainkey_rng = generate_random_string(this->nbit);

    // declaring character array
    char rkey1[n];

    // copying the contents of the
    // string to char array
    strncpy(rkey1, mainkey_rng.substr(0, 16).c_str(), n);
    unsigned char S1[this->nbit];
    char rkey2[n];

    // copying the contents of the
    // string to char array
    strncpy(rkey2, mainkey_rng.substr(16).c_str(), n);
    unsigned char S2[this->nbit];
    //to implement later a beetter way to store the important data at rest
    // unsigned char main[this->nbit];
    //
    // std::string tpwd(reinterpret_cast<const char*>(shaResult), 32);
    // char* pk = reinterpret_cast<char*>(shaResult);
    // strncpy(S1, tpwd.c_str(), this->nbit + 1);
    // S1[nbit + 1] = '\0';
    // Serial.println("verif3");
    // Serial.println(tpwd.c_str());
    // Serial.println((char*)shaResult);
    // Serial.println(pk);
    // Serial.println(S1);

    // pwd_crypt(S1, rkey, main);

    // std::string mainkey(reinterpret_cast<const char*>(shaResult), this->nbit);
    // unsigned char check[this->nbit];

    // char* key = (char*)"concombre";
    // pwd_crypt(key, rkey, check);

    // Serial.println("verif1");
    // Serial.println(S1);
    // Serial.println(rkey);
    // Serial.println((char*)main);
    // this->mainkeys.push_back(main);
    // this->mainkeys.push_back(check);

    pwd_crypt(rkey1, ca1, S1);
    pwd_crypt(rkey2, ca2, S2);
    std::string tpwd1(reinterpret_cast<const char*>(S1), 16);
    std::string tpwd2(reinterpret_cast<const char*>(S2), 16);
    std::string hash(reinterpret_cast<const char*>(shaResult), 32);

    this->masterUser = masterUser;
    this->mainkey.push_back(tpwd1);
    this->mainkey.push_back(tpwd2);
    this->hashWord = (hash);
}

// std::string Wallet::testHash(std::string hash)
// {
//     int n2 = hash.length();
//     char main[n2];
//     strncpy(main, hash.c_str(), n2);

//     unsigned char rkey[this->nbit];
//     if (this->mainkeys[0] == this->test) {
//         Serial.println("on est bon");
//     }
//     Serial.println((char*)this->mainkeys[0]);
//     Serial.println((char*)this->test);
//     pwd_decrypt(this->mainkeys[0], main, rkey);
//     Serial.println("verif2");
//     std::string mainkey(reinterpret_cast<const char*>(rkey), 32);
//     Serial.println(hash.c_str());
//     Serial.println(mainkey.c_str());
//     Serial.println((char*)this->mainkeys[0]);

//     int n = hash.length();
//     char check[n];
//     strncpy(check, mainkey.c_str(), n);

//     unsigned char key[this->nbit];

//     pwd_decrypt(this->mainkeys[1], check, key);
//     std::string checkkey(reinterpret_cast<const char*>(key));

//     return checkkey;
// }

// std::string Wallet::getKey(std::string hash)
// {
//     char* main = new char[hash.size() + 1];
//     std::copy(hash.begin(), hash.end(), main);
//     main[hash.size()] = '\0';
//     unsigned char rkey[32];

//     pwd_decrypt(this->mainkeys[0], main, rkey);
//     std::string mainkey(reinterpret_cast<const char*>(rkey), 32);
// }

bool Wallet::unlock(std::string username, std::string pwd)
{
    if (this->masterUser != username) {
        return false;
    }
    char ca[this->nbit + 1];
    strncpy(ca, pwd.c_str(), this->nbit);
    ca[this->nbit] = '\0';
    unsigned char shaResult[this->nbit];

    hash_data(ca, 32, shaResult);

    std::string hash(reinterpret_cast<const char*>(shaResult), 32);

    if (hash == this->hashWord) {

        std::string pwd2 = pwd;
        int c = 0;
        while (this->nbit > pwd2.length()) {
            pwd2 += pwd2[c];
            c++;
        }
        // creation of the pointers necessary
        int n = 16;
        std::string str1 = pwd2.substr(0, 16);
        std::string str2 = pwd2.substr(16, 16);

        char ca1[n + 1];
        strncpy(ca1, pwd.c_str(), n);
        ca1[n] = '\0';

        char ca2[n + 1];
        strncpy(ca2, pwd.c_str(), n);
        ca2[n] = '\0';

        unsigned char ttest[this->nbit / 2 + 1];
        unsigned char t2test[this->nbit / 2 + 1];
        for (int i = 0; i <= this->nbit / 2; i++) {
            ttest[i] = this->mainkey[0].c_str()[i];
            t2test[i] = this->mainkey[1].c_str()[i];
        }
        unsigned char truekey1[this->nbit];
        unsigned char truekey2[this->nbit];
        // creation of the hash
        pwd_decrypt(ttest, ca1, truekey1);
        pwd_decrypt(t2test, ca1, truekey2);

        std::string tpwd1(reinterpret_cast<const char*>(truekey1), 16);
        std::string tpwd2(reinterpret_cast<const char*>(truekey2), 16);

        this->keys.push_back(tpwd1);
        this->keys.push_back(tpwd2);
        this->lock = false;

        return true;
    }
    Serial.println("oups");
    return false;
}

bool Wallet::addAccount(std::string username, std::string pwd, int len)
{
    /*
        This method is used to add an account in a wallet class
    */
    Serial.println("oui");
    if (this->lock == false) {
        std::string str1;
        std::string str2;
        if (username == "") {

            Serial.println("non1");
            return false;
        }

        if (pwd == "") {
            if (len <= 0 || pwd.length() > 32 || len > 32) {

                Serial.println("non2");
                return false;
            }
            pwd = generate_random_string(len);
        }
        if (pwd.length() > 16) {
            std::string pwd2 = pwd;
            // creation of the pointers necessary
            str1 = pwd2.substr(0, 16);
            str2 = pwd2.substr(16, 16);
            if (pwd.length() != 32) {
                str2[pwd.length() - 1] = ' ';
            }
        } else {
            str1 = pwd;
            str2 = " ";
        }
        int l = this->strongbox.size();

        Account acc;
        // in order to manipulate string outside wallet we need to transform a string in a char
        int n = 16;

        char ca1[n + 1];
        strncpy(ca1, str1.c_str(), n);
        ca1[n] = '\0';

        char ca2[n + 1];
        strncpy(ca2, str2.c_str(), n);
        ca2[n] = '\0';

        char key1[n + 1];
        strncpy(key1, this->keys[0].c_str(), n);
        key1[n] = '\0';

        char key2[n + 1];
        strncpy(key2, this->keys[1].c_str(), n);
        key2[n] = '\0';

        unsigned char cipherTextOutput1[16];
        unsigned char cipherTextOutput2[16];

        pwd_crypt(ca1, key1, cipherTextOutput1);
        pwd_crypt(ca2, key2, cipherTextOutput2);
        Serial.println(1);
        Serial.println(ca1);
        Serial.println(ca2);
        unsigned char ttest[17];
        unsigned char t2test[17];
        for (int j = 0; j < 16; j++) {
            ttest[j] = cipherTextOutput1[j];
            t2test[j] = cipherTextOutput2[j];
        }
        ttest[16] = '\0';
        t2test[16] = '\0';

        std::string tpwd1(reinterpret_cast<const char*>(ttest), strlen((char*)ttest));
        std::string tpwd2(reinterpret_cast<const char*>(t2test), strlen((char*)t2test));

        acc.initAccount(username, tpwd1 + tpwd2);

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
    this->lock = true;
    this->keys.clear();
}

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
    if (this->lock == false) {
        std::vector<std::string> pwds;
        int n = 16;
        char key1[n + 1];
        strncpy(key1, this->keys[0].c_str(), n);
        key1[n] = '\0';

        char key2[n + 1];
        strncpy(key2, this->keys[1].c_str(), n);
        key2[n] = '\0';

        for (auto& acc : this->strongbox) {
            std::string str1 = acc.getPwd().substr(0, 16);
            std::string str2 = acc.getPwd().substr(16);

            Serial.println(str1.c_str());
            Serial.println(str2.c_str());
            Serial.println(key2);

            unsigned char ttest[17];
            unsigned char t2test[17];
            Serial.println("test");
            for (int j = 0; j < 16; j++) {
                ttest[j] = str1[j];
                t2test[j] = str2[j];
            }
            ttest[16] = '\0';
            t2test[16] = '\0';

            unsigned char decipheredTextOutput1[16];
            unsigned char decipheredTextOutput2[16];

            pwd_decrypt(ttest, key1, decipheredTextOutput1);
            pwd_decrypt(t2test, key2, decipheredTextOutput2);

            std::string tpwd1(reinterpret_cast<const char*>(decipheredTextOutput1), strlen((char*)ttest));
            std::string tpwd2(reinterpret_cast<const char*>(decipheredTextOutput2), strlen((char*)t2test));

            std::string pwd = tpwd1 + tpwd2;
            int c = 0;

            while (pwd[c] != ' ') {
                c++;
            }

            pwds.push_back(pwd.substr(0, c));
        }
        return pwds;
    }
}

bool Wallet::changeMasterUsername(std::string Username)
{
    if (this->lock == false) {
        this->masterUser = Username;
        return true;
    }
    return false;
}
bool Wallet::changeUsername(std::string Username, std::string pwd, std::string newUsername)
{
    if (this->lock == false) {
        std::vector<std::string> pwds = this->getPwd();
        std::vector<int> posible;
        for (int i = 0; i < pwds.size(); i++) {
            if (pwds[i] == pwd) {
                posible.push_back(i);
            }
        }
        std::vector<int> posible2;
        for (auto& pos : posible) {
            if (this->strongbox[pos].getUsername() == Username) {
                posible2.push_back(pos);
            }
        }
        if (posible2.size() == 1) {
            this->strongbox[posible2[0]].changeUsername(newUsername);
            return true;
        }
        return false;
    }
    return false;
}

bool Wallet::changePwd(std::string Username, std::string pwd, std::string newpwd, int len)
{
    if (this->lock == false) {
        std::vector<std::string> pwds = this->getPwd();
        std::vector<int> posible;
        for (int i = 0; i < pwds.size(); i++) {
            if (pwds[i] == pwd) {
                posible.push_back(i);
            }
        }
        std::vector<int> posible2;
        for (auto& pos : posible) {
            if (this->strongbox[pos].getUsername() == Username) {
                posible2.push_back(pos);
            }
        }
        if (posible2.size() == 1) {
            std::string str1;
            std::string str2;

            if (pwd == "") {
                if (len <= 0 || newpwd.length() > 32 || len > 32) {
                    return false;
                }
                pwd = generate_random_string(len);
            }
            if (newpwd.length() > 16) {
                std::string pwd2 = pwd;
                // creation of the pointers necessary
                str1 = pwd2.substr(0, 16);
                str2 = pwd2.substr(16, 16);
                if (pwd.length() != 32) {
                    str2[pwd.length() - 1] = ' ';
                }
            } else {
                str1 = pwd;
                str2 = " ";
            }
            int l = this->strongbox.size();

            Account acc;
            // in order to manipulate string outside wallet we need to transform a string in a char
            int n = 16;

            char ca1[n + 1];
            strncpy(ca1, str1.c_str(), n);
            ca1[n] = '\0';

            char ca2[n + 1];
            strncpy(ca2, str2.c_str(), n);
            ca2[n] = '\0';

            char key1[n + 1];
            strncpy(key1, this->keys[0].c_str(), n);
            key1[n] = '\0';

            char key2[n + 1];
            strncpy(key2, this->keys[1].c_str(), n);
            key2[n] = '\0';

            unsigned char cipherTextOutput1[16];
            unsigned char cipherTextOutput2[16];

            pwd_crypt(ca1, key1, cipherTextOutput1);
            pwd_crypt(ca2, key2, cipherTextOutput2);
            Serial.println(1);
            Serial.println(ca1);
            Serial.println(ca2);
            unsigned char ttest[17];
            unsigned char t2test[17];
            for (int j = 0; j < 16; j++) {
                ttest[j] = cipherTextOutput1[j];
                t2test[j] = cipherTextOutput2[j];
            }
            ttest[16] = '\0';
            t2test[16] = '\0';

            std::string tpwd1(reinterpret_cast<const char*>(ttest), strlen((char*)ttest));
            std::string tpwd2(reinterpret_cast<const char*>(t2test), strlen((char*)t2test));
            this->strongbox[posible2[0]].changePwd(tpwd1 + tpwd2);
            return true;
        }
        return false;
    }
    return false;
}
