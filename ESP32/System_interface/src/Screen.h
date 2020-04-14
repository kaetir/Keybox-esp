#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define NUM_LINE 4
#define NUM_COL 21

class Screen
{
private:
    Adafruit_SSD1306 display; //DISPLAY OF THE SCREEN

public:
    /** 
     * @brief  Constructor
     */
    Screen();

    /** 
     * @brief  Destructor
     */
    ~Screen();

    /** 
     * @brief  Clear up the screen
     */
    void clear();

    /** 
     * @brief  Set a string on a line
     * @param str  String to set
     * @param line Number of the line (start at 0)
     */
    void setLine(std::string str, int line = 0);

    /** 
     * @brief  Display the content of the screen
     */
    void show();
};