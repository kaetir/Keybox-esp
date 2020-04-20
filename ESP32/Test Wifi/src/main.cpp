#include "creditential.h"
#include "wifi_keybox.h"

wifi_keybox my_wifi;

void setup()
{
  // For logging
  Serial.begin(115200);
  //Serial.println(xPortGetCoreID());
  my_wifi.connect_wifi(ssid, password);
  Serial.println("connected to wifi");
  my_wifi.get_ip();
  my_wifi.diconnect_wifi();
  delay(1000);
  my_wifi.enable_AP();
  my_wifi.get_ip();
  delay(1000);
  my_wifi.list_wifi();
}

void loop() { delay(1000); }