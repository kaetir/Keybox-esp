#include "Controller.h"

#define BUTTON_LEFT 33
#define BUTTON_RIGHT 32
#define BUTTON_TOP 27
#define BUTTON_BOTTOM 14
#define BUTTON_OK 12
#define BUTTON_BACK 13
#define THRESHOLD_VAL 10

std::string filenames[] = {"Welcome_menu", "Login", "Main_menu", "Web_server", "Accounts_menu", 
"Add_account", "Account_selection", "Display_account", "Delete_account", "Send_to_computer", 
"Modify_account", "New_password", "New_username"};

Controller::Controller(){
    this->view = new View();
    this->model = new Model();

    if(!this->spf.begin(true)){
        Serial.println("SPIFFS Mount Failed");
    }
    this->load_menu(filenames[0]);
    this->init_buffer();
}

Controller::~Controller(){
    delete this->view;
}

void Controller::init_buffer(){
    this->view->clear();
    this->view->clear_buffer();
    for(int i = 0; i < menu_lines.size();i++){ //FILL THE BUFFER WITH THE MENU LINES
        if(i < NUM_LINE){
            this->view->draw_text(menu_lines[i],i,0);
            this->buffer.push_back(i);
        }else{
            break;
        }
    }
    this->cursor_position = 0;
    this->view->show(); //DISPLAY THE BUFFER
}

void Controller::load_menu(std::string menu_name){
    this->line_number_of_choices.clear(); //Clear the choices position
    this->inputs_function.clear(); //Clear the choices function (and arguments)
    this->inputs_link.clear(); //Clear the choices link
    this->input_fields.clear(); //Clear the input fields

    this->menu_lines = this->model->read(this->spf, menu_name, "txt"); //Fill the menu_lines with the new menu
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

    for(int i = 0; i < this->menu_lines.size(); i++){
        std::istringstream ss(struct_tmp[i]);
        ss >> num >> type;

        switch (type){
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
            tmp_vect = {"InputField", "None"};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("None");
            this->input_fields[name] = "";
            break;

        case 'f': //ACTIVATE A FUNCTION BEFORE SWITCHING MENU
            this->line_number_of_choices.push_back(num);
            ss >> menu >> funct;
            this->inputs_link.push_back(menu);

            if(funct == "add_account"){ //add_account(arg1:name, arg2:username, arg3:password)
                ss >> arg1 >> arg2 >> arg3;
                tmp_vect = {funct, arg1, arg2, arg3};
                this->inputs_function.push_back(tmp_vect);

            }else if(funct == "deleteAccount"){ //deleteAccount()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);

            }else if(funct == "login"){ //login(arg1:user, arg2:password)
                ss >> arg1 >> arg2;
                tmp_vect = {funct, arg1, arg2};
                this->inputs_function.push_back(tmp_vect);
                
            }else if(funct == "logoff"){ //logoff()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
                
            }else if(funct == "setAccountPassword"){ //setAccountPassword(arg1:password)
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
                
            }else if(funct == "setAccountUsername"){ //setAccountUsername(arg1:username)
                ss >> arg1;
                tmp_vect = {funct, arg1};
                this->inputs_function.push_back(tmp_vect);
                
            }else if(funct == "sendToComputer"){ //sendToComputer()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);
                
            }else if(funct == "switch_ServerStatus"){ //switch_ServerStatus()
                tmp_vect = {funct};
                this->inputs_function.push_back(tmp_vect);   
            }
            break;

        case 'g': //GET FUNCTIONS
            ss >> funct;
            if(funct == "getAccountlist"){ //DISPLAY THE LIST OF ACCOUNTS
                std::vector<std::string> account_list = this->model->get_accounts();

                this->menu_lines[num] = account_list[0];
                this->line_number_of_choices.push_back(num);
                
                tmp_vect = {"selectAccount", std::string(0)};
                this->inputs_function.push_back(tmp_vect);
                this->inputs_link.push_back("Display_account");

                for(int j = 1; j < account_list.size(); j++){
                    this->menu_lines.push_back(account_list[j]);
                    this->line_number_of_choices.push_back(menu_lines.size()-1);

                    std::stringstream int_to_string;
                    int_to_string << j;

                    tmp_vect = {"selectAccount", int_to_string.str()};
                    this->inputs_function.push_back(tmp_vect);
                    this->inputs_link.push_back("Display_account");
                }

            }else if(funct == "getAccountName"){
                this->menu_lines[num] += this->model->get_account(this->selected_account)[0]; //DISPLAY THE SELECTED ACCOUNT NAME

            }else if(funct == "getAccountUsername"){
                this->menu_lines[num] += this->model->get_account(this->selected_account)[1]; //DISPLAY THE SELECTED ACCOUNT USERNAME

            }else if(funct == "getAccountPassword"){
                this->menu_lines[num] += this->model->get_account(this->selected_account)[2]; //DISPLAY THE SELECTED ACCOUNT PASSWORD

            }else if(funct == "getServerStatus"){
                if(this->model->is_webserver_on()){
                    this->menu_lines[num] += " ON"; //DISPLAY WEB SERVER STATUS
                }else{
                    this->menu_lines[num] += " OFF"; //DISPLAY WEB SERVER STATUS
                }
            }
            break;
        }
    }
}

