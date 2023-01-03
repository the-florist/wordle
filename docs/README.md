# Wordle solver #

The purpose of this program is to solve the wordle, in both
an independent and interactive format. In independent mode, the 
user provides a word for the computer to guess, and the computer 
will use a ranking algorithm to guess the word (see the "best start" 
function below). In interactive mode, the computer will generate 
a hidden word and the user will guess the word. In this mode, 
the user can either supply their own first word, or they can use a 
good first word recommended by the computer. The computer will 
also provide a list of the next "best guesses" using the ranking 
algorithm to help the user out (currently the computer provides 
5 of these hints, but this number can be easily changed. See line 
59 in modes.cpp).

This program is written in tree format, with four main files where 
most of the computation is performed.
* wordle.cpp: this file controls the mode chosen by the user and calls 
the functions associated with each mode.
* modes.cpp: this file contains the function definitions for the two main 
modes, sets the overall variables that those functions rely on and loops over  
the most important sub-functions, which do the bulk of the calculating and 
ranking work.
* functions.cpp: this file contains all of the most important functions 
that modes.cpp relies upon, including the "best start" algorithm that 
ranks the utility of guesses and the routines which compare the current 
guess to the hidden word.
* subroutines.cpp: this file contains all of the small functions that 
functions.cpp relies upon. All of the functions in this file are independent 
of the other files. It is here, and here only, that header.cpp is included (to 
avoid double declarations). In this file you can find many of the debugging tools 
I've written (see "debugging functionality" below) as well as functions that 
return comparisons between the hidden word and the guess word, and 
functions that eliminate candidate "best words" based on the information 
in current and previous guesses.

There are a few important auxiliary files as well.
* header.cpp: this file contains all imported c++ standard header files 
as well as all global variables.
* tools/tests.cpp: this contains all testing routines that are run 
before commits to this program can be pushed to Github, by testing the  
output from most of the functions in subroutines.cpp for consistency.

Below, I describe how some of the most important functions in this code work. 
If you have any questions/comments/bug reports, please reach out to me 
via Github or at eaf49@cam.ac.uk. Good luck!

## A run in interactive mode ##

## The "best start" function ##

This function takes the list of all possible words and decides 
which one is the best word to start the game off with. To do this, 
it counts how many times each letter of the alphabet shows up in 
each position of the word, and divides by the total number of words, 
giving a rough "likelyhood" of each letter showing up in each location.

The program then takes each word and adds up this probability value for 
each letter which appears in the word. This total score is then used to 
rank words for their "generality", i.e. the likelyhood that the letters 
appearing in the word will appear in that place in a randomly generated 
word. This word is then given as the best option to start with.

IMPORTANT: This function ranks words based on how common their individual 
letters are, *not* how common the word itself is. I don't currently have 
the data to add this feature but I suspect it would improve the accuracy 
of the ranking algorithm significantly.

## Debugging functionality ##

## Structure of testing protocol ##

## Docker use and contents ##
### OS requirements ###

## Future improvements and known bugs ##

## Notes to self ##
Remaining tasks:

2. finish all the documentation (README and repo description mainly)
3. write 3,000 word report

Future improvements:
1. Make the all_words and total vars global -- will need to check that these 
are never altered by the program, but should improve speeds by a lot in 
various functions.

Bugs:
1. Sometimes the word suggestion algorithm prints multiple of the next word 
if you've narrowed it down to less than five words... not sure why it started 
doing this...