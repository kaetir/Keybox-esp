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
      Model : -my_wifi : wifi_keybox
      Model : -my_webserver : https_server_keybox*
      Model : -Server_task : xTaskHandle
      Model : -wifi_list : vector<string>
      Model : -current_server : vector<string>
      Model : -locker : vector<vector<string>>
      Model : -is_hotspot : bool
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
      Model : +login()
      Model : +get_config()
      Model : +set_config()
      Model : +getSSID()
      Model : +getWifis()
      Model : +connect_wifi()
      Model : +emit_wifi()
      Model : +turn_wifi_Off()
      Model : +getCurrentWifi()
      Model : +logout()
      Model : +send_ids()
      Model : +save_Wifi_Key()
      Model : +get_Wifi_Key()
      
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
      Controller : -cursor_position : int
      Controller : -entries : vector<int>
      Controller : -menu_lines : vector<string>
      Controller : -buffer : vector<int>
      Controller : -current_menu : string
      Controller : -selected_account : int
      Controller : -inputs_function : vector<vector<string>>
      Controller : -inputs_link : vector<string>
      Controller : -input_fields : map<string, string>
      Controller : -language : string
      Controller : -stop_back : bool
      Controller : -isWalletCreated : bool
      Controller : -selected_wifi : int
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