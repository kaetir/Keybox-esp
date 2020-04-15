class account {
    // Tout ce qui suit est public (accessible depuis l'extérieur)
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