#include <Arduino.h>
#include <RandomPwdGenerator.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  string test;
  test = generate(10);
  printf(test);
}