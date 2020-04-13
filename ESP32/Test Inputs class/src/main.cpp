#include "SPIFFS.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Inputs.h"

Inputs *inputs;

void setup()
{
  Serial.begin(115200);
  inputs = new Inputs();
}

void loop()
{
  if (inputs->has_input()) //CHECK IF THERE IS AN INPUT
  {
    int input = inputs->get_input(); //GET THE USER INPUT
    if (input != -1 && input != -2)
    {
      switch (input)
      {
      case Direction::LEFT:
        Serial.println("[INPUT]: LEFT");
        break;

      case Direction::RIGHT:
        Serial.println("[INPUT]: RIGHT");
        break;

      case Direction::UP:
        Serial.println("[INPUT]: UP");
        break;

      case Direction::DOWN:
        Serial.println("[INPUT]: DOWN");
        break;

      case Direction::OKAY:
        Serial.println("[INPUT]: OK");
        break;

      case Direction::BACK:
        Serial.println("[INPUT]: BACK");
        break;
      }
    }
  }
  delay(50);
}