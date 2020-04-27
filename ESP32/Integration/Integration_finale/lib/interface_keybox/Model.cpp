#include "Model.h"

Model::Model(Wallet *wallet) {
  this->wallet = wallet;
  this->my_webserver = new https_server_keybox(wallet);
  this->is_hotspot = false;
}

std::vector<std::string> Model::read(fs::FS &fs, std::string filename,
                                     std::string type, std::string lang) {
  std::vector<std::string> ret;
  std::string file_str;

  // CHECK THE TYPE OF FILE ("txt" for the content OR "struct" for the
  // structure)
  if (type == "struct") {
    filename = "/" + filename + "." + type;
  } else if (type == "txt") {
    filename = "/" + lang + "/" + filename + "." + type;
  } else {
    return ret;
  }

  // CONVERT THE STRING TO A CONST CHAR*
  char tmp[filename.size() + 1];
  std::copy(filename.begin(), filename.end(), tmp);
  tmp[filename.size()] = '\0';

  const char *path = tmp;

  // OPEN THE FILE
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    file.close();
    Serial.print("ERR: FAILED TO OPEN ");
    Serial.println(path);
    return ret;
  }

  while (file.available())  // GET THE FILE CONTENT
  {
    file_str += char(file.read());
  }

  // CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  while (std::getline(ss, line)) {
    ret.push_back(line);
  }
  file.close();
  return ret;
}

std::vector<std::string> Model::get_accounts() {
  std::vector<std::string> ret;
  for (int i = 0; i < this->locker.size();
       i++)  // GET THE NAME OF ALL ACCOUNTS IN THE LOCKER
  {
    ret.push_back(this->locker[i][0]);
  }
  return ret;
}

std::vector<std::string> Model::get_account(int account_index) {
  return this->locker[account_index];
}

bool Model::add_account(std::string name, std::string user, std::string pwd) {
  if (this->wallet->addAccount(name, user, pwd) ==
      true)  // ADD AN ACCOUNT TO THE LIST
  {
    std::vector<std::string> vec = {name, user, pwd};
    this->locker.push_back(vec);
    return true;
  } else {
    return false;
  }
}

bool Model::modify_account_password(int account_index, std::string password) {
  if (this->wallet->changePwd(account_index, password) ==
      true)  // MODIFY THE PASSWORD OF AN ACCOUNT
  {
    this->locker[account_index][2] = password;
    return true;
  } else {
    return false;
  }
}

bool Model::modify_account_username(int account_index, std::string user) {
  if (this->wallet->changeUsername(account_index, user) ==
      true)  // MODIFY THE USERNAME OF AN ACCOUNT
  {
    this->locker[account_index][1] = user;
    return true;
  } else {
    return false;
  }
}

void Model::delete_account(int account_index) {
  // ERASE THE ACCOUNT FROM THE LIST
  this->wallet->delAccount(account_index);
  this->locker.erase(this->locker.begin() + account_index);
}

bool Model::is_webserver_on() {
  if (this->current_server.size() == 3)  // CHECK THE WEB SERVER INFORMATIONS
  {
    return true;
  } else {
    return false;
  }
}

bool Model::login(std::string password) {
  if (this->wallet->unlock(password) == true)  // LOG IN
  {
    this->locker = this->wallet->getAccounts();  // GET THE ACCOUNT LIST
    return true;
  } else {
    return false;
  }
}

std::vector<std::string> Model::get_config(fs::FS &fs) {
  std::vector<std::string> ret;
  std::string file_str;

  // OPEN THE FILE confif.txt
  File file = fs.open("/config.txt");
  if (!file || file.isDirectory()) {
    file.close();
    Serial.println("ERR: FAILED TO OPEN config.txt");
    return ret;
  }

  // GET THE CONTENT OF THE CONFIG FILE
  while (file.available()) {
    file_str += char(file.read());
  }

  // CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  while (std::getline(ss, line)) {
    ret.push_back(line);
  }
  return ret;
}

void Model::set_config(fs::FS &fs, std::string txt) {
  // CONVERT THE STRING TO A CONST CHAR*
  char tmp[txt.size() + 1];
  std::copy(txt.begin(), txt.end(), tmp);
  tmp[txt.size()] = '\0';

  const char *str = tmp;

  // WRITE ON THE CONFIG FILE
  File file = fs.open("/config.txt", FILE_WRITE);
  if (!file) {
    file.close();
    Serial.println("ERR: FAILED TO OPEN config.txt");
  } else {
    if (!file.print(str)) {
      Serial.println("ERR: COULD NOT WRITE ON config.txt");
    }
    file.close();
  }
}

std::string Model::getSSID(int index) {
  return this->wifi_list[index];  // WIFI SSID
}

std::vector<std::string> Model::getWifis() {
  this->wifi_list.clear();
  std::vector<String> lw = this->my_wifi.list_wifi();
  for (String w : lw) {
    this->wifi_list.push_back(w.c_str());
  }
  return this->wifi_list;
}

