/*
*****************************************************************************
                             MS - #5
Full Name  : NONTHACHAI PLODTHONG
Student ID#: 152487211
Email      : nplodthong@myseneca.ca
Section    : NII

//|* 219*| P123 | The Story of My Experiments wi | 12345 | 2022/08/07 | Mohandas Karamc |

Authenticity Declaration:

I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#include "Book.h"
#include <iostream>
#include <cstring>
#include <iomanip>


namespace sdds {

	void Book::controlC(const char *name) {
		if (name) {
			size_t length;
			length = strlen(name);
			author = new char[length + 1];
			strncpy(this->author, name, length);
			author[length] = '\0';
		}
	}

	Book::Book() { this->author = nullptr; }

	Book::Book(const char *authorName) { if (authorName) { controlC(authorName); }}

	Book::~Book() { delete[] author; } //RULE 1 Destructor

	Book &Book::operator=(const Book &authorR) {
		Publication::operator=(authorR);
		delete[] author;
		controlC(authorR.author);
		return *this;

	} // Rule 2 Copy assignment

	Book::Book(const Book &authorB) : Publication(authorB) {
		controlC(authorB.author);
	} // Rule 3 Copy Constructor

	char Book::type() const {
		return 'B';
	}

	std::ostream &Book::write(std::ostream &os) const {
		Publication::write(os);
		if (Publication::conIO(os)) {
			os << " ";
			int length = strlen(author);
			if (length > SDDS_AUTHOR_WIDTH) {
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
					os.put(this->author[i]);
				}
			} else {
				os << std::setw(SDDS_AUTHOR_WIDTH) << std::setfill(' ') << std::left << this->author;
			}
			os << " |";
		} else {
			os << '\t';
			os << this->author;
		}
		return os;
	}

	std::istream &Book::read(std::istream &istr) {
		Publication::read(istr);
		delete[] author;
		char authorString[256];

		if (Publication::conIO(istr)) {
			istr.ignore(25, '\n');
			std::cout << "Author: ";
		} else {
			istr.ignore(256, '\t');
		}
		istr.get(authorString, 256, '\n');
		controlC(authorString);
		return istr;
	}

	void Book::set(int member_id) {
		Publication::set(member_id);
		resetDate();
	}


	Book::operator bool() const {
		if (author == nullptr) {
			return false;
		}
		return strlen(author) > 0;
	}

}
