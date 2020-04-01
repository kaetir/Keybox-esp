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
     * @Desc:  Clear the screen up
     * @Params:  none
     * @Returns:  none
     */
    void clear();

    /** 
     * @Desc:  Set a line
     * @Params:  String to display and the number of the line
     * @Returns:  none
     */
    void setLine(std::string str, int line=0);

    /** 
     * @Desc:  Update the screen display
     * @Params:  none
     * @Returns:  none
     */
    void show();
};