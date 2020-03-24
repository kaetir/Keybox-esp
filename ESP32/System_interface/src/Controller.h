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
    std::vector<std::string> menu_lines;

    public:
    Controller();
    ~Controller();
    void update();
    int get_input();
    bool has_input();
    std::string typing_input(int line=0, int col=0);
};