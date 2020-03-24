#include "View.h"

View::View(){
    this->display = Adafruit_SSD1306(128, 32, &Wire);

    if(!this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    this->display.display();
    delay(2000);
    this->display.clearDisplay();
    this->display.display();

    this->display.setTextSize(1);
    this->display.setTextColor(SSD1306_WHITE);

    for(int i=0; i < NUM_LINE; i++){
        for(int j=0; j < NUM_COL; j++){
            buffer[i][j] = ' ';
        }
    }
}

View::~View(){
    delete &this->display;
}

void View::clear(){
    this->display.clearDisplay();
    this->display.setCursor(0,0);
    this->display.display();
}

void View::show(){
    for(int i=0; i < NUM_LINE; i++){
        this->display.setCursor(0,i*8);
        std::string tmp;
        for(int j=0; j < NUM_COL; j++){
            tmp.push_back(buffer[i][j]);
        }
        this->display.println(tmp.c_str());
    }
    this->display.display();
}

void View::draw_text(std::string txt, int line, int col){
    if(line >= 0 && line < NUM_LINE && col >= 0 && col < NUM_COL){
        for(int i=col; i < txt.length()+col; i++){
            if(i < NUM_COL){
                buffer[line][i] = txt[i-col];
            }else{
                break;
            }
        }
    }
}

void View::draw_char(char a, int line, int col){
    if(line >= 0 && line < NUM_LINE && col >= 0 && col < NUM_COL){
        this->buffer[line][col] = a;
    }
}

void View::clear_buffer(){
    for(int i=0; i < NUM_LINE; i++){
        for(int j=0; j < NUM_COL; j++){
            buffer[i][j] = ' ';
        }
    }
}