#ifndef HTTPS_SERVER_KEYBOX_H
#define HTTPS_SERVER_KEYBOX_H

// We need to specify some content-type mapping, so the resources get delivered
// with the right content type and are displayed correctly in the browser
char contentTypes[][2][32] = {
    {".htm", "text/html"},         {".html", "text/html"},
    {".css", "text/css"},          {".js", "application/javascript"},
    {".json", "application/json"}, {".png", "image/png"},
    {".jpg", "image/jpg"},         {"", ""}};

/** Check if we have multiple cores */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Include certificate data (see note above)
#include "cert.h"
#include "private_key.h"

// Includes for the server
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>

// We will use SPIFFS and FS
#include "SPIFFS_tools.h"

// Declare some handler functions for the various URLs on the server
void handleRessources(httpsserver::HTTPRequest* req,
                      httpsserver::HTTPResponse* res);
void handleSPIFFS(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res);

class https_server_keybox {
 private:
  // Create an SSL-enabled server that uses the certificate
  // Create an SSL certificate object from the files included above
  httpsserver::SSLCert cert =
      httpsserver::SSLCert(example_crt_DER, example_crt_DER_len,
                           example_key_DER, example_key_DER_len);
  httpsserver::HTTPSServer secureServer = httpsserver::HTTPSServer(&cert);

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
   * @brief Run the serveur on the second core of the ESP32 to let the first one
   * do is things
   *
   */
  void run();

  /**
   * @brief function that will be the entry-point for the task that is going
   * to be created.
   *
   * @param params
   */
  void serverTask(void* params);
};

#endif