#include "Model.h"

Model::Model(){
    this->lang_folder = "/FR";
}

std::vector<std::string> Model::read(std::string filename){
    std::vector <std::string> ret;
    std::string line;

    std::ifstream file(MENU_LANG_FOLDER+this->lang_folder+"/"+filename+".txt");
    if(file){
        while(getline(file,line)){
            ret.push_back(line);
        }
    }
    return ret;
}