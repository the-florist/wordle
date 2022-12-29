/*********
 * This file containts all tests which must be passed in order for 
 * a new version of the code to upload successfully onto github.
*********/

#include "../modes.cpp"

int main() 
{
    int tot=12947;
    string words[tot];
    read_words(tot, words);

    cout << "Beginning testing protocol.\n---------" << endl;

    /********
     Functions that extract info from guesses
    ********/

    if (find_unique_letters("gregs") != "gres") 
    {
        cout << "Issue: find_unique_letters." << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function find_unique_letters passed." << endl;
    }

    if (letters_in_position("bools", "growl") != "00o00")
    {
        cout << "Issue: letters_in_position, condition 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if (letters_in_position("boats", "growl") != "00000") 
    {
        cout << "Issue: letters_in_position, condition 2" << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function letters_in_position passed." << endl;
    }

    if (letters_in_position_comp("helps", "hiden", "h") != "lps") 
    {
        cout << "Issue: letters_in_position_complement, condition 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if (letters_in_position_comp("hider", "hider", "dr") != "") 
    {
        cout << "Issue: letters_in_position_complement, condition 2" << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function letters_in_position_complement passed." << endl;
    }

    if (letters_elsewhere("diner", "hiden", "0ine0") != "dn") 
    {
        cout << "Issue: letters_elsewhere, condition 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if (letters_elsewhere("julie", "karps", "0u00e") != "") 
    {
        cout << "Issue: letters_elsewhere, condition 2" << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function letters_elsewhere passed." << endl;
    }

    /********
     Subroutines for generating a new list of guesses
    ********/

    if (position_remover("hiden", "tiles", "0i0e0") != "tiles")
    {
        cout << "Issue: position_remover, condition 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if (position_remover("tiles", "hiden", "0i000") != "") 
    {
        cout << "Issue: postion_remover, condition 2" << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function position_remover passed." << endl;
    }

    if (eliminated_letter_remover("carts", "0a00s", "szlv") != "carts") 
    {
        cout << "Issue: eliminated_letter_remover, condition 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if (eliminated_letter_remover("carts", "0a000", "zlv") != "carts") 
    {
        cout << "Issue: eliminated_letter_remover, condition 2" << endl;
        exit(EXIT_FAILURE);
    }
    else if (eliminated_letter_remover("carts", "0a000", "szlv") != "") 
    {
        cout << "Issue: eliminated_letter_remover, condition 3" << endl;
        exit(EXIT_FAILURE);
    }
    else 
    {
        cout << "Function eliminated_letter_remover passed" << endl;
    }

    /********
     Functions from functions.cpp
    ********/

   string test_array[3] = {"carbs", "truck", "colon"};
   string test_array_false[3] = {"carbs", "trace", "colon"};

   if (new_guess_array("carts", "trace", "00000", "atcr", "zb", test_array, 3) != "trace") 
   {
       cout << "Issue: new_guess_array, condition 1" << endl;
       exit(EXIT_FAILURE);
   }
   else if (new_guess_array("carts", "trace", "0a000", "atcr", "zb", test_array, 3) != "") 
   {
       cout << "Issue: new_guess_array, condition 2" << endl;
       exit(EXIT_FAILURE);
   }
   else if (new_guess_array("carts", "trace", "00000", "atcs", "zb", test_array, 3) != "") 
   {
       cout << "Issue: new_guess_array, condition 3" << endl;
       exit(EXIT_FAILURE);
   }
   else if (new_guess_array("carts", "trace", "00000", "atcr", "zbe", test_array, 3) != "") 
   {
       cout << "Issue: new_guess_array, condition 4" << endl;
       exit(EXIT_FAILURE);
   }
   else if (new_guess_array("carts", "trace", "00000", "atcr", "zb", test_array_false, 3) != "") 
   {
       cout << "Issue: new_guess_array, condition 5" << endl;
       exit(EXIT_FAILURE);
   }
   else 
   {
       cout << "Function new_guess_array passed." << endl;
   }

   if (best_word(1, tot, words) != "sores") 
   {
       cout << "Issue: best_word\nIf you have altered the ranking algorithm, please update this test." << endl;
       exit(EXIT_FAILURE);
   }
   else 
   {
       cout << "Function best_word passed." << endl;
   }

    cout << "All test have been passed. You may now commit this version." << endl;
    cout << "---------" << endl;
}