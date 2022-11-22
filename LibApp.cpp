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
#include "LibApp.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;
namespace sdds {
	LibApp::~LibApp() {
		for (int i = 0; i < numberOfPub; i++) {
			delete pPA[i];
		}
	}

	LibApp::LibApp(const char *filename) : m_change(false),
	                                       m_mainmenu("Seneca Library Application"),
	                                       m_exitmenu("Changes have been made to the data, what would you like to do?"),
	                                       numberOfPub(0),
	                                       typeOfMenu("Choose the type of publication:") {

		m_mainmenu << "Add New Publication"
		           << "Remove Publication"
		           << "Checkout publication from library"
		           << "Return publication to library";
		m_exitmenu << "Save changes and exit"
		           << "Cancel and go back to the main menu";
		typeOfMenu << "Book";
		typeOfMenu << "Publication";
		if (filename) {
			strcpy(pubFileName, filename);
		}
		load();
	}

	bool LibApp::confirm(const char *message) {
		Menu m(message);
		m << "Yes";
		if (m.run() == 1) {
			return true;
		}
		return false;
	}

	char LibApp::getType() {
		int selector = typeOfMenu.run();
		char type;
		if (selector == 1) {
			type = 'B';
		}

		if (selector == 2) {
			type = 'P';
		}
		return type;

	}

	void LibApp::load() {
		cout << "Loading Data" << endl;
		ifstream loadFile(pubFileName);
		char type{};
		for (int i = 0; loadFile && i < SDDS_LIBRARY_CAPACITY; i++) {
			loadFile >> type;
			if (loadFile) {
				if (type == 'P') {
					pPA[i] = new Publication;
				} else if (type == 'B') {
					pPA[i] = new Book;
				}
				if (pPA[i]) {
					loadFile >> *pPA[i];
					libRefNumber = pPA[i]->getRef();
					numberOfPub++;
				}
			}
			loadFile.ignore(1000, '\n');
			//libRefNumber = pPA[numberOfPub - 1]->getRef();
			///cout << "debug ref Num" << libRefNumber << endl;
		}
	} // prints: "Loading Data"<NEWLINE>

	void LibApp::save() {
		cout << "Saving Data" << endl << endl;
		ofstream saveFile(this->pubFileName);
		for (int i = 0; i < numberOfPub; i++) {
			if (pPA[i]->getRef() != 0) {
				saveFile << *pPA[i] << endl;
			}
		}

	}  // prints: "Saving Data"<NEWLINE>

