#include "Header/list.h"
#include <iostream>
using namespace std;

template <class T>
void Union(SeqList<T> &List1, SeqList<T> &List2)
{
    int *tmp = new int[List2.length];
    for (int i = 0; i != List2.length; i++)
    {
        tmp[i] = 0;
        if (List1.LocateFirst(List2[i]) == -1)
        {
            tmp[i] = 1;
        }
    }

    for (int i = 0; i != List2.length; i++)
    {
        if (tmp[i] == 1)
        {
            List1.Add(List2[i]);
        }
    }

    delete[] tmp;
}

template <class T>
void Intersect(SeqList<T> &List1, SeqList<T> &List2)
{
    int i = 0;
    while (i != List1.length)
    {
        if (List2.LocateFirst(List1[i]) != -1)
        {
            List1.Delete(i);
        }
        i++;
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    SeqList<int> tsl(arr, 5);

    cout << "Print the list after initialized"
         << "\n";
    tsl.PrintList();
    cout << "The length of the list is: " << tsl.Length()
         << "\n";

    try
    {
        tsl.Insert(4, 9);
        cout << "After inserting 9 in index 4: "
             << "\n";
        tsl.PrintList();

        tsl.Insert(6, 4);
        cout << "After inserting 4 in index 6: "
             << "\n";
        tsl.PrintList();
    }
    catch (char const *s)
    {
        cout << s << "\n";
    }

    cout << "First index of element 4 is: " << tsl.LocateFirst(4)
         << "\n"
         << "First index of element 7 is: " << tsl.LocateFirst(7)
         << "\n";

    cout << "Before deleting the elements, print list: "
         << "\n";
    tsl.PrintList();

    try
    {
        tsl.Delete(1);
        cout << "After deleting the element in index 1: "
             << "\n";
        tsl.PrintList();

        tsl.Delete(10);
        cout << "After deleting the element in index 10: "
             << "\n";
        tsl.PrintList();
    }
    catch (char const *s)
    {
        cout << s << "\n";
    }

    cout << "After deleting the elements, print list: "
         << "\n";
    tsl.PrintList();
    cout << "The length of the list is: " << tsl.Length()
         << "\n";

    int arr2[6] = {1, 7, 8, 9, 100, 8};
    SeqList<int> tsl1(tsl);    
    SeqList<int> tsl2(arr2, 6);

    cout << "The two list that used to union: "
         << "\n";
    tsl.PrintList();
    tsl2.PrintList();
    Union<int>(tsl, tsl2);
    cout << "After union the two list, the elements of  first list has: "
         << "\n";
    tsl.PrintList();

    cout << "The two lists that used to interact: "
         << "\n";
    tsl1.PrintList();
    tsl2.PrintList();
    Intersect<int>(tsl1, tsl2);
    cout << "After interact, the element has: "
         << "\n";
    tsl1.PrintList();

    system("pause");
    return 0;
}