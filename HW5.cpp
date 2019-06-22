#include "Header/ApplicationOfList.h"
#include <iostream>
using namespace std;

int main()
{
    // the original array used to create the lists
    int arr[7] = {1, 2, 3, 4, 5, 6, 7};

    // 1.	循环链表设计实现：带头节点
    // 循环链表的实现：实现循环链表，并进行测试。参考实验书p174单链表的实现做法，实现循环链表。
    // 2.	单链表的设计实现：不带头节点
    // 参考实验书p174单链表的实现做法，实现不带头节点的单链表。

    // 对1，2题要求：
    // （1）加入求线性表的长度等操作：结合本章习题的算法设计题做。
    // （2）重新给定测试数据，验证抛出异常机制
    // （3）将单链表的结点结构用结点类实现

    cout << "test of construct functions: "
         << "\n";
    CyclicList<int> cl(arr, 7);
    cout << "The test of the normal constructor: ";
    cl.PrintList();
    CyclicList<int> cl1(cl);
    cout << "The test of the copy constructor: ";
    cl1.PrintList();
    CyclicList<int> cl2 = cl;
    cout << "The test of the equal operator: ";
    cl2.PrintList();

    cout << "\n"
         << "now we test the function of this class: "
         << "\n";

    const int numOfInsert = 4;
    int insertArr[numOfInsert][2] = {
        {123, 0},
        {9, 8},
        {9, 7},
        {13, 5},
    };

    for (int i = 0; i != numOfInsert; i++)
    {
        try
        {
            cout << "Insert number " << insertArr[i][0] << " in index " << insertArr[i][1] << ": ";
            cl.Insert(insertArr[i][1], insertArr[i][0]);
            cl.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    const int numOfDel = 7;
    int delArr[numOfDel] = {14, 1, 0, 6, 4, 12, 2};

    cout << "\n"
         << "Before deleteing elements, the list has: "
         << "\n";
    cl1.PrintList();

    for (int i = 0; i != numOfDel; i++)
    {
        try
        {
            cout << "Del number in index " << delArr[i] << ": ";
            cl1.Delete(delArr[i]);
            cl1.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    const int numOfLocate = 7;
    int locArr[numOfLocate] = {14, 1, 0, 6, 4, 12, 2};

    cout << "\n"
         << "Before test the locate function which is to find elements, the list has: "
         << "\n";
    cl2.PrintList();

    for (int i = 0; i != numOfLocate; i++)
        cout << "The number " << locArr[i] << " is in index: " << cl2.Locate(locArr[i]) << "\n";

    cout << "\n"
         << "test the add function: "
         << "\n";

    const int numOfAdd = 7;
    int addArr[numOfLocate] = {14, 1, 0, 6, 4, 12, 2};

    for (int i = 0; i != numOfAdd; i++)
    {
        cl2.Add(addArr[i]);
        cout << "After add number, the length is: " << cl2.Length() << " And the list has: ";
        cl2.PrintList();
    }

    cout << "\n"
         << "\n"
         << "test of construct functions: "
         << "\n";

    int arr1[7] = {12, 14, 45, 96, 73, 15, 6};
    NoHeadLinkList<int> nhll(arr1, 7);
    cout << "The test of the normal constructor: ";
    nhll.PrintList();
    NoHeadLinkList<int> nhll1(nhll);
    cout << "The test of the copy constructor: ";
    nhll1.PrintList();
    NoHeadLinkList<int> nhll2 = nhll;
    cout << "The test of the equal operator: ";
    nhll2.PrintList();

    cout << "\n"
         << "now we test the function of this class: "
         << "\n";

    for (int i = 0; i != numOfInsert; i++)
    {
        try
        {
            cout << "Insert number " << insertArr[i][0] << " in index " << insertArr[i][1] << ": ";
            nhll.Insert(insertArr[i][1], insertArr[i][0]);
            nhll.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before deleteing elements, the list has: "
         << "\n";
    nhll1.PrintList();

    for (int i = 0; i != numOfDel; i++)
    {
        try
        {
            cout << "Del number in index " << delArr[i] << ": ";
            nhll1.Delete(delArr[i]);
            nhll1.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before test the locate function which is to find elements, the list has: "
         << "\n";
    nhll2.PrintList();

    for (int i = 0; i != numOfLocate; i++)
        cout << "The number " << locArr[i] << " is in index: " << nhll2.Locate(locArr[i]) << "\n";

    cout << "\n"
         << "test the add function: "
         << "\n";

    for (int i = 0; i != numOfAdd; i++)
    {
        nhll2.Add(addArr[i]);
        cout << "After add number, the length is: " << nhll2.Length() << " And the list has: ";
        nhll2.PrintList();
    }

    // 3. 设计实验:  用顺序表或无头节点的循环链表做
    // 约瑟夫环问题：实验书p178

    cout << "\n"
         << "Joseph Ring Problem: "
         << "\n"
         << "The test arr is: "
         << "\n";

    for (int i = 0; i != 7; i++)
        cout << arr[i] << " ";

    cout << "\n"
         << "Then we solve this ring using no head link list: "
         << "\n";

    JosephRing(arr, 7, 4);

    cout << "\n"
         << "Then we solve this ring using array: "
         << "\n";

    SimplifyJosephRing(arr, 7, 4);

    cout << "\n"
         << "\n";

    system("pause");
}