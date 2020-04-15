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
    unsigned char* uc;
    std::string hash(reinterpret_cast<const char*>(shaResult), 32);
    this->masterWord = hash;
}

bool loadWallet();

bool savetWallet();

bool addAccount(std::string username, std::string pwd)
{
    Account acc;

    acc.initAccount(username, pwd);

    mon_coffre.push_back(acc);
}

std::string getAccounts();

std::string getPwd();
}
;