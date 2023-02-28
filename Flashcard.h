#include <string>
using std::string;

class Flashcard {
public:
	string q; // Question
	string a="No answer provided"; // Answer
	bool isAnswered;
	
    Flashcard(string question, string answer="No answer provided.") : q(question), a(answer), isAnswered(0) {}
};