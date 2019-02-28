#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
char* convertToChars(int toBeConverted, int len);
char* getDecimalPortion(int dividedInto, int dividedBy, int len);
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
     int newNumeratorOne = 0;
     int newNumeratorTwo = 0;
     int multipliedDenominators = 1;
    if(d1 == 0 && d2!= 0)
    {
        newNumeratorOne = c1;
    }
    else if(d2 == 0 && d1 != 0)
    {
        newNumeratorTwo = c2;
    }
    else if(d1 ==0 && d2 ==0)
    {
        newNumeratorOne = 1; 
        newNumeratorTwo = c2;
    }
    else
    {
        newNumeratorOne = (c1 * d1) + n1; //must convert to mixed number so multiply whole number by denominator
                                         //then add the result to the numerator
        newNumeratorTwo = (c2*d2)+n2; //repeat above for second fraction
        multipliedDenominators = d1 * d2; //no converting needs to be done to the denominators so they are multiplied together
    }
    int multipliedNumerators = newNumeratorOne * newNumeratorTwo; //multiply the numerators together
    
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
    if(toBeConverted >= 1000000000) //int max is 10 numbers long so it is possible for something to be this long
    {

    }
    else if(toBeConverted >= 100000000 && toBeConverted < 1000000000) //9 numbers long
    {

    }
    else if(toBeConverted >= 10000000 && toBeConverted < 100000000) //8 numbers long
    {

    }
    else if(toBeConverted >= 1000000 && toBeConverted < 10000000) //7 numbers long
    {
        
    }
    else if(toBeConverted >= 100000 && toBeConverted < 1000000) //6 numbers long
    {

    }
    else if(toBeConverted >= 10000 && toBeConverted < 100000) //5 numbers long
    {
        
    }
    else if(toBeConverted >= 1000 && toBeConverted < 10000) //4 numbers long
    {
        
    }
    else if(toBeConverted >= 100 && toBeConverted < 1000) //3 numbers long
    {
        
    }
    else if(toBeConverted >= 10 && toBeConverted < 100) //2 numbers long
    {
        arr[1] = toBeConverted % 10; //ones place
        arr[0] = toBeConverted % 10; //placeholder for tens place
    }
    else if(toBeConverted < 10) //1 number long
    {
        arr[0] = toBeConverted;
    }

    return arr;

}
char* getDecimalPortion(int dividedInto, int dividedBy,int len) //newfunction to get the decimal portion of float
{                                                 //dividedInto divided by dividedBy 
    char* arr = new char[len];
    arr[0] = dividedBy; //assign first position in array to be first remainder
    int counter = 1; 
    if(dividedBy > 0)
    {
        while(dividedInto % dividedBy > 1 && counter < len) //keep track of remainder from mod so we are not looping unnecessarily 
    {
        arr[counter] = dividedInto % dividedBy;
        dividedInto = dividedBy;
        dividedBy = arr[counter];
        counter++;
    }
    }
    return arr;
}


