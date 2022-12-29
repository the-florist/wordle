/*******
 * This file contains all functions which depend on the subroutines in subroutines.cpp. 
 * There are four main functions here:
 * 1. new_guess_array returns a new candidate based upon info gathered from current and past guesses.
 * 2. best_word returns the nth "best" word from an array (see README for justification of this 
        classification method).
 * 3. narrow_down is the basic routine for independent mode, by generating a new best guess based on 
        previous information.
*******/

#include "subroutines.cpp"

string new_guess_array(string guess_word, string word_from_array, string pos, string lets_in_word, string pos_comp, string previous[], int previous_len) 
{
    /*
    Entry key:
    1. a word from a list; either all_words if no letters are correct, or a candidate with 
        correct letters in the right position.
    2. the current guess.
    3. string with floating letters in it.
    4. string with those letters in the correct position (or "00000").
    5. string with all eliminated letters.
    6. array of all previous guesses.
    7. the maximum number of rounds.
    */

    string new_guess = "";          //candidates
    string lets_in_word_temp = lets_in_word;  //letters in the word, which can be altered in the function

    //this counts the number of floating letters in the candidate
    if (word_from_array != "")
    {
        int count = 0;
        for (int l=0; l<6; l++) for (int ll=0; ll<lets_in_word.length(); ll++)
        {
            if (pos[l] == zero[0] && word_from_array[l] == lets_in_word_temp[ll]) 
            {
                lets_in_word_temp[ll] = zero[0];
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
        else if (count == lets_in_word.length())
        {
            new_guess = word_from_array;
        }
        else 
        {
            new_guess = "";
        }

        /*This eliminates a candidate if it does not contain letters in the right position,
            if it is a previous guess, or if it contains eliminated letters.*/
        new_guess = position_remover(guess_word, new_guess, pos);
        new_guess = prev_guess_remover(new_guess, word_from_array, previous_len, previous);
        new_guess = eliminated_letter_remover(new_guess, pos, pos_comp);
    }

    return new_guess;
}

string best_word(int nth, int total_words, string word_array[])
{
    /**********
    Entry key:
    1. Total number of words accepted by the game (default is 12947)
    2. An array containing all of these words in string format
    3. The nth best word you would like (i.e. first best, second best, etc.)
    **********/
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    float prob[26][6];                              //first index counts the letter, second counts its position
    float score[total_words];                             //array that stores the score values
    int count = 0;

    for (int w=0; w<total_words; w++) 
    {
        score[w] = 0.;
    }

    //This calculates the probabilities for each letter of the alphabet as a function of word position.
    for (int a=0; a<26; a++) for (int l=0; l<6; l++) 
    {
        for (int w=0; w<total_words; w++) 
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
        prob[a][l] = (float)count/total_words;
        count = 0;
    }

    //This calculates the total score for each word
    for (int w=0; w<total_words; w++) for (int l=0; l<6; l++) for (int a=0; a<26; a++) 
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

    int best_index = nth_best(nth, score, total_words);
    return word_array[best_index];
}

string narrow_down(string guess_word, string hidden_word, string pos_complement, int prev_guess_len, string prev_guesses[], int total_words, string all_words[]) 
{
    /*
    Entry key:
    1. the guess word for this round.
    2. the hidden word.
    3. an array containing all previous guesses.
    4. the maximum number of rounds that can be played.
    5. a string with all letters that have been eliminated.
    6. the total number of words.
    7. an array containing all acceptable words.
    */
    
   //finding the letters in correct positions, correct letters, and letters that have been eliminated.
    string pos = letters_in_position(guess_word, hidden_word);
    string lets_in_word = letters_elsewhere(guess_word, hidden_word, pos);
    pos_complement += letters_in_position_comp(guess_word, hidden_word, lets_in_word);


    string new_guesses[total_words];
    for (int i=0; i<total_words; i++)
    {
        new_guesses[i] = "";
    }

    //gather the candidates, depending on if any letters are in the correct position
    for (int w=0; w<total_words; w++) 
    {
        if (pos == "00000")
        {
            new_guesses[w] = new_guess_array(guess_word, all_words[w], pos, lets_in_word, pos_complement, prev_guesses, prev_guess_len);
        }

        else
        {
            new_guesses[w] = new_guess_array(guess_word, make_position_guesses(w, pos, all_words), pos, lets_in_word, pos_complement, prev_guesses, prev_guess_len);
        }
    }

    //finds the next best word to guess from the candidates, using the best_word function
    string best_new_word = best_word(1, total_words, new_guesses);
    return best_new_word;
}
