#include "Controller.h"

//MENU FILE NAMES
std::vector<std::string> filenames = {
    "Welcome_menu",      //0
    "Login",             //1
    "Main_menu",         //2
    "Web_server",        //3
    "Accounts_menu",     //4
    "Add_account",       //5
    "Account_selection", //6
    "Display_account",   //7
    "Delete_account",    //8
    "Send_to_computer",  //9
    "Modify_account",    //10
    "New_password",      //11
    "New_username"       //12
};

//PREVIOUS MENU INDEX
int previous_menu[] = {
    0,  //Welcome_menu
    0,  //Login
    2,  //Main_menu
    2,  //Web_server
    2,  //Accounts_menu
    4,  //Add_account
    4,  //Account_selection
    6,  //Display_account
    7,  //Delete_account
    7,  //Send_to_computer
    7,  //Modify_account
    10, //New_password
    10  //New_username
};

Controller::Controller()
{
    //INITIALIZING THE NEW OBJECTS
    this->view = new View();
    this->model = new Model();
    this->inputs = new Inputs();
    this->keyboard = new Keyboard();

    //INITIALIZING THE SPIFFS READER/WRITER
    if (!this->spf.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
    }

    //LOADING THE WELCOME MENU AND INITIALIZING THE BUFFER OF THE MENU
    this->load_menu(filenames[0]);
    this->current_menu = filenames[0];
    this->init_buffer();
}

Controller::~Controller()
{
    //CLEARING OF THE CONTROLLER
    delete this->view;
    delete this->model;
    delete this->inputs;
    delete this->keyboard;
}

void Controller::init_buffer()
{
    //CLEARING OF THE THE BUFFER OF THE MENU AND OF THE DISPLAY
    this->buffer.clear();
    this->view->clear();
    this->view->clear_buffer();

    //FILLING THE BUFFER WITH THE MENU LINES
    for (int i = 0; i < menu_lines.size(); i++)
    {
        if (i < NUM_LINE)
        {
            this->view->draw_text(this->menu_lines[i], i, 0);
            this->buffer.push_back(i);
        }
        else
        {
            break;
        }
    }
    this->cursor_position = 0;

    //DISPLAY THE BUFFER OF THE MENU
    this->view->show();
}

void Controller::load_menu(std::string menu_name)
{
    //CLEARING OF THE MENU ENTRIES
    this->line_number_of_choices.clear();

    //CLEARING OF THE ACTIVATIONS FUNCTION OF EACH MENU ENTRY
    this->inputs_function.clear();

    //CLEARING OF THE MENU LINKS OF EACH MENU ENTRY
    this->inputs_link.clear();

    //CLEARING OF THE INPUT FIELDS
    this->input_fields.clear();

    //FILLING THE MENU LINES WITH THE NEW ONES
    this->menu_lines = this->model->read(this->spf, menu_name, "txt");

    //GETTING THE MENU STRUCTURE
    std::vector<std::string> struct_tmp = this->model->read(this->spf, menu_name, "struct");
    std::vector<std::string> tmp_vect;

    int num;
    char type;
    std::string funct;
    std::string menu;
    std::string name;
    std::string arg1;
    std::string arg2;
    std::string arg3;

    //SETTING UP THE STRUCTURE FOR EACH MENU LINE
    for (int i = 0; i < this->menu_lines.size(); i++)
    {
        std::istringstream ss(struct_tmp[i]);
        ss >> num >> type;

        switch (type)
        {
        case '>': //LINK TO ANOTHER MENU
            ss >> menu;
            this->line_number_of_choices.push_back(num);
            tmp_vect = {"None"};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back(menu);
            break;

        case '<': // INPUT FIELD
            ss >> name;
            this->line_number_of_choices.push_back(num);
            tmp_vect = {"InputField", name};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("None");
            this->input_fields[name] = "";
            break;

        case 'f': //ACTIVATE A FUNCTION BEFORE SWITCHING MENU
            this->line_number_of_choices.push_back(num);
            ss >> menu >> funct;
            this->inputs_link.push_back(menu);

            if (funct == "add_account") //add_account(arg1:name, arg2:username, arg3:password)
            {
                ss >> arg1 >> arg2 >> arg3;
                tmp_vect = {funct, arg1, arg2, arg3};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "deleteAccount") //deleteAccount()
            {
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "login") //login(arg1:user, arg2:password)
            {
                ss >> arg1 >> arg2;
                tmp_vect = {funct, arg1, arg2};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "logoff") //logoff()
            {
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "setAccountPassword") //setAccountPassword(arg1:password)
            {
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "setAccountUsername") //setAccountUsername(arg1:username)
            {
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "sendToComputer") //sendToComputer()
            {
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "switch_ServerStatus") //switch_ServerStatus()
            {
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            break;

        case 'g': //GET FUNCTIONS
            ss >> funct;
            if (funct == "getAccountlist") //DISPLAY THE LIST OF ACCOUNTS
            {
                std::vector<std::string> account_list = this->model->get_accounts();

                this->menu_lines[num] = account_list[0];
                this->line_number_of_choices.push_back(num);

                tmp_vect = {"selectAccount", std::string(0)};
                this->inputs_function.push_back(tmp_vect);
                this->inputs_link.push_back("Display_account");

                for (int j = 1; j < account_list.size(); j++)
                {
                    this->menu_lines.push_back(account_list[j]);
                    this->line_number_of_choices.push_back(menu_lines.size() - 1);

                    std::stringstream int_to_string;
                    int_to_string << j;

                    tmp_vect = {"selectAccount", int_to_string.str()};
                    this->inputs_function.push_back(tmp_vect);
                    this->inputs_link.push_back("Display_account");
                }
            }
            else if (funct == "getAccountName") //DISPLAY THE SELECTED ACCOUNT NAME
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[0];
            }
            else if (funct == "getAccountUsername") //DISPLAY THE SELECTED ACCOUNT USERNAME
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[1];
            }
            else if (funct == "getAccountPassword") //DISPLAY THE SELECTED ACCOUNT PASSWORD
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[2];
            }
            else if (funct == "getServerStatus") //DISPLAY WEB SERVER STATUS
            {
                if (this->model->is_webserver_on())
                {
                    this->menu_lines[num] += " ON";
                }
                else
                {
                    this->menu_lines[num] += " OFF";
                }
            }
            break;
        }
    }
}

