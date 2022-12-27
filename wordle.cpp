//A c++ program which solves the Wordle independently and interactively.
//Created December 2022 by Ericka Florio
//For the purpose of assessment in the Michaelmas 2022 Research in Computing course.

//#include "header.hpp"
#include "modes.cpp"

int main() 
{
    //declaring main type variables
    int tot=12947;
    int typ;
    string words[tot];
    string hid;
    string ans;

    int test;

    if (debug != 1) 
    {
        test = 1;
    }
    else if (debug == 1)
    {
        test = 0;
        debug_out = fopen("./tools/debug_output.txt", "w");
    }
    else 
    {
        printf("Debug flag isn't working, stopping program.");
        exit(EXIT_FAILURE);
    }

    read_words(tot, words);

    //Independent test block
    /*narrow_down(tot, words);
    hid = "stick";
    ans = independent(hid, tot, words);
    cout << "Is this your word?: " << ans << endl;*/

    //Interactive test block
    string start = "triti";
    //cout << "Guess: " << start << endl;
    //string hidden = "voter";
    //string prev_comp = "crzh";

    interactive(start, tot, words);

    //cout << prev_comp + letters_in_position_comp(start, hidden, prev_comp) << endl;
    fclose(debug_out);

    /*string temp = letters_in_position(start, "helps");
    string float_lets = letters_elsewhere(start, "helps", temp);
    cout << temp << endl;
    cout << float_lets << endl;

    string new_guesses[tot];

    string previous_guesses[3] = {"stout", "stood", "sloop"};
    int previous_guesses_len = 3;

    for (int w=0; w<tot; w++)
    {
        new_guesses[w] = "";
        new_guesses[w] = new_guess_array(tot, words[w], start, temp, float_lets, make_position_guesses(w, words, temp), previous_guesses, previous_guesses_len);
    }
    
    print_string_list(new_guesses, tot, "new guesses");
    cout << eliminated_letter_remover("000e0", "hlpsran", "noted") << endl;
    cout << letters_in_position_comp("ranee", "noted", "n") << endl;*/
    
    if(test==1)
    {

    //opening message
    cout << "Welcome to my Wordle solver!\nWould you like to play indpendently (0) or interactively (1)?: ";
    cin >> typ;

    //main body for independent mode
    if (typ == 0) 
    {
        int max;
        cout << "---------\nYou have chosen to play independently.\nPlease enter a word for me to find: ";
        cin >> hid;

        cout << "Please enter a maximum number of times you want me to guess: ";
        cin >> max;
        
        ans = independent(hid, max, tot, words);

        cout << "Your hidden word is: ";
        cout << ans << endl;
    }

    //main body for interactive mode
    else if (typ == 1) 
    {
        string best = best_word(tot, words, 1);
        
        int strt;
        string start;
        cout << "---------\nYou have chosen to play interactively.\nDo you wish to enter a starting word (0) or use the best starting word (1)?: ";
        cin >> strt;

        if (strt == 0)
        {
            cout << "Please enter your starting word: ";
            cin >> start;

            interactive(start, tot, words);
        }
        else if (strt == 1)
        {
            printf("The best starting word is: ");
            cout << best << endl;
            
            interactive(best, tot, words);
        }

        //error trap
        else {
            cout << "Please enter a value of either 0 or 1." << endl;
            exit(EXIT_FAILURE);
        }
    }

    //error trap
    else 
    {
        cout << "Please enter a type which is either 0 or 1.\n";
    }

    }

    printf("Program ended. Thanks for playing!\n");
}
