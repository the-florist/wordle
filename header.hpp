#include <stdio.h>  //cout, endl, etc.
#include <stdlib.h> //standard functions
#include <iostream> //fopen, etc.
#include <cstdlib>  //rand and srand
#include <string>   //string type format and functions (very important!!)
//#include <vector>
#include <ctime>    //used for random number seed

using namespace std;

int debug = 0;        //flag that controls a number of build-in debugging functionality
FILE *debug_out;      //points to file where useful output can be stored during testing
string zero = "0";    //the "zero" string (needed because of a quirk in the string format type)