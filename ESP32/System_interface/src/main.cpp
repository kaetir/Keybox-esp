#include <Arduino.h>
#include "Menu.h"
#define TOUCH_1 27
#define TOUCH_2 14
#define TOUCH_3 12
#define TOUCH_4 13
#define TOUCH_OK 32
#define TOUCH_BACK 33

int touch_1_val;
int touch_2_val;
int touch_3_val;
int touch_4_val;
int touch_ok_val;
int touch_back_val;

Menu *menu = new Menu();

//DESCRIPTION: initialize the serial communications
//PARAMS: none
//RETURN VALUE: none
void setup() {
  Serial.begin(115200);
}

//DESCRIPTION: main loop to update the interface
//PARAMS: none
//RETURN VALUE: none
void loop() {
  touch_1_val = touchRead(TOUCH_1);
  touch_2_val = touchRead(TOUCH_2);
  touch_3_val = touchRead(TOUCH_3);
  touch_4_val = touchRead(TOUCH_4);
  touch_ok_val = touchRead(TOUCH_OK);
  touch_back_val = touchRead(TOUCH_BACK);
  
  if(touch_1_val < 50 || touch_2_val < 50 || touch_3_val < 50 || touch_4_val < 50 || touch_ok_val < 50 || touch_back_val < 50){
    menu->update();
  }
}