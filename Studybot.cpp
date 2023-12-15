// Studybot.cpp
// Andrew C. Mattson
// 2023-02-27
//
// Personal Project
// Source file for Studybot.h

#include "Studybot.h"


Studybot::Studybot() : choiceIdx(1) {
	if (DEBUGGING) cout << "DBG: Default CTOR called" << endl;

	int maxChoice = printFiles();
	if (maxChoice >= 1) {
		_validMats = true;
		if (maxChoice != 1) {
			getChoice(1, maxChoice);
		}

		setMats(getFilename());
	}
	else {
		clearScr();
		cout << "No study materials found. Please place .txt files in the documented format in the current directory: ";
		cout << endl << fs::current_path() << endl;
		_validMats = false;
		_hasMats = false;
		waitForKeypress();
	}
}

void Studybot::newChoice() {
	if (DEBUGGING) cout << "DBG: newChoice() called" << endl;

	if (!_hasMats) return;
	clearScr();
	int maxChoices = printFiles();
	if (maxChoices > 1) getChoice(1, maxChoices);
	else if (maxChoices == 1) {
		cout << "Only one file choice available (you can only study that one)" << endl;
		waitForKeypress();
	}
	setMats(getFilename());
}

void Studybot::setMats(string filename) {
	if (DEBUGGING) cout << "DBG: setMats() called" << endl;

	mats.clear();

	ifstream file(filename);
	string line;
	while (std::getline(file, line)) { // For every line in file
		if (line.length() > 1 && isSubstr(COMMENT, line)) {
			int commentPos = line.find(COMMENT);
			line = line.substr(0, commentPos);
		}
		if (line.length() > 1) { // Remove empty lines
			while (isSubstr("\\n", line)) {
				int newlinePos = line.find("\\n");
				line = line.substr(0, newlinePos) + '\n' + line.substr(newlinePos+2, line.length());
			}
			if (isSubstr(DELIM, line)) { // If answer given
				int delimPos = line.find(DELIM);
				string question = line.substr(0, delimPos);
				string answer = line.substr(delimPos + DELIM_LEN, line.length() - (delimPos + DELIM_LEN));
				mats.push_back(Flashcard(question, answer));
			}
			else { // If no answer given
				mats.push_back(Flashcard(line));
			}
		}
	}
	if (mats.size() <= 0) {
		clearScr();
		cout << "The chosen text file was empty." << endl;
		waitForKeypress();
		_validMats = false;
	}
	else {
		_validMats = true;
		_hasMats = true;
	}
}

void Studybot::resetMats() {
	if (DEBUGGING) cout << "DBG: resetMats() called" << endl;

	for (int i = 0; i < mats.size(); i++) {
		mats[i].isAnswered = false;
	}
}

bool Studybot::studyInc() {
	if (DEBUGGING) cout << "DBG: studyInc() called" << endl;

	if (!_hasMats) return false;
	if (!_validMats) return false;

	resetMats();

	int prevIdx = -2;
	int currQS = 1;
	int remQS = mats.size() - 1;
	string decision;
	while (remQS >= 0) {
		mats[currQS - 1].isAnswered = true;

		int randIdx = -1;
		// Of Q's added, study random one.
		while ((randIdx < 0) || prevIdx == randIdx) {
			if (currQS == 1) {
				randIdx = 0;
				break;
			}
			randIdx = randInRange(0, currQS - 1);
		}

		prevIdx = randIdx;


		decision = dispQandA(randIdx, remQS, false);
		if (decision == "n") {
			currQS++;
			remQS--;
		}
		else if (decision == "stop") break;
	}

	for (int i = 0; i < mats.size(); i++) {
		mats[i].isAnswered = false;
	}

	clearScr();

	if (decision != "stop" && remQS <= 0)
		cout << "All questions answered! ";

	return true;
}

bool Studybot::studyDec() {
	if (DEBUGGING) cout << "DBG: studyDec() called" << endl;

	if (!_hasMats) return false;
	if (!_validMats) return false;

	resetMats();

	int prevIdx = -2;
	int remQS = mats.size();
	string decision;
	while (remQS >= 0) {
		int randIdx = -1;
		while ((randIdx < 0) || (mats[randIdx].isAnswered == true || prevIdx == randIdx)) {
			if (remQS == 0) {
				randIdx = 0;
				break;
			}
			randIdx = randInRange(0, mats.size() - 1);
		}

		prevIdx = randIdx;

		decision = dispQandA(randIdx, remQS, true);
		if (decision == "") {
			mats[randIdx].isAnswered = true;
			remQS--;
		}
		else if (decision == "stop") break;
	}

	clearScr();

	if (decision != "stop")
		cout << "All questions answered! ";

	return true;
}

