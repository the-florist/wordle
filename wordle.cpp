//A c++ program which solves the Wordle independently and interactively.
//Created December 2022 by Ericka Florio
//For the purpose of assessment in the Michaelmas 2022 Research in Computing course.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "functions.cpp"
using namespace std;


int main() {
    //declaring main type variables
    int typ;
    char hid[6];
    //opening message
    cout << "Would you like to play indpendently (0) or interactively (1)?: ";
    cin >> typ;

    //main body for independent mode
    if (typ == 0) 
    {
        printf("You have chosen to play independently.\nPlease enter a word for me to find: ");
        scanf("%5s", hid);
        //printf("%s\n", hid);
        
        independent(hid);
    }

    //main body for interactive mode
    else if (typ == 1) 
    {
        int strt;
        cout << "You have chosen to play interactively.\nDo you wish to enter a starting word (0) or use the best starting word (1)?: ";
        cin >> strt;

        if (strt == 0)
        {
            printf("Please enter your starting word: ");
            scanf("%5s", hid);

            //printf("%s %s\n", hid, &hid);

            interactive(hid);
        }
        else if (strt == 1)
        {
            printf("The best starting word is: %s\n", best_start());
            printf("Is this ok? If so please re-enter this word: ");
            scanf("%5s", hid);

            //printf("%s %s\n", hid[0], hid);
            
            interactive(hid);
        }
    }

    //error message
    else {
        cout << "Please enter a type which is either 0 or 1.\n";
    }

    printf("Program ended.\n");
}
