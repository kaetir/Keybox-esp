#include <vector>
#include "Arduino.h"
#include <string>
#include <iterator>
#include <algorithm>

#define WIDTH 19

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
};