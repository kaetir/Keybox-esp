#include "PwdCypher.h"
#include "RandomPwdGenerator.h"
#include "SPIFFS.h"

#ifndef WALLET_H
#define WALLET_H

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
  bool addAccount(std::string nameAccount, std::string username,
                  std::string pwd, int l = -1);
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
  bool unlock(std::string pwd);
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
  /**
   * @brief  Verify the precense of wallet.json file
   * @param fs spiffs variable
   * @return  Success
   */
  bool isJson(fs::FS& fs);
  /**
   * @brief  Verify the the creation of wallet from the file
   * @return  Success
   */
  bool isWalletcreated();
  /**
   * @brief Get adapt the .json in a string
   * @param  fs SPIFFS pointer
   * @return  the json in a string dormat
   */
  std::string getWalletJson(fs::FS& fs);
  /**
   * @brief Get adapt the .json in a string
   * @param fs SPIFFS pointer
   * @param txt the text we want to write
   * @return  the json in a string dormat
   */
  void setWalletJson(fs::FS& fs, std::string txt);

 private:
  std::string masterUser;  // Contain the user of the wallet
  std::string hashWord;    // Contain the hash of the pwd of the user
  std::vector<std::vector<std::string>>
      strongbox;                     // Contain all the Accounts of the user
  std::vector<std::string> mainkey;  // Contain the cipher mainkey
  std::vector<std::string> keys;     // Contain the mainkey
  bool lock;                         // Determine if the wallet is open
  int nbytes;                        // Determine the number bit of encryption
};

#endif  // WALLET_H