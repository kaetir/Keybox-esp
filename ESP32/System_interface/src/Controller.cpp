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

    this->cursor_postion = 0; //INITIALIZE THE CURSOR OF THE USER ON THE FIRST CHOICE
    this->line_number_of_choices.push_back(2); //ADDING THE "LOG IN" CHOICE NUMBER OF LINE
    //TODO CALL model->read()
    //TODO INITIALIZE menu_lines

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