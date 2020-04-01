#include <Arduino.h>
#include <vector>

#define THRESHOLD_VAL 5

class Inputs{
    private:

    public:
    Inputs();
    ~Inputs();
    bool has_input();
    int get_input();
};