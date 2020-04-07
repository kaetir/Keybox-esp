#include <vector>
#include "Arduino.h"
#include <string>
#include <iterator>
#include <algorithm>

#define WIDTH 17 //21 - 2 - 2

class Keyboard
{
private:
public:
    Keyboard();
    ~Keyboard();
    std::vector<char> Alphabet;
    void up(int *cursor_pos, std::vector<char> *word);
    void down(int *cursor_pos, std::vector<char> *word);
    void left(int *cursor_pos, std::vector<int> *buffer);
    void right(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);
    void del(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word);
    void add(std::vector<char> *word, std::vector<int> *buffer);
    std::string get_display(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word, bool *new_char);
};