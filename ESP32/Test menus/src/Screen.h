#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

class Screen{
    private:
    Adafruit_SSD1306 display;

    public:
    Screen();
    ~Screen();
    void clear();
    void setLine(std::string str, int line=0);
    void show();
};