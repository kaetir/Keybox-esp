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

// We will use SPIFFS and FS
//#include "SPIFFS_tools.h"
#include "FS.h"
#include "SPIFFS.h"

// Declare some handler functions for the various URLs on the server
void handleRessources(httpsserver::HTTPRequest* req,
                      httpsserver::HTTPResponse* res);
void handleSPIFFS(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res);

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
  https_server_keybox();
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
};

#endif