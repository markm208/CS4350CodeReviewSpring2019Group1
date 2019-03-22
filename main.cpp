#include <iostream> //do not include anything other than this

using namespace std;

void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(char number[]);

bool characteristic(char numString[], int& c);
char* removeSpaces(char*& numString);
bool checkValidCharacteristic(char*& numString);
int atoiReplica(char*& numString);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int power(int x, int y);

void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	testMath();
    return 0;
}
//--
void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123, 456, 1000);
	shouldConvert("    123.456", 123, 456, 1000);
	shouldConvert("123.456    ", 123, 456, 1000);
	shouldConvert("    123.456    ", 123, 456, 1000);

	shouldConvert("+123.456", 123, 456, 1000);
	shouldConvert("   +123.456", 123, 456, 1000);
	shouldConvert("+123.456   ", 123, 456, 1000);
	shouldConvert("   +123.456   ", 123, 456, 1000);

	shouldConvert("-123.456", -123, 456, 1000);
	shouldConvert("   -123.456", -123, 456, 1000);
	shouldConvert("-123.456   ", -123, 456, 1000);
	shouldConvert("    -123.456   ", -123, 456, 1000);

	shouldConvert("0.456", 0, 456, 1000);
	shouldConvert("   0.456", 0, 456, 1000); 
	shouldConvert("0.456   ", 0, 456, 1000);
	shouldConvert("   0.456   ", 0, 456, 1000);

	shouldConvert("-0.456", 0, -456, 1000);
	shouldConvert("   -0.456", 0, -456, 1000);
	shouldConvert("-0.456   ", 0, -456, 1000);
	shouldConvert("   -0.456   ", 0, -456, 1000);

	shouldConvert(".456", 0, 456, 1000);
	shouldConvert("    .456", 0, 456, 1000);
	shouldConvert(".456   ", 0, 456, 1000);
	shouldConvert("   .456   ", 0, 456, 1000);

	shouldConvert("-.456", 0, -456, 1000);
	shouldConvert("    -.456", 0, -456, 1000);
	shouldConvert("-.456   ", 0, -456, 1000);
	shouldConvert("   -.456   ", 0, -456, 1000);

	shouldConvert("123456", 123456, 0, 10);
	shouldConvert("   123456", 123456, 0, 10);
	shouldConvert("123456   ", 123456, 0, 10);
	shouldConvert("   123456   ", 123456, 0, 10);

	shouldConvert("-123456", -123456, 0, 10);
	shouldConvert("   -123456", -123456, 0, 10);
	shouldConvert("-123456   ", -123456, 0, 10);
	shouldConvert("   -123456   ", -123456, 0, 10);

	shouldConvert("000123.456", 123, 456, 1000);
	shouldConvert("123.45600000", 123, 456, 1000);
	shouldConvert("00000123.45600000", 123, 456, 1000);

	shouldConvert("-000123.456", -123, 456, 1000);
	shouldConvert("-123.45600000", -123, 456, 1000);
	shouldConvert("-00000123.45600000", -123, 456, 1000);

	shouldConvert("123.00000456", 123, 456, 100000000);
	shouldConvert("-123.00000456", -123, 456, 100000000);
}

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




bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	int numberOne = c1 * d1 + n1;
	int numberTwo = c2 * d2 + n2;
	int newDenominator;
	int counter = 0;
	bool retVal = true;

	if (d1 != d2)
	{
		//Convert the fractions into improper fractions first.
		numberOne = numberOne * d2;
		numberTwo = numberTwo * d1;
		newDenominator = d1 * d2;
	}
	else
	{
		newDenominator = d1;
	}

	//Create the new numerator
	int newNumerator = numberOne + numberTwo;
	//charact is the new main number.
	int charact = newNumerator / newDenominator;

	int temp = charact;
	int digitsLeft;


	while (temp != 0)
	{
		counter++;
		temp = temp / 10;
	}

	//See if it is possible to return the function.
	if (counter + 2 > len)
	{
		retVal = false;
		return retVal;
	}
	else
	{
		temp = charact;

		if (counter == 0)
		{
			result[counter] = '0';
			result[counter + 1] = '.';
			counter += 2;
		}
		else
		{
			result[counter] = '.';

			for (int i = counter; i > 0; i--)
			{
				int remainder = temp % 10;
				result[i - 1] = char('0' + remainder);
				temp = temp / 10;
			}

			counter++;
		}

		digitsLeft = len - (counter);
	}

	int multiplier = 1;
	int digitsRem = digitsLeft;

	while (digitsRem != 0)
	{
		multiplier = multiplier * 10;
		digitsRem--;
	}

	unsigned long mantissa = 0;
	mantissa = (newNumerator * multiplier) / newDenominator;

	temp = mantissa;

	for (int i = 0; i < len - counter; i++)
	{
		int remainder = temp % 10;
		result[len - i - 1] = char('0' + remainder);
		temp = temp / 10;
	}

	return retVal;
}



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
    //cout << newCharacteristic << endl;
    
    // Calculating how many digets the characteristic has in it
    int digetcounter;
    int temporaryNumber;
    while (temporaryNumber != 0)
    {
        digetcounter++;
        temporaryNumber = temporaryNumber / 10;
    }
    if (digetcounter > len)
    {
        return false;
    }
    else
    {
        // For if the number is less than 1 but greater than 0
        if (digetcounter == 0)
        {
            result[0] = '.';
            digetcounter++;
        }
        else
        {
            for (int i = 0; i < digetcounter; i++)
            {
                //  Trying to place the numbers inside the char array.
                int r = temporaryNumber % 10;
                result[i + 1] = char('0' + r);
                temporaryNumber = temporaryNumber / 10;
            }
            digetcounter++;
        }
        
    }
    //cout << digetcounter << endl;
    //  Trying to work back out of the complex fraction
    int remaindingDec = (newCharacteristic * digetcounter) / commonDenom;
    //cout << remaindingDec << endl;
    
   return true;
}


bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    bool isNegative = false;
    if (c1 < 0)
    {
        c1 = c1 * -1;
        isNegative = !isNegative;
    }
    if (c2 < 0)
    {
        c2 = c2 * -1;
        isNegative = !isNegative;
    }
    
    int newDenom1 = (c1 * d1) + n1;
    int numDigits = 0;
    int temp = newDenom1;
    //this loop divides the integer by ten until it reaches 0 to find the number of digits it has
    while (temp != 0)
    {
        numDigits++;
        temp = temp / 10;
    }
    //if the int holds 9 digits, then with the decimal point, the array will hold 8 digits
    int multiplyer = power(10, (9 - numDigits));
    //this gives an 8 digit number, so the decimals are preserved when dividing
    int bigDenom = newDenom1 * multiplyer;
    
    int newDenom2 = (c2 * d2) + n2;
    
    int answer = bigDenom / newDenom2;
    temp = newDenom1 / newDenom2;
    int decPlace = 1; //decimal point goes at result[1]

    while (temp != 0) //this could probably be a function
    {
        decPlace++; //increases index for decimal point for every digit in characteristic of answer
        temp = temp / 10;
    }
    if(isNegative)
    {
        decPlace++;
    }
    
    int temp2 = answer;
    //cout << temp2 << endl;
    char temparray2[10];
    for(int i = 0; i < 10; i++)
    {
        temparray2[i] = '0' + (temp2 % 10);
        //cout << temp2 % 10 << endl;
        //cout << "test " << temparray2[i] << endl;
        temp2 = temp2 / 10;
    }
    /*
    while (temp2 > 0)
    {
        temparray2[count] = static_cast<char>(temp2 % 10);
        cout << temparray2[count] << " ";
        temp2 = temp2 / 10;
        count++;
    }
     */
     /*
    cout << endl << "temparray2 ";
    for (int i = 0; i < len - 1; i++)
        cout << temparray2[i];
    cout << endl;
    */
    char temparray[10];
    
    // temparray2 into temparray the correct direction
    int b = 9;
    while(temparray2[b] == '0')
    {
        b--;
    }
    int c = b;
    for(int i = 0; i < b + 1; i++)
    {
        temparray[i] = temparray2[c];
        c--;
    }
     
    
    
    //sprintf(temparray, "%d", answer);
    
    /*
     for (int i = 0; i < len; i++)
         cout << temparray[i];
     cout << endl;
    */
    
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        if (i == 0 && isNegative)
        {
            result[i] = '-';
            continue;
        }
        if (i == decPlace)
        {
            result[i] = '.';
            continue;
        }
        if (i == 9)
        {
            result[i] = '\0';
        }
        else {
            result[i] = temparray[j];
            j++;
        }
    }
    

    return true;
}

int power(int x, int y) // this should not be a function
{
    int answer = x;
    for (int i = 0; i < (y - 1); i++)
    {
        answer = answer * x;
    }
    return answer;
}
