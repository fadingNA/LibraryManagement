/*
*****************************************************************************
                             MS - #2
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
#ifndef MS1_MENU_H
#define MS1_MENU_H

#include <iostream>

namespace sdds {
	const unsigned int MAX_MENU_ITEMS = 20;

	class Menuitem {
	private:
		char *menuItem;

		Menuitem() = default;

		Menuitem(Menuitem &) = delete;

		Menuitem(const char *menuItemContent);

		~Menuitem();

		//   operator bool();

		operator const char *() const;

		std::ostream &display(std::ostream &os) const;

	public:
		friend class Menu;
	};

	class Menu {
	private:
		Menuitem mainTitle;
		Menuitem *menuitem[MAX_MENU_ITEMS];
		unsigned int menuTrack;
	public:
		Menu();

		Menu(const char *menuName);

		~Menu();

		unsigned int run();

		std::ostream &titleDisplay(std::ostream &os) const;

		Menu &operator<<(const char *menuitemContent);

		std::ostream &display(std::ostream &out);

		operator int() const;

		operator unsigned int() const;

		operator bool() const;

		friend std::ostream &operator<<(std::ostream &s, const Menu &m);

		int operator~();

		const char *operator[](int i) const;
	};


}
#endif //MS1_MENU_H
