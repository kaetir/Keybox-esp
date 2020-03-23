#include <Arduino.h>

#define TOUCH_9 32
#define TOUCH_8 33
#define TOUCH_7 27
#define TOUCH_6 14
#define TOUCH_5 12
#define TOUCH_4 13

#define TOUCH_3 15
#define TOUCH_2 2
#define TOUCH_0 4

void setup() {
  Serial.begin(9600);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop() {
  Serial.println(touchRead(T4));  // can be replaced with TOUCH_9 value
  delay(500);
}