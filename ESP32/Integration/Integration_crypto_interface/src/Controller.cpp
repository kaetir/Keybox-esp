#include "Controller.h"

// UNCOMMENT THIS TO ACTIVATE THE DEBUG MODE
//#define DEBUG_MODE

// MENU FILE NAMES
std::vector<std::string> filenames = {
    "Welcome_menu",       // 0
    "Login",              // 1
    "Main_menu",          // 2
    "Web_server",         // 3
    "Accounts_menu",      // 4
    "Add_account",        // 5
    "Account_selection",  // 6
    "Display_account",    // 7
    "Delete_account",     // 8
    "Send_to_computer",   // 9
    "Modify_account",     // 10
    "New_password",       // 11
    "New_username",       // 12
    "Lang_option",        // 13
    "Wifi_list",          // 14
    "Wifi_connect"        // 15
};

// PREVIOUS MENU INDEX
int previous_menu[] = {
    0,   // Welcome_menu
    0,   // Login
    2,   // Main_menu
    2,   // Web_server
    2,   // Accounts_menu
    4,   // Add_account
    4,   // Account_selection
    6,   // Display_account
    7,   // Delete_account
    7,   // Send_to_computer
    7,   // Modify_account
    10,  // New_password
    10,  // New_username
    2,   // Lang_option
    3,   // Wifi_list
    14   // Wifi_connect
};

std::vector<std::string> Lang = {
    "FR"  // FRENCH
};

Controller::Controller() {
  // INITIALIZING THE NEW OBJECTS
  Wallet *wallet = new Wallet();
  this->view = new View();
  this->model = new Model(wallet);
  this->inputs = new Inputs();
  this->keyboard = new Keyboard();

  if (wallet->isJson(SPIFFS) == false)  // JSON NOT YET CREATED
  {
    this->isWalletCreated = false;
  } else  // JSON CREATED
  {
    this->isWalletCreated = true;
  }

  std::vector<std::string> conf = this->model->get_config(SPIFFS);
  if (conf.size() == 0 ||
      this->isWalletCreated == false)  // FIRST BOOT DETECTED
  {
    this->first_boot = true;
    this->menu_lines.push_back("LANGUAGE:");

    std::vector<std::string> tmp_vect;
    for (int i = 0; i < Lang.size(); i++) {
      this->menu_lines.push_back(Lang[i]);
      this->line_number_of_choices.push_back(this->menu_lines.size() - 1);

      tmp_vect = {"First_boot", Lang[i]};
      this->inputs_function.push_back(tmp_vect);

      if (this->isWalletCreated == true)  // LINK TO THE WELCOME MENU
      {
        this->inputs_link.push_back(filenames[0]);
      } else  // LINK TO THE WIFI MENU
      {
        this->inputs_link.push_back("Wifi_informations");
      }
    }
    this->current_menu = "First_Boot";
  } else {
    this->language = conf[0];

    // LOADING THE WELCOME MENU
    this->first_boot = false;
    this->load_menu(filenames[0]);
    this->current_menu = filenames[0];
#ifdef DEBUG_MODE
    Serial.println("");
#endif
  }
  this->init_buffer();  // INITIALIZING THE BUFFER OF THE MENU
}

Controller::~Controller() {
  // CLEARING OF THE CONTROLLER
  delete this->view;
  delete this->model;
  delete this->inputs;
  delete this->keyboard;
}

void Controller::init_buffer() {
  // CLEARING OF THE THE BUFFER OF THE MENU AND OF THE DISPLAY
  this->buffer.clear();
  this->view->clear();
  this->view->clear_buffer();

  // FILLING THE BUFFER WITH THE MENU LINES
  for (int i = 0; i < menu_lines.size(); i++) {
    if (i < NUM_LINE) {
      if (i == 0 && this->line_number_of_choices[0] == 0) {
        this->view->draw_text("->" + this->menu_lines[i], i, 0);
      } else {
        this->view->draw_text(this->menu_lines[i], i, 0);
      }
      this->buffer.push_back(i);
    } else {
      break;
    }
  }
  this->cursor_position = 0;

  // DISPLAY THE BUFFER OF THE MENU
  this->view->show();
}

