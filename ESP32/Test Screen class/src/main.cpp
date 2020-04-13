#include "SPIFFS.h"
#include "Screen.h"

Screen *screen;

void setup()
{
  Serial.begin(115200);
  screen = new Screen();
}

void loop()
{
  std::string str = "Hello world!";

  //TEST THE setLine() FUNCTION
  screen->setLine(str);

  //TEST THE DISPLAY
  screen->show();
  delay(1000);

  //TEST THE CLEARING OF THE DISPLAY
  screen->clear();
  delay(1000);
}