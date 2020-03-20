#include "View.h"
#include <vector>
#include <string>
#include <Arduino.h>

#define TOUCH_1 27
#define TOUCH_2 14
#define TOUCH_3 12
#define TOUCH_4 13
#define TOUCH_OK 32
#define TOUCH_BACK 33
#define THRESHOLD_VAL 50

int touch_1_val;
int touch_2_val;
int touch_3_val;
int touch_4_val;
int touch_ok_val;
int touch_back_val;

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