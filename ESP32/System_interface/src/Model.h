#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "FS.h"
#include "SPIFFS.h"

#define MENU_LANG_FOLDER "/MENU/LANG"
#define MENU_STRUCTURE_FOLDER "/MENU/STRUCTURE"

class Model
{
private:
    std::string lang_folder;
    std::vector<std::string> unlocked_locker;
    std::vector<std::string> user_ids;

public:
    Model();
    ~Model();
    std::vector<std::string> read(fs::FS &fs, std::string filename, std::string type, std::string lang);
    std::vector<std::string> get_accounts();
    std::vector<std::string> get_account(int account_index);
    bool add_account(std::string name, std::string user, std::string pwd);
    bool modify_account_password(std::string name, std::string pwd);
    bool modify_account_username(std::string name, std::string user);
    void delete_account(std::string name);
    bool is_webserver_on();
    void switch_server_status();
    bool login(std::string user, std::string password);
    std::vector<std::string> get_config(fs::FS &fs);
    void set_config(fs::FS &fs, std::string txt);
};
