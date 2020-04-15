#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
void Wallet::createWallet(std::string masterUser, std::string masterWord)
{
    this->masterUser = masterUser;
    std::vector<char> pwd(masterWord.c_str(), masterWord.c_str() + masterWord.size() + 1);
    void hash_data(pwd, masterWord.size(), this->masterWord);
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