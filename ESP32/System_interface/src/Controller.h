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
    void update();
    void update_display();
    int get_input();
    bool has_input();
    std::string typing_input(int line=0, int col=0);
};