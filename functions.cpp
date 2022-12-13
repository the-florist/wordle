#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const char* best_start()
{
    return "Hello";
}

void independent(char* hidden) 
{
    printf("The word you have entered is: %s\n", hidden);
}

void interactive(char* hidden)
{
    printf("The word you have entered is: %s\n", hidden);
}