void Controller::load_menu(std::string menu_name) {
  // CLEARING OF THE MENU ENTRIES
  this->line_number_of_choices.clear();

  // CLEARING OF THE ACTIVATIONS FUNCTION OF EACH MENU ENTRY
  this->inputs_function.clear();

  // CLEARING OF THE MENU LINKS OF EACH MENU ENTRY
  this->inputs_link.clear();

  // CLEARING OF THE INPUT FIELDS
  this->input_fields.clear();

  // FILLING THE MENU LINES WITH THE NEW ONES
  this->menu_lines =
      this->model->read(SPIFFS, menu_name, "txt", this->language);

  // GETTING THE MENU STRUCTURE
  std::vector<std::string> struct_tmp =
      this->model->read(SPIFFS, menu_name, "struct", this->language);
  std::vector<std::string> tmp_vect;

  int num;
  char type;
  std::string funct;
  std::string menu;
  std::string name;
  std::string arg1;
  std::string arg2;
  std::string arg3;

  // SETTING UP THE STRUCTURE FOR EACH MENU LINE
  for (int i = 0; i < struct_tmp.size(); i++) {
    std::istringstream ss(struct_tmp[i]);
    ss >> num >> type;

    if (num == this->menu_lines.size())  // SECURITY FOR NEW LINES
    {
      this->menu_lines.push_back("");
    }

    switch (type) {
      case '>':  // LINK TO ANOTHER MENU
        ss >> menu;
        this->line_number_of_choices.push_back(num);
        tmp_vect = {"None"};
        this->inputs_function.push_back(tmp_vect);
        this->inputs_link.push_back(menu);
        break;

      case '<':  // INPUT FIELD
        ss >> name;
        this->line_number_of_choices.push_back(num);
        tmp_vect = {"InputField", name};
        this->inputs_function.push_back(tmp_vect);
        this->inputs_link.push_back("None");
        this->input_fields[name] = "";
        break;

      case 'f':  // ACTIVATE A FUNCTION BEFORE SWITCHING MENU
        this->line_number_of_choices.push_back(num);
        ss >> menu >> funct;
        this->inputs_link.push_back(menu);

        if (funct == "add_account")  // add_account(arg1:name, arg2:username,
                                     // arg3:password)
        {
          ss >> arg1 >> arg2 >> arg3;
          tmp_vect = {funct, arg1, arg2, arg3};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "deleteAccount")  // deleteAccount()
        {
          tmp_vect = {funct};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "login")  // login(arg1:user, arg2:password)
        {
          ss >> arg1 >> arg2;
          tmp_vect = {funct, arg1, arg2};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "logoff")  // logoff()
        {
          tmp_vect = {funct};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct ==
                   "setAccountPassword")  // setAccountPassword(arg1:password)
        {
          ss >> arg1;
          tmp_vect = {funct, arg1};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct ==
                   "setAccountUsername")  // setAccountUsername(arg1:username)
        {
          ss >> arg1;
          tmp_vect = {funct, arg1};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "sendToComputer")  // sendToComputer()
        {
          tmp_vect = {funct};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "set_Lang") {
          ss >> arg1;
          tmp_vect = {funct, arg1};
          this->inputs_function.push_back(tmp_vect);
        } else if (funct == "connect") {
          ss >> arg1;
          tmp_vect = {funct, arg1};
          this->inputs_function.push_back(tmp_vect);
        }
        break;

      case 'g':  // GET FUNCTIONS
        ss >> funct;
        if (funct == "getAccountlist")  // DISPLAY THE LIST OF ACCOUNTS
        {
          std::vector<std::string> account_list = this->model->get_accounts();

          for (int j = 0; j < account_list.size(); j++) {
            this->menu_lines.push_back(account_list[j]);
            this->line_number_of_choices.push_back(menu_lines.size() - 1);

            std::stringstream int_to_string;
            int_to_string << j;

            tmp_vect = {"selectAccount", int_to_string.str()};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("Display_account");
          }
        } else if (funct ==
                   "get_Wifi_list")  // DISPLAY THE LIST OF WIFI AVAILABLE
        {
          std::vector<std::string> wifi_list = this->model->getWifis();

          for (int j = 0; j < wifi_list.size(); j++) {
            this->menu_lines.push_back(wifi_list[j]);
            this->line_number_of_choices.push_back(menu_lines.size() - 1);

            std::stringstream int_to_string;
            int_to_string << j;

            tmp_vect = {"selectWifi", int_to_string.str()};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("Wifi_connect");
          }
        } else if (funct ==
                   "get_Wifi_SSID")  // Get the SSID of the selected Wifi
        {
          this->menu_lines[num] = this->model->getSSID(this->selected_wifi);
        } else if (funct ==
                   "getAccountName")  // DISPLAY THE SELECTED ACCOUNT NAME
        {
          this->menu_lines[num] +=
              this->model->get_account(this->selected_account)[0];
        } else if (funct == "getAccountUsername")  // DISPLAY THE SELECTED
                                                   // ACCOUNT USERNAME
        {
          this->menu_lines[num] +=
              this->model->get_account(this->selected_account)[1];
        } else if (funct == "getAccountPassword")  // DISPLAY THE SELECTED
                                                   // ACCOUNT PASSWORD
        {
          this->menu_lines[num] +=
              this->model->get_account(this->selected_account)[2];
        } else if (funct == "getServerIP") {
          this->menu_lines[num] = this->model->getCurrentWifi()[2];
        } else if (funct == "getWifiName") {
          this->menu_lines[num] = this->model->getCurrentWifi()[0];
        } else if (funct == "getWifiPassword") {
          this->menu_lines[num] = this->model->getCurrentWifi()[1];
        } else if (funct == "getServerStatus")  // DISPLAY WEB SERVER STATUS
        {
          if (this->model->is_webserver_on()) {
            this->menu_lines.push_back("IP");
            this->menu_lines.push_back(this->model->getCurrentWifi()[2]);
            this->menu_lines.push_back("Wifi:");
            this->menu_lines.push_back(this->model->getCurrentWifi()[0]);
            this->menu_lines.push_back("pass:");
            this->menu_lines.push_back(this->model->getCurrentWifi()[1]);
            this->menu_lines.push_back("OFF");
            this->line_number_of_choices.push_back(this->menu_lines.size() - 1);
            this->inputs_link.push_back("Web_server");
            tmp_vect = {"turn_off"};
            this->inputs_function.push_back(tmp_vect);
          } else {
            // SEARCH A WIFI ENTRY
            this->menu_lines.push_back("Wifi List");
            this->line_number_of_choices.push_back(this->menu_lines.size() - 1);
            tmp_vect = {"None"};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("Wifi_list");

            // EMIT WIFI ENTRY
            this->menu_lines.push_back("Wifi Hotspot");
            this->line_number_of_choices.push_back(this->menu_lines.size() - 1);
            tmp_vect = {"hotspot"};
            this->inputs_function.push_back(tmp_vect);
            this->inputs_link.push_back("Web_server");
          }
        }
        break;
    }
  }
#ifdef DEBUG_MODE
  Serial.print("[MENU_LINES]: [");
  Serial.print(0);
  for (int i = 1; i < this->menu_lines.size(); i++) {
    Serial.print(", ");
    Serial.print(i);
  }
  Serial.println("]");

  Serial.print("[MENU_ENTRIES]: [");
  Serial.print(this->line_number_of_choices[0]);
  for (int i = 1; i < this->line_number_of_choices.size(); i++) {
    Serial.print(", ");
    Serial.print(this->line_number_of_choices[i]);
  }
  Serial.println("]");

  Serial.print("[ENTRIES_LINK]: [");
  Serial.print(this->inputs_link[0].c_str());
  for (int i = 1; i < this->inputs_link.size(); i++) {
    Serial.print(", ");
    Serial.print(this->inputs_link[i].c_str());
  }
  Serial.println("]");

  Serial.print("[ENTRIES_FUNCTION]: [");
  Serial.print(this->inputs_function[0][0].c_str());
  for (int i = 1; i < this->inputs_function.size(); i++) {
    Serial.print(", ");
    Serial.print(this->inputs_function[i][0].c_str());
  }
  Serial.println("]");
#endif
}

