/*******
 * This file contains all functions which depend on the subroutines in subroutines.cpp. 
 * There are four main functions here:
 * 1. new_guess_array returns a new candidate based upon info gathered from current and past guesses.
 * 2. best_word returns the nth "best" word from an array (see README for justification of this classification method).
 * 3. narrow_down is the basic routine for independent mode, by generating a new best guess based on previous information.
*******/

//#include "header.hpp"
#include "subroutines.cpp"

string new_guess_array(string word_from_array, string guess_word, string in_word, string temp, string temp_comp, string previous[], int previous_len) 
{
    /*
    Entry key:
    1. a word from a list; either all_words if no letters are correct, or a candidate with correct letters in the right position.
    2. the current guess.
    3. string with floating letters in it.
    4. string with those letters in the correct position (or "00000").
    5. string with all eliminated letters.
    6. array of all previous guesses.
    7. the maximum number of rounds.
    */

    string new_guess = "";          //candidates
    string in_word_temp = in_word;  //letters in the word, that I can alter in the function

    //this counts the number of floating letters in the candidate
    if (word_from_array != "")
    {
        int count = 0;
        for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
        {
            if (temp[l] == zero[0] && word_from_array[l] == in_word_temp[ll]) 
            {
                in_word_temp[ll] = zero[0];
                count++;
            }
            else
            {
                continue;
            }
        }

        //This approves a candidate if it contains all floating letters
        if (word_from_array == guess_word)
        {
            new_guess = "";
        }
        else if (count == in_word.length())
        {
            new_guess = word_from_array;
        }
        else 
        {
            new_guess = "";
        }

        //This eliminates a candidate if it is a previous guess or it contains eliminated letters
        new_guess = position_remover(guess_word, new_guess, temp);
        new_guess = prev_guess_remover(previous_len, previous, new_guess, word_from_array);
        new_guess = eliminated_letter_remover(temp, temp_comp, new_guess);
    }

    return new_guess;
}

string best_word(int total, string word_array[], int nth)
{
    /**********
    Entry key:
    1. Total number of words accepted by the game (default is 12947)
    2. An array containing all of these words in string format
    3. The nth best word you would like (i.e. first best, second best, etc.)
    **********/
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    float prob[26][6];                                  //first index counts the letter, second counts its position
    float score[total];                                 //array that stores the score values
    int count = 0;

    for (int w=0; w<total; w++) 
    {
        score[w] = 0.;
    }

    //This calculates the probabilities for each letter of the alphabet as a function of word position.
    for (int a=0; a<26; a++) for (int l=0; l<6; l++) 
    {
        for (int w=0; w<total; w++) 
        {
            if (alphabet[a] == word_array[w][l])
            {
                count++;
            }
            else
            {
                continue;
            }
        }
        prob[a][l] = (float)count/total;
        count = 0;
    }

    //This calculates the total score for each word
    for (int w=0; w<total; w++) for (int l=0; l<6; l++) for (int a=0; a<26; a++) 
    {

        if (alphabet[a] == word_array[w][l])
        {
            score[w] += prob[a][l];
        }
        else if (word_array[w] == "")
        {
            score[w] = 0.;
        }
        else 
        {
            continue;
        }

    }

    int best_index = nth_best(total, score, nth);
    return word_array[best_index];
}


//FIXME
string narrow_down(string guess_word, string hidden_word, string prev_guesses[], int prev_guess_len, int total, string all_words[]) 
{
    /*
    What this function does:
    1. figure out which of the letters appear
    2. generate a new guess list based on which letters are right
        and which do appear
    3. decide which is the best word from that guess list
    4. compare the strings to determine how many letters are correct/appear
    5. if the strings are equal, exit. If not, repeat the process.
    */
    
   //finding the letters in correct positions, correct letters, and letters that have been eliminated.
    string temp = letters_in_position(guess_word, hidden_word);
    string in_word = letters_elsewhere(guess_word, hidden_word, temp);
    string temp_complement = letters_in_position_comp(guess_word, hidden_word, in_word);


    string new_guesses[total];
    for (int i=0; i<total; i++)
    {
        new_guesses[i] = "";
    }

    //gather the candidates, depending on if any letters are in the correct position
    for (int w=0; w<total; w++) 
    {
        if (temp == "00000")
        {
            new_guesses[w] = new_guess_array(all_words[w], guess_word, in_word, temp, temp_complement, prev_guesses, prev_guess_len);
        }

        else
        {
            new_guesses[w] = new_guess_array(make_position_guesses(w, all_words, temp), guess_word, in_word, temp, temp_complement, prev_guesses, prev_guess_len);
        }
    }

    //finds the next best word to guess from the candidates, using the best_word function
    string best_new_word = best_word(total, new_guesses, 1);
    return best_new_word;
}
