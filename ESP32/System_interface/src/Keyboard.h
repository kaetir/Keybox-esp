#include <vector>
#include "Arduino.h"
#include <string>
#include <iterator>
#include <algorithm>

#define WIDTH 17 //NUMBER OF COLUMNS - SIZE OF THE MENU CURSOR - SIZE OF THE KEYBOARD CURSOR

class Keyboard
{
private:
public:
    std::vector<char> Alphabet;

    /** 
     * @Desc:  Constructor
     * @Params:  none
     * @Returns:  none
     */
    Keyboard();

    /** 
     * @Desc:  Destructor
     * @Params:  none
     * @Returns:  none
     */
    ~Keyboard();

    /** 
     * @Desc:  Modify the selected character by moving up in the Alphabet
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field content
     * @Returns:  none
     */
    void up(int *cursor_pos, std::vector<char> *word);

    /** 
     * @Desc:  Modify the selected character by moving down in the Alphabet
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field content
     * @Returns:  none
     */
    void down(int *cursor_pos, std::vector<char> *word);

    /** 
     * @Desc:  Select the character of the left(if there is one) of the currently selected character
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field buffer
     * @Returns:  none
     */
    void left(int *cursor_pos, std::vector<int> *buffer);

    /** 
     * @Desc:  Select the character of the right(if there is one) of the currently selected character
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field buffer, Pointer to the input field content
     * @Returns:  none
     */
    void right(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);

    /** 
     * @Desc:  Delete the selected character
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field buffer, Pointer to the input field content
     * @Returns:  none
     */
    void del(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);

    /** 
     * @Desc:  Append a new character at the end of the input field content
     * @Params:  Pointer to the input field content, Pointer to the input field buffer
     * @Returns:  none
     */
    void add(std::vector<char> *word, std::vector<int> *buffer);

    /** 
     * @Desc:  Append a new character at the end of the input field content
     * @Params:  Pointer to the keyboard cursor, Pointer to the input field buffer, Pointer to the input field content, Pointer to the New character? boolean
     * @Returns:  String to display on the input field line
     */
    std::string get_display(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word, bool *new_char);
};