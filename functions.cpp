#include "aux_functions.cpp"

void interactive(string start_word, int total, string all_words[])
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
    
    //srand(time(NULL));
    //string hidden = all_words[(int)rand() % total];
    string hidden = "quilt";

    int max_guess_num = 100;
    int round = 0;
    string previous_guesses[max_guess_num];
    for (int g=0; g<max_guess_num; g++) 
    {
        previous_guesses[g] = "";
    }

    cout << "Hidden word: " << hidden << endl; //This is just for debugging purposes, obviously

    if (start_word == hidden)
    {
        cout << "Congrats! You got the wordle in one go!" << endl;
    }

    else 
    {
        string guess = start_word;
        string position;
        string position_complement;
        string in_word = "";
        int num_suggestions = 5;

        while (guess != hidden) 
        {
            string new_guesses[total];

            position = letters_in_position(guess, hidden);
            position_complement += letters_in_position_comp(guess, hidden);

            cout << "Compliment: " << position_complement << endl;

            if (position != "00000") 
            {
                cout << "These letters are in the right position: " << position << endl;
            }
            else
            {
                cout << "No letters were in the right position." << endl;
            }

            in_word = letters_elsewhere(guess, hidden, position);
            if (in_word != "") 
            {
                cout << "These letters are in the word, but not in the right position: " << in_word << endl;
            }
            else {
                cout << "No other letters appear in the word." << endl;
            }

            if (position == "00000")
            {
                for (int w=0; w<total; w++)
                {
                    new_guesses[w] = new_guess_array_no_position(all_words[w], in_word, guess, position_complement, previous_guesses, max_guess_num);
                }

                //print_string_list(new_guesses, total, "new guesses 00000");
                print_position_complement(position_complement);

                cout << "The next " << num_suggestions << " best words to try are: " << endl;
                for (int s=1; s<num_suggestions+1; s++) 
                {
                    cout << best_word(total, new_guesses, s) << endl;
                }
            }

            else 
            {
                for (int w=0; w<total; w++) 
                {
                    new_guesses[w] = new_guess_array(total, all_words[w], guess, position, position_complement, in_word, make_position_guesses(w, all_words, position), previous_guesses, max_guess_num);
                }

                cout << "The next " << num_suggestions << " best words to try are: " << endl;
                for (int s=1; s<num_suggestions+1; s++) 
                {
                    cout << best_word(total, new_guesses, s) << endl;
                }
            }

            previous_guesses[round] = guess;

            cout << "Which word would you like to guess next?: ";
            cin >> guess;
            round++;

            if (round >= max_guess_num) 
            {
                cout << "Sorry, we've run out of memory to store your guesses. The program will now end." << endl;
                exit(EXIT_FAILURE);
            }
        }

        cout << "Congrats! You won the wordle. The hidden word was: " << guess << endl;   
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