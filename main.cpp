#include <iostream> //do not include anything other than this

using namespace std;

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
	const int len = 10;
	char answer[len];
	int c1, n1, d1;
	int c2, n2, d2;

	c1 = 1;
	n1 = 3;
	d1 = 4;

	c2 = 2;
	n2 = 1;
	d2 = 2;

	if (add(c1, n1, d1, c2, n2, d2, answer, len))
	{
		cout << "The result is: ";
		for (int i = 0; i < len; i++)
		{
			cout << answer[i];
		}
		cout << endl;
	}
	else
	{
		cout << "Answer is to large for indicated size." << endl;
	}

	system("pause");
	return 0;
}

//new functions go here
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
		return false;
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
	mantissa = (newNumerator * multiplier);
	mantissa = mantissa / newDenominator;

	temp = mantissa;

	for (int i = 0; i < len - counter; i++)
	{
		int remainder = temp % 10;
		result[len - i - 1] = char('0' + remainder);
		temp = temp / 10;
	}

	return retVal;

}