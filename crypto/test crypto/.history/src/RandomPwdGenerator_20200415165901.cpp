
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

//selectArray is  a utility function that is used to
//randomly generate a integer in the range 1 to 4 (both inclusive)
int selectArray()
{
    // Using malloc() function we are Dynamically allocating memory
    //for a Integer and this function will return a pointer pointing to the allocated memory
    int* j = (int*)malloc(sizeof(int));
    // The content of int pointer j (i.e an address) will be
    //interpreted as an Integer and will be assigned to integer variable i.
    int i = int(j);
    i = i % 5;
    if (i == 0)
        i++;
    return i;
}

//getKey() is another utility function that is used to randomly generate
//an integer in the range 0 to 25 (both inclusive)
int getKey()
{
    // Using malloc() function we are Dynamically allocating memory for an
    //Integer and this function will return a pointer pointing to the allocated memory
    int* i = (int*)malloc(sizeof(int));
    // The content of int pointer i (i.e an address) will be interpreted as
    // an Integer and will be assigned to integer variable key.
    int key = int(i);
    key = key % 26;
    return key;
}
std::string generate_string(int length)
{
    //Intializing result string password as NULL.
    string password = "";

    //Strings whose characters will be used to build password
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s_symbol = "!@#$%&";
    string number = "0123456789";

    //intializing local variables
    int key, count_alphabet = 0, count_ALPHABET = 0, count_number = 0, count_s_symbol = 0;

    //Count will store the length of the password being created,initially this will be zero(0)
    int count = 0;
    while (count < length) {
        // selectArray() function will return a number 1 to 4
        // and will use to select one of the above defined string
        //(i.e alphabet or ALPHABET or s_symbol or number )
        // 1 is for string alphabet
        // 2 is for string ALPHABET
        // 3 is for string number
        // and 4 is for string s_symbol

        int k = selectArray();

        //for the first character of password it is mentioned that ,it should be a letter
        // so the string that should be selected is either alphabet or ALPHABET (i.e 1 or 2)
        // following if condition will take care of it.
        if (count == 0) {
            k = k % 3;
            if (k == 0)
                k++;
        }
        switch (k) {
        case 1:
            // following if condition will check if minimum requirement of alphabet
            // character has been fulfilled or not
            // incase it has been fulfilled and minimum requirements of other
            // characters is still left then it will break ;
            if ((count_alphabet == 2) && (count_number == 0 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_s_symbol == 0))
                break;

            key = getKey();
            password = password + alphabet[key];
            count_alphabet++;
            count++;
            break;

        case 2:
            // following if condition will check if minimum requirement of
            // ALPHABET character has been fulfilled or not
            // incase it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_ALPHABET == 2) && (count_number == 0 || count_alphabet == 0 || count_alphabet == 1 || count_s_symbol == 0))
                break;
            key = getKey();
            password = password + ALPHABET[key];
            count_ALPHABET++;
            count++;
            break;

        case 3:
            // following if condition will check if minimum requirement
            // of Numbers  has been fulfilled or not
            // incase it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_number == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 1 || count_ALPHABET == 0 || count_s_symbol == 0))
                break;

            key = getKey();
            key = key % 10;
            password = password + number[key];
            count_number++;
            count++;
            break;

        case 4:
            // following if condition will check if minimum requirement of
            // Special symbol character has been fulfilled or not
            // incase it has been fulfilled and minimum requirements of
            // other characters is still left then it will break ;
            if ((count_s_symbol == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_number == 0))
                break;

            key = getKey();
            key = key % 6;
            password = password + s_symbol[key];
            count_s_symbol++;
            count++;
            break;
        }
    }
    cout << " " << password;
    return password
}
