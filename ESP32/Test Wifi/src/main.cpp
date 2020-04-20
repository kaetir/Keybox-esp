#include "creditential.h"
#include "wifi_keybox.h"

wifi_keybox my_wifi;

void setup() {
  // For logging
  Serial.begin(115200);

  std::vector<String> liste_wifis = my_wifi.list_wifi();

  for (auto w : liste_wifis) {
    Serial.println(w);
  }

  // Serial.println(xPortGetCoreID());
  /*   my_wifi.connect_wifi(ssid, password);
    Serial.println("connected to wifi");
    my_wifi.get_ip();
    my_wifi.diconnect_wifi();
    delay(1000);
    Serial.println(my_wifi.enable_AP());
    delay(1000); */
}

void loop() { delay(1000); }