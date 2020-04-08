#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>

#include "View.h"
#include "Model.h"
#include "Inputs.h"
#include "Keyboard.h"

class Controller
{
private:
    View *view;                              //View OBJECT
    Model *model;                            //Model OBJECT
    Keyboard *keyboard;                      //Keyboard OBJECT
    Inputs *inputs;                          //Inputs OBJECT
    fs::SPIFFSFS spf;                        //SPIFFS READER/WRITER OBJECT
    int cursor_position;                     //CONTAIN THE POSITION OF THE CURSOR ON THE WHOLE MENU
    std::vector<int> line_number_of_choices; //CONTAIN THE INDEXES OF THE LINES WHERE THE CURSOR SHOULD APPEAR
    std::vector<std::string> menu_lines;     //CONTAIN THE WHOLE MENU LINES
    std::vector<int> buffer;                 //CONTAIN THE INDEXES OF THE LINES TO BE DISPALYED (MAX SIZE == NUM_LINE)

    std::string current_menu;                              //NAME OF THE CURRENT MENU
    int selected_account;                                  //INDEX OF THE SELECTED ACCOUNT IN THE ACCOUNT LIST
    std::vector<std::vector<std::string>> inputs_function; //NAME OF THE FUNCTIONS AND ARGUMENT FOR EACH CHOICE (IT CAN BE "NONE")
    std::vector<std::string> inputs_link;                  //NAME OF THE MENU TO SWITCH TO
    std::map<std::string, std::string> input_fields;       //LIST OF THE INPUT FIELDS IN THE MENU

    /** 
     * @Desc:  Update the display of the menu
     * @Params:  none
     * @Returns:  none
     */
    void update_display();

    /** 
     * @Desc:  Load the menu
     * @Params:  name of the menu file to load
     * @Returns:  none
     */
    void load_menu(std::string menu_name);

    /** 
     * @Desc:  Initalize the menu buffer and the screen
     * @Params:  none
     * @Returns:  none
     */
    void init_buffer();

    /** 
     * @Desc:  Check and act accordingly to the entry selected by the user
     * @Params:  none
     * @Returns:  none
     */
    void select_choice();

    /** 
     * @Desc:  Go back to the previous menu
     * @Params:  none
     * @Returns:  none
     */
    void go_back();

    /** 
     * @Desc:  Write in the input field
     * @Params:  Current content of the input field
     * @Returns:  New content of the input field
     */
    std::string write(std::string str);

    /** 
     * @Desc:  Update the cursor_position and the menu buffer
     * @Params:  none
     * @Returns:  none
     */
    void scroll(int a);

public:
    /** 
     * @Desc:  Constructor
     * @Params:  none
     * @Returns:  none
     */
    Controller();

    /** 
     * @Desc:  Destructor
     * @Params:  none
     * @Returns:  none
     */
    ~Controller();

    /** 
     * @Desc:  Update the system by taking actions determined by the user input
     * @Params:  none
     * @Returns:  none
     */
    void update();
};