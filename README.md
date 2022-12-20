# Wordle solver #

The purpose of this program is to solve the wordle, in both
an independent and interactive format. In independent mode, the 
user provides a word for the computer to guess, and the computer 
will use (----- analysis) to guess the word. In interactive mode,
the computer will generate a hidden word and the user will have to 
guess the word. In this mode, the user can either supply their own 
first word, or they can use a good first word recommended by the 
computer.

This program is written in three main sections. First the program sets 
all of the variables and arrays that it will need at the start, and scans 
in the complete list of acceptable wordle words. Then the program asks the 
user which mode they would like to play in. Then the user will enter one 
of two subroutines:

1. Independent. Here, the user will first enter a word for the computer to 
guess ---

2. Interactive. Here, 

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

To-dos:
1. put two new guess array generators into functions file
2. test these out to make sure they work here
3. finish the interactive function
4. (new branch) put the new subroutines into the independent function