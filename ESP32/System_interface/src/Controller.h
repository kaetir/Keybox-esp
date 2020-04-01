#include "View.h"
#include "Model.h"
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>
#include "Inputs.h"

class Controller{
    private:
    View *view;
    Model *model;
    Inputs *inputs;
    fs::SPIFFSFS spf;
    int cursor_position; //CONTAIN THE POSITION OF THE CURSOR ON THE WHOLE MENU
    std::vector<int> line_number_of_choices; //CONTAIN THE INDEXES OF THE LINES WHERE THE CURSOR SHOULD APPEAR
    std::vector<std::string> menu_lines; //CONTAIN THE WHOLE MENU LINES
    std::vector<int> buffer; //CONTAIN THE INDEXES OF THE LINES TO BE DISPALYED (MAX SIZE == NUM_LINE)

    std::string actual_menu; //Name of the actual menu
    int selected_account; //Index of the selected account in the account list
    std::vector<std::vector<std::string>> inputs_function; //Name of the functions and argument for each choice (it can be "None")
    std::vector<std::string> inputs_link; //Name of the menu to switch to
    std::map<std::string, std::string> input_fields; //List of the input fields in the menu


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
     * @Desc:  Get the user typing (username, password...)
     * @Params:  none
     * @Returns:  none
     */
    void typing_input(int line=0, int col=0);

    /** 
     * @Desc:  Load the menu
     * @Params:  name of the menu file to load
     * @Returns:  none
     */
    void load_menu(std::string menu_name);

     /** 
     * @Desc:  init the buffer and the view
     * @Params:  none
     * @Returns:  none
     */
    void init_buffer();
};