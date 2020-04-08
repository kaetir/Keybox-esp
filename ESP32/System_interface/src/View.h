#include "Screen.h"

class View
{
private:
    Screen *screen;                 //Screen OBJECT
    char buffer[NUM_LINE][NUM_COL]; //BUFFER OF THE CONTENT TO DISPLAY

public:
    /** 
     * @Desc:  Constructor
     * @Params:  none
     * @Returns:  none
     */
    View();

    /** 
     * @Desc:  Destructor
     * @Params:  none
     * @Returns:  none
     */
    ~View();

    /** 
     * @Desc:  Clear the display of the screen
     * @Params:  none
     * @Returns:  none
     */
    void clear();

    /** 
     * @Desc:  Display the content of the buffer on the screen
     * @Params:  none
     * @Returns:  none
     */
    void show();

    /** 
     * @Desc:  Add a string to the buffer at the designated coordinates (start at (0,0))
     * @Params:  String to draw, Number of the line, Number of the column
     * @Returns:  none
     */
    void draw_text(std::string txt, int line = 0, int col = 0);

    /** 
     * @Desc:  Add a character to the buffer at the designated coordinates (start at (0,0))
     * @Params:  Character to draw, Number of the line, Number of the column
     * @Returns:  none
     */
    void draw_char(char a, int line = 0, int col = 0);

    /** 
     * @Desc:  Clear the content of the buffer
     * @Params:  none
     * @Returns:  none
     */
    void clear_buffer();
};