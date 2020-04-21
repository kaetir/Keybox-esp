#include <Arduino.h>
#include "ArduinoJson.h"
#include "FS.h"
#include "SPIFFS.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include "SPIFFS.h"

std::string getJson(fs::FS& fs)
{
    std::string file_str;
    //OPEN THE FILE
    File file = fs.open("/wallet.json");
    if (!file || file.isDirectory()) {
        file.close();
        Serial.print("ERR: FAILED TO OPEN ");
        return file_str;
    }

    while (file.available()) //GET THE FILE CONTENT
    {
        file_str += char(file.read());
    }
    return file_str;
}

void setJson(fs::FS& fs, char* txt)
{
    //CONVERT THE STRING TO A CONST CHAR*

    //WRITE ON THE CONFIG FILE
    File file = fs.open("/wallet.json", FILE_WRITE);
    if (!file) {
        file.close();
        Serial.println("ERR: FAILED TO OPEN wallet.json");
    } else {
        if (!file.print(txt)) {
            Serial.println("ERR: COULD NOT WRITE ON wallet.json");
        }
        file.close();
    }
}

std::string HexDec2String(int hexIn)
{
    char hexString[4 * sizeof(int) + 1];
    // returns decimal value of hex
    sprintf(hexString, "%i", hexIn);
    return std::string(hexString);
}

void setup()
{
    // Initialize serial port
    Serial.begin(9600);
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
    } else {
        StaticJsonDocument<200> doc;

        std::string str = getJson(SPIFFS);
        Serial.println(str.c_str());

        char json[str.size() + 1];
        std::copy(str.begin(), str.end(), json);
        json[str.size()] = '\0';

        // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, json);

        // Test if parsing succeeds.
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
        }

        const char* master = doc["Master"];
        int size = doc["Size"];

        // Print values.
        Serial.println(master);
        Serial.println(size);

        std::vector<std::vector<std::string>> mon_coffre;

        for (int i = 0; i < size; i++) {
            const char* name = doc["Accounts"][i]["Name"];
            const char* username = doc["Accounts"][i]["Username"];
            const char* password = doc["Accounts"][i]["Password"];

            std::vector<std::string> tmp;
            tmp.push_back(std::string(name));
            tmp.push_back(std::string(username));
            tmp.push_back(std::string(password));

            mon_coffre.push_back(tmp);
        }

        for (int i = 0; i < mon_coffre.size(); i++) {
            Serial.println(mon_coffre[i][0].c_str());
            Serial.println(mon_coffre[i][1].c_str());
            Serial.println(mon_coffre[i][2].c_str());
        }
        DynamicJsonDocument doc2(1024);
        std::string Fire = "Fire";
        doc2["Master"] = Fire.c_str();
        doc2["Hash"] = "azerty";
        doc2["Accounts"][0]["Name"] = "laposte";
        doc2["Accounts"][0]["Username"] = "loupio";
        doc2["Accounts"][0]["Password"] = "1234azerty";
        doc2["Size"] = 1;
        char output[1024];
        serializeJson(doc2, output, 1024);
        setJson(SPIFFS, output);
        std::string hex = "71F7E519849F6B33A9D3B8537EEEFB8D188449FD376ED7F10EBB37A8F28CF6";
        std::string rc(16, '0');
        char s[] = "71F7E519";

        int x = strtoul(s, NULL, 16);
        Serial.println(x);
        std::string test = HexDec2String(x);
        Serial.println(test.c_str());
    }
}
void loop()
{
    // not used in this example
}