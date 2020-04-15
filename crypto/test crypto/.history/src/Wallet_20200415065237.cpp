#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"

void Wallet::createWallet(std::string masterUser, std::string masterWord)
{
    char* ca = new char[masterWord.size() + 1];
    std::copy(masterWord.begin(), masterWord.end(), ca);
    ca[masterWord.size()] = '\0';
    unsigned char shaResult[32];
    std::vector<char> cstr(masterWord.c_str(), masterWord.c_str() + masterWord.size() + 1);
    hash_data(ca, masterWord.size(), shaResult);
    std::string hash(reinterpret_cast<const char*>(shaResult), 32);
    this->masterWord = hash;
}

bool Wallet::addAccount(std::string username, std::string pwd)
{
    Account acc;

    acc.initAccount(username, pwd);

    this->strongbox.push_back(acc);
}

std::string getAccounts();

std::string getPwd();
}
;