void Controller::scroll(int a){
    if(a == 1){ //SCROLL UP
        if(this->cursor_position != this->buffer[0]){ //THE CURSOR IS NOT AT THE TOP OF THE BUFFER
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position); 
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE BUFFER (from 1 to 3)
            bool has_found = false; //HAS FOUND AN INPUT ABOVE THE CURSOR ACTUAL POSITION ?
            for(int i = index_of_cursor-1; i >= 0; i--){
                if(std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true){
                    this->cursor_position = this->buffer[i]; //INPUT FOUND ABOVE (CASE 1)
                    has_found = true;
                    break;
                }
            }
            if(has_found == false && this->buffer[0] != 0){ //NO INPUT FOUND ABOVE (CASE 2)
                this->cursor_position = this->buffer[0]-1;
                for(int i = 0; i < this->buffer.size(); i++){ //UPDATE THE BUFFER
                    this->buffer[i] --;
                }
            }
        }else{ //THE CURSOR IS AT THE TOP OF THE BUFFER (CASE 3)
            if(this->cursor_position != 0){
                this->cursor_position --;
                for(int i = 0; i < this->buffer.size(); i++){ //UPDATE THE BUFFER
                    this->buffer[i] --;
                }
            }
        }

    }else{ //SCROLL DOWN
        if(this->cursor_position != this->buffer[this->buffer.size()-1]){ //THE CURSOR IS NOT AT THE BOTTOM OF THE BUFFER
            std::vector<int>::iterator it = std::find(this->buffer.begin(), this->buffer.end(), this->cursor_position); 
            int index_of_cursor = std::distance(this->buffer.begin(), it); //INDEX OF THE CURSOR IN THE BUFFER (from 0 to 2)
            bool has_found = false; //HAS FOUND AN INPUT BELOW THE CURSOR ACTUAL POSITION ?
            for(int i = index_of_cursor+1; i < this->buffer.size(); i++){
                if(std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true){
                    this->cursor_position = this->buffer[i]; //INPUT FOUND BELOW (CASE 1)
                    has_found = true;
                    break;
                }
            }
            if(has_found == false && this->buffer[this->buffer.size()-1] != this->menu_lines.size()-1){ //NO INPUT FOUND BELOW (CASE 2)
                this->cursor_position = this->buffer[this->buffer.size()-1]+1;
                for(int i = 0; i < this->buffer.size(); i++){ //UPDATE THE BUFFER
                    this->buffer[i] ++;
                }
            }
        }else{ //THE CURSOR IS AT THE BOTTOM OF THE BUFFER (CASE 3)
            if(this->cursor_position != this->menu_lines.size()-1){
                this->cursor_position ++;
                for(int i = 0; i < this->buffer.size(); i++){ //UPDATE THE BUFFER
                    this->buffer[i] ++;
                }
            }
        }
    }
}

