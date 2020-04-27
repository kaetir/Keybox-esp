#ifndef HTTPS_SERVER_KEYBOX_H
#define HTTPS_SERVER_KEYBOX_H

/** Check if we have multiple cores */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Includes for the server
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>

// manipulations of data
#include <stdio.h>

#include <vector>

// We will use SPIFFS and FS
#include "SPIFFS.h"
#include "Wallet.h"

// Declare some handler functions for the various URLs on the server
/** @brief This is a more generic demo for the query parameters. It makes use of
 * the iterator interface to access them, which is useful if you do not know the
 * paramter names in adavance.
 */
void handleParams(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res);
/**
 * @brief This handler function will try to load the requested resource from
 * SPIFFS's / folder. If the method is not GET or POST, it will throw 405, if
 * the file is not found, it will throw 404.
 */
void handleSPIFFS(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res);
/**
 * @brief fonction for the create Wallet page
 *
 */
void handleCreate(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res);

/**
 * @brief function for creating an acount in the wallet
 *
 */
void handleCreateAccount(httpsserver::HTTPRequest* req,
                         httpsserver::HTTPResponse* res);

/**
 * @brief reply to the request with an array of acounts
 *
 */
void handleGetAccounts(httpsserver::HTTPRequest* req,
                       httpsserver::HTTPResponse* res);

/**
 * @brief delete an account
 *
 */
void handleDeleteAccount(httpsserver::HTTPRequest* req,
                         httpsserver::HTTPResponse* res);

/**
 * @brief lock and save the file
 *
 */
void handleLock(httpsserver::HTTPRequest* req, httpsserver::HTTPResponse* res);

class https_server_keybox {
 private:
  // Create an SSL-enabled server that uses the certificate
  // Create an SSL certificate object from the files included above
  httpsserver::SSLCert cert;

  httpsserver::HTTPSServer secureServer;

 public:
  /**
   * @brief Construct a new https server keybox object
   *
   */
  https_server_keybox(Wallet* w);
  /**
   * @brief Destroy the https server keybox object
   *
   */
  ~https_server_keybox();

  /**
   * @brief function that will be the entry-point for the task that is going
   * to be created.
   *
   * @param params
   */
  static void serverTask(void* params);
  /**
   * @brief decode url encoded format from body of post request
   *
   * @return std::vector<std::pair<std::string, std::string>>
   */
  static std::vector<std::pair<std::string, std::string>> decodeUrlEncode(
      char*);
};

#endif