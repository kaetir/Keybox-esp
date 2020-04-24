
#include "wifi_keybox.h"

wifi_keybox::wifi_keybox() {}

wifi_keybox::~wifi_keybox() {}

bool wifi_keybox::connect_wifi(const char *ssid, const char *password)
{
  // Serial.print("start");
  WiFi.begin(ssid, password);
  // Serial.print("begin");
  int start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000)
  {
    // Serial.print(".");
    delay(500);
  }
  return WiFi.status() == WL_CONNECTED;
}

bool wifi_keybox::connect_wifi(String ssid, String password)
{
  return connect_wifi(ssid.c_str(), password.c_str());
}

void wifi_keybox::diconnect_wifi() { WiFi.disconnect(); }

IPAddress wifi_keybox::get_ip()
{
  // IPAddress ip = WiFi.localIP();
  // Serial.print("IP = ");
  // Serial.println(WiFi.localIP());
  return WiFi.localIP();
}

String wifi_keybox::enable_AP(String s_ssid, String s_passwd)
{
  const char *ssid = s_ssid.c_str();
  const char *password = s_passwd.c_str();
  WiFi.softAP(ssid, password);
  return s_ssid + " " + s_passwd + " " + WiFi.softAPIP().toString();
}

void wifi_keybox::disable_AP() { WiFi.softAPdisconnect(true); }

std::vector<String> wifi_keybox::list_wifi()
{
  std::vector<String> liste;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  // Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    // Serial.print(n);
    // Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      // Serial.print(WiFi.SSID(i));
      liste.push_back(WiFi.SSID(i));
      // Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    }
  }
  return liste;
}