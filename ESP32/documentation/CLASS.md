# CLASSES:

```mermaid
 classDiagram
      class Screen
      Screen : -display : Adafruit_SSD1306 
      Screen : +Screen()
      Screen : +~Screen()
      Screen : +clear()
      Screen : +setLine()
      Screen : +show()
      
      class View
      View : -screen : Screen*
      View : -buffer : char[NUM_LINE][LUM_COL] 
      View : +View()
      View : +~View()
      View : +clear()
      View : +show()
      View : +draw_text()
      View : +draw_char()
      View : +clear_buffer()
      
      class Model
      Model : -lang_folder : string
      Model : -unlocked_locker : vector<string>
      Model : -user_ids : vector<string>
      Model : +Model()
      Model : +~Model()
      Model : +read()
      Model : +get_accounts()
      Model : +get_account()
      Model : +add_account()
      Model : +modify_account_password()
      Model : +modify_account_username()
      Model : +delete_account()
      Model : +is_webserver_on()
      Model : +switch_server_status()
      Model : +login()
      Model : +get_config()
      Model : +set_config()
      
      class Inputs
      Inputs : +Inputs()
      Inputs : +~Inputs()
      Inputs : +has_input()
      Inputs : +get_input()
      
      class Keyboard
      Keyboard : +Alphabet : vector<char>
      Keyboard : +Keyboard()
      Keyboard : +~Keyboard()
      Keyboard : +up()
      Keyboard : +down()
      Keyboard : +left()
      Keyboard : +right()
      Keyboard : +del()
      Keyboard : +add()
      Keyboard : +get_display()
      
      class Controller
      Controller : -view : View*
      Controller : -model : Model*
      Controller : -keyboard : Keyboard*
      Controller : -inputs : Inputs*
      Controller : -spf : SPIFFS
      Controller : -cursor_position : int
      Controller : -line_number_of_choices : vector<int>
      Controller : -menu_lines : vector<string>
      Controller : -buffer : vector<int>
      Controller : -current_menu : string
      Controller : -selected_account : int
      Controller : -inputs_function : vector<vector<string>>
      Controller : -inputs_link : vector<string>
      Controller : -input_fields : map<string, string>
      Controller : -language : string
      Controller : -first_boot : bool
      Controller : -update_display()
      Controller : -load_menu()
      Controller : -init_buffer()
      Controller : -select_choice()
      Controller : -go_back()
      Controller : -write()
      Controller : -scroll()
      Controller : +Controller()
      Controller : +~Controller()
      Controller : +update()
      
      Screen <-- View : screen
      View <-- Controller : view
      Model <-- Controller : model
      Inputs <-- Controller : inputs
      Keyboard <-- Controller : keyboard
```