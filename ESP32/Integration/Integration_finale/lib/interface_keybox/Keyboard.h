#include <vector>
#include "Arduino.h"
#include <string>
#include <iterator>
#include <algorithm>

#define FIELD_WIDTH 17 //NUMBER OF COLUMNS - SIZE OF THE MENU CURSOR - SIZE OF THE KEYBOARD CURSOR

class Keyboard
{
private:
public:
    std::vector<char> Alphabet;

    /** 
     * @brief  Constructor
     */
    Keyboard();

    /** 
     * @brief  Destructor
     */
    ~Keyboard();

    /** 
     * @brief  Modify the selected character by moving up in the Alphabet
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param word Pointer to the input field content
     */
    void up(int *cursor_pos, std::vector<char> *word);

    /** 
     * @brief  Modify the selected character by moving down in the Alphabet
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param word Pointer to the input field content
     */
    void down(int *cursor_pos, std::vector<char> *word);

    /** 
     * @brief  Select the character of the left(if there is one) of the currently selected character
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param buffer  Pointer to the input field display buffer
     */
    void left(int *cursor_pos, std::vector<int> *buffer);

    /** 
     * @brief  Select the character of the right(if there is one) of the currently selected character
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param buffer  Pointer to the input field display buffer
     * @param word Pointer to the input field content
     */
    void right(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);

    /** 
     * @brief  Delete the selected character
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param buffer  Pointer to the input field display buffer
     * @param word Pointer to the input field content
     */
    void del(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);

    /** 
     * @brief  Append a new character at the end of the input field content
     * @param word Pointer to the input field content
     * @param buffer  Pointer to the input field display buffer
     */
    void add(std::vector<char> *word, std::vector<int> *buffer);

    /** 
     * @brief  Append a new character at the end of the input field content
     * @param cursor_pos  Pointer to the keyboard cursor
     * @param buffer  Pointer to the input field display buffer
     * @param word Pointer to the input field content
     * @param new_char Pointer to the boolean (Is the keyboard cursor at a new character ?)
     * @return  String to display on the input field line
     */
    std::string get_display(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word, bool *new_char);
};