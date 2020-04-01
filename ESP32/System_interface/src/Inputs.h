#include <Arduino.h>
#include <vector>

#define THRESHOLD_VAL 5

class Inputs{
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
     * @Desc:  Check if there is an input from the user
     * @Params:  none
     * @Returns:  Return True if there is an input and False if there is no input
     */
    bool has_input();

    /** 
     * @Desc:  Get the input from the user
     * @Params:  none
     * @Returns:  none
     */
    int get_input();
};