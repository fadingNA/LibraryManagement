/*
*****************************************************************************
                             MS - #5
Full Name  : NONTHACHAI PLODTHONG
Student ID#: 152487211
Email      : nplodthong@myseneca.ca
Section    : NII

 //03:56 non ignore ตัดทิ้ง
 //03:56 non getline นับหมดเอาทั้งแถว
 //03:56 non get คือสุดจนกว่าจะเจอ delimeter

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#include "Publication.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
namespace sdds {
	Publication::Publication() {
		mTitle = nullptr;
		mShelfId = nullptr;
		mMember = 0;
		mRef = -1;
	}

	Publication::Publication(const Publication &newPub) {
		copy(newPub);
	}

	void Publication::copy(const Publication &newPub) {
		delete[] this->mTitle;
		this->mTitle = nullptr;
		if (newPub.mTitle != nullptr) {
			int titleLength = strlen(newPub.mTitle);
			this->mTitle = new char[titleLength + 1];
			for (int i = 0; i < titleLength; i++) {
				this->mTitle[i] = newPub.mTitle[i];
			}
			this->mTitle[titleLength] = '\0';
		}

		delete[] this->mShelfId; // first error
		this->mShelfId = nullptr;
		if (newPub.mShelfId != nullptr) {
			this->mShelfId = new char[SDDS_SHELF_ID_LEN + 1];
			for (int i = 0; i < SDDS_SHELF_ID_LEN; i++) {
				this->mShelfId[i] = newPub.mShelfId[i];
			}
			this->mShelfId[SDDS_SHELF_ID_LEN] = '\0';
		}

		this->mMember = newPub.mMember;
		this->mDate = newPub.mDate;
		this->mRef = newPub.mRef;
	}

	Publication::~Publication() {
		delete[] mTitle;
		mTitle = nullptr;
		delete[] mShelfId;
		mShelfId = nullptr;
	}

	void Publication::set(int member_id) {
		if (member_id >= 0 && member_id <= 99999) {
			this->mMember = member_id;
		}
	}

	void Publication::setRef(int value) {
		this->mRef = value;
	}

	void Publication::resetDate() {
		Date currentDate;
		this->mDate = currentDate;
	}

	// Sets the date to the current date of the system.

	Publication *Publication::getPub(int libRef) {
		if (this->mRef == libRef) {
			return this;
		}
		return nullptr;
	}

	char Publication::type() const {
		return 'P';
	}

	//Returns the character 'P' to identify this object as a "Publication object"
	bool Publication::onLoan() const {
		return this->mMember != 0;
	}

	//Returns true is the publication is checkout (membership is non-zero)
	Date Publication::checkoutDate() const {
		return mDate;
	}

	Publication &Publication::operator=(const Publication &newPub) {
		if (this == &newPub) {
			return *this;
		}
		copy(newPub);
		return *this;
	}

	//Returns the date attribute
	bool Publication::operator==(const char *title) const {
		if (title) {
			if (strstr(this->mTitle, title)) {
				return true;
			}
		}
		return false;
	}

	//Returns true if the argument title appears anywhere in the title of the
	//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
	Publication::operator const char *() const {
		return this->mTitle;
	}

	//Returns the title attribute
	int Publication::getRef() const {
		return this->mRef;
	}

	//Returns the libRef attirbute.
	bool Publication::conIO(std::ios &io) const {
		return &io == &std::cin || &io == &std::cout;
	}

	std::ostream &Publication::write(std::ostream &os) const {
		if (conIO(os)) {
			os << "| " << setw(4) << this->mShelfId
			   << " | ";
			int length = strlen(mTitle);
			if (length > SDDS_TITLE_WIDTH) {
				for (int i = 0; i < SDDS_TITLE_WIDTH; i++) {
					os.put(this->mTitle[i]);
				}
			} else {
				char prevFill = os.fill('.');
				os << std::setw(SDDS_TITLE_WIDTH) << std::left << this->mTitle;
				os.fill(prevFill);
			}
			os << " | ";
			if (this->mMember == 0) {
				os << setw(5) << " N/A " << " | ";
			} else {
				os << setw(5) << this->mMember << " | ";
			}
			os << this->mDate << " |";
		} else {
			os << this->type() << '\t' << this->mRef << "\t"
			   << this->mShelfId << "\t"
			   << this->mTitle << "\t";

			os << this->mMember << "\t";

			os << this->mDate;
		}
		return os;
	}

	std::istream &Publication::read(std::istream &istr) {
		char shelfId[SDDS_SHELF_ID_LEN + 2];
		char title[256];
		int membership = 0;
		int libref = this->mRef;
		Date d;

		if (conIO(istr)) {
			std::cout << "Shelf No: ";
			istr.get(shelfId, SDDS_SHELF_ID_LEN + 2, '\n');
			if (istr.gcount() != SDDS_SHELF_ID_LEN) {
				//set fail bit
				istr.setstate(std::ios_base::failbit);
			}
			istr.ignore(1000, '\n');

			std::cout << "Title: ";
			istr.get(title, 256, '\n');
			istr.ignore(1000, '\n');

			std::cout << "Date: ";
			istr >> d;
			//istr.ignore(1000, '\n');
		} else {
			//istr.ignore(100,'\t');
			//istr.getline(m_libRef, 100, '\t');
			istr >> libref;
			istr.ignore(100, '\t');
			istr.get(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.ignore(100, '\t');
			istr.get(title, 256, '\t');
			istr.ignore(100, '\t');
			istr >> membership;
			istr.ignore(100, '\t');
			istr >> d;
		}

		if (!d)
			istr.setstate(std::ios_base::failbit);

		if (istr.good()) {
			delete this->mTitle;
			int titleLength = strlen(title);
			this->mTitle = new char[titleLength + 1];
			for (int i = 0; i < titleLength; i++) {
				this->mTitle[i] = title[i];
			}
			this->mTitle[titleLength] = '\0';

			delete this->mShelfId;
			this->mShelfId = new char[SDDS_SHELF_ID_LEN + 1];
			for (int i = 0; i < SDDS_SHELF_ID_LEN; i++) {
				this->mShelfId[i] = shelfId[i];
			}
			this->mShelfId[SDDS_SHELF_ID_LEN] = '\0';

			this->mMember = membership;
			this->mDate = d;
			this->mRef = libref;
		}
		return istr;
	}

	Publication::operator bool() const {
		if (mTitle != nullptr) {
			if (mShelfId != nullptr) {
				if (strlen(mTitle) > 0 && strlen(mShelfId) > 0) {
					return true;
				}
			}
		}
		return false;
	}
}
