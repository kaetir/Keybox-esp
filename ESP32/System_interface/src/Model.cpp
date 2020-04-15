#include "Model.h"

Model::Model()
{
  this->lang_folder = "/FR";
}

std::vector<std::string> Model::read(fs::FS &fs, std::string filename, std::string type, std::string lang)
{
  std::vector<std::string> ret;
  std::string file_str;

  if (type == "struct")
  {
    filename = "/" + filename + "." + type;
  }
  else
  {
    filename = "/" + lang + "/" + filename + "." + type;
  }
  char tmp[filename.size() + 1];
  std::copy(filename.begin(), filename.end(), tmp);
  tmp[filename.size()] = '\0';

  const char *path = tmp;

  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    file.close();
    Serial.print("ERR: FAILED TO OPEN ");
    Serial.println(path);
    return ret;
  }

  while (file.available())
  {
    file_str += char(file.read());
  }

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
  return ret;
}

std::vector<std::string> Model::get_account(int account_index)
{
  std::vector<std::string> ret;
  return ret;
}

bool Model::is_webserver_on()
{
  return false;
}

std::vector<std::string> Model::get_config(fs::FS &fs)
{
  std::vector<std::string> ret;
  std::string file_str;

  File file = fs.open("/config.txt");
  if (!file || file.isDirectory())
  {
    file.close();
    Serial.println("ERR: FAILED TO OPEN config.txt");
    return ret;
  }

  while (file.available())
  {
    file_str += char(file.read());
  }

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
  char tmp[txt.size() + 1];
  std::copy(txt.begin(), txt.end(), tmp);
  tmp[txt.size()] = '\0';

  const char *str = tmp;

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
  std::string ret;
  return ret;
}

std::vector<std::string> Model::getWifis()
{
  std::vector<std::string> ret;
  return ret;
}

bool Model::connect_wifi(int index, std::string password)
{
  return false;
}