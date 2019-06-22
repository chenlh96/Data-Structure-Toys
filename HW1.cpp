#include "Header/list.h"
#include "Header/review.h"
#include "stdlib.h"
#include <ctime>
#include <iostream>
using namespace std;

const int NumOfElem = 10;

const int NumOfElems[5] = {1000, 10000, 50000, 75000, 10000};

void RandGenArr(int *arr, int n, int min, int max)
{
    srand((unsigned)time(NULL));

    for (int i = 0; i != NumOfElem; i++)
    {
        arr[i] = rand() % (max - min); // To get the random number between 1 and 100
    }
}

void Msg(string msgStr)
{
    cout << "\n"
         << msgStr
         << "\n";
}

int main()
{
    // Generate a array with 20 interger between 1 and 100 randomly
    int TestArr[NumOfElem];
    cout << "---------------------------------------------------------";

    RandGenArr(TestArr, NumOfElem, 1, 20);

    // Generate a seqnencial list and singly link list base on ths array
    IntSeqList SeqList(TestArr, NumOfElem);

    Msg("The element of the list is: ");
    SeqList.PrintList();

    try
    {
        SeqList.Insert(5, 23);
    }
    catch (char const *s)
    {
        cout << s;
    }

    Msg("After inserting element 23 at the 6th position, the list has: ");
    SeqList.PrintList();

    Msg("The element which its value is 10 locates in: ");
    int locate = SeqList.Locate(10);
    if (locate != -1)
    {
        cout << locate;
    }
    else
    {
        cout << "No such value";
    }

    try
    {
        SeqList.Delete(6);
    }
    catch (char const *s)
    {
        cout << s
             << "\n";
    }

    Msg("After deleting the 7th element, the list has: ");
    SeqList.PrintList();

    cout << "\n"
         << "---------------------------------------------------------";

    RandGenArr(TestArr, NumOfElem, 1, 20);
    LinkList<int> LinkList(TestArr, NumOfElem);

    Msg("The element of this link list is: ");
    LinkList.PrintList();

    Msg("After inserting element 23 at the 20th position, the list has: ");
    try
    {
        LinkList.Insert(20, 23);
        LinkList.PrintList();
    }
    catch (char const *s)
    {
        cout << s;
    }

    Msg("The element which its value is 10 locates in: ");
    int locate1 = LinkList.Locate(10);
    if (locate1 != -1)
    {
        cout << locate1;
    }
    else
    {
        cout << "No such value";
    }

    try
    {
        LinkList.Delete(6);
    }
    catch (char const *s)
    {
        cout << s
             << "\n";
    }

    Msg("After deleting the 7th element, the list has: ");
    LinkList.PrintList();

    cout << "\n"
         << "---------------------------------------------------------"
         << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << "Number of elements: " << NumOfElems[i] << " ";
        srand((unsigned)time(NULL));
        int testArr[NumOfElems[i]];
        for (int i = 0; i < NumOfElems[i]; i++)
        {
            testArr[i] = rand();
        }
        double timeUse = MySort<int>(testArr, NumOfElems[i]);
        cout << "After the sorting, the exceed time is: " << timeUse
             << "\n";
    }

    Point p, p1, p2, p3;

    cout << "------------------------------------"
         << "\n"
         << "\n"
         << "\n"
         << "------------------------------------"
         << "\n";

    cin >> p;

    cout << "Then the results are : "
         << "\n";
    cout << p
         << "\n";

    p1 = p;
    cout << p1
         << "\n";

    p2 = p1 * 3;
    cout << p2
         << "\n";

    p3 = p1 + p2;
    cout << p3
         << "\n";

    if (p3 > p2)
        cout << "p3 > p2"
             << "\n";
    if (p2 < p1)
        cout << "p2 < p1"
             << "\n";

    system("pause");
    return 0;
}