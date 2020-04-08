#include <Arduino.h>
#include <vector>

#define THRESHOLD_VAL 5 //IF touchRead() < 5: DETECT AN INPUT FROM THE USER

//INPUT DIRECTIONS
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
    /** 
     * @Desc:  Constructor
     * @Params:  none
     * @Returns:  none
     */
    Inputs();

    /** 
     * @Desc:  Destructor
     * @Params:  none
     * @Returns:  none
     */
    ~Inputs();

    /** 
     * @Desc:  Check if an input was detected
     * @Params:  none
     * @Returns:  True or False if there is an input or not
     */
    bool has_input();

    /** 
     * @Desc:  Get the input from the user
     * @Params:  none
     * @Returns:  Return an integer corresponding to an input (enum Direction)
     */
    int get_input();
};