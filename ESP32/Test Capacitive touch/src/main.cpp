#include <Arduino.h>
#include "Controller.h"

#define TOUCH_9 32
#define TOUCH_8 33
#define TOUCH_7 27
#define TOUCH_6 14
#define TOUCH_5 12
#define TOUCH_4 13

#define TOUCH_3 15
#define TOUCH_2 2
#define TOUCH_0 4

Controller *controller;

void setup() {
  Serial.begin(9600);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  controller = new Controller;
}

void loop() {
  //Serial.println(touchRead(TOUCH_9));
  if(controller->has_input() == true){
    switch (controller->get_input()){
    case 1:
      Serial.println("LEFT");
      break;

    case 2:
      Serial.println("RIGHT");
      break;

    case 3:
      Serial.println("TOP");
      break;

    case 4:
      Serial.println("BOTTOM");
      break;

    case 5:
      Serial.println("OK");
      break;

    case 6:
      Serial.println("BACK");
      break;

    case 0:
      Serial.println("MULTIPLE INPUT");
      break;
    }
  }
  delay(50);
}