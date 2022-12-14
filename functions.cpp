#include "header.h"

void independent(char* hidden) 
{
    printf("The word you have entered is: %s\n", hidden);
}

void interactive(char* starter, char* hidden)
{
    printf("The word you have entered is: %s\n", hidden);
}

const char* best_start(int total, char all_words[][6])
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    float prob[26][6]; //first index is letter, second is position
    float score[total];
    int count = 0;

    for (int w=0; w<total; w++) 
    {
        score[w] = 0.;
    }

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
    //printf("%s %s %s\n", all_words[total-1], all_words[total-2], all_words[total-3]);
    //printf("The max score (index %i) is %f, and the best word is %s\n", max, score[max], all_words[max]);

    return all_words[max];
}

void read_words(int total, char word_array[][6])
{
    FILE *wordfile;
    wordfile = fopen("WordleWords.txt","r");

    for (int i=0; i<total; i++)
    {
        fscanf(wordfile, "%6s", word_array[i]);
    }

    //fscanf(wordfile, "%s", word_array[0]);
    //fscanf(wordfile, "%s", word_array[1]);

    //printf("Some words: %s %s %s %s\n", word_array[0], word_array[1], word_array[2], word_array[3]);
}