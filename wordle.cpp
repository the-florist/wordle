/*********
A c++ program which solves the Wordle independently and interactively.
Created December 2022 by Ericka Florio
For the purpose of assessment in the Michaelmas 2022 Research in Computing course.
**********/

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

    int run_main;
    if (debug != 1) 
    {
        run_main = 1;
    }
    else if (debug == 1)
    {
        run_main = 0;
        debug_out = fopen("./tools/debug_output.txt", "w");
    }
    else 
    {
        printf("Debug flag isn't working, stopping program.");
        exit(EXIT_FAILURE);
    }

    read_words(tot, words);
    
    if(run_main==1)
    {
        //opening message
        cout << "Welcome to my Wordle solver!\nWould you like to play independently (0) or interactively (1)?: ";
        cin >> typ;

        //main body for independent mode
        if (typ == 0) 
        {
            int max;
            cout << "---------\nYou have chosen to play independently.\nPlease enter a word for me to find: ";
            cin >> hid;

            check_is_word(hid, tot, words);

            cout << "Please enter a maximum number of times you want me to guess: ";
            cin >> max;
            
            ans = independent(hid, max, tot, words);

            cout << "Your hidden word is: ";
            cout << ans << endl;
        }

        //main body for interactive mode
        else if (typ == 1) 
        {
            string best = best_word(1, tot, words);
            
            int strt;
            string start;
            cout << "---------\nYou have chosen to play interactively.\nDo you wish to enter a starting word (0) or use the best starting word (1)?: ";
            cin >> strt;

            if (strt == 0)
            {
                cout << "Please enter your starting word: ";
                cin >> start;

                check_is_word(start, tot, words);

                interactive(start, tot, words);
            }

            else if (strt == 1)
            {
                printf("The best starting word is: ");
                cout << best << endl;
                
                interactive(best, tot, words);
            }

            //error trap
            else 
            {
                cout << "Please enter a value of either 0 or 1." << endl;
                exit(EXIT_FAILURE);
            }
        }

        //error trap
        else 
        {
            cout << "Please enter a type which is either 0 or 1.\n";
            exit(EXIT_FAILURE);
        }
    }

    printf("Program ended. Thanks for playing!\n");
    if(debug == 1) 
    {
        fclose(debug_out);
    }
}
