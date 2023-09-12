all:
	g++ -o studybot.o Studybot.cpp Studybot.h Flashcard.h Studybot_main.cpp 
test:
	g++ -o studybot.o Studybot.cpp Studybot.h Flashcard.h test_main.cpp 