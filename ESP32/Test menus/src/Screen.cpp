#include "Screen.h"

Screen::Screen(){
    this->display = Adafruit_SSD1306(128, 32, &Wire); //INITIALISATION

    if(!this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //SECURITY AGAINST INT ERROR
        Serial.println(F("SSD1306 allocation failed")); //TODO INPUT IN LOG FILE
        for(;;); // Don't proceed, loop forever
    }
    this->display.display();
    delay(1000);
    this->display.clearDisplay();
    this->display.display();

    this->display.setTextSize(1);
    this->display.setTextColor(SSD1306_WHITE);
}

Screen::~Screen(){
    delete &this->display;
}

void Screen::clear(){
    this->display.clearDisplay();
    this->display.setCursor(0,0);
    this->display.display();
}

void Screen::setLine(std::string str, int line){
    this->display.setCursor(0,line*8);
    this->display.println(str.c_str());
}

void Screen::show(){
    this->display.display();
}