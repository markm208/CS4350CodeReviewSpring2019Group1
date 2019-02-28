#include <iostream>

using namespace std;

int main(){
    char arr[] = "-123.456";
    int i = atoi(arr);
    std::cout<<i<<std::endl;
    //returned -123

    char arr2[] = {'-','1','a','3'};
    i = atoi(arr2);
    std::cout<<i<<std::endl;
    //returned 0

    char arr3[] = {'-','1','2','3'};
    char* ptr = arr3 + 1;
    i = atoi(ptr);
    std::cout<<i<<std::endl;
    //returned 123
    return 0;
}