int Controller::get_input(){
    int button_left_val, button_right_val, button_top_val, button_bottom_val, button_ok_val, button_back_val;
    button_left_val = touchRead(BUTTON_LEFT);
    button_right_val = touchRead(BUTTON_RIGHT);
    button_top_val = touchRead(BUTTON_TOP);
    button_bottom_val = touchRead(BUTTON_BOTTOM);
    button_ok_val = touchRead(BUTTON_OK);
    button_back_val = touchRead(BUTTON_BACK);

    if(button_left_val > THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return -1; //No input detected
    }
    //Loop to wait for the user to release the buttons
    while(touchRead(BUTTON_LEFT) < THRESHOLD_VAL || touchRead(BUTTON_RIGHT) < THRESHOLD_VAL || touchRead(BUTTON_TOP) < THRESHOLD_VAL || touchRead(BUTTON_BOTTOM) < THRESHOLD_VAL || touchRead(BUTTON_OK) < THRESHOLD_VAL || touchRead(BUTTON_BACK) < THRESHOLD_VAL){
        delay(100);
    }
    //Input detected:
    if(button_left_val < THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return 1; //Input 1 detected
    
    }else if(button_right_val < THRESHOLD_VAL && button_left_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return 2; //Input 2 detected
    
    }else if(button_top_val < THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_left_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return 3; //Input 3 detected
    
    }else if(button_bottom_val < THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_left_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return 4; //Input 4 detected
    
    }else if(button_ok_val < THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_left_val > THRESHOLD_VAL && button_back_val > THRESHOLD_VAL){
        return 5; //Input ok detected
    
    }else if(button_back_val < THRESHOLD_VAL && button_right_val > THRESHOLD_VAL && button_top_val > THRESHOLD_VAL && button_bottom_val > THRESHOLD_VAL && button_ok_val > THRESHOLD_VAL && button_left_val > THRESHOLD_VAL){
        return 6; //Input back detected

    }else{
        return 0; //Multiple inputs detected

    }
}

bool Controller::has_input(){
    int button_left_val, button_right_val, button_top_val, button_bottom_val, button_ok_val, button_back_val;
    button_left_val = touchRead(BUTTON_LEFT);
    button_right_val = touchRead(BUTTON_RIGHT);
    button_top_val = touchRead(BUTTON_TOP);
    button_bottom_val = touchRead(BUTTON_BOTTOM);
    button_ok_val = touchRead(BUTTON_OK);
    button_back_val = touchRead(BUTTON_BACK);

    if(button_left_val < THRESHOLD_VAL || button_right_val < THRESHOLD_VAL || button_top_val < THRESHOLD_VAL || button_bottom_val < THRESHOLD_VAL || button_ok_val < THRESHOLD_VAL || button_back_val < THRESHOLD_VAL){
        return true; //input detected
    }else{
        return false; //No input detected
    }
}

void Controller::update_display(){
    this->view->clear_buffer();
    this->view->clear();

    for(int i=0; i < this->buffer.size();i++){
        if(this->buffer[i] == this->cursor_position){
            if(std::binary_search(this->line_number_of_choices.begin(), this->line_number_of_choices.end(), this->buffer[i]) == true){
                this->view->draw_text("->"+this->menu_lines[this->buffer[i]],i); //CURSOR ON AN INPUT
            }else{
                this->view->draw_text(this->menu_lines[this->buffer[i]],i); //CURSOR NOT ON AN INPUT
            }
        }else{
            this->view->draw_text(this->menu_lines[this->buffer[i]],i); //CURSOR NOT HERE
        }
    }
    this->view->show();
}

void Controller::update(){
    if(this->has_input()){
        int input = this->get_input();
        if(input != -1 && input != 0){

            switch (input){
            case 3: //TOP
                this->scroll(1);
                Serial.println("TOP");
                Serial.println("CURSOR:");
                Serial.println(this->cursor_position);
                this->update_display();
                break;

            case 4: //BOTTOM
                this->scroll(-1);
                Serial.println("BOTTOM");
                Serial.println("CURSOR:");
                Serial.println(this->cursor_position);
                this->update_display();
                break;

            case 5: //OK
                break;

            
            case 6: //BACK
                break;

            }
        }
    }
}