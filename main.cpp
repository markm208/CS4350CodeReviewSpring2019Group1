#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int main()
{
    char result[4];
    if(multiply(1,0,0,2,0,0,result,4)==true) //test with "whole numbers"
    {
        for(int i =0; i < 3; i++) //avoid /0 being printed
        {
            cout<<result[i]<<endl;
        }
    }
    else
    {
        cout<<"Error trying to multiply values together"<<endl;
    }
    if(multiply(1,1,2,2,1,2,result,4)==true) //test with fractions should result in 3.75
    {
        for(int i =0; i < 3; i++) //avoid /0 being printed
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

    return retval;
}
