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
}

void loop() { delay(1000); }