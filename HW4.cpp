#include "Header\bigInt.h"
#include "Header/bigInt.cpp"
#include "Header\list.h"
#include "Header\applicationOfList.h"
#include <iostream>
using namespace std;

int main()
{
    int arr[6] = {1, 2, 3, 4, 5, 6};
    LinkList<int> ll(arr, 6);

    cout << "Print the list after initialized"
         << "\n";
    ll.PrintList();
    cout << "The length of the list is: " << ll.Length()
         << "\n";

    try
    {
        ll.Insert(4, 9);
        cout << "After inserting 9 in index 4: "
             << "\n";
        ll.PrintList();

        ll.Insert(8, 4);
        cout << "After inserting 4 in index 8: "
             << "\n";
        ll.PrintList();
    }
    catch (char const *s)
    {
        cout << s << "\n";
    }

    cout << "First index of element 4 is: " << ll.Locate(4)
         << "\n"
         << "First index of element 7 is: " << ll.Locate(7)
         << "\n";

    cout << "Before deleting the elements, print list: "
         << "\n";
    ll.PrintList();

    try
    {
        ll.Delete(1);
        cout << "After deleting the element in index 1: "
             << "\n";
        ll.PrintList();

        ll.Delete(100);
        cout << "After deleting the element in index 100: "
             << "\n";
        ll.PrintList();
    }
    catch (char const *s)
    {
        cout << s << "\n";
    }

    cout << "After deleting the elements, print list: "
         << "\n";
    ll.PrintList();
    cout << "The length of the list is: " << ll.Length()
         << "\n";

    cout << "\n"
         << "--------------------------------------------"
         << "\n";

    cout << "Now test the func of the sets calculate: "
         << "\n"
         << "First we test the copy constructor and the override operator= :"
         << "\n";

    LinkList<int> llcopy1(ll);
    LinkList<int> llcopy2 = ll;

    cout << "Copy of the list ll"
         << "\n";
    llcopy1.PrintList();
    cout << "llcopy2 is the operator= of the ll"
         << "\n";
    llcopy2.PrintList();

    int arrUnion[5] = {1, 2, 8, 4, 7};
    LinkList<int> llunion(arrUnion, 5);

    cout << "Union: ";
    ll.PrintList();
    cout << "and: ";
    llunion.PrintList();

    Union<int>(ll, llunion);
    cout << "is: ";
    ll.PrintList();

    cout << "Intersect: ";
    llcopy1.PrintList();
    cout << "and: ";
    llunion.PrintList();

    Intersect<int>(llcopy1, llunion);
    cout << "is: ";
    llcopy1.PrintList();

    LinkList<int> llunioncopy(llunion);
    cout << "Compare: ";
    llunion.PrintList();
    cout << "and: ";
    llunioncopy.PrintList();
    cout << "is: " << IsEqual<int>(llunion, llunioncopy);

    cout << "Compare: ";
    llunion.PrintList();
    cout << "and: ";
    ll.PrintList();
    cout << "is: " << IsEqual<int>(llunion, ll) << "\n"
         << "let the former list different the latter list, The result is:  "
         << "\n";

    Different(ll, llunion);
    ll.PrintList();

    cout
        << "\n"
        << "--------------------------------------------"
        << "\n";

    int arr1[9] = {1, 2, 3, 4, 5, 6, 1, 1, 1};
    int arr2[9] = {8, 3, 1, 4, 9, 2, 1, 1, 1};
    int arr3[3] = {6, 5, 8};
    int arr4[6] = {1, 1, 1, 1, 1, 1};
    int arr5[3] = {2, 1, 1};
    int i = 4521;

    BigInt bi1(arr1, 9);
    BigInt bi2(arr2, 9, -1);
    BigInt bi3(arr3, 3);
    BigInt bi4(arr4, 6);
    BigInt bi5(arr5, 3);
    BigInt bi6 = i;
    BigInt bi7;
    BigInt bi2eq = bi2;

    cout << "Test of the constructors: "
         << "\n"
         << "  Copy of BigInt " << bi1 << " is: " << BigInt(bi1) << "\n"
         << "  Override of operator= BigInt: " << bi2 << " = " << bi2eq << "\n"
         << "  Int to BigInt " << i << " is: " << BigInt(i) << "\n"
         << "  Override of operator= Int: " << i << " = " << bi6 << "\n"
         << "Test of logic operator: "
         << "\n"
         << "  !" << bi6 << " is: " << !bi6 << "\n"
         << bi7 << " && " << bi1 << " is: " << (bi7 && bi1) << "\n"
         << bi7 << " || " << bi1 << " is: " << (bi7 || bi1) << "\n"
         << "Test of comparison operator: "
         << "\n"
         << bi1 << " == Copy of " << bi1 << " ? " << (bi1 == BigInt(bi1)) << "\n" // 1
         << bi1 << " != " << bi3 << " ? " << (bi1 != bi3) << "\n"                 // 1
         << bi1 << " < " << bi2 << " ? " << (bi1 < bi2) << "\n"                   // 1
         << bi1 << " >= " << bi4 << " ? " << (bi1 >= bi4) << "\n"                 // 0
         << bi5 << " > " << bi3 << " ? " << (bi5 > bi3) << "\n"                   // 1
         << bi3 << " <= " << bi4 << " ? " << (bi3 <= bi4) << "\n"                 // 0
         << "Test of calculation operator: "
         << "\n"
         << bi1 << " + " << bi2.abs() << " = " << bi1 + bi2.abs() << "\n"
         << bi1 << " - " << bi3 << " = " << bi1 - bi3 << "\n"
         << -bi3 << " * " << bi5 << " = " << (-bi3) * bi5 << "\n"
         << bi4 << " / " << bi5 << " = " << bi4 / bi5 << "\n"
         << bi4 << " % " << bi5 << " = " << bi4 % bi5 << "\n";

    system("pause");
}