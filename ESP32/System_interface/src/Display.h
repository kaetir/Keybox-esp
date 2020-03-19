#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

class Display{
    private:
    Adafruit_SSD1306 display; //Obj controlling the ssd1306 screen

    public:
    Display(); //Constructor
    ~Display(); //Destructor
    void clear(); //Clearing the screen
    void show(std::string str); //Displaying the string on the screen
};