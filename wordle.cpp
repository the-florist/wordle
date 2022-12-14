//A c++ program which solves the Wordle independently and interactively.
//Created December 2022 by Ericka Florio
//For the purpose of assessment in the Michaelmas 2022 Research in Computing course.

#include "header.h"
#include "functions.cpp"

int main() {
    //declaring main type variables
    int tot=12947;
    int typ;
    string words[tot];
    string hid;

    int test = 1;

    //words[0] = "First string";
    //cout << words[0] << endl;
    //cout << words[0][0] << endl;

    read_words(tot, words);
    printf("The best word to start with is: ");
    cout << best_start(tot, words) << endl;
    
    if(test==1)
    {

    //opening message
    cout << "Welcome to my Wordle solver!\nWould you like to play indpendently (0) or interactively (1)?: ";
    cin >> typ;

    //main body for independent mode
    if (typ == 0) 
    {
        cout << "You have chosen to play independently.\nPlease enter a word for me to find: ";
        cin >> hid;
        //cout << hid << endl;
        
        independent(hid, tot, words);
    }

    //main body for interactive mode
    else if (typ == 1) 
    {
        string best = best_start(tot, words);
        
        int strt;
        char start[6];
        cout << "You have chosen to play interactively.\nDo you wish to enter a starting word (0) or use the best starting word (1)?: ";
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
    }

    //error message
    else 
    {
        cout << "Please enter a type which is either 0 or 1.\n";
    }

    }

    printf("Program ended.\n");
}
