#include "Inputs.h"

std::vector<int> input_pin = {
    33, //LEFT
    32, //RIGHT
    27, //UP
    14, //DOWN
    12, //OKAY
    13  //BACK
};

Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

bool Inputs::has_input()
{
    for (int i = 0; i < input_pin.size(); i++)
    {
        if (int(touchRead(input_pin[i])) < THRESHOLD_VAL)
        {
            return true;
        }
    }
    return false;
}

int Inputs::get_input()
{
    bool has_input = false;
    std::vector<int> input_val;

    for (int i = 0; i < input_pin.size(); i++)
    {
        input_val.push_back(int(touchRead(input_pin[i])));

        if (input_val[input_val.size() - 1] <= THRESHOLD_VAL && has_input == false)
        {
            has_input = true;
        }
        else if (input_val[input_val.size() - 1] <= THRESHOLD_VAL && has_input == true)
        {
            return -2; //MULTIPLE INPUT DETECTED
        }
    }

    if (has_input == true)
    {
        while (this->has_input() == true)
        {
            delay(100);
        }
        for (int i = 0; i < input_val.size(); i++)
        {
            if (input_val[i] <= THRESHOLD_VAL)
            {
                return i;
            }
        }
    }
    return -1; //NO INPUT FOUND
}