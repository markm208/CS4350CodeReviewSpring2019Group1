#include <iostream> //do not include anything other than this

using namespace std;

int main()
{
    // Number A      = 2.66;
    // Number B      = 1.50;
    // Number Answer = 1.16

    char answer[5];
    int c1, n1, d1;
    int c2, n2, d2;



    return 0;
}

//new functions go here

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) 
{
    int wholeNums = c1 - c2;    // This will give us the first thing to be put into the resutl array
    int decimalNums = n1 - n2;   //This will give us the second thing to be put into the result array

    if (decimalNums < 0) 
    {
        decimalNums = 100 + decimalNums;    // Just in case the decimals come out to be negative. 
    }
    
    
}