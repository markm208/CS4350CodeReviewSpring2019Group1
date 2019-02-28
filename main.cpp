#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int main()
{
    char result[10];
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
    if(multiply(1,1,2,2,1,2,result,9)==true) //test with fractions should result in 3.75
    {
        for(int i =0; i < 9; i++) //avoid /0 being printed
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
    result[len] ='\0'; // place null terminated char at end of result so its not left off by mistake
    int newNumeratorOne = (c1 * d1) + n1; //must convert to mixed number so multiply whole number by denominator
                                         //then add the result to the numerator
    int newNumeratorTwo = (c2*d2)+n2; //repeat above for second fraction
    int multipliedNumerators = newNumeratorOne * newNumeratorTwo; //multiply the numerators together
    int multipliedDenominators = d1 * d2; //no converting needs to be done to the denominators so they are multiplied together
    
    //now left with improper fraction which must be converted to decimal
    //to get the whole number first we must divide the new numerator by its denominator
    //newWholeNum being an int will prevent us from getting any decimals and still uphold spec
    int newWholeNum = multipliedNumerators / multipliedDenominators; 
    char* toChar = convertToChars(newWholeNum,len); 

    //to get the decimal portion of the "float" we will use a helper function which takes the 
    //value of the multiplied denominators and the remainder of the division between the multiplied
    //numerators and denominators, as well as the length -1 to not overwrite the null terminated char
    char* decimals = getDecimalPortion(multipliedDenominators, (multipliedNumerators % multipliedDenominators),len-1);
    
    delete decimals;
    delete toChar;
    return retval;
}

char* convertToChars(int toBeConverted,int len)
{
    //to isolate digits to cast to chars -> use mods of 10 and regular division as well
    char* arr = new char[len];

}
char* getDecimalPortion(int dividedInto, int dividedBy,int len) //newfunction to get the decimal portion of float
{                                                 //dividedInto divided by dividedBy 
    char* arr = new char[len];
    *arr[0] = dividedBy; //assign first position in array to be first remainder
    int counter = 1; 

    while(dividedInto % dividedBy > 1 && counter < len) //keep track of remainder from mod so we are not looping unnecessarily 
    {
        *arr[counter] = dividedInto % dividedBy;
        dividedInto = dividedBy;
        dividedBy = *arr[counter];
        counter++;
    }
    return arr;
}


