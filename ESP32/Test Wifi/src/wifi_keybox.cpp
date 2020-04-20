
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
  Serial.print("Connected. IP = ");
  Serial.println(WiFi.localIP());
}

void wifi_keybox::connect_wifi(String ssid, String password)
{
  connect_wifi(ssid.c_str(), password.c_str());
}

void wifi_keybox::diconnect_wifi()
{
  WiFi.disconnect();
}

IPAddress wifi_keybox::get_ip()
{
  //IPAddress ip = WiFi.localIP();
  Serial.print("IP = ");
  Serial.println(WiFi.localIP());
  return (WiFi.localIP());
}

String wifi_keybox::enable_AP()
{
  const char *ssid = "ESP-32-WIFI";
  const char *password = "00000000";
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Starting WiFi AP : ");
  Serial.print("IP = ");
  Serial.println(IP);
  Serial.print("ssid = ");
  Serial.println(ssid);
  Serial.print("password = ");
  Serial.println(password);
  //return (ssid);
}

std::vector<String> wifi_keybox::list_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("Disconnected from WiFi");
  delay(100);
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
}