#include "aux_functions.cpp"

void interactive(string starter, int total, string all_words[])
{
    string hidden = all_words[(int)rand() % total];

    printf("The word you are starting with is: \n");
    cout << starter << endl;
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