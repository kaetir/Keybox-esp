#include "Controller.h"

int Controller::get_input(){
    touch_1_val = touchRead(TOUCH_1);
    touch_2_val = touchRead(TOUCH_2);
    touch_3_val = touchRead(TOUCH_3);
    touch_4_val = touchRead(TOUCH_4);
    touch_ok_val = touchRead(TOUCH_OK);
    touch_back_val = touchRead(TOUCH_BACK);

    if(touch_1_val > THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return -1; //No input detected
    }
    //Loop to wait for the user to release the buttons
    while(touchRead(TOUCH_1) < THRESHOLD_VAL || touchRead(TOUCH_2) < THRESHOLD_VAL || touchRead(TOUCH_3) < THRESHOLD_VAL || touchRead(TOUCH_4) < THRESHOLD_VAL || touchRead(TOUCH_OK) < THRESHOLD_VAL || touchRead(TOUCH_BACK) < THRESHOLD_VAL){
        delay(100);
    }
    //Input detected:
    if(touch_1_val < THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return 1; //Input 1 detected
    
    }else if(touch_2_val < THRESHOLD_VAL && touch_1_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return 2; //Input 2 detected
    
    }else if(touch_3_val < THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_1_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return 3; //Input 3 detected
    
    }else if(touch_4_val < THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_1_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return 4; //Input 4 detected
    
    }else if(touch_ok_val < THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_1_val > THRESHOLD_VAL && touch_back_val > THRESHOLD_VAL){
        return 5; //Input ok detected
    
    }else if(touch_back_val < THRESHOLD_VAL && touch_2_val > THRESHOLD_VAL && touch_3_val > THRESHOLD_VAL && touch_4_val > THRESHOLD_VAL && touch_ok_val > THRESHOLD_VAL && touch_1_val > THRESHOLD_VAL){
        return 6; //Input back detected

    }else{
        return 0; //Multiple inputs detected

    }
}