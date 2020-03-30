#include <Arduino.h>
#include "RandomPwdGenerator.h"
#include "PwdCypher.h"
#include <iostream>
#include <string>
using namespace std;
int n = 0;
string key = "concombre";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char test[] ="abcd";
  char[] *a = &test;
  pwd_crypt(*test, &key, &a);
  printf("%s\n",test.c_str());
}