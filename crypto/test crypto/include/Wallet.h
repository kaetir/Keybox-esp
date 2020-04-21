#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
#include "FS.h"
#include "SPIFFS.h"

class Wallet {
public:
    /** 
     * @brief  Constructor
     */
    Wallet();

    /** 
     * @brief  Destructor
     */

    void createWallet(std::string username, std::string pwd);
    /** 
     * @brief  Add an account to the wallet and cipher the pwd
     * @param nameAccount name of the account
     * @param username username of the account
     * @param pwd  pwd of the account
     * @return  Success
     */
    bool addAccount(std::string nameAccount, std::string username, std::string pwd, int l = -1);
    /** 
     * @brief  Save the wallet on the SPIFFS
     */
    void saveWallet();
    /** 
     * @brief  Init the wallet from the SPIFFS
     */
    void initWalletJson();
    /** 
     * @brief  Lock the wallet
     */
    void locked();
    /** 
     * @brief  Give access to the wallet
     * @param username username of the account
     * @param pwd  pwd of the account
     * @return  Success
     */
    bool unlock(std::string username, std::string pwd);
    /** 
     * @brief  Give all the account in the wallet if open
     * @return  All the account
     */
    std::vector<std::vector<std::string>> getAccounts();
    /** 
     * @brief  changeUsername of one account
     * @param accountIndex index of the account
     * @param newUsername  new username of the account
     * @return  Success
     */
    bool changeUsername(int accountIndex, std::string newUsername);
    /** 
     * @brief  Give access to the wallet
     * @param accountIndex username of the account
     * @param newpwd  pwd of the account
     * @return  Success
     */
    bool changePwd(int accountIndex, std::string newpwd);
    /** 
     * @brief  Give access to the wallet
     * @param accountIndex username of the account
     * @param newpwd  pwd of the account
     * @return  Success
     */
    bool delAccount(int accountIndex);
    bool isJson(fs::FS& fs);
    bool isWalletcreated();

private:
    std::string masterUser; // Contain the user of the wallet
    std::string hashWord; // Contain the hash of the pwd of the user
    std::vector<std::vector<std::string>> strongbox; // Contain all the Accounts of the user
    std::vector<std::string> mainkey; // Contain the cipher mainkey
    std::vector<std::string> keys; // Contain the mainkey
    bool lock; // Determine if the wallet is open
    int nbit; // Determine the number bit of encryption
};