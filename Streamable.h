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
#ifndef MS3_STREAMABLE_H
#define MS3_STREAMABLE_H

#include <iostream>
#include <ostream>


namespace sdds {
    class Streamable {
    public:
        virtual std::ostream &write(std::ostream &os) const = 0;

        virtual std::istream &read(std::istream &is) = 0;

        static bool conIO(std::ios &io);

        virtual ~Streamable();

        virtual operator bool() const = 0;

        friend std::ostream &operator<<(std::ostream &os1, const Streamable &sa);

        friend std::istream &operator>>(std::istream &is1, Streamable &as);


    };
}

#endif //MS3_STREAMABLE_H
