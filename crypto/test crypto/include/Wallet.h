#include "Account.h"
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
class Wallet {
public:
    void createWallet(std::string username, std::string pwd);
    bool addAccount(std::string nameAccount, std::string username, std::string pwd, int l = -1);
    void locked();
    bool unlock(std::string username, std::string pwd);
    std::vector<std::vector<std::string>> getAccounts();
    bool changeUsername(int accountIndex, std::string newUsername);
    bool changePwd(int accountIndex, std::string newpwd);
    bool delAccount(int accountIndex);
    //std::string testHash(std::string hash);
    //std::string getKey(std::string hash);

private:
    std::string masterUser;
    std::string hashWord;
    std::vector<std::vector<std::string>> strongbox;
    std::vector<std::string> mainkey;
    std::vector<std::string> keys;
    bool lock = true;
    int nbit = 32;
};