#include "SPIFFS.h"
#include "Controller.h"

Controller *controller;

void setup()
{
  Serial.begin(115200);
  controller = new Controller();
}

void loop()
{
}