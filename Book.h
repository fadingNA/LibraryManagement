//
// Created by Nonthachai Plodthong on 27/7/2022 AD.
//

#ifndef MS4_BOOK_H
#define MS4_BOOK_H

#include "Publication.h"

namespace sdds {
    class Book : public Publication {
    private:
        char *author;
    public:
        Book();

        Book(const char *authorName);

        void controlC(const char *name);

        ~Book(); //RULE 1 Destructor

        Book &operator=(const Book &authorR); // Rule 2 Copy assignment

        Book(const Book &authorB); // Rule 3 Copy Constructor

        char type() const override;

        std::ostream &write(std::ostream &os) const override;

        std::istream &read(std::istream &istr) override;

        void set(int member_id) override;

        operator bool() const override;


    };
}
#endif //MS4_BOOK_H
