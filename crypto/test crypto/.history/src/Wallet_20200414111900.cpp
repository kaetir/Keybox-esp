include "Account.h" class wallet {
public:
    void createtWallet(string masterUser, string masterWord)
    {
        this.masterUser = masterUser;
        this.masterWord = masterWord
    }

    bool loadWallet();

    bool savetWallet();

    bool addAccount()
    {
        Account acc;
        mon_coffre.push_back(acc);
    }

    string getAccounts();

    string getPwd();

private:
    string masterUser;
    string masterWord;
    std::vector<std::vector<std::Account>> mon_coffre;
};