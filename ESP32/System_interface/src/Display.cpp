#include "Display.h"

Display::Display(){
    this->display = Adafruit_SSD1306(128, 32, &Wire);

    if(!this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    this->display.display();
    this->display.clearDisplay();
    this->display.display();
}

Display::~Display(){
    delete &this->display;
}

void Display::clear(){
    this->display.clearDisplay();
    this->display.setCursor(0,0);
    this->display.display();
}

void Display::show(std::string str){
    this->display.setTextSize(1);
    this->display.setTextColor(SSD1306_WHITE);
    this->display.setCursor(0,0);
    this->display.print(str.c_str());
    this->display.display();
}