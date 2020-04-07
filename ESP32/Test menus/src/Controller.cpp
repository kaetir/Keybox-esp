#include "Controller.h"

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
    this->view = new View();
    this->model = new Model();
    this->inputs = new Inputs();
    this->keyboard = new Keyboard();

    if (!this->spf.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
    }
    this->load_menu(filenames[0]);
    this->current_menu = filenames[0];
    this->init_buffer();
}

Controller::~Controller()
{
    delete this->view;
    delete this->model;
    delete this->inputs;
}

void Controller::init_buffer()
{
    this->buffer.clear();
    this->view->clear();
    this->view->clear_buffer();
    for (int i = 0; i < menu_lines.size(); i++)
    { //FILL THE BUFFER WITH THE MENU LINES
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
    this->view->show(); //DISPLAY THE BUFFER
}

void Controller::load_menu(std::string menu_name)
{
    this->line_number_of_choices.clear(); //Clear the choices position
    this->inputs_function.clear();        //Clear the choices function (and arguments)
    this->inputs_link.clear();            //Clear the choices link
    this->input_fields.clear();           //Clear the input fields

    this->menu_lines = this->model->read(this->spf, menu_name, "txt");                       //Fill the menu_lines with the new menu
    std::vector<std::string> struct_tmp = this->model->read(this->spf, menu_name, "struct"); //get the menu structure

    std::vector<std::string> tmp_vect;

    int num;
    char type;
    std::string funct;
    std::string menu;
    std::string name;
    std::string arg1;
    std::string arg2;
    std::string arg3;

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

            if (funct == "add_account")
            { //add_account(arg1:name, arg2:username, arg3:password)
                ss >> arg1 >> arg2 >> arg3;
                tmp_vect = {funct, arg1, arg2, arg3};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "deleteAccount")
            { //deleteAccount()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "login")
            { //login(arg1:user, arg2:password)
                ss >> arg1 >> arg2;
                tmp_vect = {funct, arg1, arg2};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "logoff")
            { //logoff()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "setAccountPassword")
            { //setAccountPassword(arg1:password)
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "setAccountUsername")
            { //setAccountUsername(arg1:username)
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "sendToComputer")
            { //sendToComputer()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            else if (funct == "switch_ServerStatus")
            { //switch_ServerStatus()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
            }
            break;

        case 'g': //GET FUNCTIONS
            ss >> funct;
            if (funct == "getAccountlist")
            { //DISPLAY THE LIST OF ACCOUNTS
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
            else if (funct == "getAccountName")
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[0]; //DISPLAY THE SELECTED ACCOUNT NAME
            }
            else if (funct == "getAccountUsername")
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[1]; //DISPLAY THE SELECTED ACCOUNT USERNAME
            }
            else if (funct == "getAccountPassword")
            {
                this->menu_lines[num] += this->model->get_account(this->selected_account)[2]; //DISPLAY THE SELECTED ACCOUNT PASSWORD
            }
            else if (funct == "getServerStatus")
            {
                if (this->model->is_webserver_on())
                {
                    this->menu_lines[num] += " ON"; //DISPLAY WEB SERVER STATUS
                }
                else
                {
                    this->menu_lines[num] += " OFF"; //DISPLAY WEB SERVER STATUS
                }
            }
            break;
        }
    }
}

void Controller::scroll(int a)
{
    if (a == 1)
    { //SCROLL UP
        if (this->cursor_position != this->buffer[0])
        { //THE CURSOR IS NOT AT THE TOP OF THE BUFFER
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position);
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE BUFFER (from 1 to 3)
            bool has_found = false;                                        //HAS FOUND AN INPUT ABOVE THE CURSOR ACTUAL POSITION ?
            for (int i = index_of_cursor - 1; i >= 0; i--)
            {
                if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true)
                {
                    this->cursor_position = this->buffer[i]; //INPUT FOUND ABOVE (CASE 1)
                    has_found = true;
                    break;
                }
            }
            if (has_found == false && this->buffer[0] != 0)
            { //NO INPUT FOUND ABOVE (CASE 2)
                this->cursor_position = this->buffer[0] - 1;
                for (int i = 0; i < this->buffer.size(); i++)
                { //UPDATE THE BUFFER
                    this->buffer[i]--;
                }
            }
        }
        else
        { //THE CURSOR IS AT THE TOP OF THE BUFFER (CASE 3)
            if (this->cursor_position != 0)
            {
                this->cursor_position--;
                for (int i = 0; i < this->buffer.size(); i++)
                { //UPDATE THE BUFFER
                    this->buffer[i]--;
                }
            }
        }
    }
    else
    { //SCROLL DOWN
        if (this->cursor_position != this->buffer[this->buffer.size() - 1])
        { //THE CURSOR IS NOT AT THE BOTTOM OF THE BUFFER
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position);
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE BUFFER (from 0 to 2)
            bool has_found = false;                                        //HAS FOUND AN INPUT BELOW THE CURSOR ACTUAL POSITION ?
            for (int i = index_of_cursor + 1; i < this->buffer.size(); i++)
            {
                if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true)
                {
                    this->cursor_position = this->buffer[i]; //INPUT FOUND BELOW (CASE 1)
                    has_found = true;
                    break;
                }
            }
            if (has_found == false && this->buffer[this->buffer.size() - 1] != this->menu_lines.size() - 1)
            { //NO INPUT FOUND BELOW (CASE 2)
                this->cursor_position = this->buffer[this->buffer.size() - 1] + 1;
                for (int i = 0; i < this->buffer.size(); i++)
                { //UPDATE THE BUFFER
                    this->buffer[i]++;
                }
            }
        }
        else
        { //THE CURSOR IS AT THE BOTTOM OF THE BUFFER (CASE 3)
            if (this->cursor_position != this->menu_lines.size() - 1)
            {
                this->cursor_position++;
                for (int i = 0; i < this->buffer.size(); i++)
                { //UPDATE THE BUFFER
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
    for (int i = 0; i < this->buffer.size(); i++)
    {
        if (this->buffer[i] == this->cursor_position)
        {
            if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true)
            {
                this->view->draw_text("->" + this->menu_lines[this->buffer[i]], i); //CURSOR ON AN INPUT
            }
            else
            {
                this->view->draw_text(this->menu_lines[this->buffer[i]], i); //CURSOR NOT ON AN INPUT
            }
        }
        else
        {
            this->view->draw_text(this->menu_lines[this->buffer[i]], i); //CURSOR NOT HERE
        }
    }
    this->view->show();
}

void Controller::select_choice()
{
    for (int i = 0; i < this->buffer.size(); i++)
    {
        if (this->buffer[i] == this->cursor_position)
        {
            if (std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true)
            { //CURSOR ON AN INPUT

                bool is_valid = false;
                std::vector<int>::iterator it = std::find(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->cursor_position);
                int index_of_cursor = std::distance(this->line_number_of_choices.begin(), it); //INDEX OF THE CURSOR IN THE VECTOR OF CHOICES

                std::string funct = this->inputs_function[index_of_cursor][0];

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
                if (is_valid == true && this->inputs_link[index_of_cursor] != "None")
                {
                    this->current_menu = this->inputs_link[index_of_cursor];
                    this->load_menu(this->inputs_link[index_of_cursor]);
                    this->init_buffer();
                }
                break;
            }
        }
    }
}

void Controller::go_back()
{
    std::vector<std::string>::iterator it = std::find(filenames.begin(), filenames.end(), this->current_menu);
    int index_of_filename = std::distance(filenames.begin(), it); //INDEX OF THE MENU IN THE FILENAMES (from 0 to 12)

    this->current_menu = filenames[previous_menu[index_of_filename]];
    this->load_menu(filenames[previous_menu[index_of_filename]]);
    this->init_buffer();
}

std::string Controller::write(std::string str)
{
    int keyboard_cursor = 0;
    std::vector<char> word;
    std::vector<int> word_display;

    if (str.size() == 0)
    {
        word_display.push_back(0);
        word.push_back(this->keyboard->Alphabet[0]);
    }
    else
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (i < NUM_COL - 2) //NUMBER OF COLUMN - THE SIZE OF THE MENU CURSOR
            {
                word_display.push_back(i);
            }
            word.push_back(str[i]);
        }
    }

    bool has_finished = false;
    bool new_char = false;
    int input;

    this->menu_lines[this->cursor_position] = this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char);
    this->update_display();

    while (has_finished == false)
    {
        if (this->inputs->has_input() == true)
        {
            input = this->inputs->get_input();

            if (input != -1 && input != -2)
            {

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
                    has_finished = true;
                    break;

                case Direction::BACK:
                    this->keyboard->del(&keyboard_cursor, &word_display, &word);
                    break;
                }
                this->menu_lines[this->cursor_position] = this->keyboard->get_display(&keyboard_cursor, &word_display, &word, &new_char);
                this->update_display();

                Serial.print("CURSOR: ");
                Serial.println(keyboard_cursor);
                Serial.print("WORD: ");
                for (int s = 0; s < word.size(); s++)
                {
                    Serial.print(word[s]);
                    Serial.print("-");
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

    std::string ret = "";
    for (int i = 0; i < word.size(); i++)
    {
        ret += word[i];
    }
    this->menu_lines[this->cursor_position] = ret;
    this->update_display();
    return ret;
}

void Controller::update()
{
    if (this->inputs->has_input())
    {
        int input = this->inputs->get_input();
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