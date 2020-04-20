using namespace std;
class account {
public:
    void initAccount(string username, string pwd);

    void changeUsername(string username);

    void changePwd(string pwd);

private:
    string username;
    string pwd;
};