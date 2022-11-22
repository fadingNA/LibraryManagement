/*
*****************************************************************************
                             MS - #3
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
#include "Streamable.h"

namespace sdds {

    bool Streamable::conIO(std::ios &io) {
        return &io == &std::cin || &io == &std::cout;
    }


    Streamable::~Streamable() = default;

    std::ostream &operator<<(std::ostream &os1, const Streamable &sa) {
        if (sa) {
            sa.write(os1);
        }
        return os1;
    }

    std::istream &operator>>(std::istream &is1, Streamable &as) {
        as.read(is1);
        return is1;
    }

}