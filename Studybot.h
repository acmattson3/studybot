// Studybot.h  
// Andrew C. Mattson
// 2023-02-27
//
// Personal Project
// Header file for Studybot

#ifndef FILE_Studybot_H_INCLUDED
#define FILE_Studybot_H_INCLUDED

/*** INCLUDES ***/
#include <iostream> // For cout, cin, endl
using std::cout;
using std::endl;
using std::cin;
#include <fstream> // For ifstream
using std::ifstream;
#include <filesystem> // for filesystem
namespace fs = std::filesystem;
#include <string> // For string, getline
using std::string;
using std::getline;
#include <utility> // For pair 
using std::pair;
#include <vector> // For vector
using std::vector;
#include <algorithm> // For sort
using std::sort;
#include <ctime> // For time
using std::time;
#include <cstdlib> // For srand, rand, system
using std::srand;
using std::rand;
using std::system;
#include <sstream> // For stringstream
using std::stringstream;

#include "Flashcard.h" // For class Flashcard


/*** CONSTANTS ***/
static const int DELIM_LEN = 4;
static const string DELIM = " !! "; // Separator between Q and A in txt files
static const int COMMENT_LEN = 2;
static const string COMMENT = "//"; // Indicator for a full-line comment

#if ( defined(WIN32) || defined(_WIN32) || defined(__WIN32) ) && !defined(__CYGWIN__)
static const char* CLEARCMD = "cls";
static const char* WAITCMD = "pause";
#else
static const char* CLEARCMD = "clear";
static const char* WAITCMD = "read";
#endif


// *********************************************************************
// class Studybot - Class definition
// *********************************************************************

// class Studybot
// Object to load and study questions and answers from txt files in a flashcard-like style.
// Exception-safe
// 
// Invariants: 
//   0 <= choiceIdx <= the total number of text files in the current directory (0 when no choices)
class Studybot
{
/*** TYPE DEFINITIONS ***/
public:
	// Directory iterator type (not random-access)
	typedef fs::directory_iterator dir_iter;

/*** PRIVATE MEMBER VARIABLES ***/ 	
private: 
	int choiceIdx; // User's chosen file from the list
	//vector<pair<string, string>> mats; // Old mats vector
	vector<Flashcard> mats;
	//vector<int> answered; // Old answered vector
	bool _validMats;
	bool _hasMats;

/*** CTORS ***/
public: 
	// Default ctor
	// Asks the user to select a file to load into memory.
	// Preconditions: None
	// Strong Guarantee
	Studybot();

/*** PUBLIC MEMBER FUNCTIONS ***/
public: 
	// Allows the user to select a new file to study from.
	// Preconditions: None
	// Strong Guarantee
	void newChoice();

	// Studies the loaded materials decrementally (removes the known questions).
	// Preconditions: None
	// No-Throw Guarantee
	bool studyDec();

	// Studies the loaded materials incrementally (adds more questions as you get to know them).
	// Preconditions: None
	// No-Throw Guarantee
	bool studyInc();

	// Prints all loaded questions and answers.
	// Preconditions: None
	// No-Throw Guarantee
	void printAllQandA();

	// Print the available files to choose from.
	// Preconditions: None
	// Strong Guarantee
	int printFiles();

	// Clear the screen. Just a wrapper around system(CLEARCMD).
	// Preconditions: None
	// No-Throw Guarantee
	void clearScr();

	// Returns true or false depending on if valid materials are loaded into memory.
	// Preconditions: None
	// No-Throw Guarantee
	bool validMats();

	// Returns true or false depending on if there are text files in the current directory
	// Preconditions: None
	// No-Throw Guarantee
	bool hasMats();

/*** PRIVATE MEMBER FUNCTIONS ***/
private: 
	// Loads a selected file into memory.
	// Preconditions: 
	//   filename must be the name of a valid txt file
	// Strong Guarantee
	void setMats(string filename);

	// Returns a random number from min to max inclusively.
	// Preconditions: 
	//   min <= max
	// No-Throw Guarantee
	int randInRange(int min, int max);

	// Used by the "studyXXX" functions to display questions and answers to users and receive their input.
	// Preconditions: 
	//   0 <= idx <= mats.size() - 1
	// No-Throw Guarantee
	string dispQandA(int idx, int rem, bool isDec);

	// Repeatedly asks a user for a value until it is within the defined min-max range.
	// Preconditions: 
	//   1 <= lower <= upper
	// No-Throw Guarantee
	void getChoice(int lower, int upper);

	// Given a file's index (determined alphabetically, 1 to n), return the name of the file. 
	// Preconditions: None
	// Strong Guarantee
	string getFilename();

	// Returns true if sub is a substring of str.
	// Preconditions: None
	// No-Throw Guarantee
	bool isSubstr(const string& sub, const string& str);

	// Waits for a user to press any key. Just a wrapper around system(WAITCMD).
	// Preconditions: None
	// No-Throw Guarantee
	void waitForKeypress();

	// Requests an integer from the user. Returns -1 given invalid input.
	// Preconditions: None
	// No-Throw Guarantee
	int getIntFromUser();
}; // End of class Studybot

#endif // #ifndef FILE_Studybot_H_INCLUDED