bool Model::connect_wifi(int index, std::string password) {
  if (this->my_wifi.connect_wifi(this->wifi_list[index].c_str(),
                                 password.c_str())) {
    this->current_server.push_back(this->wifi_list[index]);
    this->current_server.push_back(password);
    this->current_server.push_back(this->my_wifi.get_ip().toString().c_str());
    this->is_hotspot = false;
    xTaskCreatePinnedToCore(my_webserver->serverTask, "https443", 4096,
                            my_webserver, 2, &this->Server_task,
                            ARDUINO_RUNNING_CORE);
    return true;
  }
  return false;
}

bool Model::emit_wifi() {
  String connect = this->my_wifi.enable_AP();
  this->is_hotspot = true;
  std::stringstream ss(connect.c_str());
  std::string tmp;
  for (size_t i = 0; i < 3; i++) {
    ss >> tmp;
    this->current_server.push_back(tmp);
  }
  // We pass:
  // serverTask - the function that should be run as separate task
  // "https443" - a name for the task (mainly used for logging)
  // 4096       - stack size in byte. If you want up to four clients, you should
  //              not go below 6kB. If your stack is too small, you will
  //              encounter Panic and stack canary exceptions, usually during
  //              the call to SSL_accept.
  // Priority of 2 for faster response time
  xTaskCreatePinnedToCore(my_webserver->serverTask, "https443", 4096,
                          my_webserver, 2, &this->Server_task,
                          ARDUINO_RUNNING_CORE);
  return true;
}

void Model::turn_wifi_Off() {
  this->wallet->saveWallet();
  ESP.restart();
  // vTaskDelete(this->Server_task); //PB
}

std::vector<std::string> Model::getCurrentWifi() {
  return this->current_server;
}

void Model::logout() {
  // LOCK THE ACCOUNT
  this->wallet->saveWallet();
  ESP.restart();
}

void Model::send_ids(int index) {
  // TODO
}

void Model::save_Wifi_Key(fs::FS &fs, int index, std::string pwd) {
  std::string SSID = this->wifi_list[index];
  std::vector<std::string> Wifis_SSID;
  std::string file_str;

  // OPEN THE FILE wifi_keys.txt
  File file = fs.open("/wifi_keys.txt");
  if (!file || file.isDirectory()) {
    file.close();
    Serial.println("ERR: FAILED TO OPEN wifi_keys.txt");
  }

  // GET THE CONTENT OF THE CONFIG FILE
  while (file.available()) {
    file_str += char(file.read());
  }
  file.close();

  // CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  int i = 0;
  while (std::getline(ss, line)) {
    if (i % 2 == 0) {
      Wifis_SSID.push_back(line);
    }
  }

  if (std::binary_search(Wifis_SSID.begin(), Wifis_SSID.end(), SSID) ==
      false)  // SSID NOT FOUND IN THE LIST
  {
    std::string added = SSID + "\n" + pwd + "\n";
    file_str += added;
    char tmp[file_str.size() + 1];
    std::copy(file_str.begin(), file_str.end(), tmp);
    tmp[file_str.size()] = '\0';

    const char *str = tmp;

    // WRITE ON THE WIFI FILE
    File file = fs.open("/wifi_keys.txt", FILE_WRITE);
    if (!file) {
      file.close();
      Serial.println("ERR: FAILED TO OPEN wifi_keys.txt");
    } else {
      if (!file.print(str)) {
        Serial.println("ERR: COULD NOT WRITE ON wifi_keys.txt");
      }
      file.close();
    }
  }
}

std::string Model::get_Wifi_Key(fs::FS &fs, int index) {
  std::string SSID = this->wifi_list[index];
  std::vector<std::string> Wifis_SSID;
  std::vector<std::string> Wifis_Key;
  std::string file_str;

  // OPEN THE FILE wifi_keys.txt
  File file = fs.open("/wifi_keys.txt");
  if (!file || file.isDirectory()) {
    file.close();
    Serial.println("ERR: FAILED TO OPEN wifi_keys.txt");
  }

  // GET THE CONTENT OF THE wifi_keys.txt file
  while (file.available()) {
    file_str += char(file.read());
  }
  file.close();

  // CONVERT THE CONTENT TO AN ARRAY OF STRING
  std::stringstream ss(file_str);
  std::string line;
  int i = 0;
  while (std::getline(ss, line)) {
    if (i % 2 == 0) {
      Wifis_SSID.push_back(line);
    } else {
      Wifis_Key.push_back(line);
    }
  }

  std::string ret = "";
  if (std::binary_search(Wifis_SSID.begin(), Wifis_SSID.end(), SSID) ==
      true)  // SSID NOT FOUND IN THE LIST
  {
    for (int i = 0; i < Wifis_SSID.size(); i++) {
      if (SSID == Wifis_SSID[i]) {
        ret = Wifis_Key[i];
        break;
      }
    }
  }

  return ret;
}