#include <iostream>
class Account {
public:
    void initAccount(std::string username, std::string pwd);

    void changeUsername(std::string username);

    void changePwd(std::string pwd);

    std::string getUsername();

    std::string getPwd();

private:
    std::string username;
    std::string pwd;
};