#include "Controller.h"

Controller::Controller()
{
    //INITIALIZING THE NEW OBJECTS
    this->inputs = new Inputs();
    this->keyboard = new Keyboard();
    this->view = new View();

    std::string str = "";
    this->write(str);
}

Controller::~Controller()
{
    //CLEARING OF THE CONTROLLER
    delete this->inputs;
    delete this->keyboard;
    delete this->view;
}

std::string Controller::write(std::string str)
{
    //CURSOR OF THE INPUT FIELD (ON A CHARACTER)
    int keyboard_cursor = 0;

    //WORD OF THE INPUT FIELD
    std::vector<char> word;

    //BUFFER OF THE WORD
    std::vector<int> word_display;

    if (str.size() == 0) //THE INPUT FIELD IS EMPTY
    {
        word_display.push_back(0);
        word.push_back(this->keyboard->Alphabet[0]);
    }
    else //THE INPUT FIELD IS NOT EMPTY
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (i < FIELD_WIDTH) //NUMBER OF COLUMN - THE SIZE OF THE MENU CURSOR - THE SIZE OF THE KEYBOARD CURSOR
            {
                word_display.push_back(i);
            }
            word.push_back(str[i]);
        }
    }

    //USER FINISHED WRITING ?
    bool has_finished = false;

    //ADDING A NEW CHARACTER ?
    bool new_char = false;

    //INPUT VALUE
    int input;

    //UPDATE THE DISPLAY OF THE INPUT FIELD
    this->view->draw_text(this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char));
    this->view->show();

    while (has_finished == false)
    {
        if (this->inputs->has_input() == true)
        {
            input = this->inputs->get_input();

            if (input != -1 && input != -2)
            {
                //INPUT ACTIONS
                switch (input)
                {
                case Direction::LEFT:
                    this->keyboard->left(&keyboard_cursor, &word_display);
                    if (new_char == true)
                    {
                        new_char = false;
                    }
                    break;

                case Direction::RIGHT:
                    this->keyboard->right(&keyboard_cursor, &word_display, &word);
                    if (keyboard_cursor == word.size() && new_char == false)
                    {
                        new_char = true;
                    }
                    break;

                case Direction::UP:
                    if (new_char == true)
                    {
                        new_char = false;
                        this->keyboard->add(&word, &word_display);
                    }
                    else
                    {
                        this->keyboard->up(&keyboard_cursor, &word);
                    }
                    break;

                case Direction::DOWN:
                    if (new_char == true)
                    {
                        new_char = false;
                        this->keyboard->add(&word, &word_display);
                    }
                    else
                    {
                        this->keyboard->down(&keyboard_cursor, &word);
                    }
                    break;

                case Direction::OKAY:
                    //EXIT THE INPUT FIELD
                    //has_finished = true;
                    break;

                case Direction::BACK:
                    //DELETE THE SELECTED CHARACTER
                    this->keyboard->del(&keyboard_cursor, &word_display, &word);
                    break;
                }

                //UPDATE THE DISPLAY OF THE INPUT FIELD
                this->view->clear_buffer();
                this->view->clear();
                this->view->draw_text(this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char));
                this->view->show();

                Serial.println("");
                Serial.print("[KEYBOARD_CURSOR]: ");
                Serial.println(keyboard_cursor);
                Serial.print("[INPUT FIELD]: [");
                Serial.print(word[0]);
                for (int s = 1; s < word.size(); s++)
                {
                    Serial.print(", ");
                    Serial.print(word[s]);
                }
                Serial.println("]");
                Serial.print("[BUFFER]: [");
                Serial.print(word_display[0]);
                for (int s = 1; s < word_display.size(); s++)
                {
                    Serial.print(", ");
                    Serial.print(word_display[s]);
                }
                Serial.println("]");
            }
        }
        delay(50);
    }

    //RETURN A STRING CONTAINING THE WORD OF THE INPUT FIELD
    std::string ret = "";
    for (int i = 0; i < word.size(); i++)
    {
        ret += word[i];
    }

    //UPDATE THE DISPLAY OF THE INPUT FIELD
    this->view->clear_buffer();
    this->view->clear();
    this->view->draw_text(ret);
    this->view->show();
    return ret;
}