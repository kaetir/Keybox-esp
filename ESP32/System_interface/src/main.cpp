#include <Arduino.h>
#include "Interface.h"
#define TOUCH_1 27
#define TOUCH_2 14
#define TOUCH_3 12
#define TOUCH_4 13
#define TOUCH_OK 32
#define TOUCH_BACK 33

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
  
  if(touchRead(TOUCH_1) < 50 || touchRead(TOUCH_2) < 50 || touchRead(TOUCH_3) < 50  || touchRead(TOUCH_4) < 50 || touchRead(TOUCH_OK) < 50 || touchRead(TOUCH_BACK) < 50 ){


  }
}