#include <Arduino.h>
#include "RandomPwdGenerator.h"
#include "Wallet.h"
#include "PwdCypher.h"
#include <iostream>
#include <string>
using namespace std;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.print("Ok");
    std::string username = "Fire";
    std::string pwd = "azertymaqsde";
}

void loop()
{
    /*
    // put your main code here, to run repeatedly:

    std::string username = "Fire";
    std::string pwd = "azertymaqsde";
    Serial.println(10, BIN);
    Wallet wallet;
    wallet.createWallet(username, pwd);
    Serial1.print(wallet.checkValid(pwd));
    Serial.println(10, HEX);
    vTaskDelay(500000000);*/
}