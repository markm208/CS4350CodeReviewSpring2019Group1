#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
char* convertToChars(int toBeConverted, int len);
char* getDecimalPortion(int dividedInto, int dividedBy, int len);
int main()
{
	char result[10];
	if (multiply(1, 0, 0, 2, 0, 0, result, 9) == true) //test with "whole numbers"
	{
		for (int i = 0; i < 4; i++) //avoid /0 being printed
		{
			cout << static_cast<int>(result[i]) << endl; //have to cast back to an int to get proper numbers
														//anything over 255 cast as a char will result in wrong values being printed otherwise
		}
	}
	else
	{
		cout << "Error trying to multiply values together" << endl;
	}
	if (multiply(1, 1, 2, 2, 1, 2, result, 9) == true) //test with fractions should result in 3.75
	{
		for (int i = 0; i < 9; i++) //avoid /0 being printed
		{
			cout << static_cast<int>(result[i]) << endl;
		}
	}
	else
	{
		cout << "Error trying to multiply values together" << endl;
	}

	return 0;
	system("pause");
}

//new functions go here
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	bool retval = false; //assume there will be errors
	result[len] = '\0'; // place null terminated char at end of result so its not left off by mistake
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
		newNumeratorTwo = (c2*d2) + n2; //repeat above for second fraction
		multipliedDenominators = d1 * d2; //no converting needs to be done to the denominators so they are multiplied together
	}
	int multipliedNumerators = newNumeratorOne * newNumeratorTwo; //multiply the numerators together

	//now left with improper fraction which must be converted to decimal
	//to get the whole number first we must divide the new numerator by its denominator
	//newWholeNum being an int will prevent us from getting any decimals and still uphold spec
	int newWholeNum = multipliedNumerators / multipliedDenominators;
	char * toChar = convertToChars(newWholeNum, len);
	int pos = 0; //start at beginning of array
	while (toChar[pos] == 0)
	{
		pos++; //increment until we hit something that isn't a zeros
	}
	int i = 0; //will be used to move through result array
 	bool seenNonZero = false; //keep track whether or not we have seen a non zero number
 	while (pos< len && i < len)
	{
		if (toChar[pos] != 0 && seenNonZero == false) //if we haven't seen one then we have not reached proper number yet
		{
			seenNonZero = true; //once we have seen one set this to true and store the number
			result[i] = toChar[pos]; //this will put the number in the correct order at the front of the result array
		}
		else
		{
			result[i] = toChar[pos]; //otherwise we have seen a nonzero before and the zeroes we are seeing are important (such as in 20)
		}
		pos++; //either way increment both arrays
		i++;
	}
	//to get the decimal portion of the "float" we will use a helper function which takes the 
	//value of the multiplied denominators and the remainder of the division between the multiplied
	//numerators and denominators, as well as the length -1 to not overwrite the null terminated char
	char* decimals = getDecimalPortion(multipliedDenominators, (multipliedNumerators % multipliedDenominators), len - 1);
	retval = true;
	delete decimals; //free memory
	delete toChar;
	return retval;
}

char* convertToChars(int toBeConverted, int len)
{
	//to isolate digits to cast to chars -> use mods of 10 and regular division as well
	char* arr = new char[len]; //array to hold values, will be in reverse order 
	for (int i = 0; i < len-2; i++)
	{
		arr[i] = static_cast<char>(0); //fill array with zeroes for easier parsing later
	}
	arr[len-1] = '\0';
	int count = len-2; //start from one less then len to avoid overwriting null char
	while (toBeConverted > 0)
	{
		arr[count] = static_cast<char>(toBeConverted % 10); 
		count--; //putting actual number at end makes it easier to remove zeroes later on 
		toBeConverted = toBeConverted / 10;
	}
	return arr;

}
char* getDecimalPortion(int dividedInto, int dividedBy, int len) //newfunction to get the decimal portion of float
{                                                 //dividedInto divided by dividedBy 
	char* arr = new char[len];
	arr[0] = static_cast<char>(dividedBy); //assign first position in array to be first remainder
	int counter = 1;
	if (dividedBy > 0)
	{
		while (dividedInto % dividedBy > 1 && counter < len) //keep track of remainder from mod so we are not looping unnecessarily 
		{
			arr[counter] = static_cast<char>(dividedInto % dividedBy);
			dividedInto = dividedBy;
			dividedBy = arr[counter];
			counter++;
		}
	}
	return arr;
}


