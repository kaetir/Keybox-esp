import "Account.h" class wallet {
public:
    void createtWallet(string masterUser, string masterWord)
    {
        this.masterUser = masterUser;
        this.masterWord = masterWord
    }

    bool loadWallet();

    bool savetWallet();

    string getAccounts();

    string getPwd();

private:
    string masterUser;
    string masterWord;
    std::vector<std::vector<std::Account>> mon_coffre;
};