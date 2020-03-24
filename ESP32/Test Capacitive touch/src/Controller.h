#include <vector>
#include <string>
#include <Arduino.h>

class Controller{
    private:

    public:
    Controller();
    ~Controller();
    void update();
    int get_input();
    bool has_input();
    std::string typing_input(int line=0, int col=0);
};