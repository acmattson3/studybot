// Flashcard.h  
// Andrew C. Mattson
// 2023-02-13
//
// Personal Project: Flashcard Class
// Header file for Flashcard

#include <string>
using std::string;


// class Flashcard
// Object containing the information a standard flashcard would contain (question, answer, and if it's being studied)
// Exception-safe
// 
// Invariants: 
//   0 <= choiceIdx <= the total number of text files in the current directory (0 when no choices)
class Flashcard {
public:
	string q; // Question
	string a="No answer provided"; // Answer
	bool isAnswered; // Whether or not the card in in the "pile"
	
    Flashcard(string question, string answer="No answer provided.") : q(question), a(answer), isAnswered(false) {}
};