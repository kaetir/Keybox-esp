class account {
public:
    void initAccount(string username, string pwd)
    {
        this.username = username;
        this.pwd = pwd;
    }

    void changeUsername(string username)
    {
        this.username = username;
    }

    void changePwd(string pwd
    {
        this.pwd = pwd;
    }
 
    

    private:
    
    string username;
    string pwd;
};