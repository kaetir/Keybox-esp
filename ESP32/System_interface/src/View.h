#include "Screen.h"

class View
{
private:
    Screen *screen;                 //Screen OBJECT
    char buffer[NUM_LINE][NUM_COL]; //BUFFER OF THE CONTENT TO DISPLAY

public:
    /** 
     * @brief  Constructor
     */
    View();

    /** 
     * @brief  Destructor
     */
    ~View();

    /** 
     * @brief  Clear the display of the screen
     */
    void clear();

    /** 
     * @brief  Display the content of the buffer on the screen
     */
    void show();

    /** 
     * @brief  Add a string to the buffer at the designated coordinates
     * @param txt String to add to the buffer
     * @param line Number of the line (start at 0)
     * @param col Number of the column (start at 0)
     */
    void draw_text(std::string txt, int line = 0, int col = 0);

    /** 
     * @brief  Add a character to the buffer at the designated coordinates
     * @param a Character to add to the buffer
     * @param line Number of the line (start at 0)
     * @param col Number of the column (start at 0)
     */
    void draw_char(char a, int line = 0, int col = 0);

    /** 
     * @brief  Clear the content of the buffer
     */
    void clear_buffer();
};