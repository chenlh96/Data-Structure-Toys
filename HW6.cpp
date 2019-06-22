#include "Header\ApplicationOfList.h"
#include "Header\List.h"
#include <iostream>
using namespace std;

int main()
{
    // 1.双链表的设计实现：带头节点
    // 双链表的实现：实现双链表，并进行测试。参考实验书p174单链表的实现做法，实现双链表。
    // 2.循环双链表的设计实现：带头节点
    // 参考实验书p174单链表的实现做法，实现带头节点的循环双链表。

    // 对1，2题要求：
    // （1）加入求线性表的长度等操作。
    // （2）给定测试数据，验证抛出异常机制
    // （3）将链表的结点结构用结点类实现，仿照实验书p175的做法。

    const int numOfArr = 8;
    int arr[numOfArr] = {1, 15, 7, 12, 26, 9, 15, 2};

    const int numOfInsert = 8;
    int insertArr[numOfInsert][2] = {
        {1012, 2},
        {123, 0},
        {944, 8},
        {901, 7},
        {1312, numOfArr + 4},
        {9, numOfArr + 4},
        {9, numOfArr + 4},
        {9, 1245},
    };

    const int numOfDel = 7;
    int delArr[numOfDel] = {14, 1, 0, 6, 4, 12, 2};

    const int numOfLocate = 7;
    int locArr[numOfLocate] = {14, 1, 0, 6, 4, 12, 2};

    cout << "test of construct functions: "
         << "\n";
    DualLinkList<int> dual(arr, numOfArr);
    cout << "The test of the normal constructor: ";
    dual.PrintList();
    DualLinkList<int> dual1(dual);
    cout << "The test of the copy constructor: ";
    dual1.PrintList();
    DualLinkList<int> dual2 = dual;
    cout << "The test of the equal operator: ";
    dual2.PrintList();

    cout << "\n"
         << "now we test the function of this class: "
         << "\n"
         << "Before insert the elem int he list, the list has: "
         << "\n";
    dual.PrintList();
    for (int i = 0; i != numOfInsert; i++)
    {
        try
        {
            cout << "Insert number " << insertArr[i][0] << " in index " << insertArr[i][1] << ": ";
            dual.Insert(insertArr[i][1], insertArr[i][0]);
            dual.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before deleteing elements, the list has: "
         << "\n";
    dual1.PrintList();
    for (int i = 0; i != numOfDel; i++)
    {
        try
        {
            cout << "Del number in index " << delArr[i] << ": ";
            dual1.Delete(delArr[i]);
            dual1.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before test the locate function which is to find elements, the list has: "
         << "\n";
    dual2.PrintList();
    for (int i = 0; i != numOfLocate; i++)
        cout << "The number " << locArr[i] << " is in index: " << dual2.Locate(locArr[i]) << "\n";

    const int numOfArr1 = 8;
    int arr1[numOfArr1] = {1, 8, 7, 5, 3, 1, 2, 6};

    cout << "\n"
         << "\n"
         << "\n"
         << "test of construct functions: "
         << "\n";

    CyclyicDualLinkList<int> cyclcDual(arr1, numOfArr);
    cout << "The test of the normal constructor: ";
    cyclcDual.PrintList();
    CyclyicDualLinkList<int> cyclcDual1(cyclcDual);
    cout << "The test of the copy constructor: ";
    cyclcDual1.PrintList();
    CyclyicDualLinkList<int> cyclcDual2 = cyclcDual;
    cout << "The test of the equal operator: ";
    cyclcDual2.PrintList();

    cout << "\n"
         << "now we test the function of this class: "
         << "\n"
         << "Before insert the elem int he list, the list has: "
         << "\n";
    cyclcDual.PrintList();
    for (int i = 0; i != numOfInsert; i++)
    {
        try
        {
            cout << "Insert number " << insertArr[i][0] << " in index " << insertArr[i][1] << ": ";
            cyclcDual.Insert(insertArr[i][1], insertArr[i][0]);
            cyclcDual.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before deleteing elements, the list has: "
         << "\n";
    cyclcDual1.PrintList();
    for (int i = 0; i != numOfDel; i++)
    {
        try
        {
            cout << "Del number in index " << delArr[i] << ": ";
            cyclcDual1.Delete(delArr[i]);
            cyclcDual1.PrintList();
        }
        catch (char const *s)
        {
            cout << s << "\n";
        }
    }

    cout << "\n"
         << "Before test the locate function which is to find elements, the list has: "
         << "\n";
    cyclcDual2.PrintList();
    for (int i = 0; i != numOfLocate; i++)
        cout << "The number " << locArr[i] << " is in index: " << cyclcDual2.Locate(locArr[i]) << "\n";

    // 3. 综合实验:  一元多项式相加
    // 实验书p183, 多项式的系数为float型， 系数相加后不为零，要表示为：if (fabs(A.coef+B.coef)>1e-6) ，即大于一个很小的数，就表示不为零。
    const int alen = 4;
    int apoly[alen] = {0, 6, 8, 14};
    float acoef[alen] = {1, -10, 2, 8};
    const int blen = 5;
    int bpoly[blen] = {4, 6, 10, 14, 18};
    float bcoef[blen] = {-1, 10, -3, 8, 4};

    Polynomial(apoly, acoef, alen, bpoly, bcoef, blen);

    system("pause");
}