# studybot
This is a program that, given any text (.txt) file in its current directory (and preferably in the defined format), will read each line as a question and its (optional) corresponding answer. If the program's current directory has multiple text files, you will be prompted to choose one. After that, the program lets you "study" the questions and answers in one of two ways:
1. **Decremental Mode** - Start with every question, and remove questions when you're comfortable with them (traditional flashcard style).
2. **Incremental Mode** - Start with one question, and add them as you feel comfortable with the ones you have.

As an example of how to use each mode, I use the decremental mode for studying, as the format is like that of flashcards. I use the incremental mode when learning new things, as the format is like that of most traditional academic classes (start with chapter one, then add chapter two, etc).

# How To Use
Place text files in the same directory as the program. Each line should be formatted with ' !! ' between the questions and their corresponding answers. Any text on a line following a '//' will be excluded from the line (works as a traditional C++ comment). Blank lines are skipped. If '\n' is found in your string, it will be replaced with a newline character, allowing for questions and answers with multiple lines.

## Example:
**Filename:** *example.txt*

**Contents:**
```
What is the answer? !! This is the answer!
// This is a comment line!

// This is /// also a comment line!
What is the meaning of life? 
2 + 2 = ? !! 2 + 2 = 4 // This is also a comment!

What is a\nnewline? !! This\nis a newline!
```
**From this file, the following questions and answers will be loaded:**

1. **Q.** What is the answer? **A.** This is the answer!

2. **Q.** What is the meaning of life? **A.** No answer provided.

3. **Q.** 2 + 2 = ? **A.** 2 + 2 = 4

4. **Q.** What is a

newline?

**A.** This

is a newline!

**Note:** The comment character and Q/A delimiter (the thing separating the questions and answers on each line) are defined in Studybot.h if you wish to change them.

## Compilation:
The best way to compile studybot is using the included makefile. Simply run the "make" command in the terminal (assuming make is installed) and execute the resulting file (the prompt resulting from the make command will tell you the filename). For Windows users, this assumes you have make installed on your system, which may be difficult (keep reading).

I highly recommend using WSL if you are a Windows user!

Alternatively, compile it yourself (possibly easier for Windows users in Powershell or CMD) using your favorite compiler (For example, using g++: ```g++ Studybot.h Studybot.cpp Studybot_main.cpp Flashcard.h -o myStudybot.exe```).

Now you can get your study on! My code should work on Windows, Mac, and Linux (if you run into problems, please submit a detailed issue report).

## Lore..?
I originally wrote this program *very* poorly in Python a couple years ago. This year, I needed to study in a flashcard-like style, preferably without the writing. When I tried using my old studybot, the thing was an *absolute mess* of bugs and crashes. As a result, I chose to rewrite the program as professionally as possible to best avoid bugs. I chose to rewrite it in C++ to make things as explicit as possible so I can change things in the future.

## Future Goals
* Make a question "marking" feature so that, as you study, you can mark questions
  * The questions would be displayed at the very end either when you finish all materials or stop studying. 
  * Useful for marking questions with typos to be fixed later, or for remembering which questions to write down/work on later.
* Make a saving feature that saves remaining questions to be studied later.
  * Possible implementation: When the user enters "stop," ask them if they want to save. If they do, create a new txt file called "filename_save" where filename is the name of the text file being studied. For the decremental mode, enter the current remaining questions into this new txt file. When the save file is done being studied, the file is deleted.
* Make intuitive GUIs
  * Studying GUI with ability to click instead of using terminal
  * Note-taking GUI to avoid semi-gross format of text file (wouldn't have to deal with delimeters or having to type '\n')
