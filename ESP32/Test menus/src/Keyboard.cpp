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
    if (buffer->size() < WIDTH)
    {
        buffer->push_back(buffer->size());
    }
    else
    {
        for (int i = 0; i < buffer->size(); i++)
        {
            (*buffer)[i]++;
        }
    }
    word->push_back(this->Alphabet[0]);
}

void Keyboard::del(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word)
{
    if (word->size() > 1) //SECURITY TO LIMIT TO 1 CHARACTER BY WORD MINIMUM
    {
        if (word->size() > buffer->size()) //THE WORD IS LONGER THAN THE BUFFER
        {
            word->erase(word->begin() + *cursor_pos);
            this->left(cursor_pos, buffer);
        }
        else //THE WORD IS SHORTER THAN THE BUFFER (OR HAVE AN EQUAL LENGTH)
        {
            word->erase(word->begin() + *cursor_pos);
            buffer->pop_back();
            left(cursor_pos, buffer);
        }
    }
}

void Keyboard::left(int *cursor_pos, std::vector<int> *buffer)
{
    if (*cursor_pos != 0) //SECURITY TO STOP THE CURSOR FROM BEIGN NEGATIVE
    {
        *cursor_pos -= 1;
        if (*cursor_pos < (*buffer)[0]) //THE CURSOR IS NO LONGER IN THE BUFFER
        {
            for (int i = 0; i < buffer->size(); i++) //MOVE THE BUFFER
            {
                (*buffer)[i]--;
            }
        }
    }
}

void Keyboard::right(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word)
{
    if (*cursor_pos < word->size() - 1)
    {
        *cursor_pos += 1;
        if (*cursor_pos > (*buffer)[buffer->size() - 1])
        {
            for (int i = 0; i < buffer->size(); i++)
            {
                (*buffer)[i]++;
            }
        }
    }
    else if (*cursor_pos == word->size() - 1)
    {
        *cursor_pos += 1; //cursor_pos == word->size()
    }
}

void Keyboard::up(int *cursor_pos, std::vector<char> *word)
{
    if ((*word)[*cursor_pos] != Alphabet[0])
    {
        std::vector<char>::iterator it = std::find(Alphabet.begin(), Alphabet.end(), (*word)[*cursor_pos]);
        int index = std::distance(Alphabet.begin(), it);
        (*word)[*cursor_pos] = Alphabet[index - 1];
    }
    else
    {
        (*word)[*cursor_pos] = Alphabet[Alphabet.size() - 1];
    }
}

void Keyboard::down(int *cursor_pos, std::vector<char> *word)
{
    if ((*word)[*cursor_pos] != Alphabet[Alphabet.size() - 1])
    {
        std::vector<char>::iterator it = std::find(Alphabet.begin(), Alphabet.end(), (*word)[*cursor_pos]);
        int index = std::distance(Alphabet.begin(), it);
        (*word)[*cursor_pos] = Alphabet[index + 1];
    }
    else
    {
        (*word)[*cursor_pos] = Alphabet[0];
    }
}

std::string Keyboard::get_display(int *cursor_pos, std::vector<int> *buffer, std::vector<char> *word, bool *new_char)
{
    std::string ret = "";
    if (buffer->size() < WIDTH)
    {
        if (*new_char == true)
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
    else
    {
        if (*new_char == true)
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