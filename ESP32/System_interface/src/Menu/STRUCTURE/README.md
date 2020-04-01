# This folder contains the structure of each menus

## Each line is described by: LINE_NUMBER LINE_TYPE ARG1 ARG2 ARG3 ARG4
- LINE_NUMBER: The number of the correspong menu line (starting from 0)
- LINE_TYPE: It is a character describing the type of the line ('t' for plain text,'>' for direct menu link, '<' for an input field, 'f' for a function to execute before going to a menu, 'g' to get an information at the loading of the menu and display it)
- ARGs: Arguments, their number depends on the function used

## exemples:
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

## List of input fields:
- user: Name of the user of the Vault
- username: Name of the user of the account
- name: Name/URL of the account
- password: password of the Vault or password of the account

## List of funct1 and their arguments:
- add_account name username password
- deleteAccount
- login user password
- logoff
- setAccountPassword password
- setAccountUsername username
- sendToComputer
- switch_ServerStatus

## List of funct2:
- getAccountlist
- getAccountName
- getAccountUsername
- getAccountPassword
- getServerStatus