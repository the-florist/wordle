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

This program is run off of the makefile that I've included in the main folder. 
To compile and run the program, nagivate to the "wordle" directory and run "make 
run." If you would like to simply compile the code, run "make main." If you would 
like to clean up the directory (of old executibles, etc.) run "make clean," and 
if you would like to run tests locally, run "make test." You may also compile and run 
the program in the standard way using the wordle.cpp file as the main file.

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
program to rank words from an array of strings. The function adds up the number 
of times each letter in the alphabet shows up in each position (1-5) for 
a given word, then divides this number (calculated for each position) 
by the total number of words. This gives a sort of "probability measure" 
for how likely a given letter is likely to appear in a given position 
in the word. The program then determines a given word's "score" by adding 
up the probability values for each letter in the word, for that position. 
The word with the highest score is said to be in some sense the "best" 
word of the array.

Note, however, that this function ranks words based on how common their individual 
letters are, *not* how common the word itself is. I don't currently have 
the data to add this feature but I suspect it would improve the accuracy 
of the ranking algorithm significantly. In addition, this algorithm values 
accuracy over diversity i.e. it does not select for words that have unique 
letters, which may give the user more information from which to make future guesses.

## Debugging functionality ##

I have added many of the most common features I used to debug this program 
in as options during writing and debugging. To turn on all of the debugging 
options, set the *debug* global flag in header.cpp to 1. This will, for 
instance, print the complement for each round to the terminal, and allow 
the programmer to specify their own hidden word (which I found particularly 
useful while learning how to calculate *position*, *in_word*, etc.). Turning 
on the debug flag will also generate a text file at the end of the run, stored 
in the tools/ directory, which will contain all of the information gathered by 
the program during every run. There also exists a separate flag which can 
control whether the main, interactive bulk of the program is run -- so 
for instance, if you would like to run a specific function but skip the 
intro messages, etc., then you can alter lines 18-32 in wordle.cpp to turn off 
the *run_main* flag.

## Structure of the testing protocol ##

The testing protocol laid out in tools/tests.cpp represents a set of 
conditions that this program must pass before it can be pushed onto the 
public git repository. The tests file examines most of the functions in 
the subroutines.cpp file, focusing on those which do the heart of the 
calculation of the program and skipping those which directly interact with 
external files that may not exist (such as *print_to_debug_file*) or which 
print to the terminal (such as *print_string_list*).

All of the tests involve comparing the output of a function to the value 
that it must return for the program's logic to work. To do this it gives 
sample hidden and guess words to each function -- the word choice here 
is not significant, but the words have been chosen to produce the expected 
outcome in the program. Both empty returns (for instance, the combination 
of "boats" and "growl" for the *letters_in_position* function giving "00000") 
and partially filled returns (such as the combination in the same function of 
"bools" and "growl" giving "00o00") have been tested. If a function passes 
it's tests, a message will print to the screen showing this result. If a 
function fails a test, the program exits and a message is printed to the screen 
giving the name of the function that failed and a number indicating which 
condition the function failed.

If you decide to alter the testing protocol, __please do so very carefully__. 
The protocol is currently constructed to test each function properly, and 
altering these routines may produce errors where none exist.

## Docker use and contents ##

This program is primarily built using the standard c++ library and 
functions, so any device which can read this language should be able 
to run the program. However, if you are working on a device with an 
unfamiliar OS or cannot get the code to compile, I've included a Dockerfile 
in tools/ which can be used to create a virtual environment from which 
this program should run. 

Currently the Docker file sets up the most basic Alpine Linux system with 
vim, git and gcc added in. To use this Docker file, you must first build 
the docker system by navigating to the wordle/ directory and running:

$ docker build -t alpine_main . 

This will create an image, which can be activated using the command: 

$ docker run --rm -ti alpine_main

which will generate a detached terminal accessible via command line input. 
The Dockerfile as currently configured will drop the user into the home/ directory, 
where the wordle/ directory has been cloned off of github. To run the program, 
change into this wordle/ directory *first*, then run the program as described above. 
Note that once you exit this environment, it will be deleted, so if there are any 
changes you wish to save, do push them to the github before exiting the environment!

## Future improvements and known bugs ##

To improve this code in the future, I am looking to alter 
the structure so as to make the *words[]* and *tot* variables global -- 
this way, all functions can access these variables once they are set, 
and the program does not need to call on them in every instance of a 
function which needs them (which is most of the functions). In addition 
I am considering changing the ranking algorithm to better match 
how humans tend to play the game, such as weighing a word according to 
the diversity of letters it contains and the relativy commonality of 
those letters.

There are also a few bugs of which I am currently aware of. The first 
is that the "round count" variable, which counts how many iterations 
are needed to determine the hidden word in independent mode, often returns 
very low numbers, lower than one may expect from similar games played in 
interactive mode. It is possible that this variable is working as 
expected (and the computer is just very fast), but I do suspect this 
counter is not iterating correctly, or not iterating on every round.

In addition, I have had issues opening the debug output file in some editors 
as the *position_complement* variable can sometimes contain non-standard 
characters. If you run into this problem, consider opening the debug output 
file using a simple text editor, making notes of which characters can be ignored. 
Finally, in the last few rounds of interactive mode, when there are less than 5 best 
words remaining, the program will print the least best of these words multiple times. 
Again I am not sure what is causing this issue, but it seems to affect merely 
how the program looks in the terminal, and not it's overall performance.

If you find any bugs (particularly more serious ones) in addition to these, 
or suspect that one of these bugs may point to a larger issue with this 
program, please reach out to me using the contact details provided above.

Enjoy!

### Resources ###

I used advice from the following websites to help me build the Docker 
environment using the apk function: 
1. https://stackoverflow.com/questions/58392792/how-to-download-git-only-on-docker
2. https://wiki.alpinelinux.org/wiki/GCC 