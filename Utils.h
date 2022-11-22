/*
*****************************************************************************
                             MS - #1
Full Name  : NONTHACHAI PLODTHONG
Student ID#: 152487211
Email      : nplodthong@myseneca.ca
Section    : NII

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__

#include <iostream>

namespace sdds {
    int isAlpha(char ch);

    int isSpace(char ch);

    int getint(const char *prompt, std::istream &istr);

    std::istream &getint(int &num, const char *prompt, std::istream &istr);

    bool isNumber(char c);
}
#endif // !