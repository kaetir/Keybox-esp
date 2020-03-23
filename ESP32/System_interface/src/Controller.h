#include "View.h"
#include <vector>
#include <string>
#include <Arduino.h>

class Controller{
    private:
    View view;
    int cursor_postion;
    std::vector<int> line_number_of_choices;
    std::vector<int> type_of_choices;
    std::vector<std::string> menu_lines;
    std::vector<std::string> filenames;

    public:
    Controller();
    ~Controller();
    void update();
    int get_input();
    bool has_input();
    std::string typing_input(int line=0, int col=0);
};