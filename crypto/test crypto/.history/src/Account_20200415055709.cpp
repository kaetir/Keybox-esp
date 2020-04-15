using namespace std;
#include <iostream>
void initAccount(std::string username, std::string pwd)
{
    this->username = username;
    this->pwd = pwd;
}

void changeUsername(std::string username)
{
    this->username = username;
}

void changePwd(std::string pwd)
{
    this->pwd = pwd;
}