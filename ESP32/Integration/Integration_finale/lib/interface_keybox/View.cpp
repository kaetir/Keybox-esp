#include "View.h"

View::View() {
  this->screen = new Screen();
  this->clear_buffer();
}

View::~View() { delete &this->screen; }

void View::clear() { this->screen->clear(); }

void View::show() {
  for (int i = 0; i < NUM_LINE; i++) {
    std::string tmp;
    for (int j = 0; j < NUM_COL;
         j++) {  // PUT EVERY CHARACTER OF A LINE ON A SINGLE STRING
      tmp.push_back(buffer[i][j]);
    }
    this->screen->setLine(tmp,
                          i);  // DISPLAY THE CONTENT OF THE BUFFER LINE BY LINE
  }
  this->screen->show();
}

void View::draw_text(std::string txt, int line, int col) {
  if (line >= 0 && line < NUM_LINE && col >= 0 && col < NUM_COL) {
    for (int i = col; i < txt.length() + col; i++) {
      if (i < NUM_COL) {                 // OVERFLOW SECURITY
        buffer[line][i] = txt[i - col];  // DRAW A STRING CHARACTER BY CHARACTER
                                         // AT THE COORDINATES (line, col)
      } else {
        break;
      }
    }
  }
}

void View::draw_char(char a, int line, int col) {
  if (line >= 0 && line < NUM_LINE && col >= 0 && col < NUM_COL) {
    this->buffer[line][col] =
        a;  // DRAW A CHARACTER AT THE COORDINATES (line, col)
  }
}

void View::clear_buffer() {
  for (int i = 0; i < NUM_LINE; i++) {
    for (int j = 0; j < NUM_COL; j++) {
      buffer[i][j] = ' ';  // GO THROUGH ALL LINES AND CLEAR EACH CHARACTER
    }
  }
}