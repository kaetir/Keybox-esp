#include "Account.h"
class wallet {
public:
    void createtWallet();

    bool loadWallet();

    bool savetWallet();

    bool addAccount();

    string getAccounts();

    string getPwd();

private:
    string masterUser;
    string masterWord;
    std::vector<std::vector<std::Account>> mon_coffre;
};