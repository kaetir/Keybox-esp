#include "Model.h"

Model::Model()
{
}

std::vector<std::string> Model::read(fs::FS &fs, std::string filename, std::string type, std::string lang)
{
  std::vector<std::string> ret;
  std::string file_str;

  //CHECK THE TYPE OF FILE ("txt" for the content OR "struct" for the structure)
  if (type == "struct")
  {
    filename = "/" + filename + "." + type;
  }
  else if (type == "txt")
  {
    filename = "/" + lang + "/" + filename + "." + type;
  }
  else
  {
    return ret;
  }

  //CONVERT THE STRING TO A CONST CHAR*
  char tmp[filename.size() + 1];
  std::copy(filename.begin(), filename.end(), tmp);
  tmp[filename.size()] = '\0';

  const char *path = tmp;

  //OPEN THE FILE
  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    file.close();
    Serial.print("ERR: FAILED TO OPEN ");
    Serial.println(path);
    return ret;
  }

  while (file.available()) //GET THE FILE CONTENT
  {
    file_str += char(file.read());
  }

  //CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  while (std::getline(ss, line))
  {
    ret.push_back(line);
  }
  file.close();
  return ret;
}

std::vector<std::string> Model::get_accounts()
{
  std::vector<std::string> ret;
  for (int i = 0; i < this->locker.size(); i++) //GET THE NAME OF ALL ACCOUNTS IN THE LOCKER
  {
    ret.push_back(this->locker[i][0]);
  }
  return ret;
}

std::vector<std::string> Model::get_account(int account_index)
{
  return this->locker[account_index];
}

bool Model::add_account(std::string name, std::string user, std::string pwd)
{
  //TODO
  return false;
}

bool Model::modify_account_password(int account_index, std::string password)
{
  //TODO
  return false;
}

bool Model::modify_account_username(int account_index, std::string user)
{
  //TODO
  return false;
}

void Model::delete_account(int account_index)
{
  //TODO
}

bool Model::is_webserver_on()
{
  if (this->current_server.size() == 3)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Model::login(std::string user, std::string password)
{
  //TODO
  return false;
}

std::vector<std::string> Model::get_config(fs::FS &fs)
{
  std::vector<std::string> ret;
  std::string file_str;

  //OPEN THE FILE confif.txt
  File file = fs.open("/config.txt");
  if (!file || file.isDirectory())
  {
    file.close();
    Serial.println("ERR: FAILED TO OPEN config.txt");
    return ret;
  }

  //GET THE CONTENT OF THE CONFIG FILE
  while (file.available())
  {
    file_str += char(file.read());
  }

  //CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  while (std::getline(ss, line))
  {
    ret.push_back(line);
  }
  return ret;
}

void Model::set_config(fs::FS &fs, std::string txt)
{
  //CONVERT THE STRING TO A CONST CHAR*
  char tmp[txt.size() + 1];
  std::copy(txt.begin(), txt.end(), tmp);
  tmp[txt.size()] = '\0';

  const char *str = tmp;

  //WRITE ON THE CONFIG FILE
  File file = fs.open("/config.txt", FILE_WRITE);
  if (!file)
  {
    file.close();
    Serial.println("ERR: FAILED TO OPEN config.txt");
  }
  else
  {
    if (!file.print(str))
    {
      Serial.println("ERR: COULD NOT WRITE ON config.txt");
    }
    file.close();
  }
}

std::string Model::getSSID(int index)
{
  return this->wifi_list[index][0]; //WIFI SSID
}

std::vector<std::string> Model::getWifis()
{
  std::vector<std::string> ret;

  for (int i = 0; i < this->wifi_list.size(); i++) //GET THE SSID OF EVERY WIFI AVAILABLE
  {
    ret.push_back(this->wifi_list[i][0]);
  }
  return ret;
}

bool Model::connect_wifi(int index, std::string password)
{
  //TODO
  return false;
}

bool Model::emit_wifi()
{
  //TODO
  return false;
}

bool Model::turn_wifi_Off()
{
  //TODO
  return false;
}

std::vector<std::string> Model::getCurrentWifi()
{
  return this->current_server;
}

bool Model::logout()
{
  //TODO
  return false;
}

void Model::send_ids(int index)
{
  //TODO
}