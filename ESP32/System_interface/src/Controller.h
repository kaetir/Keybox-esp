#include "View.h"
#include "Model.h"
#include <vector>
#include <string>
#include <Arduino.h>

class Controller{
    private:
    View *view;
    Model *model;
    int cursor_postion;
    std::vector<int> line_number_of_choices;
    std::vector<std::string> menu_lines; //CONTAIN THE WHOLE MENU LINES
    std::vector<std::string> menu_display; //CONTAIN ONLY THE 4 MENU LINES TO DISPLAY

    public:
    Controller();
    ~Controller();

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
};