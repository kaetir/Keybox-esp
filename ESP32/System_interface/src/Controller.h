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
    View *view; //Oject containing the View
    Model *model; //Oject containing the Model
    Inputs *inputs; //Oject reading the inputs from the user
    fs::SPIFFSFS spf; //Object containing the SPIFFS reader/writer
    int cursor_position; //Current position of the cursor on the menu (starting at 0)
    std::vector<int> line_number_of_choices; //Array of index of choices on the current menu
    std::vector<std::string> menu_lines; //Array of the content of each menu lines
    std::vector<int> buffer; //Array of index (of menu_lines) to display

    std::string actual_menu; //Filename of the current menu
    int selected_account; //Index of the selected account in the account list
    std::vector<std::vector<std::string>> inputs_function; //Name of the functions and argument for each choice (it can be "None")
    std::vector<std::string> inputs_link; //Name of the next menu to load
    std::map<std::string, std::string> input_fields; //List of the input fields in the current menu


    public:
    Controller();
    ~Controller();

    /** 
     * @Desc:  Update the cursor_position and the buffer
     * @Params:  1 for scroll up and -1 for scroll down
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