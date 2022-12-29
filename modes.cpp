/*********
 * This file containts the two functions on which each mode of operation is based.
*********/

#include "functions.cpp"

void interactive(string start_word, int total, string all_words[])
{
    /*
    This program does the following:
    1. generate a hidden word for the user to guess.
    2. if the starting word is the guess word, return the guess as the answer.
    3. if not, determine how many letters are correct and/or in the right position, 
            and return this to the user.
    4. at return, the program also suggests five of the best words for the user 
            to chose from if she chooses.
    5. take a new starting word from the user and repeat the process.
    */
    
   string hidden;

    if (debug !=1)
    {
        //This chooses a random word from the list to be hidden
        srand(time(NULL));
        hidden = all_words[(int)rand() % total];
    }
    
    else if (debug == 1)
    {
        //here you can choose a specific word to use for debugging
        hidden = "creed";
        cout << "Hidden: " << hidden << endl;
    }

    int max_guess_num = 100;                //maximum number of rounds (to somewhat preserve memory)
    int round = 0;                          //number of times you've guessed
    string previous_guesses[max_guess_num]; //tracks previous guesses

    for (int g=0; g<max_guess_num; g++) 
    {
        previous_guesses[g] = "";
    }

    //If you just so happen to get the wordle in one go...
    if (start_word == hidden)
    {
        cout << "Congrats! You got the wordle in one go!" << endl;
    }

    //This will run instead most of the time
    else 
    {
        string guess = start_word;
        string position;            //tracks which letters are in the right position
        string in_word = "";        //tracks which letters appear but aren't in the right position
        string position_complement; //tracks which letters have been eliminated

        int num_suggestions = 5;    //how many suggestions the computer should give you at the end
        string new_guesses[total];  //array containing all the new candidates

        while (guess != hidden) 
        {
            //resets the array of candidates
            for (int t=0; t<total; t++) 
            {
                new_guesses[t] = "";
            }

            //calculates which letters are in the right position
            position = letters_in_position(guess, hidden);
            if (position != "00000") 
            {
                cout << "These letters are in the right position: " << position << endl;
            }
            else
            {
                cout << "No letters were in the right position." << endl;
            }

            //calculates which letters are right but not in position
            in_word = letters_elsewhere(guess, hidden, position);
            if (in_word != "") 
            {
                cout << "These letters are in the word, but not in the right position: " << in_word << endl;
            }
            else {
                cout << "No other letters appear in the word." << endl;
            }

            //adds all letters that have been eliminated to the complement
            position_complement += letters_in_position_comp(guess, hidden, in_word);

            //generates a new array of candidates depending on if some letters are in the right position
            for (int w=0; w<total; w++) 
            {
                if (position == "00000") 
                {
                    new_guesses[w] = new_guess_array(all_words[w], guess, in_word, position, position_complement, previous_guesses, max_guess_num);
                }

                else 
                {
                    new_guesses[w] = new_guess_array(make_position_guesses(w, all_words, position), guess, in_word, position, position_complement, previous_guesses, max_guess_num);
                }
            }

            //returns the letters that have been eliminated (for debugging)
            if (debug == 1) 
            {
                cout << "These letters have been eliminated: ";
                for (int i=0; i<position_complement.length(); i++)
                {
                    cout << position_complement[i];
                }
                printf("\n");
            }

            //returns the next best n guesses
            cout << "The next " << num_suggestions << " best words to try are: " << endl;
            for (int s=1; s<num_suggestions+1; s++) 
            {
                cout << best_word(total, new_guesses, s) << endl;
            }

            //puts the current guess in the array of previous guesses
            previous_guesses[round] = guess;

            //this puts information from the round into the debug file
            if (debug == 1)
            {
                string best = best_word(total, new_guesses, 1);
                print_to_debug_file(round, guess, hidden, position, in_word, position_complement, best);
                fprintf(debug_out, "\n\n");
            }

            //reads in the new guess
            cout << "Which word would you like to guess next?: ";
            cin >> guess;
            round++;

            //determines if you've maximised the number of rounds
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
    /*
    This program does the following:
    1. makes an initial guess based on the best word algorithm
    2. checks to see if the hidden word is the guess word
    3. while the first guess is not the hidden word, a new guess is generated 
        using the narrow_down function (see functions.cpp)
    4. returns the number of rounds and the hidden word, once it is found.
    */
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
        string complement;

        for (int g=0; g<max_guesses; g++) 
        {
            previous[g] = "";
        }

        while (guess != hidden)
        {
            previous[round_count] = guess;
            temp_guess = narrow_down(guess, hidden, previous, max_guesses, complement, total, all_words);
            guess = temp_guess;

            if(round_count >= max_guesses) 
            {
                printf("Round count has exceeded ability for computer to remember past guesses. Exiting program.\n");
                exit(EXIT_FAILURE);
            }

            round_count++;
        }

        cout << "Number of rounds: " << round_count << endl;
        return guess;
    }
}