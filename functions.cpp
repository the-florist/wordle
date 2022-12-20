#include "aux_functions.cpp"

string interactive(string start_word, int total, string all_words[])
{
    /*
    This program should:
    1. generate a hidden word for the user to guess.
    2. if the starting word is the guess word, return the guess as the answer.
    3. if not, determine how many letters are correct and/or in the right position, 
            and return this to the user.
    4. at return, the program should also suggest five of the best words for the user 
            to chose from if she chooses.
    5. take a new starting word from the user and repeat the process.
    */
    
    string hidden = all_words[(int)rand() % total];
    cout << "Hidden word: " << hidden << endl; //This is just for debugging purposes, obviously

    if (start_word == hidden)
    {
        cout << "Congrats! You got the wordle in one go!" << endl;
        return start_word;
    }

    else 
    {
        string guess = start_word;
        string position;
        string in_word = "";

        position = letters_in_position(guess, hidden);
        cout << "These letters are in the right position: " << position << endl;

        in_word = letters_elsewhere(guess, hidden, position);
        cout << "These letters are in the word, but not in the right position: " << in_word << endl;

        if (position == "00000")
        {
            string new_guesses[total];
            for (int w=0; w<total; w++)
            {
                //new_guesses[w] = new_guess_array(w, in_word, guess, all_words, total);
            }
        }

        return "holds";
    }
}


string independent(string hidden, int max_guesses, int total, string all_words[]) 
{
    string guess = best_word(total, all_words, 1);

    //if computer guesses the hidden word right off
    if (guess == hidden)
    {
        return guess;
    }

    //if the computer needs to do some work
    else
    {
        int round_count = 0;
        string temp_guess;
        string previous[max_guesses];

        for (int g=0; g<max_guesses; g++) 
        {
            previous[g] = "";
        }

        while (guess != hidden)
        {
            previous[round_count] = guess;
            temp_guess = narrow_down(guess, hidden, previous, max_guesses, total, all_words);
            guess = temp_guess;
            round_count++;

            if(round_count >= max_guesses) 
            {
                printf("Round count has exceeded ability for computer to remember past guesses. Exiting program.\n");
                exit(EXIT_FAILURE);
            }
        }

        cout << "Number of rounds: " << round_count << endl;
        return guess;
    }
}