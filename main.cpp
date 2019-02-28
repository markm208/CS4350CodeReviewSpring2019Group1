#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int& c);
char* removeSpaces(char*& numString);
bool checkValidCharacteristic(char*& numString);
void test(char* num, int& c);

int main()
{
    int c = 0;
    char* num;
    num = "123.456";
    test(num, c);//good
    num = "   +123.456   ";
    test(num, c);//good
    num = "abc 123";
    test(num, c);//bad
    num = "-12f5.345";
    test(num, c);//bad
    num = "1 2 3    4 5    . 6  7   9  ";
    test(num, c);//good

}

void test(char* num, int& c){
    if(characteristic(num,c)){
        cout<<"good"<<endl;
        cout<<c<<endl;
    }
    else{
        cout<<"bad"<<endl;
    }
}

//new functions go here

bool characteristic(char* numString, int& c){
    //removes all ' ' from the numString array, which gets returned as a new array
    numString = removeSpaces(numString); //numString is not passed by reference, so it is a copy of the original

    //check for all values in the array being a number, '-', '+', or '.'
    if(!checkValidCharacteristic(numString)){
        return false;
    }
    
    //at this point, the characteristic is valid, atoi will return a valid characteristic (up to '.')
    c = atoi(numString);

    delete[] numString; //numString will point to the dynamically allocated array

    return true;
}

//removeSpaces alters the array given (numString) to remove all the spaces
char* removeSpaces(char*& numString){
    //a pointer to run through the numString array
    char* lead = numString;

    //the size of the array without spaces 
    int sizeofArray = 0;

    //loop through the array to find the size of the array without spaces
    while(*lead!='\0'){
        if(*lead!=' '){
            sizeofArray++;
        }
        lead++;
    }
    //one more to keep the null terminator
    sizeofArray++;

    //a new array is created to store all the non-space characters
    char* retArr = new char[sizeofArray];

    //have a trailing pointer to store the values
    char* trail = retArr;

    //reset the lead to the beginning of the input
    lead = numString;

    //loop through numString looking for non-space characters and add them to the new array
    while(*lead!='\0'){
        if(*lead != ' '){
            *trail = *lead;
            trail++;
            lead++;
        }
        else{
            lead++;
        }
    }
    *trail = '\0';//setting last char in new array to '\0', should be at the last index of the new array

    return retArr;
}

bool checkValidCharacteristic(char*& numString){
    //this function steps through the string to make sure it is a valid input for the characteristic function.
    char* ptr = numString;

    //the chars '-', or '+', have to be the first values and the rest of the string cannot have them
    if(*ptr == '-'||*ptr == '+'){
        //if they are the first value, they are valid, move to next char
        ptr++;
    }

    //at any point, if the numString contains a '.', the atoi function will break there, and the characteristic
    //will be found. 
    while(*ptr!='\0'){
        if(*ptr=='.'){
            return true;
        }
        //any values that are not 0 through 9 (or '.') are invalid at this point
        else if(*ptr<'0' || *ptr>'9'){
            return false;
        }
        ptr++;
    }

    //all the values in the string are numbers/valid, so return true;
    return true;
}