void Controller::scroll(int a)
{
    if (a == 1) //SCROLLING UP
    {
        if (this->cursor_position != this->buffer[0]) //THE CURSOR IS NOT AT THE TOP OF THE MENU BUFFER
        {
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position);
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE MENU BUFFER (from 1 to 3)
            bool has_found = false;                                        //HAS FOUND AN ENTRY ABOVE THE CURSOR ACTUAL POSITION ?
            for (int i = index_of_cursor - 1; i >= 0; i--)
            {
                if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true) //ENTRY FOUND ABOVE THE CURSOR (CASE 1)
                {
                    this->cursor_position = this->buffer[i];
                    has_found = true;
                    break;
                }
            }
            if (has_found == false && this->buffer[0] != 0) //NO ENTRY FOUND ABOVE THE CURSOR (CASE 2)
            {
                this->cursor_position = this->buffer[0] - 1;
                for (int i = 0; i < this->buffer.size(); i++) //MOVE THE MENU BUFFER UP
                {
                    this->buffer[i]--;
                }
            }
        }
        else //THE CURSOR IS AT THE TOP OF THE BUFFER (CASE 3)
        {
            if (this->cursor_position != 0)
            {
                this->cursor_position--;
                for (int i = 0; i < this->buffer.size(); i++) //MOVE THE MENU BUFFER UP
                {
                    this->buffer[i]--;
                }
            }
        }
    }
    else //SCROLLING DOWN
    {
        if (this->cursor_position != this->buffer[this->buffer.size() - 1]) //THE CURSOR IS NOT AT THE BOTTOM OF THE BUFFER
        {
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position);
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE MENU BUFFER (from 0 to 2)
            bool has_found = false;                                        //HAS FOUND AN ENTRY BELOW THE CURSOR ACTUAL POSITION ?
            for (int i = index_of_cursor + 1; i < this->buffer.size(); i++)
            {
                if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true) //ENTRY FOUND BELOW THE CURSOR (CASE 1)
                {
                    this->cursor_position = this->buffer[i];
                    has_found = true;
                    break;
                }
            }
            if (has_found == false && this->buffer[this->buffer.size() - 1] != this->menu_lines.size() - 1) //NO ENTRY FOUND BELOW THE CURSOR (CASE 2)
            {
                this->cursor_position = this->buffer[this->buffer.size() - 1] + 1;
                for (int i = 0; i < this->buffer.size(); i++) //MOVE THE MENU BUFFER DOWN
                {
                    this->buffer[i]++;
                }
            }
        }
        else
        {
            if (this->cursor_position != this->menu_lines.size() - 1) //THE CURSOR IS AT THE BOTTOM OF THE MENU BUFFER (CASE 3)
            {
                this->cursor_position++;
                for (int i = 0; i < this->buffer.size(); i++) //MOVE THE MENU BUFFER DOWN
                {
                    this->buffer[i]++;
                }
            }
        }
    }
}

