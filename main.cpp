#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int power(int x, int y);

int main()
{
    
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;
    ///////
    c1 = -2;
    n1 = 3;
    d1 = 10;
    c2 = 1;
    n2 = 33;
    d2 = 100;
    ///////
    if (divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        for(int i = 0; i < 10; i++)
        {
            cout << answer[i];
        }
        cout << endl;
    }
    else
    {
        cout << "Does not compute." << endl;
    }
    
    return 0;
}

//new functions go here
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
    cout << temp2 << endl;
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
    cout << endl << "temparray2 ";
    for (int i = 0; i < len - 1; i++)
        cout << temparray2[i];
    cout << endl;

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

