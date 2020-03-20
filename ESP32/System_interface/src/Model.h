#include <string>
#include <vector>

class Model{
    private:
    std::string path_to_folder;
    std::vector<std::string> unlocked_locker;
    std::vector<std::string> user_ids;
    
    public:
    Model();
    ~Model();
    std::vector<std::string> read(std::string filename);
    std::vector<std::string> get_accounts();
    std::vector<std::string> get_account(std::string account_name);
    bool add_account(std::string name, std::string user, std::string pwd);
    bool modify_account_password(std::string name, std::string pwd);
    bool modify_account_username(std::string name, std::string user);
    void delete_account(std::string name);
    bool is_webserver_on();
    void switch_server_status();
};
