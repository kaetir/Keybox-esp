#include <Arduino.h>

#include <vector>

#define THRESHOLD_VAL 5  // IF touchRead() < 5: DETECT AN INPUT FROM THE USER

// INPUT DIRECTIONS
enum Direction : int { LEFT, RIGHT, UP, DOWN, OKAY, BACK };

class Inputs {
 private:
 public:
  /**
   * @brief  Constructor
   */
  Inputs();

  /**
   * @brief  Destructor
   */
  ~Inputs();

  /**
   * @brief  Check if an input was detected
   * @return  True or False if there is an input or not
   */
  bool has_input();

  /**
   * @brief  Get the input from the user
   * @return  An integer corresponding to the input used (enum Direction)
   */
  int get_input();
};