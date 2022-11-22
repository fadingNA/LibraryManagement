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

#ifndef MS3_PUBLICATION_H
#define MS3_PUBLICATION_H

#include "Date.h"
#include "Lib.h"
#include "Streamable.h"
#include <ctime>

namespace sdds {
    class Publication : public Streamable {
        char *mTitle{};
        //This attribute is null by default.
        char *mShelfId{};
        //This attribute is an empty string by default.
        int mMember = 0;
        //This attribute is an integer to hold a 5 digit
        // membership number of members of the library.
        int mRef{};

        Date mDate;
    public:
        Publication();

        Publication(const Publication &newPub);

        void copy(const Publication &newPub);

        ~Publication();

        Publication &operator=(const Publication &newPub);

        virtual void set(int member_id);

        // Sets the membership attribute to either zero or a five-digit integer.
        void setRef(int value);

        // Sets the **libRef** attribute value
        void resetDate();

        // Sets the date to the current date of the system.
        virtual char type() const;

        //Returns the character 'P' to identify this object as a "Publication object"
        bool onLoan() const;

        //Returns true is the publication is checkout (membership is non-zero)
        Date checkoutDate() const;

        //Returns the date attribute
        bool operator==(const char *title) const;

        //Returns true if the argument title appears anywhere in the title of the
        //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        operator const char *() const;

        //Returns the title attribute
        int getRef() const;

        //Returns the libRef attirbute.
        bool conIO(std::ios &io) const;

        std::ostream &write(std::ostream &os) const override;

        std::istream &read(std::istream &istr) override;

        operator bool() const override;

	    Publication* getPub(int libRef);
    };

}
#endif //MS3_PUBLICATION_H
