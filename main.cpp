#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int main()
{
    char result[9];
    if(multiply(1,0,0,2,0,0,result,9)==true) //test with "whole numbers"
    {
        for(int i =0; i < 4; i++) //avoid /0 being printed
        {
            cout<<result[i]<<endl;
        }
    }
    else
    {
        cout<<"Error trying to multiply values together"<<endl;
    }
    if(multiply(1,1,2,2,1,2,result,4)==true) //test with fractions should result in 3.75
    {
        for(int i =0; i < 3; i++) //avoid /0 being printed
        {
            cout<<result[i]<<endl;
        }
    }
    else
    {
        cout<<"Error trying to multiply values together"<<endl;
    }

    return 0;
}

//new functions go here
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    bool retval = false; //assume there will be errors
    int newNumeratorOne = c1 + n1; //add the whole number to the numerator for first number
    int newNumeratorTwo = c2+n2; //add the whole to the numerator for second number
    int multipliedNumerators = newNumeratorOne * newNumeratorTwo; //multiply the numerators together
    int multipliedDenominators = d1 * d2; //no converting needs to be done to the denominators so they are multiplied together
    //now left with imperfect fraction 

    return retval;
}
