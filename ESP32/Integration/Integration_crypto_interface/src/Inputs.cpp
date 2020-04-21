#include "Inputs.h"

// INPUT PIN VALUES
std::vector<int> input_pin = {
    33,  // LEFT
    32,  // RIGHT
    27,  // UP
    14,  // DOWN
    12,  // OKAY
    13   // BACK
};

Inputs::Inputs() {}

Inputs::~Inputs() {}

bool Inputs::has_input() {
  for (int i = 0; i < input_pin.size(); i++) {
    if (int(touchRead(input_pin[i])) < THRESHOLD_VAL)  // AN INPUT WAS DETECTED
    {
      return true;
    }
  }
  return false;  // NO INPUT WAS DETECTED
}

int Inputs::get_input() {
  bool has_input = false;
  std::vector<int> input_val;

  for (int i = 0; i < input_pin.size(); i++) {
    input_val.push_back(int(touchRead(input_pin[i])));

    if (input_val[input_val.size() - 1] <= THRESHOLD_VAL &&
        has_input == false)  // ONE INPUT WAS DETECTED
    {
      has_input = true;
    } else if (input_val[input_val.size() - 1] <= THRESHOLD_VAL &&
               has_input == true)  // MULTIPLE INPUT DETECTED
    {
      return -2;
    }
  }

  if (has_input == true)  // ONE INPUT WAS DETECTED
  {
    while (this->has_input() ==
           true)  // WAIT FOR THE USER TO RELEASE THE INPUT/BUTTON
    {
      delay(100);
    }
    for (int i = 0; i < input_val.size(); i++) {
      if (input_val[i] <= THRESHOLD_VAL)  // INPUT FOUND
      {
        return i;
      }
    }
  }
  return -1;  // NO INPUT FOUND
}