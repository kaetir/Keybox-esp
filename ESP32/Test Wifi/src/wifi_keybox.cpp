
#include "wifi_keybox.h"

wifi_keybox::wifi_keybox() {}

wifi_keybox::~wifi_keybox() {}

void wifi_keybox::connect_wifi(const char *ssid, const char *password)
{
  Serial.print("start");
  WiFi.begin(ssid, password);
  Serial.print("begin");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected. IP=");
  Serial.println(WiFi.localIP());
}

void wifi_keybox::connect_wifi(String ssid, String password)
{
  connect_wifi(ssid.c_str(), password.c_str());
}
