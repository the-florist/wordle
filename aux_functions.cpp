#include "header.hpp"

void print_string_list(string strings[], int len, string name) //This is just a nice debugging routine
{
    cout << "String list " << name << ": " << endl;
    for(int g=0; g<len; g++)
    {
        if (strings[g] != "")
        {
            cout << strings[g] << endl;
        }
        else
        {
            continue;
        }
    }
}

//Prints all the letters that have been eliminated so far
void print_position_complement(string pos_comp) 
{
    string zero = "0";
    cout << "These letters have been eliminated: ";
    for (int i=0; i<pos_comp.length(); i++){
        if (pos_comp[i] != zero[0]){
            cout << pos_comp[i];
        }
        else {
            continue;
        }
    }
    printf("\n");
}

void read_words(int total, string word_array[])
{
    /*
    This function reads the words from the WordleWords.txt file
        into an array that the program can work with.
    */
    char reads[total][6];

    FILE *wordfile;
    wordfile = fopen("WordleWords.txt","r");

    for (int i=0; i<total; i++)
    {
        fscanf(wordfile, "%6s", reads[i]);
        word_array[i] = (string)reads[i];
    }
}

//This is fine
string letters_in_position(string guess_word, string hidden_word) 
{
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

    return temp;
}

string letters_in_position_comp(string guess_word, string hidden_word) 
{
    string temp;

   //Adds letters in the correct position to temp
   for (int l=0; l<6; l++)
    {
        if (guess_word[l] != hidden_word[l])
        {
            temp += guess_word[l];
        }
        else 
        {
            continue;
        }
    }

    return temp;
}

//This is fine
string letters_elsewhere(string guess_word, string hidden_word, string temp) 
{
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

    return in_word;
}

//This works - it eliminates words from the guess list if their letters have been ruled out.
string eliminated_letter_remover(string let, string let_comp, string next_guess, int pos_bool) 
{
    if (pos_bool == 0)
    {
        for (int l=0; l<5; l++) for (int ll=0; ll<let_comp.length(); ll++)
        {
            if (next_guess[l] == let_comp[ll]) 
            {
                next_guess = "";
            }
            else 
            {
                continue;
            }
        }
    }
    else 
    {
        for (int l=0; l<5; l++) for (int ll=0; ll<let_comp.length(); ll++)
        {
            if (next_guess[l] == let_comp[ll] && let[l] != let_comp[ll]) 
            {
                next_guess = "";
            }
            else 
            {
                continue;
            }
        }
    }

    return next_guess;
}

//This is fine
string prev_guess_remover_no_position(int prev_guess_len, string prev_guesses[], string this_guess, string word_from_array)
{

    //This removes all previous guesses from the candidate array
    for(int g=0; g<prev_guess_len; g++)
    {
        if (word_from_array == prev_guesses[g])
        {
            this_guess = "";
        }
        else
        {
            continue;
        }
    }

    return this_guess;
}

//This is fine
//************
string new_guess_array_no_position(string word_from_array, string in_word, string guess_word, string temp_comp, string previous[], int previous_len) 
{
    string new_guess = ""; //candidate
    string in_word_temp = in_word;
    string zero = "0";

    int count = 0;
    for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
    {
        if (in_word_temp[ll] == word_from_array[l]) 
        {
            in_word_temp[ll] = zero[0];
            count++;
        }
        else
        {
            continue;
        }
    }

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

    new_guess = prev_guess_remover_no_position(previous_len, previous, new_guess, word_from_array);

    /*if (new_guess != "") 
    {
        cout << "Condition 2: " << new_guess << endl;
    }*/

    new_guess = eliminated_letter_remover("00000", temp_comp, new_guess, 0);

    if (new_guess != "") 
    {
        cout << "Condition 3: " << new_guess << endl;
    }

    return new_guess;
}