void Controller::scroll(int a) {
  if (a == 1)  // SCROLLING UP
  {
#ifdef DEBUG_MODE
    Serial.println("SCROLL UP");
#endif
    if (this->cursor_position !=
        this->buffer[0])  // THE CURSOR IS NOT AT THE TOP OF THE MENU BUFFER
    {
      std::vector<int>::iterator it = std::find(
          this->buffer.begin(), this->buffer.end(), this->cursor_position);
      int index_of_cursor = std::distance(
          this->buffer.begin(),
          it);  // INDEX OF THE CURSOR IN THE MENU BUFFER (from 1 to 3)
      bool has_found =
          false;  // HAS FOUND AN ENTRY ABOVE THE CURSOR ACTUAL POSITION ?
      for (int i = index_of_cursor - 1; i >= 0; i--) {
        if (std::binary_search(this->line_number_of_choices.begin(),
                               this->line_number_of_choices.end(),
                               this->buffer[i]) ==
            true)  // ENTRY FOUND ABOVE THE CURSOR (CASE 1)
        {
          this->cursor_position = this->buffer[i];
          has_found = true;
          break;
        }
      }
      if (has_found == false &&
          this->buffer[0] != 0)  // NO ENTRY FOUND ABOVE THE CURSOR (CASE 2)
      {
        this->cursor_position = this->buffer[0] - 1;
        for (int i = 0; i < this->buffer.size();
             i++)  // MOVE THE MENU BUFFER UP
        {
          this->buffer[i]--;
        }
      }
    } else  // THE CURSOR IS AT THE TOP OF THE BUFFER (CASE 3)
    {
      if (this->cursor_position != 0) {
        this->cursor_position--;
        for (int i = 0; i < this->buffer.size();
             i++)  // MOVE THE MENU BUFFER UP
        {
          this->buffer[i]--;
        }
      }
    }
  } else  // SCROLLING DOWN
  {
#ifdef DEBUG_MODE
    Serial.println("SCROLL DOWN");
#endif
    if (this->cursor_position !=
        this->buffer[this->buffer.size() -
                     1])  // THE CURSOR IS NOT AT THE BOTTOM OF THE BUFFER
    {
      std::vector<int>::iterator it = std::find(
          this->buffer.begin(), this->buffer.end(), this->cursor_position);
      int index_of_cursor = std::distance(
          this->buffer.begin(),
          it);  // INDEX OF THE CURSOR IN THE MENU BUFFER (from 0 to 2)
      bool has_found =
          false;  // HAS FOUND AN ENTRY BELOW THE CURSOR ACTUAL POSITION ?
      for (int i = index_of_cursor + 1; i < this->buffer.size(); i++) {
        if (std::binary_search(this->line_number_of_choices.begin(),
                               this->line_number_of_choices.end(),
                               this->buffer[i]) ==
            true)  // ENTRY FOUND BELOW THE CURSOR (CASE 1)
        {
          this->cursor_position = this->buffer[i];
          has_found = true;
          break;
        }
      }
      if (has_found == false &&
          this->buffer[this->buffer.size() - 1] !=
              this->menu_lines.size() -
                  1)  // NO ENTRY FOUND BELOW THE CURSOR (CASE 2)
      {
        this->cursor_position = this->buffer[this->buffer.size() - 1] + 1;
        for (int i = 0; i < this->buffer.size();
             i++)  // MOVE THE MENU BUFFER DOWN
        {
          this->buffer[i]++;
        }
      }
    } else {
      if (this->cursor_position !=
          this->menu_lines.size() -
              1)  // THE CURSOR IS AT THE BOTTOM OF THE MENU BUFFER (CASE 3)
      {
        this->cursor_position++;
        for (int i = 0; i < this->buffer.size();
             i++)  // MOVE THE MENU BUFFER DOWN
        {
          this->buffer[i]++;
        }
      }
    }
  }
#ifdef DEBUG_MODE
  Serial.print("MENU BUFFER: -");
  for (int i = 0; i < this->buffer.size(); i++) {
    Serial.print(i);
    Serial.print("-");
  }
  Serial.println("");
#endif
}

