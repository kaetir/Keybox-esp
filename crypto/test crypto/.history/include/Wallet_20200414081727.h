import "Account.h" class wallet {
public:
    void initAccount();

    void changeUsername();

    void changePwd();

private:
    string masterUser;
    string masterWord;
    std::vector<std::vector<std::Account>> mon_coffre;
};