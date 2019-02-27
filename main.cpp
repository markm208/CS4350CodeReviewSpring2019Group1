#include <iostream> //do not include anything other than this

using namespace std;

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    const int len = 10;
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;
    
    c1 = 1;
    n1 = 1;
    d1 = 2;
    
    c2 = 2;
    n2 = 2;
    d2 = 3; 
    
    //if the C string could hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666
    }
    else
    {
        //display error message
    }

    return 0;
}

//new functions go here
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    int numberOne = c1 * d1 + n1;
    int numberTwo = c2 * d2 + n2;
    int newDenominator;
    
    if(d1 != d2)
    {
        numberOne = numberOne * d2;
        numberTwo = numberTwo * d1;
        newDenominator = d1 * d2;
    }
    else
    {
        newDenominator = d1;
    }

    int newNumerator = numberOne + numberTwo;
    float returnNum = newNumerator/newDenominator;
    float temp = returnNum;
    int deciCount = 0;
    int wholeCount = 0;

    while(temp > 1)
    {
        wholeCount++;
        temp/10;
    }

    if(len - wholeCount < 0)
    {
        return false;
    }
    else
    {
        int left = len - wholeCount;
        int divisor = 1;
        for(int i = left; i > 0; i--)
        {
            divisor = divisor * 10;
        }
        returnNum = returnNum * divisor;

        float answer = returnNum / divisor;
    }


    
}