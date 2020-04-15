#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createWallet(std::string username, std::string pwd);
    bool addAccount(std::string username, std::string pwd);
    std::string getAccounts();
    std::string getPwd();

private:
    std::string masterUser;
    std::string masterWord;
    std::vector<std::vector<Account>> strongbox;
};