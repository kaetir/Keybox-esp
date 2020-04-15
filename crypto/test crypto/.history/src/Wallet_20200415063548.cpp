#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
void Wallet::createWallet(std::string masterUser, std::string masterWord)
{
    this->masterUser = masterUser;
    char* ca = new char[masterWord.size() + 1];
    std::copy(masterWord.begin(), masterWord.end(), ca);
    ca[masterWord.size()] = '\0';
    std::vector<char> cstr(masterWord.c_str(), masterWord.c_str() + masterWord.size() + 1);
    void hash_data(ca, masterWord.size(), this->masterWord);
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