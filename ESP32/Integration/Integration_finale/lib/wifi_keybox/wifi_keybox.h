/**
 *
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

class wifi_keybox {
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
  bool connect_wifi(const char *ssid, const char *password);

  /**
   * @brief connect_wifi pour String
   *
   * @param ssid
   * @param password
   */
  bool connect_wifi(String ssid, String password);

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
   * @brief enables esp32 as acces point and return the serialized ssid and
   * password and ip adress
   *
   * @return String : ssid password ip
   */
  String enable_AP(String ssid = "ESP-32-WIFI", String passwd = "00000000");

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