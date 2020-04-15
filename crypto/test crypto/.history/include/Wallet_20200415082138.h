#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createWallet(std::string username, std::string pwd);
    bool addAccount(std::string username, std::string pwd);
    void lock();
    bool unlock();
    bool chack_valid(unsigned char* password_hash);
    std::vector<std::string> getUsers();
    std::vector<std::string> getPwd();

private:
    std::string masterUser;
    std::string masterWord;
    std::vector<Account> strongbox;
    std::vector<std::string> mainkeys;
    bool lock = true;
};