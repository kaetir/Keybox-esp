#include <Arduino.h>
#include <vector>

#define THRESHOLD_VAL 5

enum Direction : int
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    OKAY,
    BACK
};

class Inputs
{
private:
public:
    Inputs();
    ~Inputs();
    bool has_input();
    int get_input();
};