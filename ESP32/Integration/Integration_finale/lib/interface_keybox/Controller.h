#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Inputs.h"
#include "Keyboard.h"
#include "Model.h"
#include "View.h"

class Controller {
 private:
  View *view;           // View OBJECT
  Model *model;         // Model OBJECT
  Keyboard *keyboard;   // Keyboard OBJECT
  Inputs *inputs;       // Inputs OBJECT
  int cursor_position;  // CONTAIN THE POSITION OF THE CURSOR ON THE WHOLE MENU
  std::vector<int> line_number_of_choices;  // CONTAIN THE INDEXES OF THE LINES
                                            // WHERE THE CURSOR SHOULD APPEAR
  std::vector<std::string> menu_lines;      // CONTAIN THE WHOLE MENU LINES
  std::vector<int> buffer;  // CONTAIN THE INDEXES OF THE LINES TO BE DISPALYED
                            // (MAX SIZE == NUM_LINE)

  std::string current_menu;  // NAME OF THE CURRENT MENU
  int selected_account;  // INDEX OF THE SELECTED ACCOUNT IN THE ACCOUNT LIST
  std::vector<std::vector<std::string>>
      inputs_function;  // NAME OF THE FUNCTIONS AND ARGUMENT FOR EACH CHOICE
                        // (IT CAN BE "NONE")
  std::vector<std::string> inputs_link;  // NAME OF THE MENU TO SWITCH TO
  std::map<std::string, std::string>
      input_fields;      // LIST OF THE INPUT FIELDS IN THE MENU
  std::string language;  // LANGUAGE OF THE USER
  bool first_boot;       // HAS THIS MACHINE EVER BOOTED?
  bool isWalletCreated;
  int selected_wifi;  // INDEX OF THE SELECTED WIFI IN THE WIFI LIST

  /**
   * @brief  Update the display of the menu
   */
  void update_display();

  /**
   * @brief  Load the menu
   * @param menu_name  name of the menu file to load
   */
  void load_menu(std::string menu_name);

  /**
   * @brief  Initalize the menu buffer and the screen
   */
  void init_buffer();

  /**
   * @brief  Check and act accordingly to the entry selected by the user
   */
  void select_choice();

  /**
   * @brief  Go back to the previous menu
   */
  void go_back();

  /**
   * @brief  Write in the input field
   * @param str  Current content of the input field
   * @return  New content of the input field
   */
  std::string write(std::string str);

  /**
   * @brief  Update the cursor_position and the menu buffer
   * @param a Must be equal to 1 to scroll up and equal to -1 to scroll down
   */
  void scroll(int a);

 public:
  /**
   * @brief  Constructor
   */
  Controller();

  /**
   * @brief  Destructor
   */
  ~Controller();

  /**
   * @brief  Update the system by taking actions determined by the user input
   */
  void update();
};

#endif  // CONTROLLER_H