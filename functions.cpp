#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void independent(char* hidden) 
{
    printf("The word you have entered is: %s\n", hidden);
}

void interactive(char* hidden)
{
    printf("The word you have entered is: %s\n", hidden);
}

const char* best_start(char all_words[][6])
{
    return "Hello";
}

void read_words(int total, char word_array[][6])
{
    FILE *wordfile;
    wordfile = fopen("WordleWords.txt","r");

    for (int i=0;i<total;i++)
    {
        fscanf(wordfile, "%s", word_array[i]);
    }
}