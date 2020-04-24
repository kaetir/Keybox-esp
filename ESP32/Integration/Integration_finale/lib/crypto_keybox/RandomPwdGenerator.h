#include <Arduino.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

char GenRand();
/**
 * @brief  generate a random string
 * @param len lenght of the string
 * @return  the random string
 */
std::string generate_random_string(int len);
