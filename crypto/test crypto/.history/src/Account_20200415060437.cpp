#include <iostream>
#include "Account.h"
void Account::initAccount(std::string username, std::string pwd)
{
    this->username = username;
    this->pwd = pwd;
}

void Account::changeUsername(std::string username)
{
    this->username = username;
}

void Account::changePwd(std::string pwd)
{
    this->pwd = pwd;
}