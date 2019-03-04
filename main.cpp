#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    // Number A      = 2.66;
    // Number B      = 1.50;
    // Number Answer = 1.16

    char answer[5];
    int len = 10;
    int c1 = 20; int n1 = 66; int d1 = 100;
    int c2 = 10; int n2 = 5; int d2 = 10;

    if(subtract(c1, n1, d1, c2, n2, d2, answer, len))
    {
        for (int i = 0; i < len; i++)
        {
            cout << answer[i];
        }
    }
    else
    {
        cout << "Error Computing" << endl;
    }

    return 0;
}

//new functions go here

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) 
{
    // Turns the numbers into complex fractions
    int numberOne = (c1 * d1) + n1;
    int numberTwo = (c2 * d2) + n2;

    // Making common denominators
    int commonDenom;
    if (d1 != d2) 
    {
        numberOne = numberOne * d2;
        numberTwo = numberTwo * d1;
        commonDenom = d1 * d2;
    }
    
    // Subtract newly complex numbers
    int subtractedNum = numberOne - numberTwo;
    int newCharacteristic = subtractedNum / commonDenom;
    cout << newCharacteristic << endl;
    
   return false;
}