#include "Wallet.h"
#include "ArduinoJson.h"
#include <bits/stdc++.h>

Wallet ::Wallet()
{
    this->lock = true;
    this->nbit = 32;
}

std::string getWalletJson(fs::FS& fs)
{
    std::string file_str;
    //OPEN THE FILE
    File file = fs.open("/wallet.json");
    if (!file || file.isDirectory()) {
        file.close();
        Serial.print("ERR: FAILED TO OPEN ");
        return file_str;
    }

    while (file.available()) //GET THE FILE CONTENT
    {
        file_str += char(file.read());
    }
    return file_str;
}

void setWalletJson(fs::FS& fs, std::string txt)
{
    //CONVERT THE STRING TO A CONST CHAR*
    char tmp[txt.size() + 1];
    std::copy(txt.begin(), txt.end(), tmp);
    tmp[txt.size()] = '\0';

    const char* str = tmp;

    //WRITE ON THE CONFIG FILE
    File file = fs.open("/wallet.json", FILE_WRITE);
    if (!file) {
        file.close();
        Serial.println("ERR: FAILED TO OPEN wallet.json");
    } else {
        if (!file.print(str)) {
            Serial.println("ERR: COULD NOT WRITE ON wallet.json");
        }
        file.close();
    }
}

bool Wallet::isJson(fs::FS& fs)
{
    File file = fs.open("/wallet.json");
    if (!file || file.isDirectory()) {
        file.close();
        Serial.print("ERR: FAILED TO OPEN ");
        return false;
    }
    return true;
}

bool Wallet::isWalletcreated()
{
    if (this->masterUser == "" || this->mainkey[0] == "" || this->hashWord == "") {
        return false;
    }
    return true;
}

void Wallet::initWalletJson()
{
    //OPEN THE FILE
    DynamicJsonDocument doc(20000);

    std::string str = getWalletJson(SPIFFS);
    Serial.println(str.c_str());

    char json[str.size() + 1];
    std::copy(str.begin(), str.end(), json);
    json[str.size()] = '\0';

    //Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    const char* master = doc["master"];
    const char* hash = doc["hash"];
    const char* k = doc["key"];
    int size = doc["size"];

    std::string key = k;

    // Print values.
    Serial.println(master);
    Serial.println(size);

    std::vector<std::vector<std::string>> stgbox;

    for (int i = 0; i < size; i++) {
        const char* name = doc["accounts"][i]["name"];
        const char* username = doc["accounts"][i]["username"];
        const char* password = doc["accounts"][i]["password"];

        std::vector<std::string> tmp;
        tmp.push_back(std::string(name));
        tmp.push_back(std::string(username));
        tmp.push_back(std::string(password));

        stgbox.push_back(tmp);
    }

    for (int i = 0; i < stgbox.size(); i++) {
        Serial.println(stgbox[i][0].c_str());
        Serial.println(stgbox[i][1].c_str());
        Serial.println(stgbox[i][2].c_str());
    }
    this->masterUser = master;
    this->hashWord = hash;
    this->strongbox = stgbox;
    Serial.println(this->masterUser.c_str());
    Serial.println(this->hashWord.c_str());
    for (auto& acc : this->strongbox) {
        Serial.println(acc[0].c_str());
        Serial.println(acc[1].c_str());
        Serial.println(acc[2].c_str());
    }
    this->mainkey.push_back(key.substr(0, 16));
    this->mainkey.push_back(key.substr(16, 16));
}

void Wallet::saveWallet()
{
    DynamicJsonDocument doc(20000);
    std::string key = this->mainkey[0] + this->mainkey[1];
    doc["master"] = this->masterUser.c_str();
    doc["hash"] = this->hashWord.c_str();
    doc["key"] = key.c_str();
    int size = this->strongbox.size();
    for (int i = 0; i < size; i++) {
        doc["accounts"][i]["name"] = this->strongbox[i][0];
        doc["accounts"][i]["username"] = this->strongbox[i][1];
        doc["accounts"][i]["password"] = this->strongbox[i][2];
    }
    doc["size"] = size;
    std::string output;
    serializeJson(doc, output);
    setWalletJson(SPIFFS, output);
}

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

    pwd_crypt(rkey1, ca1, S1);
    pwd_crypt(rkey2, ca2, S2);
    std::string tpwd1(reinterpret_cast<const char*>(S1), 16);
    std::string tpwd2(reinterpret_cast<const char*>(S2), 16);
    std::string hash(reinterpret_cast<const char*>(shaResult), 32);
    std::string test = tpwd1 + tpwd2;

    std::stringstream ss;
    for (int i = 0; i < 32; ++i)
        ss << HEX << (int)shaResult[i];
    std::string mystr = ss.str();

    this->masterUser = masterUser;

    this->mainkey.push_back(tpwd1);
    this->mainkey.push_back(tpwd2);
    this->hashWord = hash;
}

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
    return false;
}

bool Wallet::addAccount(std::string nameAccount, std::string username, std::string pwd, int l)
{
    /*
        This method is used to add an account in a wallet class
    */
    if (this->lock == false) {
        std::string str1;
        std::string str2;
        if (username == "") {

            return false;
        }

        if (pwd == "") {
            if (l <= 0 || pwd.length() > 32 || l > 32) {

                return false;
            }
            pwd = generate_random_string(l);
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

        std::vector<std::string> acc;
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
        std::string npwd = tpwd1 + tpwd2;
        acc.push_back(nameAccount);
        acc.push_back(username);
        acc.push_back(npwd);

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

std::vector<std::vector<std::string>> Wallet::getAccounts()
{
    std::vector<std::vector<std::string>> accounts;
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
            std::vector<std::string> account;
            std::string str1 = acc[2].substr(0, 16);
            std::string str2 = acc[2].substr(16);

            unsigned char ttest[17];
            unsigned char t2test[17];
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
            account.push_back(acc[0]);
            account.push_back(acc[1]);
            account.push_back(pwd.substr(0, c));
            accounts.push_back(account);
        }
        return accounts;
    }
    return accounts;
}

bool Wallet::changeUsername(int accountIndex, std::string newUsername)
{
    if (this->lock == false) {
        if (0 <= accountIndex && accountIndex < this->strongbox.size()) {
            return false;
        }
        this->strongbox[accountIndex][1] = newUsername;
        return true;
    }
    return false;
}

bool Wallet::changePwd(int accountIndex, std::string newpwd)
{
    if (this->lock == false) {
        if (0 <= accountIndex && accountIndex < this->strongbox.size()) {

            std::string str1;
            std::string str2;

            std::vector<std::string> acc;
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

            this->strongbox[accountIndex][2] = tpwd1 + tpwd2;

            return true;
        }
    }
    return false;
}

bool Wallet::delAccount(int accountIndex)
{
    if (this->lock == false) {
        if (0 <= accountIndex && accountIndex < this->strongbox.size()) {
            this->strongbox.erase(this->strongbox.begin() + accountIndex);
            return true;
        }
    }
    return false;
}
