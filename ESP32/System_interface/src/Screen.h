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
     * @Desc:  Constructor
     * @Params:  none
     * @Returns:  none
     */
    Screen();

    /** 
     * @Desc:  Destructor
     * @Params:  none
     * @Returns:  none
     */
    ~Screen();

    /** 
     * @Desc:  Clear up the screen
     * @Params:  none
     * @Returns:  none
     */
    void clear();

    /** 
     * @Desc:  Set a string on a line
     * @Params:  The string to set, the number of the line (start at 0)
     * @Returns:  none
     */
    void setLine(std::string str, int line = 0);

    /** 
     * @Desc:  Display the content of the screen
     * @Params:  none
     * @Returns:  none
     */
    void show();
};