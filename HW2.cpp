#include "stdlib.h"
#include "Header/review.h"
#include <ctime>
#include <iostream>
using namespace std;

void PrintIntArr(int arr[], int n)
{
    for (int i = 0; i != n; i++)
    {
        cout << arr[i] << " ";
    }
}

int main()
{
    int num = 10;
    int test[num];
    srand((unsigned)time(NULL));

    for (int i = 0; i != num; i++)
    {
        test[i] = rand() % 19;
    }

    cout << "The element before rotate the array: "
         << "\n";
    PrintIntArr(test, num);

    rotate<int>(test, num, 3);
    cout << "\n"
         << "The element after rotate the array with k = 3: "
         << "\n";
    PrintIntArr(test, num);

    LeftOddRightEven(test, num);
    cout << "\n"
         << "The element after sperating the odd to left and even to right: "
         << "\n";
    PrintIntArr(test, num);

    cout << "\n";

    int a = 100;
    int &b = a;
    int &&c = a * 100;
    cout << a << " " << &b << " " << c;

    system("pause");
}