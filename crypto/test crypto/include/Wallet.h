#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createWallet(std::string username, std::string pwd);
    bool addAccount(std::string username, std::string pwd, int l = -1);
    void locked();
    bool unlock();
    bool checkValid(std::string username, std::string pwd);
    std::vector<std::string> getUsers();
    std::vector<std::string> getPwd();
    //std::string testHash(std::string hash);
    //std::string getKey(std::string hash);

private:
    std::string masterUser;
    std::string hashWord;
    std::vector<Account> strongbox;
    std::vector<std::string> mainkey;
    std::vector<std::string> keys;
    bool lock = true;
    int nbit = 32;
};