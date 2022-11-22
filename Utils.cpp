/***********************************************************************
// OOP244 Utils Module:
// File  utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>

using namespace std;

#include "Utils.h"

namespace sdds {
    int isAlpha(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    int isSpace(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    int getint(const char *prompt, istream &istr) {
        int num;
        if (prompt) cout << prompt;
        istr >> num;
        istr.ignore(1000, '\n');
        return num;
    }

    // raplicating the cin.get() funciton
    istream &getint(int &num, const char *prompt, istream &istr) {
        num = getint(prompt, istr);
        return istr;
    }
    bool isNumber(char c) {
        return (c >= '0' && c <= '9');
    }
}