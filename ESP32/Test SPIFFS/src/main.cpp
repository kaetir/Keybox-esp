
#include "SPIFFS_tools.h"

void setup() {
  Serial.begin(115200);
  if (!start_spiffs()) {
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
    }
  }

  /* listDir(SPIFFS, "/", 0);
  writeFile(SPIFFS, "/hello.txt", "Hello ");
  appendFile(SPIFFS, "/hello.txt", "World!\r\n");
  readFile(SPIFFS, "/hello.txt");
  renameFile(SPIFFS, "/hello.txt", "/foo.txt");
  readFile(SPIFFS, "/foo.txt");
  deleteFile(SPIFFS, "/foo.txt");
  testFileIO(SPIFFS, "/test.txt");
  deleteFile(SPIFFS, "/test.txt");
  Serial.println("Test complete"); */
}

void loop() {}