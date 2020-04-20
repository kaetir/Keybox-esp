#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class wallet {
    void createtWallet(std::string masterUser, std::string masterWord)
    {
        this.masterUser = masterUser;
        void hash_data(char* masterWord.c_str(), int payloadLength, unsigned char* this->masterWord;
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
};