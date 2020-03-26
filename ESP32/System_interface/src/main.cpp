#include "Controller.h"

Controller *controller;

//DESCRIPTION: initialize the serial communications
//PARAMS: none
//RETURN VALUE: none
void setup() {
  Serial.begin(9600);
  controller = new Controller();
}

//DESCRIPTION: main loop to update the interface
//PARAMS: none
//RETURN VALUE: none
void loop() {
  controller->update();
  delay(50);
}