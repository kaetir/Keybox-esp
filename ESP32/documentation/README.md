# README

## Menu structure:

```mermaid
stateDiagram
Setup : Choose your language (only at the first boot)
Welcome_menu : Welcome menu
Login : Login menu (Username + Password)
Main_menu : Main menu
Web_server : Web server (ON/OFF)
Accounts_menu : Accounts menu
Add_account : Add an account (Name + Username + Password)
Account_selection : Select an account in the list
Display_account : Display the account informations (Name + Username + Password)
Delete_account : Delete the account?
Send_to_computer : Send the ids to the computer?
Modify_account : Modify the account informations
New_username : New Username
New_password : New Password
Language : Choose your Language

Setup --> Welcome_menu
Welcome_menu --> Login
Login --> Main_menu
Main_menu --> Web_server
Main_menu --> Accounts_menu
Main_menu --> Language
Accounts_menu --> Add_account
Accounts_menu --> Account_selection
Account_selection --> Display_account
Display_account --> Delete_account
Delete_account --> Account_selection
Display_account --> Send_to_computer
Send_to_computer --> Display_account
Display_account --> Modify_account
Modify_account --> New_username
Modify_account --> New_password
New_username --> Display_account
New_password --> Display_account
```

## Inputs:

### LEFT:

```mermaid
graph TD
input_left[LEFT] --> cond1[Is the user writing?]
cond1-- YES -->cond2[Is the keyboard cursor at the begining of the word?]
cond2-- NO -->go_left[Move the keyboard cursor to the left, new_char = False]
go_left-->cond3[Is the keyboard cursor out of screen display?]
cond3-- YES -->move_left[Move the screen display to the left]
```

### RIGHT:

```mermaid
graph TD
input_right[RIGHT] --> cond1_1[Is the user writing?]
cond1_1-- YES -->cond2_1[Is the keyboard cursor < word.size-1?]
cond2_1-- NO -->cond4_1[new_char = True]
cond4_1-->cond5_1[Is Is the keyboard cursor = word.size?]
cond5_1-- NO -->cond6_1[Move the keyboard cursor to the right]
cond2_1-- YES -->go_right[Move the keyboard cursor to the right]
go_right-->cond3_1[Is the keyboard cursor out of screen display?]
cond3_1-- YES -->move_right[Move the screen display to the right]
cond6_1-->cond3_1
```

### UP:

```mermaid
graph TD
input_right[UP] --> cond1[Is the user writing?]
cond1-- YES -->cond2[Is new_char = True?]
cond2-- YES -->cond3[Add a new char to the word, new_char = False]
cond2-- NO -->cond4[Modify the character by moving up in the alphabet]
cond1-- NO -->cond5[Is the menu cursor at the begining of the menu?]
cond5-- NO -->cond6[Is the menu cursor at the top of the menu display?]
cond6-- NO -->cond7[Is there an input above the cursor in the menu display?]
cond7-- YES -->cond8[Move the cursor to the closest input found above]
cond7-- NO -->cond9[Move the cursor above the menu display if possible]
cond9-->move_up[Move the menu display up]
cond6-- YES -->cond9
```

### DOWN:

```mermaid
graph TD
input_right[DOWN] --> cond1[Is the user writing?]
cond1-- YES -->cond2[Is new_char = True?]
cond2-- YES -->cond3[Add a new char to the word, new_char = False]
cond2-- NO -->cond4[Modify the character by moving down in the alphabet]
cond1-- NO -->cond5[Is the menu cursor at the end of the menu?]
cond5-- NO -->cond6[Is the menu cursor at the bottom of the menu display?]
cond6-- NO -->cond7[Is there an input below the cursor in the menu display?]
cond7-- YES -->cond8[Move the cursor to the closest input found below]
cond7-- NO -->cond9[Move the cursor below the menu display if possible]
cond9-->move_up[Move the menu display down]
cond6-- YES -->cond9
```

### OK:

```mermaid
graph TD
ok[ok]-->cond1[Is the user writing?]
cond1-- YES -->exit[Exit the writing of the input field]
cond1-- NO -->cond2[Is the menu cursor on an input field/menu?]
cond2-- YES -->cond3[Is this an input field?]
cond3-- YES -->writing[Enter the writing mode of the input field]
cond3-- NO -->cond4[Is there a function on this menu link?]
cond4-- YES -->funct[is_valid = Call the function associated to this entry]
funct-->cond5[is_valid = True?]
cond5-- YES -->link[Load the menu associated if there is one]
cond4-- NO -->link
```

### BACK:

```mermaid
graph TD
back[BACK]-->cond1[Is the user writing?]
cond1-- YES -->exit[Delete the selected character]
cond1-- NO -->cond2[Go back to the last menu]
```

## Class structure:

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

## Menu files .struct

### Each line is described by: LINE_NUMBER LINE_TYPE ARG1 ARG2 ARG3 ARG4
- LINE_NUMBER: The number of the correspong menu line (starting from 0)
- LINE_TYPE: It is a character describing the type of the line ('t' for plain text,'>' for direct menu link, '<' for an input field, 'f' for a function to execute before going to a menu, 'g' to get an information at the loading of the menu and display it)
- ARGs: Arguments, their number depends on the function used

### exemples:
```
0 t //Display plain text
1 > menu1  //Direct link to the menu1
2 < name_of_input //Input Field name: name_fo_input
3 f menu1 funct1 name_of_arg1 name_of_arg2 name_of_arg3 //Go to the menu1 after calling the funct1
4 g funct2 //Call the funct2 at the loading of the current menu
```

Login.txt:
```
Connection:
user:

password:

Login
```
Login.struct:
```
0 t
1 t
2 < user
3 t
4 < password
5 f Main_menu login user password
```

### List of input fields:
- user: Name of the user of the Vault
- username: Name of the user of the account
- name: Name/URL of the account
- password: password of the Vault or password of the account

### List of funct1 and their arguments:
- add_account name username password
- deleteAccount
- login user password
- logoff
- setAccountPassword password
- setAccountUsername username
- sendToComputer
- switch_ServerStatus
- set_Lang language(FR, EN, GE...)

### List of funct2:
- getAccountlist
- getAccountName
- getAccountUsername
- getAccountPassword
- getServerStatus