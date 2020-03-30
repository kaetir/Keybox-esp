#include "ArduinoJson.h"
#include <string>

bool gen_new_file(char * filename, char * username, char * main_password_hash, char * key, unsigned char * outputBuffer){
    Serial.println("Parsing start: ");
    String test = " {\"mainuser\": \"" + *username;
    test += "\", \"checkpwd\": \"concombre\"} ";
    
    int n = test.length();

    char cstr[n + 1];
    strncpy(cstr, test.c_str(), n+1); 
    char JSONMessage[] = cstr; //Original message
 
    StaticJsonDocument<200> doc;                         //Memory pool
    auto error = deserializeJson(doc, JSONMessage); //Parse message
 
    if (error) {   //Check for errors in parsing
 
        Serial.println("Parsing failed");
        delay(5000);
        return;
 
    }
 
    const char * sensorType = doc["SensorType"]; //Get sensor type value
    int value = doc["Value"];                    //Get value of sensor measurement
 
    Serial.print("mainuser: ");
    Serial.println(sensorType);
    Serial.print("checkpwd: ");
    Serial.println(value);
 
    Serial.println();
  delay(5000);
    jload = {"mainuser": username,
                     "mainkeys": [{
                         "mainkey": mainkey[0],
                         "nonce": mainkey[1]
                     }],
                     "checkpasswd": {
                         "check": concombre[0],
                         "nonce": concombre[1]
                     },
                     "entries": []}
}

