/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Nonthachai Plodthong
Revision History
-----------------------------------------------------------
Date      Reason
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include <iostream>
#include "Menu.h"
#include "iomanip"
#include <cstring>

using namespace std;
namespace sdds {
	Menuitem::Menuitem(const char *menuItemContent) {
		if (menuItemContent && menuItemContent[0] != '\0') {
			menuItem = new char[strlen(menuItemContent) + 1];
			strcpy(menuItem, menuItemContent);
		} else {
			menuItem = nullptr;
		}
	}

	Menuitem::~Menuitem() { delete[] menuItem; }

	Menuitem::operator const char *() const { return menuItem; }

	ostream &Menuitem::display(ostream &os) const {
		if (menuItem) {
			os << menuItem;
		}
		return os;
	}

	Menu::Menu() : menuTrack{
			0
	} {
		mainTitle = nullptr;
		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
			menuitem[i] = nullptr;
		}
	}

	Menu::Menu(const char *menuName) : mainTitle(menuName), menuTrack{
			0
	} {
		/* for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			 menuitem[i] = nullptr;
		 }*/
	}

	unsigned int Menu::run() {
		display(cout);
		unsigned int selection;
		int pass = 0;
		do {
			cin >> selection;
			if (cin.fail()) {
				cout << "Invalid Selection, try again: ";
				cin.clear();
				while (cin.get() != '\n');
			} else if (cin.get() != '\n') {
				cout << "Invalid Selection, try again: ";
				cin.clear();
				while (cin.get() != '\n');
			} else if (selection > menuTrack) {
				cout << "Invalid Selection, try again: ";
			} else {
				pass = 1;
			}
		} while (pass == 0);
		return selection;
	}

	Menu::~Menu() {
		for (unsigned int i = 0; i < menuTrack; i++) {
			delete menuitem[i];
		}
	}

	Menu &Menu::operator<<(const char *menuitemContent) {
		if (menuTrack < MAX_MENU_ITEMS) {
			this->menuitem[menuTrack] = new Menuitem(menuitemContent);
			menuTrack++;
		}
		return *this;
	}

	Menu::operator int() const {
		//Overload two type conversions for int and unsigned int to return the number of MenuItems on the Menu.
		return menuTrack + 1;
	}

	Menu::operator unsigned int() const {
		return ((unsigned int) (menuTrack));
	}

	//Overload the type conversion for bool to return true if the Menu has one or more MenuItems otherwise, false;
	Menu::operator bool() const {
		return menuTrack > 0;
	}

	//Overload the insertion operator to print the title of the Menu using cout.
	ostream &operator<<(ostream &s, const Menu &m) {
		//cout << "The " << M << " is not empty and has "      //  insertion operator overload
		return m.titleDisplay(s);
	}

	int Menu::operator~() {
		return run();
	}

	std::ostream &Menu::titleDisplay(std::ostream &os) const {
		if (mainTitle) {
			mainTitle.display(os);
		}
		return os;
	}

	const char *Menu::operator[](int i) const {
		return menuitem[i % menuTrack]->menuItem;
	}

	ostream &Menu::display(ostream &out) {
		if (*this) {
			if (mainTitle) {
				mainTitle.display(out);
				out << endl;
			}
			for (unsigned int i = 0; i < menuTrack; i++) {
				out << setw(2) << right << (i + 1) << "- ";
				menuitem[i]->display(out);
				out << endl;
			}
			out << " 0- Exit" << endl;
			out << "> ";
		}
		return out;
	}
}
