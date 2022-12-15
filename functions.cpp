#include "header.hpp"

void interactive(string starter, int total, string all_words[])
{
    string hidden = all_words[(int)rand() % total];

    printf("The word you are starting with is: \n");
    cout << starter << endl;
}

int nth_best(int tot_words, float scores[], int place) 
{
    int counter = 0;
    int max = 0;
    float scores_rm[tot_words];

    for(int w=1; w<tot_words; w++) 
    {
        scores_rm[w] = scores[w];
    }
    
    while (counter<place)
    {
        for (int w=1; w<tot_words; w++) 
        {
            if (scores_rm[w] > scores_rm[max])
            {
                max = w;
            }
            else 
            {
                continue;
            }
        }

        scores_rm[max] = 0.;
        counter++;
    }

    //cout << "nth max index is: " << max << endl;
    return max;
}

string best_word(int total, string all_words[], int nth)
{
    /*********
    Entry key:
    1. Total number of words accepted by the game (default is 12947)
    2. An array containing all of these words in string format
    3. The nth best word you would like (i.e. first best, second best, etc.)
    This function calculates the scores array which is used with the nth_best
         function to determine the nth-best word.
    **********/

    int check_scores = 1;
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    float prob[26][6]; //first index is letter, second is position
    float score[total];
    int count = 0;

    for (int w=0; w<total; w++) 
    {
        score[w] = 0.;
    }

    //This loop calculates the probabilities for each letter of the alphabet as a function of word position.
    for (int a=0; a<26; a++) for (int l=0; l<6; l++) 
    {
        for (int w=0; w<total; w++) 
        {
            if (alphabet[a] == all_words[w][l])
            {
                count ++;
            }
            else
            {
                continue;
            }
        }
        prob[a][l] = (float)count/total;
        count = 0;
    }

    //This calculates the total score for each word
    for (int w=0; w<total; w++) for (int l=0; l<6; l++) for (int a=0; a<26; a++) 
    {

        if (alphabet[a] == all_words[w][l])
        {
            score[w] += prob[a][l];
        }
        else 
        {
            continue;
        }

    }

    return all_words[nth_best(total, score, nth)];
}

void read_words(int total, string word_array[])
{
    char reads[total][6];

    FILE *wordfile;
    wordfile = fopen("WordleWords.txt","r");

    for (int i=0; i<total; i++)
    {
        fscanf(wordfile, "%6s", reads[i]);
        word_array[i] = (string)reads[i];
    }
}

void independent(string hidden, int total, string all_words[]) 
{
    printf("Your hidden word is: \n");
    cout << hidden << endl;


}