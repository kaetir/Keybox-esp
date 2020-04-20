#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createtWallet(std::string username, string pwd);

    bool addAccount();

    std::string getAccounts();

    std::string getPwd();

private:
    std::string masterUser;
    std::string masterWord;
    std::vector<std::vector<std::Account>> mon_coffre;
};