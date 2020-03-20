#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define NUM_LINE 4
#define NUM_COL 22

class View{
    private:
    Adafruit_SSD1306 display; //Obj controlling the ssd1306 screen
    char buffer[NUM_LINE][NUM_COL];

    public:
    View(); //Constructor
    ~View(); //Destructor
    void clear(); //Clearing the screen
    void show(); //Displaying the buffer on the screen
    void draw_text(std::string txt, int line=0, int col=0);
    void draw_char(char a, int line=0, int col=0);
    void clear_buffer();
};