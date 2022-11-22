/*
*****************************************************************************
                             MS - #5
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
#ifndef MS2_LIBAPP_H
#define MS2_LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
#include <fstream>

namespace sdds {
	const int lengthFile = 256;

	class LibApp {
	private:
		bool m_change = false;

		Menu m_mainmenu;

		Menu m_exitmenu;

		// MS5 ADD ATT
		char pubFileName[lengthFile];

		Publication *pPA[SDDS_LIBRARY_CAPACITY];
		// ppa = public pointer array

		int numberOfPub;

		int libRefNumber;

		Menu typeOfMenu;

		char getType();

		Publication *getPub(int libRef);

		// MS5 ADD ATT

		bool confirm(const char *message);

		void load();  // prints: "Loading Data"<NEWLINE>

		void save();  // prints: "Saving Data"<NEWLINE>

		int  search(int selection);  // prints: "Searching for publication"<NEWLINE>
		// change to int MS5

		void returnPub();

		void newPublication();

		void removePublication();

		void checkOutPub();


	public:
		void run();

		LibApp(const char *filename);

		~LibApp();
	};
}

#endif //MS2_LIBAPP_H
