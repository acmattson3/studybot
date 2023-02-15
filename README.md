# studybot
A program that, given any text (.txt) file in its current directory (and preferably in the defined format), will read each line as a question and its corresponding answer. The program lets you "study" the questions and answers in one of two ways:
1. Decremental Mode - Start with every question, and remove questions when you're comfortable with them (traditional flashcard style).
2. Incremental Mode - Start with one question, and add them as you feel comfortable with the ones you have.

As an example of how to use each mode, I use the decremental mode for studying, as the format is like that of flashcards. I use the incremental mode when learning new things, as the format is like that of most traditional academic classes (start with chapter one, then add chapter two, etc).

# How to use: 
Place text files in the same directory as the program. Each line should be formatted with ' !! ' between the questions and their corresponding answers. Any line containing '//' will be considered a "comment line" and will not show up in the questions and answers loaded into the program. 

**Note:** The comment character and Q/A delimiter (the thing separating the questions and answers on each line) are defined in Studybot.h if you wish to change them).

## Example:
**Filename:** *example.txt*

**Contents:**
```
What is the answer? !! This is the answer!
// This is a comment line!
This is also a comment line! //
This is /// also a comment line!
What is the meaning of life? 
```
**The following questions and answers will be loaded:**

1. **Q.** What is the answer? **A.** This is the answer!

2. **Q.** What is the meaning of life? **A.** No answer provided.
