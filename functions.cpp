/*******
 * This file contains all functions which depend on the subroutines in subroutines.cpp. 
 * There are four main functions here:
 * 1. new_guess_array returns a new candidate based upon info gathered from current and past guesses.
 * 2. best_word returns the nth "best" word from an array (see README for justification of this classification method).
 * 3. narrow_down is the basic routine for independent mode, by generating a new best guess based on previous information.
*******/

#include "header.hpp"
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
    string zero = "0";              //the zero string

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
    

    string temp = letters_in_position(guess_word, hidden_word); //THIS IS NEW YOU"LL NEED TO CHECK IT

    //Writes all letters from the guess word which also appear in the hidden word to in_word
    string in_word = letters_elsewhere(guess_word, hidden_word, temp);

    string new_guesses[total]; //candidates
    string position_guesses[total];
    string zero = "0";
    for (int i=0; i<total; i++){
        new_guesses[i] = "";
        position_guesses[i] = "";
    }

    //This runs if none of the letters in the guess are in the right position
    if (temp == "00000")
    {
        for (int w=0; w<total; w++)
        {
            int count = 0;
            for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
            {
                if (in_word[ll] == all_words[w][l]) 
                {
                    count++;
                }
                else
                {
                    continue;
                }
            }

            if (all_words[w] == guess_word)
            {
                new_guesses[w] = "";
            }
            else if (count == in_word.length())
            {
                new_guesses[w] = all_words[w];
            }
            else 
            {
                new_guesses[w] = "";
            }

            //This removes all previous guesses from the candidate array
            for(int g=0; g<prev_guess_len; g++)
            {
                if (all_words[w] == prev_guesses[g])
                {
                    new_guesses[w] = "";
                }
                else
                {
                    continue;
                }
            }
        }

    }
    
    //This runs if some letters in the guess are in the right position
    else 
    {
        //This deals with doubled letters
        for (int w=0; w<total; w++) for (int l=0; l<5; l++)
        {
            int count = 0;
            if (temp[l] != zero[0] && temp[l] == all_words[w][l] && count == 0){
                position_guesses[w] = all_words[w];
                count++;
            }

            else if (temp[l] != zero[0] && temp[l] != all_words[w][l]) {
                position_guesses[w] = "";
                break;
            }

            else 
            {
                continue;
            }
        }

        //This adds to candidate array
        for (int w=0; w<total; w++)
        {
            if (position_guesses[w] != "")
            {
                int count = 0;
                for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
                {
                    if (temp[l] == zero[0] && position_guesses[w][l] == in_word[ll]) 
                    {
                        count++;
                    }
                    else
                    {
                        continue;
                    }
                }

                if (position_guesses[w] == guess_word)
                {
                    new_guesses[w] = "";
                }
                else if (count == in_word.length())
                {
                    new_guesses[w] = position_guesses[w];
                }
                else 
                {
                    new_guesses[w] = "";
                }

                for(int g=0; g<prev_guess_len; g++)
                {
                    if (position_guesses[w] == prev_guesses[g])
                    {
                        new_guesses[w] = "";
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            else
            {
                continue;
            }
        }
    }

    //This finds the next best word to guess from the candidates, using the best_word function
    string best_new_word = best_word(total, new_guesses, 1);
    return best_new_word;
}

/*
This is the version of narrow_down from before I did the interactive mode merge, so this function definitely works
I'm including it here cause I made some on-the-fly changes to narrow_down while I was working on interactive mode...
and may have broken it... we shall see.

string narrow_down(string guess_word, string hidden_word, string prev_guesses[], int prev_guess_len, int total, string all_words[]) 
{
    What this function does:
    1. figure out which of the letters appear
    2. generate a new guess list based on which letters are right
        and which do appear
    3. decide which is the best word from that guess list
    4. compare the strings to determine how many letters are correct/appear
    5. if the strings are equal, exit. If not, repeat the process.
    

   string temp = "00000";

   //Adds letters in the correct position to temp
   for (int l=0; l<6; l++)
    {
        if (guess_word[l] == hidden_word[l])
        {
            temp[l] = guess_word[l];
        }
        else 
        {
            continue;
        }
    }

    //Writes all letters from the guess word which also appear in the hidden word to in_word
    string in_word = "";
    int let = 0;
    while (let < 6)
    {
        //Deals with doubled letters
        for (int lt=0; lt<let; lt++)
        {
            if (guess_word[let] == guess_word[lt])
            {
                let++;
                break;
            }

            else
            {
                continue;
            }
        }

        //Removes letters that are already accounted for in temp
        for (int lh=0; lh<6; lh++)
        {
            if (guess_word[let] == temp[lh])
            {
                continue;
            }
            else if (guess_word[let] == hidden_word[lh])
            {
                in_word += guess_word[let];
            }
            else
            {
                continue;
            }
        }
        let++;
    }


    string new_guesses[total]; //candidates
    string position_guesses[total];
    string zero = "0";
    for (int i=0; i<total; i++){
        new_guesses[i] = "";
        position_guesses[i] = "";
    }

    //This runs if none of the letters in the guess are in the right position
    if (temp == "00000")
    {
        for (int w=0; w<total; w++)
        {
            int count = 0;
            for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
            {
                if (in_word[ll] == all_words[w][l]) 
                {
                    count++;
                }
                else
                {
                    continue;
                }
            }

            if (all_words[w] == guess_word)
            {
                new_guesses[w] = "";
            }
            else if (count == in_word.length())
            {
                new_guesses[w] = all_words[w];
            }
            else 
            {
                new_guesses[w] = "";
            }

            //This removes all previous guesses from the candidate array
            for(int g=0; g<prev_guess_len; g++)
            {
                if (all_words[w] == prev_guesses[g])
                {
                    new_guesses[w] = "";
                }
                else
                {
                    continue;
                }
            }
        }

    }
    
    //This runs if some letters in the guess are in the right position
    else 
    {
        //This deals with doubled letters
        for (int w=0; w<total; w++) for (int l=0; l<5; l++)
        {
            int count = 0;
            if (temp[l] != zero[0] && temp[l] == all_words[w][l] && count == 0){
                position_guesses[w] = all_words[w];
                count++;
            }

            else if (temp[l] != zero[0] && temp[l] != all_words[w][l]) {
                position_guesses[w] = "";
                break;
            }

            else 
            {
                continue;
            }
        }

        //This adds to candidate array
        for (int w=0; w<total; w++)
        {
            if (position_guesses[w] != "")
            {
                int count = 0;
                for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
                {
                    if (temp[l] == zero[0] && position_guesses[w][l] == in_word[ll]) 
                    {
                        count++;
                    }
                    else
                    {
                        continue;
                    }
                }

                if (position_guesses[w] == guess_word)
                {
                    new_guesses[w] = "";
                }
                else if (count == in_word.length())
                {
                    new_guesses[w] = position_guesses[w];
                }
                else 
                {
                    new_guesses[w] = "";
                }

                for(int g=0; g<prev_guess_len; g++)
                {
                    if (position_guesses[w] == prev_guesses[g])
                    {
                        new_guesses[w] = "";
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            else
            {
                continue;
            }
        }
    }

    //This finds the next best word to guess from the candidates, using the best_word function
    string best_new_word = best_word(total, new_guesses, 1);
    return best_new_word;
}
*/
