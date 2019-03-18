#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

void testMath();
void testSubtract();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	testMath();

    return 0;
}
//--
void testMath()
{
	testSubtract();
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
	//shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	//shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	//shouldConvert(largeArray, 0, 0, 10);

	//2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	//shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	//shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	//shouldConvert(largeArray, 1, 0, 10);

	//1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	//shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	//shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	//shouldConvert(largeArray, 2, 5, 10);

	//1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	//shouldConvert(shortArray, 0, -54, 100);

	//1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	//shouldConvert(mediumArray, 0, -5416666, 10000000);

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