//This is fine
string make_position_guesses(int word, string all_words[], string temp) //goes in for loop over w
{
    string position_guess = "";
    string zero = "0";

    //This deals with doubled letters
    for (int l=0; l<5; l++)
    {
        int count = 0;
        if (temp[l] != zero[0] && temp[l] == all_words[word][l] && count == 0){
            position_guess = all_words[word];
            count++;
        }

        else if (temp[l] != zero[0] && temp[l] != all_words[word][l]) {
            position_guess = "";
            break;
        }

        else 
        {
            continue;
        }
    }

    return position_guess;
}

//This is fine
string prev_guess_remover(int prev_guess_len, string prev_guesses[], string this_guess, string pos_guess) //goes in function that calls "word"
{
    for(int g=0; g<prev_guess_len; g++)
    {
        if (pos_guess == prev_guesses[g])
        {
            this_guess = "";
        }
        else
        {
            continue;
        }
    }

    return this_guess;
}

//This runs fine and fast now!
//***************
string new_guess_array(int total, string word_from_array, string guess_word, string temp, string temp_comp, string in_word, string position_guess, string previous[], int previous_len) 
{
    string new_guess = ""; //candidates
    string in_word_temp = in_word;
    string zero = "0";

    //This adds to candidate array
    if (position_guess != "")
    {
        int count = 0;
        for (int l=0; l<6; l++) for (int ll=0; ll<in_word.length(); ll++)
        {
            if (temp[l] == zero[0] && position_guess[l] == in_word_temp[ll]) 
            {
                in_word_temp[ll] = zero[0];
                count++;
            }
            else
            {
                continue;
            }
        }

        if (position_guess == guess_word)
        {
            new_guess = "";
        }
        else if (count == in_word.length())
        {
            new_guess = position_guess;
        }
        else 
        {
            new_guess = "";
        }

        new_guess = prev_guess_remover(previous_len, previous, new_guess, position_guess);
        new_guess = eliminated_letter_remover(temp, temp_comp, new_guess, 1);
    }

    return new_guess;
}

int nth_best(int tot_words, float scores[], int place) 
{
    /*
    This function uses the scores generated by best_word
        to find the nth ranked word.
    */
    int counter = 0;
    int max = 0;
    float scores_rm[tot_words];

    for(int w=1; w<tot_words; w++) 
    {
        scores_rm[w] = scores[w];
    }
    
    while (counter<place)
    {
        for (int w=1; w<tot_words; w++) 
        {
            if (scores_rm[w] > scores_rm[max])
            {
                max = w;
            }
            else 
            {
                continue;
            }
        }

        scores_rm[max] = 0.;
        counter++;
    }

    //cout << "nth max index is: " << max << endl;
    return max;
}

string best_word(int total, string all_words[], int nth)
{
    /**********
    This function calculates the scores array which is used with the nth_best
         function to determine the nth-best word.
    Entry key:
    1. Total number of words accepted by the game (default is 12947)
    2. An array containing all of these words in string format
    3. The nth best word you would like (i.e. first best, second best, etc.)
    **********/

    int check_scores = 1;
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    float prob[26][6]; //first index is letter, second is position
    float score[total];
    int count = 0;

    for (int w=0; w<total; w++) 
    {
        score[w] = 0.;
    }

    //This loop calculates the probabilities for each letter of the alphabet as a function of word position.
    for (int a=0; a<26; a++) for (int l=0; l<6; l++) 
    {
        for (int w=0; w<total; w++) 
        {
            if (alphabet[a] == all_words[w][l])
            {
                count ++;
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

        if (alphabet[a] == all_words[w][l])
        {
            score[w] += prob[a][l];
        }
        else if (all_words[w] == "")
        {
            score[w] = 0;
        }
        else 
        {
            continue;
        }

    }

    int best_index = nth_best(total, score, nth);
    //cout << "Score: " << score[best_index] << endl;
    return all_words[best_index];
}

string narrow_down(string guess_word, string hidden_word, string prev_guesses[], int prev_guess_len, int total, string all_words[]) 
{
    /*What this function does:
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
