// main.cpp  
// Andrew C. Mattson
// 2023-02-14
//
// Personal Project
// Main file for Studybot


#include "Studybot.h"

int main(int argc, char** argv) {
	srand(time(0)); // This is somewhat annoying; can we put it in the class?

	Studybot studybot;

	while (studybot.hasMats()) {
		string line;

		if (studybot.validMats()) {
			cout << "How would you like to study?" << endl;
			cout << "1. Decrementally (Remove the questions you've memorized)" << endl;
			cout << "2. Incrementally (One by one, add more questions to memorize)" << endl;
			cout << "Enter choice: ";
			getline(cin, line);
			while (line != "1" && line != "2") {
				studybot.clearScr();
				cout << "Invalid choice. Enter 1 or 2." << endl;
				cout << "How would you like to study?" << endl;
				cout << "1. Decrementally" << endl;
				cout << "2. Incrementally" << endl;
				cout << "Enter choice: ";
				getline(cin, line);
			}

			if (line == "1")
				studybot.studyDec();
			else if (line == "2")
				studybot.studyInc();

			cout << "Would you like to:" << endl;
			cout << "1. Study this unit again" << endl;
			cout << "2. Study a new unit" << endl;
			cout << "Enter nothing to exit." << endl << endl;
			cout << "Enter your choice: ";
			getline(cin, line);

			if (line == "2") studybot.newChoice();
			else if (line != "1") break;
		}
		else {
			studybot.clearScr();
			cout << "Would you like to:" << endl;
			cout << "1. Select a new unit" << endl;
			cout << "Enter nothing to exit." << endl << endl;
			cout << "Enter your choice: ";
			getline(cin, line);

			if (line == "1") studybot.newChoice();
			else break;
		}
		studybot.clearScr();
	}
	

	return 0;
}