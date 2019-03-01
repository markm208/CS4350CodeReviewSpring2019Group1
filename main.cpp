#include <iostream> //do not include anything other than this

using namespace std;


int main()
{
    // Number A      = 2.66;
    // Number B      = 1.50;
    // Number Answer = 1.16

    char answer[5];
    int c1, n1, d1;
    int c2, n2, d2;

    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        for (int i = 0; i < len; i++)
        {
            cout << answer[i];
        }
    }
    else
    {
        cout << "Error Computing" << endl;
    }

    return 0;
}

//new functions go here

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) 
{
    //Wasn't able to make this happen today. 
   return false;
}