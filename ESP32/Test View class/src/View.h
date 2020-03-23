#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define NUM_LINE 4
#define NUM_COL 21

class View{
    private:
    Adafruit_SSD1306 display; //Obj controlling the ssd1306 screen
    char buffer[NUM_LINE][NUM_COL];

    public:
    View(); //Constructor
    ~View(); //Destructor

    /** 
     * @Desc:  Clear the display of the screen
     * @Params:  none
     * @DReturns:  none
     */
    void clear();

    /** 
     * @Desc:  Display the content of the buffer on the screen
     * @Params:  none
     * @DReturns:  none
     */
    void show();

    /** 
     * @Desc:  Add a string to the buffer at the designated coordinates (start at (0,0))
     * @Params:  (std::string, int, int)
     * @DReturns:  none
     */
    void draw_text(std::string txt, int line=0, int col=0);

    /** 
     * @Desc:  Add a character to the buffer at the designated coordinates (start at (0,0))
     * @Params:  (char, int, int)
     * @DReturns:  none
     */
    void draw_char(char a, int line=0, int col=0);

    /** 
     * @Desc:  Clear the content of the buffer
     * @Params:  none
     * @DReturns:  none
     */
    void clear_buffer();
};