#include <Arduino.h>
#include <RandomPwdGenerator.h>
#include <iostream>
#include <string>
using namespace std;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  string test("");
  test = random_string(10);
  printf("%s\n",test.c_str());;
}