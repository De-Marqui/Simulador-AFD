#include "afd.hpp"
#include <string>
using namespace std;

int main()
{
	int option = -1;
	int controlFlag = 0;
	string screenClearControl = "0";
	string cadeia = "";

	while (option != 0) {
		cout << "[Welcome, below we have some options to choose from]" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "| 1. Read AFD data from .txt file" << endl
			<< "| 2. Show the quintuple for the read AFD .txt file" << endl
			<< "| 3. Evaluate strings read from file" << endl
			<< "| 4. Evaluate new strings by keyboard input" << endl
			<< "| 0. close application" << endl << endl
			<< endl << ">> Choose an option: ";

		cin >> option;

		switch (option) {
		case 0:
			exit(0);
		case 1:
			if (AFDReading())
				controlFlag++;
			break;

		case 2:
			if (controlFlag >= 1)
				printQuintuple();
			break;

		case 3:
			if (controlFlag >= 1)
				fileReading();
			break;

		case 4:
			if (controlFlag >= 1)
			{
				while (cadeia != "RETURN")
				{
					cout << endl << "If you want to go back to the main menu, type RETURN";
					cout << endl << "Enter a string you want to validate: ";
					cin >> cadeia;
					if (cadeia != "RETURN")
						stringCheck(cadeia);
				}
				cadeia = "";
			}
			break;
		}

		if (controlFlag < 1) cout << "[ERROR -> afd.txt NOT READED CORRECTLY]" << endl;

		do {
			cout << endl << "[1. TO CONTINUE]" << endl << ">> ";
			cin >> screenClearControl;
		} while (screenClearControl != "1");

		system("cls");
		screenClearControl = "0";
	}
}
