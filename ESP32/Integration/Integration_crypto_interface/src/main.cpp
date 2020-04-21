#include "Controller.h"

Controller *controller;
bool has_started = false;

void setup()
{
  Serial.begin(115200);
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Mount Failed");
  }
  else
  {
    controller = new Controller();
    has_started = true;
  }
}

void loop()
{
  if (has_started == true)
  {
    controller->update();
    delay(50);
  }
}