#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"

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
    std::vector<char> cstr(masterWord.c_str(), masterWord.c_str() + masterWord.size() + 1);

    // creation of the hash
    hash_data(ca, masterWord.size(), shaResult);

    // transforamtion into a string
    std::string hash(reinterpret_cast<const char*>(shaResult), 32);
    this->masterWord = hash;
}

bool Wallet::addAccount(std::string username, std::string pwd)
{
    if (username == "" || pwd == "") {
        return false
    }
    Account acc;
    int l = this->strongbox.size();
    acc.initAccount(username, pwd);
    this->strongbox.push_back(acc);
    if (l + 1 == this->strongbox.size()) {
        return true
    }
    return false
}

std::string getAccounts();

std::string getPwd();
}
;