#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int& c);
char* removeSpaces(char*& numString);
bool checkValidCharacteristic(char*& numString);
int atoiReplica(char*& numString);

bool characteristic(char* numString, int& c){
    //removes all ' ' from the numString array, which gets returned as a new array
    char* numStringtemp = removeSpaces(numString);
    //numString now points to a dynamically allocated array, containing the original string without spaces

    //check for all values in the array being a number, '-', '+', or '.'
    if(!checkValidCharacteristic(numStringtemp)){
        delete[] numStringtemp;
        return false;
    }
    
    //at this point, the characteristic is valid, return a valid characteristic (up to '.')
    c = atoiReplica(numStringtemp);

    //numString will point to the dynamically allocated array
    delete[] numStringtemp;

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

    //at any point, if the numString contains a '.', the atoi function will break there, 
    //and the characteristic will be found. 
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

int atoiReplica(char*& numString){
    //This is a replacement for the atoi function, which can't be used in this program
    //it takes the string and, having already been value checked, converts everything up to '.'
    int retval = 0;
    //we need to make sure that we return a negative number if needed
    bool isnegative = false;
    
    //set up pointer to run through numString adding it to retval until we reach a '.' or the end of the string
    char* ptr = numString;

    //if the first character is negative, we know the number is negative
    if(*numString == '-'){
        isnegative = true;
        //increment ptr
        ptr++;
    }

    //if the first character in the array will not change the value of the return, skip it
    if(*ptr=='+' || *ptr=='0'){
        ptr++;
    }

    //loop through the numString and add values to retval appropriately
    while(*ptr!='.' && *ptr!='\0'){
        //move the value in retval over a decimal place
        retval *= 10;
        //add the next value in the array to the return
        retval += (int)(*ptr-'0');
        //increment ptr
        ptr++;
    }

    //if the returned value would be negative, make sure it is negative.
    if(isnegative){
        retval *= -1;
    }

    return retval;
}
