#include <Arduino.h>
#include <RandomPwdGenerator.h>
#include <iostream>
#include <string>
using namespace std;


void setup() {
  // put your setup code here, to run once:
  string test("");
  test = generate(10);
  std::cout << test << "\n";
}

void loop() {
  // put your main code here, to run repeatedly:
}