#include "View.h"
#include "Model.h"
#include <vector>
#include <string>
#include <Arduino.h>
#include <iterator>
#include <algorithm>

class Controller{
    private:
    View *view;
    Model *model;
    int cursor_position; //CONTAIN THE POSITION OF THE CURSOR ON THE WHOLE MENU
    std::vector<int> line_number_of_choices; //CONTAIN THE INDEXES OF THE LINES WHERE THE CURSOR SHOULD APPEAR
    std::vector<std::string> menu_lines; //CONTAIN THE WHOLE MENU LINES
    std::vector<int> buffer; //CONTAIN THE INDEXES OF THE LINES TO BE DISPALYED (MAX SIZE == NUM_LINE)

    public:
    Controller();
    ~Controller();

    /** 
     * @Desc:  Update the cursor_position and the buffer
     * @Params:  none
     * @Returns:  none
     */
    void scroll(int a);

    /** 
     * @Desc:  Update the system by taking actions determined by the user input
     * @Params:  none
     * @Returns:  none
     */
    void update();

    /** 
     * @Desc:  Update the display of the menu
     * @Params:  none
     * @Returns:  none
     */
    void update_display();

    /** 
     * @Desc:  Get the inputs of the user
     * @Params:  none
     * @Returns:  int
     */
    int get_input();

    /** 
     * @Desc:  Check if the user used an input
     * @Params:  none
     * @DReturns:  bool
     */
    bool has_input();

    /** 
     * @Desc:  Get the user typing (username, password...)
     * @Params:  none
     * @Returns:  none
     */
    void typing_input(int line=0, int col=0);

    /** 
     * @Desc:  Get the user typing (username, password...)
     * @Params:  none
     * @Returns:  none
     */
    void load_menu(std::string menu);
};