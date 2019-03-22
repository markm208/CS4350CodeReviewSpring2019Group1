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

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
char *convertToChars(int toBeConverted, int len);
char *getDecimalPortion(int dividedInto, int dividedBy, int len);

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

void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}

			if (expectedNumerator != n)
			{
				cout << "expected numerator: " << expectedNumerator << " "
					<< "actual numerator: " << n << endl;

			}

			if (expectedDenominator != d)
			{
				cout << "expected denominator: " << expectedDenominator << " "
					<< "actual denominator: " << d << endl;
			}
		}
	}
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}
//--
void shouldNotConvert(char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}
//--
void testMath()
{
	//add
	testAdd();
	testSubtract();
	testMultiply();
	testDivide();
}
//--
void testAdd()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (add(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 + 0 = "0"
	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//1 + 1 = "2"
	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 + -1.5 = "-.5"
	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5, 10);
	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, -5, 10);

	//1.125 + 1.6R = "2.79"
	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 79, 100);

	//1.125 + 1.6R = "2.7916666"
	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 7916666, 10000000);

	//1.125 + 1.6R = "2.79166666666666666"
	add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "2.79166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in add()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
//--
void testSubtract()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (subtract(INT_MIN, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 - 0 = "0"
	subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 0, 10);

	//1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 5, 10);

	//1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -54, 100);

	//1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5416666, 10000000);

	//1.125 - 1.6R = "-.54166666666666666"
	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "-.54166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in subtract()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
//--
void testMultiply()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (multiply(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 * 0 = "0"
	multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//3 * 2 = "6"
	multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 6, 0, 10);

	//3 * -1.5 = "-4.5"
	multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, -4, 5, 10);

	//1.125 * 1.6R = "1.87"
	multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 87, 100);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 875, 1000);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 875, 1000);
}
//--
void testDivide()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (divide(INT_MAX, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//cannot divide by zero
	if (divide(10, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: cannot divide by zero" << endl;
	}

	//0 / 1 = "0"
	divide(0, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//6 / 3 = "2"
	divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 0, 10);
	divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 0, 10);

	//1 / -1.5 = "-.66"
	divide(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -66, 100);
	
	//1 / -1.5 = "-.6666666"
	divide(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -6666666, 10000000);
	
	//1 / -1.5 = "-.66666666666666666"
	divide(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	char expectedResult1[] = "-.66666666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult1[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in divide()." << endl
				<< "Expected: " << expectedResult1 << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}

	//1.125 / 1.6R = "0.67"
	divide(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 67, 100);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 675, 1000);

	//1.125 / 1.6R = "0.675"
	divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 675, 1000);
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

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	bool retval = false;	//assume there will be errors
	result[len - 1] = '\0'; // place null terminated char at end of result so its not left off by mistake
	bool isNegative = false; //assume both are positive
	if (c1 < 0 && c2 >= 0 || c1 >= 0 && c2 < 0)
	{
		//one number is negative, but not both means the answer will be negative.
		isNegative = true;
	}
	int newNumeratorOne = 0;
	int newNumeratorTwo = 0;
	int multipliedDenominators = 1;
	if (d1 == 0 && d2 != 0)
	{
		newNumeratorOne = c1;
	}
	else if (d2 == 0 && d1 != 0)
	{
		newNumeratorTwo = c2;
	}
	else if (d1 == 0 && d2 == 0)
	{
		newNumeratorOne = 1;
		newNumeratorTwo = c2;
	}
	else
	{
		newNumeratorOne = (c1 * d1) + n1; //must convert to mixed number so multiply whole number by denominator
										  //then add the result to the numerator
		newNumeratorTwo = (c2 * d2) + n2; //repeat above for second fraction
		multipliedDenominators = d1 * d2; //no converting needs to be done to the denominators so they are multiplied together
	}
	int multipliedNumerators = newNumeratorOne * newNumeratorTwo; //multiply the numerators together

	//now left with improper fraction which must be converted to decimal
	//to get the whole number first we must divide the new numerator by its denominator
	//newWholeNum being an int will prevent us from getting any decimals and still uphold spec
	int newWholeNum = multipliedNumerators / multipliedDenominators;

	//we now must get the character array of the whole number and put it into our results
	char *toChar = convertToChars(newWholeNum, len);
	int pos = 0;//start at beginning of toChar array
	int i = 0; //will be used to move through result array
	//however if we have a negative we must insert a negative sign at the beginning instead
	if (isNegative == true)
	{
		//i now begins at 1
		i = 1;
		//first member of result is now a negative
		result[0] = '-'; 

	}

	//this loop checks for leading zeroes and makes sure none are picked up as part of the answer
	while (toChar[pos] == '0')
	{
		pos++; //increment until we hit something that isn't a zeros
	}

	//this loop moves through the result array from the beginning and inserts the answer from toChar
	//this will remove the need for leading zeroes
	while (pos < len && i < len)
	{

		result[i] = toChar[pos]; //this will put the number in the correct order at the front of the result array
		pos++;
		i++;
	}
	//to get the decimal portion of the "float" we will use a helper function which takes the
	//value of the multiplied denominators and the remainder of the division between the multiplied
	//numerators and denominators, as well as the length -1 to not overwrite the null terminated char
	char * decimals = getDecimalPortion(multipliedDenominators, (multipliedNumerators % multipliedDenominators), len);

	i++;			 //i still holds the position from the whole number insertion, and so moving one past it will-
					 //-allow us to avoid overwriting it
	result[i] = '.'; //at this point we know for sure we are at the decimal portion, and can add the point
	i++;			 //increment one more time to avoid overwriting decimal point
	pos = 0;		 //reset pos to be at zero so we can start from beginning of decimal array

	while (i < len) //begin moving through the result array and the decimal array and join them together
	{
		result[i] = decimals[pos];
		i++;
		pos++;
		if (i == (len - 1))
		{
			retval = true; //if we got to here its safe to assume we were able to insert things without issue and can set-
						   //-retval to true
			break;
		}
	}


	i = 0;   //reset i just to make sure next pass through function has clean slate
	pos = 0; //reset pos just to make sure next pass through function has clean slate

	delete[] decimals; //free memory
	delete[] toChar;
	return retval;
}

char *convertToChars(int toBeConverted, int len)
{
	//to isolate digits to cast to chars -> use mods of 10 and regular division as well
	char *arr = new char[len]; //array to hold values, will be in reverse order
	for (int i = 0; i < len - 1; i++)
	{
		arr[i] = '0' + (0); //fill array with zeroes for easier parsing later
	}
	arr[len - 1] = '\0';
	int count = len - 2; //start from two less then len to avoid overwriting null char
	while (toBeConverted > 0)
	{
		arr[count] = '0' + (toBeConverted % 10);
		count--; //putting actual number at end makes it easier to remove zeroes later on
		toBeConverted = toBeConverted / 10;
	}
	return arr;
}
char *getDecimalPortion(int dividedInto, int dividedBy, int len) //newfunction to get the decimal portion of float
{
	char *arr = new char[len];
	arr[0] = '0' + (dividedBy); //assign first position in array to be first remainder
	int counter = 1;
	if (dividedBy > 0)
	{
		while (dividedInto % dividedBy >= 1 && counter < len) //keep track of remainder from mod so we are not looping unnecessarily
		{
			arr[counter] = '0' + ((dividedInto) % (dividedBy));
			int newdividedBy = (dividedInto) % (dividedBy);
			dividedInto = dividedBy;
			dividedBy = newdividedBy;
			counter++;
		}
	}
	return arr;
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
