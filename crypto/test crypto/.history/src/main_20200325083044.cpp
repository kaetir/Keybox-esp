#include <Arduino.h>
#include <RandomPwdGenerator.h>
#include <iostream>


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  string test;
  test = generate(10);
  std::cout << test << "\n";