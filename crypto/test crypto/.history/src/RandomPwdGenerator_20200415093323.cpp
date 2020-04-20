#include <random>
#include "RandomPwdGenerator.h"
using namespace std;
typedef unsigned int uint;

std::string random_string(uint l, std::string charIndex)
{
    // l and charIndex can be customized, but I've also initialized them.

    uint length = l;
    // length of the string is a random value that can be up to 'l' characters.

    uint ri[15];
    /* array of random values that will be used to iterate through random 
      indexes of 'charIndex' */

    for (uint i = 0; i < length; ++i)
        ri[i] = rand() % charIndex.length();
    // assigns a random number to each index of "ri"

    std::string rs = "";
    // random string that will be returned by this function

    for (uint i = 0; i < length; ++i)
        rs += charIndex[ri[i]];
    // appends a random amount of random characters to "rs"

    if (rs.empty())
        random_string(l, charIndex);

    else
        return rs;
}