	int LibApp::search(int selection) {
		//cout << "Searching for publication" << endl;
		int returnSelect = 0;
		char title[lengthFile];

		PublicationSelector selector("Select one of the following found matches:");
		char type = getType();
		cout << "Publication Title: ";
		cin.getline(title, lengthFile);
		for (int i = 0; i < numberOfPub; i++) {
			if (selection == 1) {
				if (strstr(*pPA[i], title) && type == pPA[i]->type()) {
					selector << pPA[i];
				}
			}
			if (selection == 2) {
				if (strstr(*pPA[i], title) && pPA[i]->onLoan() && type == pPA[i]->type()) {
					selector << pPA[i];
				}
			}
			if (selection == 3) {
				if (strstr(*pPA[i], title) && !pPA[i]->onLoan() && type == pPA[i]->type()) {
					selector << pPA[i];
				}
			}
		}
		if (selector) {
			selector.sort();
			int reference = selector.run();
			if (reference) {
				returnSelect = reference;
				cout << *getPub(reference);
			} else {
				cout << "Aborted!" << endl;
			}
		} else {
			cout << "No matches found!" << endl;
			cout << endl;
		}
		cout << endl;
		return returnSelect;


	}  // prints: "Searching for publication"<NEWLINE>
	Publication *LibApp::getPub(int libRef) {
		for (int i = 0; i < numberOfPub; i++) {
			if (libRef == pPA[i]->getRef()) {
				return pPA[i];
			}
		}
		return nullptr;
	}

	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		int select = search(2);
		if (select) {
			if (confirm("Return Publication?") == 1) {
				int loan = Date() - getPub(select)->checkoutDate();
				if (loan > SDDS_MAX_LOAN_DAYS) {
					int late = loan - SDDS_MAX_LOAN_DAYS;
					double fees = 0;
					fees = 0.5 * late;
					cout << setprecision(2) << fixed << "Please pay $" << fees << " penalty for being " << late
					     << " days late!" << endl;
				}
				getPub(select)->set(0);
				m_change = true;
				cout << "Publication returned" << endl;
			}
		}
	}

	void LibApp::newPublication() {
		if (numberOfPub == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			return;
		} else {
			cout << "Adding new publication to the library" << endl;
			int typeNumber = typeOfMenu.run();
			if (typeNumber == 1) {
				pPA[numberOfPub] = new Book();
			} else if (typeNumber == 2) {
				pPA[numberOfPub] = new Publication();
			} else if (typeNumber == 0) {
				cout << "Aborted!" << endl;

				return;
			} else {
				return;
			}

			cin >> *pPA[numberOfPub];
			if (cin.fail()) {
				cin.ignore(1000, '\n');
				cout << "Aborted!" << endl;
				delete pPA[numberOfPub];
				return;
			} else {
				if (!confirm("Add this publication to the library?")) {
					cout << "Aborted!" << endl;
					delete pPA[numberOfPub];
					return;
				} else {
					if (*pPA[numberOfPub]) {
						libRefNumber += 1;
						pPA[numberOfPub]->setRef(libRefNumber);
						numberOfPub += 1;
						m_change = true;
						cout << "Publication added" << endl;
					} else {
						cout << "Failed to add publication!";
						delete pPA[numberOfPub];
					}
				}
			}
		}
	}

	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int select = search(1);
		if (select) {
			if (confirm("Remove this publication from the library?") == 1) {
				getPub(select)->setRef(0);
				m_change = true;
				cout << "Publication removed" << endl;
			}
		}
	}

	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int select = search(3);
		if (select) {
			if (confirm("Check out publication?") == 1) {
				int memNumber = 0;
				cout << "Enter Membership number: ";
				while (!memNumber) {
					cin >> memNumber;
					if (cin.fail()) {
						cin.ignore(1000, '\n');
					} else {
						if (memNumber < 99999) {
							getPub(select)->set(memNumber);
							m_change = true;
							cout << "Publication checked out" << endl;
							break;
						} else {
							cout << "Invalid membership number, try again: ";
							memNumber = 0;
						}
					}
				}
			}
		}
	}

	void LibApp::run() {
		unsigned int selection = 0;
		unsigned int exitSelect = 0;
		bool flag = true;
		do {
			do {
				selection = m_mainmenu.run();
				switch (selection) {
					case 0:
						if (m_change) {
							exitSelect = m_exitmenu.run();
							if (exitSelect == 1) {
								save();
								flag = false;
								break;
							} else if (exitSelect == 0) {
								if (confirm("This will discard all the changes are you sure?")) {
									flag = false;
								}
							}
						} else {
							flag = false;
						}
						cout << endl;
						break;
					case 1:
						newPublication();
						if (m_change) {
							cout << endl;
							break;
						} else {
							flag = false;
							cout << endl;
							break;
						}
					case 2:
						removePublication();
						if (m_change) {
							cout << endl;
							break;
						}
						flag = false;
						break;
					case 3:
						checkOutPub();
						if (m_change) {
							cout << endl;
							break;
						}
						flag = false;
						break;
					case 4:
						returnPub();

						break;
				}
				// cout << "FLAG = " << flag << endl;
			} while (flag);

		} while (selection != 0);
		cout << "-------------------------------------------\n"
		        "Thanks for using Seneca Library Application\n";
	}
}
