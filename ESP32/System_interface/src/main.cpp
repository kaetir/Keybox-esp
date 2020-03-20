#include <Arduino.h>
#include "Controller.h"

Controller *controller = new Controller();

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
  controller->update();
}