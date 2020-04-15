using namespace std;
class account {
public:
    void initAccount(std::string username = "", std::string pwd = "");

    void changeUsername(std::string username = "");

    void changePwd(std::string pwd = "");

private:
    std::string username = "";
    std::string pwd = "";
};