void Controller::update_display() {
  this->view->clear_buffer();
  this->view->clear();

  // DISPLAY EACH LINE OF THE MENU BUFFER
  for (int i = 0; i < this->buffer.size(); i++) {
    if (this->buffer[i] == this->cursor_position) {
      if (std::binary_search(this->line_number_of_choices.begin(),
                             this->line_number_of_choices.end(),
                             this->buffer[i]) ==
          true)  // THE CURSOR IS ON AN ENTRY
      {
        this->view->draw_text("->" + this->menu_lines[this->buffer[i]], i);
      } else  // THE CURSOR IS NOT ON AN ENTRY (ON A TEXT LINE)
      {
        this->view->draw_text(this->menu_lines[this->buffer[i]], i);
      }
    } else {
      this->view->draw_text(this->menu_lines[this->buffer[i]],
                            i);  // THE CURSOR IS NOT ON THIS LINE
    }
  }
  this->view->show();
}

void Controller::select_choice() {
  for (int i = 0; i < this->buffer.size(); i++) {
    if (this->buffer[i] ==
        this->cursor_position)  // CURSOR POSITION FOUND IN THE MENU BUFFER
    {
      if (std::binary_search(this->line_number_of_choices.begin(),
                             this->line_number_of_choices.end(),
                             this->buffer[i]) ==
          true)  // THE CURSOR IS ON AN ENTRY
      {
#ifdef DEBUG_MODE
        Serial.println("THE CURSOR IS ON AN ENTRY");
#endif

        bool is_valid =
            false;  // SUCCESSFUL EXECUTION OF THE ACTIVATION FUNCTIONS ?
        std::vector<int>::iterator it = std::find(
            this->line_number_of_choices.begin(),
            this->line_number_of_choices.end(), this->cursor_position);
        int index_of_cursor =
            std::distance(this->line_number_of_choices.begin(),
                          it);  // INDEX OF THE CURSOR IN THE VECTOR OF ENTRIES

        std::string funct =
            this->inputs_function[index_of_cursor]
                                 [0];  // ACTIVATION FUNCTION OF THE ENTRY (IT
                                       // CAN BE "None")

#ifdef DEBUG_MODE
        Serial.print("[ENTRY_FUNCTION]: ");
        Serial.println(funct.c_str());
#endif

        if (funct == "None") {
          is_valid = true;
        } else if (funct == "InputField")  // INPUT FIELDS
        {
#ifdef DEBUG_MODE
          Serial.print("[INPUT_FIELD]: ");
          Serial.println((this->inputs_function[index_of_cursor][1]).c_str());
#endif
          this->input_fields[this->inputs_function[index_of_cursor][1]] =
              this->write(
                  this->input_fields[this->inputs_function[index_of_cursor]
                                                          [1]]);
          is_valid = true;
        } else if (funct ==
                   "selectAccount")  // SELECT AN ACCOUNT IN THE ACCOUNT LIST
        {
          std::istringstream(this->inputs_function[index_of_cursor][1]) >>
              this->selected_account;
          is_valid = true;
        } else if (funct == "add_account")  // ADD AN ACCOUNT
        {
          std::string name =
              this->input_fields[this->inputs_function[index_of_cursor][1]];
          std::string username =
              this->input_fields[this->inputs_function[index_of_cursor][2]];
          std::string password =
              this->input_fields[this->inputs_function[index_of_cursor][3]];

          if (this->model->add_account(name, username, password)) {
            is_valid = true;
          }
        } else if (funct == "deleteAccount")  // DELETE AN ACCOUNT
        {
          this->model->delete_account(this->selected_account);
          is_valid = true;
        } else if (funct == "login")  // TRY TO LOG IN
        {
          std::string user =
              this->input_fields[this->inputs_function[index_of_cursor][1]];
          std::string password =
              this->input_fields[this->inputs_function[index_of_cursor][2]];

          if (this->model->login(user, password)) {
            is_valid = true;
          }
        } else if (funct == "logoff")  // TRY TO LOG OUT
        {
          if (this->model->logout()) {
            is_valid = true;
          }
        } else if (funct == "setAccountPassword")  // SET A NEW PASSWORD
        {
          std::string password =
              this->input_fields[this->inputs_function[index_of_cursor][1]];

          if (this->model->modify_account_password(this->selected_account,
                                                   password)) {
            is_valid = true;
          }
        } else if (funct == "setAccountUsername")  // SET A NEW USERNAME
        {
          std::string username =
              this->input_fields[this->inputs_function[index_of_cursor][1]];

          if (this->model->modify_account_username(this->selected_account,
                                                   username)) {
            is_valid = true;
          }
        } else if (funct == "sendToComputer")  // SEND THE IDS TO THE COMPUTER
        {
          this->model->send_ids(this->selected_account);
          is_valid = true;
        } else if (funct == "First_boot")  // SET THE LANGUAGE AT THE FIRST BOOT
        {
          if (this->isWalletCreated == false) {
            this->model->emit_wifi();
          } else {
            this->first_boot = false;
          }
          this->language = this->inputs_function[index_of_cursor][1];
          this->model->set_config(SPIFFS, this->language);

          is_valid = true;
        } else if (funct == "set_Lang")  // SET A LANGUAGE
        {
          this->language = this->inputs_function[index_of_cursor][1];
          this->model->set_config(SPIFFS, this->language);

          is_valid = true;
        } else if (funct == "connect")  // TRY TO CONNECT TO A WIFI
        {
          if (this->model->connect_wifi(
                  this->selected_wifi,
                  this->input_fields[this->inputs_function[index_of_cursor]
                                                          [1]]) == true) {
            is_valid = true;
          }
        } else if (funct == "selectWifi")  // SELECT A WIFI IN THE LIST
        {
          std::istringstream(this->inputs_function[index_of_cursor][1]) >>
              this->selected_wifi;
          is_valid = true;
        } else if (funct == "turn_off")  // TURN WIFI AND SERVER OFF
        {
          if (this->model->turn_wifi_Off()) {
            is_valid = true;
          }
        } else if (funct == "hotspot")  // SET AS A WIFI HOTSPOT
        {
          if (this->model->emit_wifi()) {
            is_valid = true;
          }
        }
        if (is_valid == true && this->inputs_link[index_of_cursor] !=
                                    "None")  // LOADING THE NEW MENU
        {
#ifdef DEBUG_MODE
          Serial.println("ENTRY FUNCTION VALIDATED");
          Serial.print("[CURRENT_MENU]: ");
          Serial.println(this->current_menu.c_str());
          Serial.print("[NEW_MENU]: ");
          Serial.println(this->inputs_link[index_of_cursor].c_str());
#endif
          this->current_menu = this->inputs_link[index_of_cursor];
          this->load_menu(this->inputs_link[index_of_cursor]);
          this->init_buffer();
        }
        break;
      } else {
#ifdef DEBUG_MODE
        Serial.println("THE CURSOR IS NOT ON AN ENTRY");
#endif
      }
    }
  }
}