int Studybot::randInRange(int min, int max) {
	if (DEBUGGING) cout << "DBG: randInRange() called" << endl;

	int range = max - min + 1;
	return rand() % range + min;
}

string Studybot::dispQandA(int idx, int rem, bool isDec) {
	if (DEBUGGING) cout << "DBG: dispQandA() called" << endl;

	clearScr();
	cout << "Remaining questions: " << rem << endl << endl;
	cout << "Q. " << mats[idx].q << endl;

	cout << "A. ";
	waitForKeypress();

	clearScr();
	cout << "Remaining questions: " << rem << endl << endl;
	cout << "Q. " << mats[idx].q << endl;
	cout << "A. " << mats[idx].a << endl << endl;

	if (isDec) // Change to passing const &string to print if adding more study modes
		cout << "Did you get it right? (Press enter if yes, enter 'n' if no, 'stop' to stop): ";
	else 
		cout << "What next? (Press enter to continue, enter 'n' for new question, 'stop' to stop): ";
	string line;
	getline(cin, line);
	if (line == "\n") line = "";
	return line;
}

void Studybot::printAllQandA() {
	if (DEBUGGING) cout << "DBG: printAllQandA() called" << endl;

	if (!_validMats) return;

	for (const Flashcard& elem : mats) {
		cout << "Q. " << elem.q << endl << "A. " << elem.a << endl << endl;
	}
}

int Studybot::printFiles() {
	if (DEBUGGING) cout << "DBG: printFiles() called" << endl;

	int i = 0;
	cout << "Text file(s) found in current directory: " << endl;
	for (const auto& entry : dir_iter(fs::current_path())) {
		if (entry.path().extension() == ".txt") {
			i++;
			std::cout << i << ". " << entry.path().filename() << std::endl;
		}
	}
	if (i == 0) cout << "No files found." << endl;
	return i; // Return number of choices
}

void Studybot::getChoice(int lower, int upper) {
	if (DEBUGGING) cout << "DBG: getChoice() called" << endl;

	int studyChoice;
	cout << "Enter your choice (" << lower << '-' << upper << "): ";
	studyChoice = getIntFromUser();
	while (studyChoice < lower || studyChoice > upper) { // Loop while invalid
		cout << "Invalid. Please enter your choice (" << lower << '-' << upper << "): ";
		studyChoice = getIntFromUser();
	}
	clearScr();
	choiceIdx = studyChoice; // Return choice number
}

// Code by dark_shade, 2015, and Tin Svagelj, 2018.
int Studybot::getIntFromUser() {
	if (DEBUGGING) cout << "DBG: getIntFromUser() called" << endl;
	std::stringstream ss;

	ss.clear();
	ss.str("");

	string input = "";

	int n;

	if (!getline(cin, input))
		return -1;

	ss.str(input);

	if (ss >> n)
		return n;

	ss.clear();
	ss.str("");
	input.clear();

	return -1;
}

string Studybot::getFilename() {
	if (DEBUGGING) cout << "DBG: getFilename() called" << endl;
	int i = 0;
	for (const auto& entry : dir_iter(fs::current_path())) {
		if (entry.path().extension() == ".txt") {
			i++;
			if (choiceIdx == i) {
				return entry.path().filename().string();
			}
		}
	}
	return "";
}

void Studybot::clearScr() {
	if (DEBUGGING) {
		cout << "DBG: clearScr() called; skipping." << endl;
		return;
	}

	cout.flush();
	system(CLEARCMD);
}

bool Studybot::validMats() {
	if (DEBUGGING) cout << "DBG: validMats() called" << endl;
	return _validMats;
}

bool Studybot::hasMats() {
	if (DEBUGGING) cout << "DBG: hasMats() called" << endl;
	return _hasMats;
}

void Studybot::waitForKeypress() {
	if (DEBUGGING) cout << "DBG: waitForKeypress() called" << endl;
	cout.flush();
	//system(WAITCMD); // The old way to wait for user (system dependent)
	cout << "Press enter to continue...";
	string line;
	std::getline(cin, line);
	cout.flush();
}

bool Studybot::isSubstr(const string& sub, const string& str) {
	if (DEBUGGING) cout << "DBG: isSubstr() called" << endl;
	if (str.find(sub) != string::npos) {
		return true;
	}
	return false;
}
