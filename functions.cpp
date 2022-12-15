#include "aux_functions.cpp"

void interactive(string starter, int total, string all_words[])
{
    string hidden = all_words[(int)rand() % total];

    printf("The word you are starting with is: \n");
    cout << starter << endl;
}


string independent(string hidden, int total, string all_words[]) 
{
    string guess = best_word(total, all_words, 1);
    string answer = "00000";
    
    for (int l=0; l<6; l++)
    {
        if (guess[l] == hidden[l])
        {
            answer[l] = guess[l];
        }
        else 
        {
            continue;
        }
    }

    if (answer == hidden) //if computer guesses the hidden word right off
    {
        return answer;
    }

    else if (answer != "00000") //if the computer gets some letters right
    {
        //narrow_down();

        return "else if";
    }

    else //if all the letters are wrong
    {
        /*until (keep_guessing() != "00000")
        {
            guess = keep_guessing();
        }*/
        return "else";
    }

}