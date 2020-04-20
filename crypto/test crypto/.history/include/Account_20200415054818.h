using namespace std;
class account {
public:
    void initAccount(std::string username = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", std::string pwd = "a");

    void changeUsername(std::string username = " ");

    void changePwd(std::string pwd = " ");

private:
    std::string username = " ";
    std::string pwd = " ";
};