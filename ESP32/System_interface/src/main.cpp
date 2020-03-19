#include <Arduino.h>
#include "Menu.h"

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
  menu->update();
}