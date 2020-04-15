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
    std::vector<std::vector<std::string>> wifi_list; //AVAILABLE WIFI LIST
    std::vector<std::string> current_server;         //CURRENT WIFI SSID, PASSWORD AND SERVER IP
    std::vector<std::vector<std::string>> locker;    //LIST OF ALL ACCOUNTS INFORMATIONS (Name, Username, Password)

public:
    /** 
     * @brief  Constructor
     */
    Model();

    /** 
     * @brief  Destructor
     */
    ~Model();

    /** 
     * @brief  Get the content of the menu files (.struct and .txt)
     * @param fs Pointer to the SPIFFS reader/writer
     * @param filename Name of the file to open
     * @param type Type of the file (struct or txt)
     * @param lang Language currently used (FR, EN, IT...)
     * @return An array of lines of the file
     */
    std::vector<std::string> read(fs::FS &fs, std::string filename, std::string type, std::string lang);

    /** 
     * @brief  Get the list of accounts name
     * @return An array of the accounts name
     */
    std::vector<std::string> get_accounts();

    /** 
     * @brief  Get the informations of an account in the accounts list
     * @param account_index Position of the account in the accounts list (start at 0)
     * @return An array of the informations about the account (Name, Username, Password)
     */
    std::vector<std::string> get_account(int account_index);

    /** 
     * @brief  Add an account to the accounts list
     * @param name Name/url of the account
     * @param user Username of the account
     * @param pwd Password of the account
     * @return A boolean indicating if the account has been added or not
     */
    bool add_account(std::string name, std::string user, std::string pwd);

    /** 
     * @brief  Modify the password of an account
     * @param account_index Position of the account in the accounts list (start at 0)
     * @param paswword New password
     * @return A boolean indicating if the account has been modified or not
     */
    bool modify_account_password(int account_index, std::string password);

    /** 
     * @brief  Modify the username of an account
     * @param account_index Position of the account in the accounts list (start at 0)
     * @param user New username
     * @return A boolean indicating if the account has been modified or not
     */
    bool modify_account_username(int account_index, std::string user);

    /** 
     * @brief  Delete an account
     * @param account_index Position of the account in the accounts list (start at 0)
     * @return A boolean indicating if the account has been deleted or not
     */
    void delete_account(int account_index);

    /** 
     * @brief  Check if the web server is On or Off
     * @return A boolean indicating if the web server is On or not
     */
    bool is_webserver_on();

    /** 
     * @brief  Try to log into the locker account
     * @param user Username of the locker account
     * @param password Password of the locker account
     * @return A boolean indicating if the user is log in or not
     */
    bool login(std::string user, std::string password);

    /** 
     * @brief  Get the config file content
     * @param fs Pointer to the SPIFFS reader/writer
     * @return An array of lines of the config file
     */
    std::vector<std::string> get_config(fs::FS &fs);

    /** 
     * @brief  Set the config file content
     * @param fs Pointer to the SPIFFS reader/writer
     */
    void set_config(fs::FS &fs, std::string txt);

    /** 
     * @brief  Get the SSID of a wifi in the wifis list
     * @param index Position of the wifi in the wifis list
     * @return The SSID of the wifi
     */
    std::string getSSID(int index);

    /** 
     * @brief  Get the SSID of the wifis in the wifis list
     * @return The SSID of the wifis
     */
    std::vector<std::string> getWifis();

    /** 
     * @brief  Try to connect to a wifi with a password
     * @param index Position of the wifi in the wifis list
     * @param password Password of the wifi
     * @return A boolean indicating if the connection to the wifi is a success or not
     */
    bool connect_wifi(int index, std::string password);

    /** 
     * @brief  Try to emit a wifi
     * @return A boolean indicating if the wifi has been started or not
     */
    bool emit_wifi();

    /** 
     * @brief  Try to turn the wifi Off
     * @return A boolean indicating if the wifi has been turned off or not
     */
    bool turn_wifi_Off();

    /** 
     * @brief  Get the informations of the currently used wifi
     * @return An array of informations (SSID, PASSWORD, ID)
     */
    std::vector<std::string> getCurrentWifi();

    /** 
     * @brief  Try to log out
     * @return A boolean indicating if the log out was successful or not
     */
    bool logout();
};
