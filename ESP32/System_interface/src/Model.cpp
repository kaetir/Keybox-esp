#include "Model.h"

Model::Model(){
    this->path_to_folder = "LANG/FR/";
}

std::vector<std::string> Model::read(std::string filename){
    std::vector <std::string> ret;
    std::string line;

    std::ifstream file(this->path_to_folder+filename+".txt");
    if(file){
        while(getline(file,line)){
            ret.push_back(line);
        }
    }
    return ret;
}