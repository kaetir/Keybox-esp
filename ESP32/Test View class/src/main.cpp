#include "SPIFFS.h"
#include "View.h"

View *view;

std::string a = "Hello";
std::string b = "world";
std::string c = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char d = 'T';
char e = 'E';
char f = 'S';

void setup()
{
  Serial.begin(115200);
  view = new View();
  view->clear();
}

void loop()
{
  //TEST THE TEXT PRINTING ON THE FIRST LINE
  view->draw_text(a);

  //TEST THE PRINTING OF A CHARACTER AT THE END OF THE FIRST LINE
  view->draw_char(d, 0, 20);

  //TEST THE PRINTING OF 2 WORDS ON THE SAME LINE
  view->draw_text(a, 1, 0);
  view->draw_text(b, 1, 6);

  //TEST THE PRINTING OF 4 CHARACTERS ON THE SAME LINE
  view->draw_char(d, 2, 0);
  view->draw_char(e, 2, 2);
  view->draw_char(f, 2, 4);
  view->draw_char(d, 2, 6);

  //TEST THE SIZE OVERFLOW SECURITY OF A LINE
  view->draw_text(c, 3, 0);

  //TEST THE DISPLAY OF THE BUFFER
  view->show();
  delay(5000);

  //TEST THE CLEARING OF BOTH THE SCREEN AND THE BUFFER
  view->clear_buffer();
  view->clear();
  view->show();

  delay(3000);
}