#include "Screen.h"

Screen::Screen()
{
    this->display = Adafruit_SSD1306(128, 32, &Wire); //INITIALISATION OF THE DISPLAY

    if (!this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {                                                   //SECURITY AGAINST INITIALIZATION ERROR
        Serial.println(F("SSD1306 allocation failed")); //TODO INPUT IN LOG FILE
    }
    else
    {
        this->display.display();
        delay(1000);
        this->display.clearDisplay();
        this->display.display();

        //SET THE FONT SIZE
        this->display.setTextSize(1);

        //SET THE FONT COLOR
        this->display.setTextColor(SSD1306_WHITE);
    }
}

Screen::~Screen()
{
    delete &this->display;
}

void Screen::clear()
{
    this->display.clearDisplay();
    this->display.setCursor(0, 0);
    this->display.display();
}

void Screen::setLine(std::string str, int line)
{
    if (line < NUM_LINE) //CHECK IF THE LINE NUMBER IS LOWER THAN THE TOTAL NUMBER OF LINE
    {
        this->display.setCursor(0, line * 8);
        this->display.println(str.c_str());
    }
}

void Screen::show()
{
    this->display.display();
}