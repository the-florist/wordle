#include "header.h"

void independent(string hidden, int total, string all_words[]) 
{
    printf("Your hidden word is: \n");
    cout << hidden << endl;


}

void interactive(string starter, int total, string all_words[])
{
    string hidden = all_words[(int)rand() % total];

    printf("The word you are starting with is: \n");
    cout << starter << endl;
}

string best_start(int total, string all_words[])
{
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

    //This calculates the maximum scoring word's index
    int max;
    for (int w=1; w<total; w++) 
    {
        if (score[w] > score[w-1])
        {
            max = w;
        }
        else 
        {
            continue;
        }
    }

    //printf("Some scores: %f %f %f\n", score[0], score[460], score[1346]);
    //cout << all_words[0] << " " << all_words[total-1] << endl;
    //printf("The max score (index %i) is %f, and the best word is:\n", max, score[max]);
    //cout << all_words[max] << endl;

    return all_words[max];
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

    /*cout << word_array[0] << endl;
    cout << word_array[10] << endl;
    cout << word_array[10][0] << endl;

    if (word_array[0][0] == word_array[2][1]) {
        printf("String equality works!\n");
    }
    else{
        printf("Something went wrong...\n");
    }*/
}