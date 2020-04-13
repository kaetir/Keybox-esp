#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>

#include "Inputs.h"
#include "Keyboard.h"
#include "View.h"

class Controller
{
private:
    View *view;
    Keyboard *keyboard;  //Keyboard OBJECT
    Inputs *inputs;      //Inputs OBJECT
    int cursor_position; //CONTAIN THE POSITION OF THE CURSOR ON THE WHOLE MENU

    /** 
     * @Desc:  Write in the input field
     * @Params:  Current content of the input field
     * @Returns:  New content of the input field
     */
    std::string write(std::string str);

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
};