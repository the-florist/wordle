//A c++ program which solves the Wordle independently and interactively.
//Created December 2022 by Ericka Florio
//For the purpose of assessment in the Michaelmas 2022 Research in Computing course.

#include "header.h"
#include "functions.cpp"

int main() {
    //declaring main type variables
    const int tot=12947;
    int typ;
    char words[tot][6];
    char* hid;

    int test = 0;

    read_words(tot, words);

    printf("Best word to start with is: %s\n", best_start(tot, words));

    if(test==1){

    //opening message
    cout << "Welcome to my Wordle solver!\nWould you like to play indpendently (0) or interactively (1)?: ";
    cin >> typ;

    //main body for independent mode
    if (typ == 0) 
    {
        printf("You have chosen to play independently.\nPlease enter a word for me to find: ");
        scanf("%6s", hid);
        //printf("%s\n", hid);
        
        independent(hid);
    }

    //main body for interactive mode
    else if (typ == 1) 
    {
        hid = words[(int)rand() % tot];
        
        int strt;
        char start[6];
        cout << "You have chosen to play interactively.\nDo you wish to enter a starting word (0) or use the best starting word (1)?: ";
        cin >> strt;

        if (strt == 0)
        {
            printf("Please enter your starting word: ");
            scanf("%6s", start);

            interactive(start, hid);
        }
        else if (strt == 1)
        {
            printf("The best starting word is: %s\n", best_start(tot, words));
            printf("Is this ok? If so please re-enter this word: ");
            scanf("%6s", start);
            
            interactive(start, hid);
        }
    }

    //error message
    else {
        cout << "Please enter a type which is either 0 or 1.\n";
    }

    }

    printf("Program ended.\n");
}
