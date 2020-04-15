#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class wallet {
    void createtWallet(string masterUser, string masterWord)
    {
        this.masterUser = masterUser;
        void hash_data(char* payload, int payloadLength, unsigned char* outputBuffer)

            this->masterWord
            = masterWord;
    }

    bool loadWallet();

    bool savetWallet();

    bool addAccount(string username, string pwd)
    {
        Account acc;

        acc.initAccount(username, pwd);

        mon_coffre.push_back(acc);
    }

    string getAccounts();

    string getPwd();
};