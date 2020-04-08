#include "Keyboard.h"

Keyboard::Keyboard()
{
    this->Alphabet = {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9'};
}

Keyboard::~Keyboard()
{
}

void Keyboard::add(std::vector<char> *word, std::vector<int> *buffer)
{
    if (buffer->size() < WIDTH) //INPUT FIELD BUFFER SIZE < DISPLAY SIZE (WIDTH)
    {
        buffer->push_back(buffer->size());
    }
    else //INPUT FIELD BUFFER SIZE >= DISPLAY SIZE (WIDTH)
    {
        for (int i = 0; i < buffer->size(); i++) //MOVE THE BUFFER TO THE RIGHT
        {
            (*buffer)[i]++;
        }
    }
    word->push_back(this->Alphabet[0]);
}

void Keyboard::del(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word)
{
    if (word->size() > 1) //SECURITY TO LIMIT TO 1 CHARACTER BY WORD
    {
        if (word->size() > buffer->size()) //THE WORD IS LONGER THAN THE BUFFER
        {
            word->erase(word->begin() + *cursor_pos);
            this->left(cursor_pos, buffer);
        }
        else //THE WORD AND THE BUFFER HAVE AN EQUAL LENGTH
        {
            word->erase(word->begin() + *cursor_pos);
            buffer->pop_back();
            left(cursor_pos, buffer);
        }
    }
}

void Keyboard::left(int *cursor_pos, std::vector<int> *buffer)
{
    if (*cursor_pos != 0) //SECURITY TO STOP THE KEYBOARD CURSOR FROM BEING NEGATIVE
    {
        *cursor_pos -= 1;
        if (*cursor_pos < (*buffer)[0]) //THE KEYBOARD CURSOR CURSOR IS NO LONGER IN THE BUFFER
        {
            for (int i = 0; i < buffer->size(); i++) //MOVE THE BUFFER TO THE LEFT
            {
                (*buffer)[i]--;
            }
        }
    }
}

void Keyboard::right(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word)
{
    if (*cursor_pos < word->size() - 1) //KEYBOARD CURSOR < SIZE OF THE WORD - 1
    {
        *cursor_pos += 1;
        if (*cursor_pos > (*buffer)[buffer->size() - 1]) //THE KEYBOARD CURSOR CURSOR IS NO LONGER IN THE BUFFER
        {
            for (int i = 0; i < buffer->size(); i++) //MOVE THE BUFFER TO THE RIGHT
            {
                (*buffer)[i]++;
            }
        }
    }
    else if (*cursor_pos == word->size() - 1) //KEYBOARD CURSOR == SIZE OF THE WORD - 1
    {
        *cursor_pos += 1; //KEYBOARD CURSOR == SIZE OF THE WORD
    }
}

void Keyboard::up(int *cursor_pos, std::vector<char> *word)
{
    if ((*word)[*cursor_pos] != Alphabet[0]) //THE SELECTED CHARACTER IS NOT THE FIRST CHARACTER OF Alphabet
    {
        std::vector<char>::iterator it = std::find(Alphabet.begin(), Alphabet.end(), (*word)[*cursor_pos]);
        int index = std::distance(Alphabet.begin(), it);
        (*word)[*cursor_pos] = Alphabet[index - 1]; //MOVE THE CHARACTER UP IN Alphabet
    }
    else //THE SELECTED CHARACTER IS THE FIRST CHARACTER OF Alphabet
    {
        (*word)[*cursor_pos] = Alphabet[Alphabet.size() - 1]; //THE SELECTED CHARACTER IS NOW THE LAST CHARACTER OF Alphabet
    }
}

void Keyboard::down(int *cursor_pos, std::vector<char> *word)
{
    if ((*word)[*cursor_pos] != Alphabet[Alphabet.size() - 1]) //THE SELECTED CHARACTER IS NOT THE LAST CHARACTER OF Alphabet
    {
        std::vector<char>::iterator it = std::find(Alphabet.begin(), Alphabet.end(), (*word)[*cursor_pos]);
        int index = std::distance(Alphabet.begin(), it);
        (*word)[*cursor_pos] = Alphabet[index + 1]; //MOVE THE CHARACTER DOWN IN Alphabet
    }
    else //THE SELECTED CHARACTER IS THE LAST CHARACTER OF Alphabet
    {
        (*word)[*cursor_pos] = Alphabet[0]; //THE SELECTED CHARACTER IS NOW THE FIRST CHARACTER OF Alphabet
    }
}

std::string Keyboard::get_display(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word, bool *new_char)
{
    std::string ret = "";
    if (buffer->size() < WIDTH) //KEYBOARD BUFFER < SIZE OF THE DISPLAY
    {
        if (*new_char == true) //KEYBOARD CURSOR POINTING TO AN EMPTY CHARACTER (NOT CREATED YET)
        {
            for (int i = 0; i < buffer->size(); i++)
            {
                ret += (*word)[(*buffer)[i]];
            }
            ret += "<>";
        }
        else
        {
            for (int i = 0; i < buffer->size(); i++)
            {
                if (*cursor_pos == (*buffer)[i])
                {
                    ret += "<";
                    ret += (*word)[(*buffer)[i]];
                    ret += ">";
                }
                else
                {
                    ret += (*word)[(*buffer)[i]];
                }
            }
        }
    }
    else //KEYBOARD BUFFER >= SIZE OF THE DISPLAY
    {
        if (*new_char == true) //KEYBOARD CURSOR POINTING TO AN EMPTY CHARACTER (NOT CREATED YET)
        {
            for (int i = 1; i < buffer->size(); i++)
            {
                ret += (*word)[(*buffer)[i]];
            }
            ret += "<>";
        }
        else
        {
            for (int i = 0; i < buffer->size(); i++)
            {
                if (*cursor_pos == (*buffer)[i])
                {
                    ret += "<";
                    ret += (*word)[(*buffer)[i]];
                    ret += ">";
                }
                else
                {
                    ret += (*word)[(*buffer)[i]];
                }
            }
        }
    }
    return ret;
}