void Controller::update_display()
{
    this->view->clear_buffer();
    this->view->clear();

    //DISPLAY EACH LINE OF THE MENU BUFFER
    for (int i = 0; i < this->buffer.size(); i++)
    {
        if (this->buffer[i] == this->cursor_position)
        {
            if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true) //THE CURSOR IS ON AN ENTRY
            {
                this->view->draw_text("->" + this->menu_lines[this->buffer[i]], i);
            }
            else //THE CURSOR IS NOT ON AN ENTRY (ON A TEXT LINE)
            {
                this->view->draw_text(this->menu_lines[this->buffer[i]], i);
            }
        }
        else
        {
            this->view->draw_text(this->menu_lines[this->buffer[i]], i); //THE CURSOR IS NOT ON THIS LINE
        }
    }
    this->view->show();
}

void Controller::select_choice()
{
    for (int i = 0; i < this->buffer.size(); i++)
    {
        if (this->buffer[i] == this->cursor_position) //CURSOR POSITION FOUND IN THE MENU BUFFER
        {
            if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true) //THE CURSOR IS ON AN ENTRY
            {

                bool is_valid = false; //SUCCESSFUL EXECUTION OF THE ACTIVATION FUNCTIONS ?
                std::vector<int>::iterator it = std::find(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->cursor_position);
                int index_of_cursor = std::distance(this->line_number_of_choices.begin(), it); //INDEX OF THE CURSOR IN THE VECTOR OF ENTRIES

                std::string funct = this->inputs_function[index_of_cursor][0]; //ACTIVATION FUNCTION OF THE ENTRY (IT CAN BE "None")

                if (funct == "None")
                {
                    is_valid = true;
                }
                else if (funct == "InputField")
                {
                    Serial.println((this->inputs_function[index_of_cursor][1]).c_str());
                    this->input_fields[this->inputs_function[index_of_cursor][1]] = this->write(this->input_fields[this->inputs_function[index_of_cursor][1]]);
                    is_valid = true;
                }
                else if (funct == "add_account")
                {
                }
                else if (funct == "deleteAccount")
                {
                }
                else if (funct == "login")
                {
                }
                else if (funct == "logoff")
                {
                }
                else if (funct == "setAccountPassword")
                {
                }
                else if (funct == "setAccountUsername")
                {
                }
                else if (funct == "sendToComputer")
                {
                }
                else if (funct == "switch_ServerStatus")
                {
                }
                if (is_valid == true && this->inputs_link[index_of_cursor] != "None") //LOADING THE NEW MENU
                {
                    this->current_menu = this->inputs_link[index_of_cursor];
                    this->load_menu(this->inputs_link[index_of_cursor]);
                    this->init_buffer();
                }
                break;
            }
        }
        break;
    }
}

void Controller::go_back()
{
    std::vector<std::string>::iterator it = std::find(filenames.begin(), filenames.end(), this->current_menu);
    int index_of_filename = std::distance(filenames.begin(), it); //INDEX OF THE MENU IN THE FILENAMES (from 0 to 12)

    this->current_menu = filenames[previous_menu[index_of_filename]];
    this->load_menu(filenames[previous_menu[index_of_filename]]); //LOAD THE LAST MENU
    this->init_buffer();
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
            if (i < WIDTH) //NUMBER OF COLUMN - THE SIZE OF THE MENU CURSOR - THE SIZE OF THE KEYBOARD CURSOR
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
    this->menu_lines[this->cursor_position] = this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char);
    this->update_display();

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
                    has_finished = true;
                    break;

                case Direction::BACK:
                    //DELETE THE SELECTED CHARACTER
                    this->keyboard->del(&keyboard_cursor, &word_display, &word);
                    break;
                }

                //UPDATE THE DISPLAY OF THE INPUT FIELD
                this->menu_lines[this->cursor_position] = this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char);
                this->update_display();

                Serial.print("CURSOR: ");
                Serial.println(keyboard_cursor);
                Serial.print("WORD: ");
                for (int s = 0; s < word.size(); s++)
                {
                    Serial.print(word[s]);
                }
                Serial.println("");
                Serial.print("BUFFER: ");
                for (int s = 0; s < word_display.size(); s++)
                {
                    Serial.print(word_display[s]);
                    Serial.print("-");
                }
                Serial.println("");
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
    this->menu_lines[this->cursor_position] = ret;
    this->update_display();
    return ret;
}

void Controller::update()
{
    if (this->inputs->has_input())
    {
        int input = this->inputs->get_input(); //GET THE USER INPUT
        if (input != -1 && input != -2)
        {

            switch (input)
            {
            case Direction::UP:
                this->scroll(1);
                Serial.println("UP");
                this->update_display();
                break;

            case Direction::DOWN:
                this->scroll(-1);
                Serial.println("DOWN");
                this->update_display();
                break;

            case Direction::OKAY:
                Serial.println("OK");
                this->select_choice();
                break;

            case Direction::BACK:
                Serial.println("BACK");
                this->go_back();
                break;
            }
            Serial.print("CURSOR:");
            Serial.println(this->cursor_position);
        }
    }
}