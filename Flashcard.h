// Flashcard.h  
// Andrew C. Mattson
// 2023-02-27
//
// Personal Project: Flashcard Class
// Header file for Flashcard

#ifndef FILE_Flashcard_H_INCLUDED
#define FILE_Flashcard_H_INCLUDED

/*** INCLUDES ***/
#include <string>
using std::string;


// *********************************************************************
// class Flashcard - Class definition
// *********************************************************************

// class Flashcard
// Object containing the information a standard flashcard would contain (question, answer, and if it's being studied)
// Exception-safe
// 
// Invariants: None
class Flashcard {
/*** PUBLIC MEMBER VARIABLES ***/
public:
	string q; // Question
	string a; // Answer
	bool isAnswered; // Whether or not the card is being studied.
	
/*** CTORS ***/
public:
    // Ctor given question and (optionally) an answer
	// Loads the passed information into the object.
	// Preconditions: None
	// No-Throw Guarantee
    Flashcard(string question, string answer="No answer provided.") : q(question), a(answer), isAnswered(false) {}
}; // End of class Flashcard

#endif // #ifndef FILE_Flashcard_H_INCLUDED