void Controller::go_back() {
  std::vector<std::string>::iterator it =
      std::find(filenames.begin(), filenames.end(), this->current_menu);
  int index_of_filename =
      std::distance(filenames.begin(),
                    it);  // INDEX OF THE MENU IN THE FILENAMES (from 0 to 12)

#ifdef DEBUG_MODE
  Serial.print("[CURRENT_MENU]: ");
  Serial.println(this->current_menu.c_str());
  Serial.print("[NEW_MENU]: ");
  Serial.println(filenames[previous_menu[index_of_filename]].c_str());
#endif

  this->current_menu = filenames[previous_menu[index_of_filename]];
  this->load_menu(
      filenames[previous_menu[index_of_filename]]);  // LOAD THE LAST MENU
  this->init_buffer();
}

std::string Controller::write(std::string str) {
  // CURSOR OF THE INPUT FIELD (ON A CHARACTER)
  int keyboard_cursor = 0;

  // WORD OF THE INPUT FIELD
  std::vector<char> word;

  // BUFFER OF THE WORD
  std::vector<int> word_display;

  if (str.size() == 0)  // THE INPUT FIELD IS EMPTY
  {
    word_display.push_back(0);
    word.push_back(this->keyboard->Alphabet[0]);
  } else  // THE INPUT FIELD IS NOT EMPTY
  {
    for (int i = 0; i < str.size(); i++) {
      if (i < FIELD_WIDTH)  // NUMBER OF COLUMN - THE SIZE OF THE MENU CURSOR -
                            // THE SIZE OF THE KEYBOARD CURSOR
      {
        word_display.push_back(i);
      }
      word.push_back(str[i]);
    }
  }

  // USER FINISHED WRITING ?
  bool has_finished = false;

  // ADDING A NEW CHARACTER ?
  bool new_char = false;

  // INPUT VALUE
  int input;

  // UPDATE THE DISPLAY OF THE INPUT FIELD
  this->menu_lines[this->cursor_position] = this->keyboard->get_display(
      &keyboard_cursor, &word_display, &word, &new_char);
  this->update_display();

  while (has_finished == false) {
    if (this->inputs->has_input() == true) {
      input = this->inputs->get_input();

      if (input != -1 && input != -2) {
        // INPUT ACTIONS
        switch (input) {
          case Direction::LEFT:
            this->keyboard->left(&keyboard_cursor, &word_display);
            if (new_char == true) {
              new_char = false;
            }
            break;

          case Direction::RIGHT:
            this->keyboard->right(&keyboard_cursor, &word_display, &word);
            if (keyboard_cursor == word.size() && new_char == false) {
              new_char = true;
            }
            break;

          case Direction::UP:
            if (new_char == true) {
              new_char = false;
              this->keyboard->add(&word, &word_display);
            } else {
              this->keyboard->up(&keyboard_cursor, &word);
            }
            break;

          case Direction::DOWN:
            if (new_char == true) {
              new_char = false;
              this->keyboard->add(&word, &word_display);
            } else {
              this->keyboard->down(&keyboard_cursor, &word);
            }
            break;

          case Direction::OKAY:
            // EXIT THE INPUT FIELD
            has_finished = true;
            break;

          case Direction::BACK:
            // DELETE THE SELECTED CHARACTER
            this->keyboard->del(&keyboard_cursor, &word_display, &word);
            break;
        }

        // UPDATE THE DISPLAY OF THE INPUT FIELD
        this->menu_lines[this->cursor_position] = this->keyboard->get_display(
            &keyboard_cursor, &word_display, &word, &new_char);
        this->update_display();

#ifdef DEBUG_MODE
        Serial.println("");
        Serial.print("[KEYBOARD_CURSOR]: ");
        Serial.println(keyboard_cursor);
        Serial.print("[INPUT FIELD]: [");
        Serial.print(word[0]);
        for (int s = 1; s < word.size(); s++) {
          Serial.print(", ");
          Serial.print(word[s]);
        }
        Serial.println("]");
        Serial.print("[BUFFER]: [");
        Serial.print(word_display[0]);
        for (int s = 1; s < word_display.size(); s++) {
          Serial.print(", ");
          Serial.print(word_display[s]);
        }
        Serial.println("]");
#endif
      }
    }
    delay(50);
  }

  // RETURN A STRING CONTAINING THE WORD OF THE INPUT FIELD
  std::string ret = "";
  for (int i = 0; i < word.size(); i++) {
    ret += word[i];
  }

  // UPDATE THE DISPLAY OF THE INPUT FIELD
  this->menu_lines[this->cursor_position] = ret;
  this->update_display();
  return ret;
}

void Controller::update() {
  if (this->inputs->has_input()) {
    int input = this->inputs->get_input();  // GET THE USER INPUT
    if (input != -1 && input != -2) {
      switch (input) {
        case Direction::UP:
#ifdef DEBUG_MODE
          Serial.println("[INPUT]: UP");
#endif
          this->scroll(1);
          this->update_display();
          break;

        case Direction::DOWN:
#ifdef DEBUG_MODE
          Serial.println("[INPUT]: DOWN");
#endif
          this->scroll(-1);
          this->update_display();
          break;

        case Direction::OKAY:
#ifdef DEBUG_MODE
          Serial.println("[INPUT]: OK");
#endif
          this->select_choice();
          break;

        case Direction::BACK:
          if (this->first_boot == false) {
#ifdef DEBUG_MODE
            Serial.println("[INPUT]: BACK");
#endif
            this->go_back();
          }
          break;
      }
#ifdef DEBUG_MODE
      Serial.print("[MENU_CURSOR]: ");
      Serial.println(this->cursor_position);
      Serial.println("");
#endif
    }
  }
}