#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createWallet(std::string username, std::string pwd);
    bool addAccount(std::string username, std::string pwd);
    void locked();
    bool unlock();
    bool chack_valid(std::string password_hash);
    std::vector<std::string> getUsers();
    std::vector<std::string> getPwd();

private:
    std::string masterUser;
    std::string hashWord;
    std::vector<Account> strongbox;
    std::vector<std::string> mainkeys;
    bool lock = true;
};