/**
 * Example for the ESP32 HTTP(S) Webserver
 *
 * IMPORTANT NOTE:
 * To run this script, your need to
 *  1) Enter your WiFi SSID and PSK below this comment
 *  2) Make sure to have certificate data available. You will find a
 *     shell script and instructions to do so in the library folder
 *     under extras/
 *
 * This script will install an HTTPS Server on your ESP32 with the following
 * functionalities:
 *  - Show simple page on web server root
 *  - 404 for everything else
 * The server will be run in a separate task, so that you can do your own stuff
 * in the loop() function.
 * Everything else is just like the Static-Page example
 */
#include "creditential.h"
#include "https_server_keybox.h"

// We will use wifi
#include "wifi_keybox.h"

https_server_keybox* my_webserver;
wifi_keybox my_wifi;

void setup() {
  // For logging
  Serial.begin(115200);
  SPIFFS.begin(false);

  std::vector<String> liste_wifis = my_wifi.list_wifi();

  for (auto w : liste_wifis) {
    Serial.println(w);
  }

  // Connect to WiFi
  Serial.println("Setting up WiFi");

  // WiFi.begin(ssid, password);
  // my_wifi.connect_wifi(ssid, password);
  // Serial.print(my_wifi.get_ip());

  Serial.print(my_wifi.enable_AP("esp32", "12345678"));

  // Setup the server as a separate task.
  my_webserver = new https_server_keybox();
  Serial.println("Creating server task... ");

  // We pass:
  // serverTask - the function that should be run as separate task
  // "https443" - a name for the task (mainly used for logging)
  // 4096       - stack size in byte. If you want up to four clients, you should
  //              not go below 6kB. If your stack is too small, you will
  //              encounter Panic and stack canary exceptions, usually during
  //              the call to SSL_accept.
  // Priority of 2 for faster response time
  xTaskCreatePinnedToCore(my_webserver->serverTask, "https443", 4096,
                          my_webserver, 2, NULL, ARDUINO_RUNNING_CORE);
}

void loop() {}
