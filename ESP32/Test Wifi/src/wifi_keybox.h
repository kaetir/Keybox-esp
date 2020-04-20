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

#include <Arduino.h>

// We will use wifi
#include <WiFi.h>
#include <vector>

/** Check if we have multiple cores */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef WIFI_KEYBOX_H
#define WIFI_KEYBOX_H

class wifi_keybox
{
private:
  /* data*/

public:
  wifi_keybox();
  ~wifi_keybox();

  /**
   * @brief connect to a wifi network
   *
   * @param ssid
   * @param password
   */
  void connect_wifi(const char *ssid, const char *password);

  /**
   * @brief connect_wifi pour String
   *
   * @param ssid
   * @param password
   */
  void connect_wifi(String ssid, String password);

  /**
   * @brief disconnect esp32 from wifi network
   * 
   */
  void diconnect_wifi();

  /**
   * @brief Get the ip of esp32 
   * 
   * @return String 
   */
  IPAddress get_ip();

  /**
   * @brief enables esp32 as acces point and return the serialized ssid and password and ip adress
   * 
   * @return String : ssid password ip
   */
  String enable_AP();

  /**
   * @brief disable the esp32 as wifi acces point 
   * 
   */
  void disable_AP();

  /**
   * @brief list all the wifi networks available
   * 
   * @return std::vector<String> 
   */
  std::vector<String> list_wifi();
};

#endif