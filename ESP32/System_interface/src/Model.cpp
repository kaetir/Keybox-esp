#include "Model.h"

Model::Model(){
    this->lang_folder = "/FR";
}

std::vector<std::string> Model::read(fs::FS &fs, std::string filename, std::string type){
  std::vector<std::string> ret;
  std::string file_str;

  filename = "/"+filename+"."+type;
  char tmp[filename.size()+1];
  std::copy(filename.begin(), filename.end(), tmp);
  tmp[filename.size()] = '\0';

  const char *path = tmp;

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("failed to open file for reading");
    return ret;
  }

  while(file.available()){
    file_str += char(file.read());
  }

  std::stringstream ss(file_str);
  std::string line;
  while(std::getline(ss,line)){
    ret.push_back(line);
  }
  return ret;
}

std::vector<std::string> Model::get_accounts(){
  std::vector<std::string> ret;
  return ret;
}

std::vector<std::string> Model::get_account(int account_index){
  std::vector<std::string> ret;
  return ret;
}

bool Model::is_webserver_on(){
    return false;
}