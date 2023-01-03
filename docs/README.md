# Wordle solver #

The purpose of this program is to solve the wordle, in both
an independent and interactive format. In independent mode, the 
user provides a word for the computer to guess, and the computer 
will use a ranking algorithm to guess the word (see the "best word" 
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
* __wordle.cpp__: this file controls the mode chosen by the user and calls 
the functions associated with each mode.
* __modes.cpp__: this file contains the function definitions for the two main 
modes, sets the overall variables that those functions rely on and loops over 
the most important sub-functions, which do the bulk of the calculating and 
ranking work.
* __functions.cpp__: this file contains all of the most important functions 
that modes.cpp relies upon, including the "best word" algorithm that 
ranks the utility of guesses and the routines which compare the current 
guess to the hidden word.
* __subroutines.cpp__: this file contains all of the small functions that 
functions.cpp relies upon. All of the functions in this file are independent 
of the other files. It is here, and here only, that header.cpp is included (to 
avoid double declarations). In this file you can find many of the debugging tools 
I've written (see "debugging functionality" below) as well as functions that 
return comparisons between the hidden word and the guess word, and 
functions that eliminate candidate "best words" based on the information 
in current and previous guesses.

There are a few important auxiliary files as well.
* __header.cpp__: this file contains all imported c++ standard header files 
as well as all global variables.
* __tools/tests.cpp__: this contains all testing routines that are run 
before commits to this program can be pushed to Github, by testing the  
output from most of the functions in subroutines.cpp for consistency.

Below, I describe how some of the most important functions in this code work. 
If you have any questions/comments/bug reports, please reach out to me 
via Github or at eaf49@cam.ac.uk. Good luck!

## To run the program ##



## A run in interactive mode ##

Both interactive mode and independent mode are constructed quite similarly. 
Independent mode simply consists in the computer providing its own 
starting word, comparing against the word provided by the user, and 
determining a new best guess using "best word" function. For that reason I will 
describe here the overall working of interactive mode only.

In this mode, the computer starts by receiving a starting word from 
the user, either their own starting word or the "best" starting word. The 
computer then chooses a hidden word from the list of accepted words provided 
in docs/WordleWords.txt, using the current clock time to seed the random number 
generator from the _cstdlib_ package. The computer then allocates memory to an 
array used to store the previous guesses of the user.

__Important__: in order to allocate only a reasonable amount of memory to the 
previous guess array, the maximum number of rounds that can be played is set 
in modes.cpp (currently at 100 rounds). If this number is exceeded, the program 
will exit and throw the appropriate error. In interactive mode this limit is 
set in the program files, but in independent mode this values is provided by the 
user.

If the user has guessed the hidden word on the first try, the program will 
congratulate them and exit. If not, the main routine is called -- here, the 
computer initialises four important variables:
* __position__ -- this is a string of length 5 which holds all of the letters 
that have been guessed and are in the correct position, and places zeroes in 
those locations which have not been correctly guessed. So, for example, if 
the user guesses "opens" and the hidden word is "brent" then the position variable 
for that round will be "00en0".
* __in_word__ -- this is a string of variable length which holds all letters 
that have been guessed which are in the hidden word but not in the right 
position. For instance, if the user guesses "oboes" and the hidden word is 
"brent" then the in_word variable for that round will be "be".
* __position_complement__ -- this variable refers to the mathematical definition of 
a complement as the set of elements not contained by a given set, because it 
uses the position variable to determine which letters in the guess word have 
been eliminated as being in the hidden word. This variable also stores 
letters that have been ruled out by previous guesses. So for instance, if 
in a given round the guess word is "crown" and the hidden word is "brent", 
then the position_complement will return "cow". Note that the complement is 
only printed to terminal every round if the debug flag is turned on (see the 
debugging section below for more details).
* __new_guesses__ -- this is an array of strings, which contains all of the 
next possible guesses that the user can choose from. It is generated using the 
new_guess_array function in functions.cpp, which eliminates words from the 
possible list of guesses using the information in position, in_word and 
position_complement. This array then forms the basis from which the next 
best 5 guesses are determined and printed to the terminal. Note that 
if a word is eliminated as a new guess, it is replaced in the new_guess array 
by an empty string.

The program first determines the position, in_word and position_complement variables 
for a given guess. It then fills in the new_guesses array using the new_guess_array 
function, ranks the words in new_guesses and returns the best 5. The new_guess_array 
adds a word to the array if it contains letters in the in_word variable, and 
eliminates a guess from the array if:
1. it does not contain letters in the right position, according to position,
2. it was previously guessed, or 
3. it contains a letter that has been eliminated by current or previous guesses.

The program then asks the user to guess a new word, and the program loops all 
over again. The program will exit only if the user guesses the right word, or if 
the user exceeds the number of allowed rounds.


## The "best word" function ##

The "best word" function, found in functions.cpp, is used throughout the 
program to rank words from an array of strings.

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