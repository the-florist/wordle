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
* __wordle.cpp__: this file calls the functions associated with each mode.
* __modes.cpp__: this file contains the functions for the two main 
modes and loops over the most important sub-functions, which do the 
bulk of the calculating and ranking work.
* __functions.cpp__: this file contains the most important functions 
that modes.cpp relies upon, including functions that apply information 
from current and previous guesses to determine good future guesses.
* __subroutines.cpp__: this file contains all of the small functions that 
functions.cpp relies upon. All of the functions here are independent 
of the other files. It is here, and here only, that header.cpp is included (to 
avoid double declarations). Here you can find many of the debugging tools 
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

Below, I describe how to run the code on terminal and using Docker, as well 
as any known bugs and planned improvements to the program. For more thorough 
documentation on the inner workings of the program, see the Report.pdf file in docs/. 
If you have any questions/comments/bug reports, please reach out to me 
via Github or at eaf49@cam.ac.uk. Good luck!

## To run the program ##

This program is run off of the makefile that I've included in the main folder. 
To compile and run the program, nagivate to the "wordle" directory and run "make 
run." If you would like to simply compile the code, run "make main." If you would 
like to clean up the directory (of old executibles, etc.) run "make clean," and 
if you would like to run tests locally, run "make test." You may also compile and run 
the program in the standard way using the wordle.cpp file as the main file.

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