ext := o
ifeq ($(OS),Windows_NT)
	ext := exe
endif

all:
	@echo Compiling...
	@g++ -o studybot.$(ext) Studybot.cpp Studybot.h Flashcard.h Studybot_main.cpp
	@echo Success! The output file is called studybot.$(ext)

test: # Intended for developer use.
	g++ -o studybot.test Studybot.cpp Studybot.h Flashcard.h test_main.cpp