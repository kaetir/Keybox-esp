
#include "RandomPwdGenerator.h"

static const char alphnum[] = "0123456789"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;
char GenRand()
{
    return alphnum[rand() % strLen];
}
std::string generate_random_string(int len)
{
    int n = len, c = 0, s = 0;
    time_t current_time;
    srand(time(&current_time));
    char C;
    std::string D;
    for (int z = 0; z < n; z++) {
        C = GenRand();
        D += C;
        if (isdigit(C)) {
            c++;
        }
        if (C == '!' || C == '@' || C == '$' || C == '%' || C == '^' || C == '&' || C == '*' || C == '#') {
            s++;
        }
    }
    std::cout << D;
    return D;
}
