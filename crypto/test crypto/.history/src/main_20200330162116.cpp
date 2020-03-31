#include <Arduino.h>
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
#include <iostream>
#include <string>
using namespace std;
int n = 0;
char key[] = "concombre";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(1);
  setup_hash();
  vTaskDelay(500);
  Serial.print(2);
  setup_AES();
  vTaskDelay(500);
}