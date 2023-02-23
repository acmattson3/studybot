// Studybot.cpp
// Andrew C. Mattson
// 2023-02-13
//
// Personal Project
// Source file for Studybot.h

#include "Studybot.h"


Studybot::Studybot() : choiceIdx(1) {
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
	}
}

void Studybot::newChoice() {
	if (!_hasMats) return;
	clearScr();
	int maxChoices = printFiles();
	if (maxChoices > 1) getChoice(1, maxChoices);
	else if (maxChoices == 1) {
		cout << "Only one file choice available (you get to study that one)" << endl;
		waitForKeypress();
	}
	setMats(getFilename());
}

void Studybot::setMats(string filename) {
	mats.clear();
	answered.clear();

	ifstream file(filename);
	string line;
	while (std::getline(file, line)) { // For every line in file
		if (line.length() > 0 && isSubstr(COMMENT, line)) {
			int commentPos = line.find(COMMENT);
			line = line.substr(0, commentPos);
		}
		if (line.length() > 0) { // Remove empty lines
			if (isSubstr(DELIM, line)) { // If answer given
				int delimPos = line.find(DELIM);
				string question = line.substr(0, delimPos);
				string answer = line.substr(delimPos + DELIM_LEN, line.length() - (delimPos + DELIM_LEN));
				mats.push_back(pair<string, string>(question, answer));
			}
			else { // If no answer given
				mats.push_back(pair<string, string>(line, "No answer provided."));
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
		for (int i = 0; i < mats.size(); i++) {
			answered.push_back(0);
		}
	}
}

bool Studybot::studyInc() {
	if (!_hasMats) return false;
	if (!_validMats) return false;

	int prevIdx = -2;
	int currQS = 1;
	int remQS = mats.size() - 1;
	string decision;
	while (remQS >= 0) {
		if (currQS <= answered.size()) // Maybe redundant
			answered[currQS - 1] = 1; // Start studying first Q

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
		answered[i] = 0;
	}

	clearScr();

	if (decision != "stop" && remQS <= 0)
		cout << "All questions answered! ";

	return true;
}

bool Studybot::studyDec() {
	if (!_hasMats) return false;
	if (!_validMats) return false;

	int prevIdx = -2;
	int remQS = mats.size() - 1;
	string decision;
	while (remQS >= 0) {
		int randIdx = -1;
		while ((randIdx < 0) || (answered[randIdx] == 1 || prevIdx == randIdx)) {
			if (remQS == 0) {
				randIdx = 0;
				break;
			}
			randIdx = randInRange(0, mats.size() - 1);
		}

		prevIdx = randIdx;

		decision = dispQandA(randIdx, remQS, true);
		if (decision == "") {
			answered[randIdx] = 1;
			remQS--;
		}
		else if (decision == "stop") break;
	}

	for (int i = 0; i < mats.size(); i++) {
		answered[i] = 0;
	}

	clearScr();

	if (decision != "stop")
		cout << "All questions answered! ";

	return true;
}

int Studybot::randInRange(int min, int max) {
	int range = max - min + 1;
	return rand() % range + min;
}

string Studybot::dispQandA(int idx, int rem, bool isDec) {
	clearScr();
	cout << "Remaining questions: " << rem << endl << endl;
	cout << "Q. " << mats[idx].first << endl;

	cout << "A. ";
	waitForKeypress();

	clearScr();
	cout << "Remaining questions: " << rem << endl << endl;
	cout << "Q. " << mats[idx].first << endl;
	cout << "A. " << mats[idx].second << endl << endl;

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
	if (!_validMats) return;

	for (const pair<string, string>& elem : mats) {
		cout << "Q. " << elem.first << endl << "A. " << elem.second << endl << endl;
	}
}

int Studybot::printFiles() {
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

void Studybot::clearScr()
{
	cout.flush();
	system(CLEARCMD);
}

bool Studybot::validMats()
{
	return _validMats;
}

bool Studybot::hasMats()
{
	return _hasMats;
}

void Studybot::waitForKeypress()
{
	cout.flush();
	system(WAITCMD);
}

bool Studybot::isSubstr(const string& sub, const string& str) {
	if (str.find(sub) != string::npos) {
		return true;
	}
	return false;
}