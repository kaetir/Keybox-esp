#include "Wallet.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
void Wallet::createWallet(std::string masterUser, std::string masterWord)
{
    this->masterUser = masterUser;
    char* pwd = masterWord.c_str() void hash_data(pwd.c_str(), pwd.length(), this->masterWord);
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