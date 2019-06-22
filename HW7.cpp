#include "Header\ApplicationOfStackNQueue.h"
using namespace std;

// 1. 顺序栈的实现
//      1. 实验目的
//      （1）掌握栈的顺序存储结构
//      （2）验证顺序栈及其操作的实现
//      （3）验证栈的操作特性
//      2.实验内容
//      （1）建立一个空栈
//      （2）对已建立的栈进行插入、删除、取栈顶元素等基本操作
// 2. 链队列的实现：带头节点
//      1. 实验目的
//      （1）掌握链队列的存储结构
//      （2）验证链队列的存储结构及基本操作的实现
//      （3）验证链队列的操作特性
//      2.实验内容
//      （1）建立一个空队列
//      （2）对已建立的队列进行插入、删除、取队头元素等基本操作
//
// 3. 链栈的实现：用无头节点的链表实现栈，如课本p62-63页
// 4. 循环队列的实现：用浪费一个数组空间的方法实现循环队列，如课本p66-68页
// 5. 循环队列的实现：用不浪费一个数组空间的方法实现循环队列，如如课本p77,5(4)实验书p45-46页
// 6. 链队列的实现：用不带头节点的循环链表实现队列，如课本p77,5(1)，实验书p51
// 7. 设计一个算法，把十进制整数转换为二至九进制之间的任一进制输出。如课本p77,5(3)，实验书p52

int main()
{
    const int numOfElem = 8;
    int elem[numOfElem] = {2, 5, 9, 8, 74, 5, 3, 6};

    SeqStack<int> ss;
    cout << "Test of The sequencial stack: \n"
         << "Push ";
    for (int i = 0; i != numOfElem; i++)
    {
        ss.Push(elem[i]);
        cout << elem[i] << " ";
    }
    cout << "\n"
         << "And pop: the first element of the tuple is the poped element ,and the second indicate whether it is empty"
         << "\n";
    for (int i = 0; i != numOfElem; i++)
        cout << "(" << ss.Pop() << ", " << ss.Empty() << ") ";

    LinkQueue<int> ls;
    cout << "\n"
         << "\n"
         << "Test of The Link queue: \n"
         << "Enqueue ";
    for (int i = 0; i != numOfElem; i++)
    {
        ls.Enqueue(elem[i]);
        cout << elem[i] << " ";
    }
    cout << "\n"
         << "And dequeue: the first element of the tuple is the dequeue element ,and the second indicate whether it is empty"
         << "\n";
    for (int i = 0; i != numOfElem; i++)
        cout << "(" << ls.Dequeue() << ", " << ls.IsEmpty() << ") ";

    NoHeadLinkStack<int> nhls;
    cout << "\n"
         << "\n"
         << "Test of The no head link stack: \n"
         << "Push ";
    for (int i = 0; i != numOfElem; i++)
    {
        nhls.Push(elem[i]);
        cout << elem[i] << " ";
    }
    cout << "\n"
         << "And pop: the first element of the tuple is the poped element ,and the second indicate whether it is empty"
         << "\n";
    for (int i = 0; i != numOfElem; i++)
    {
        cout << "(" << nhls.Pop() << ", " << nhls.IsEmpty() << ") ";
    }

    CirQueue<int> cq;
    cout << "\n"
         << "\n"
         << "Test of The cycle queue: \n"
         << "Enqueue ";
    for (int i = 0; i != numOfElem; i++)
    {
        cq.Enqueue(elem[i]);
        cout << elem[i] << " ";
    }
    cout << "\n"
         << "And dequeue: the first element of the tuple is the dequeue element ,and the second indicate whether it is empty"
         << "\n";
    for (int i = 0; i != numOfElem; i++)
        cout << "(" << cq.Dequeue() << ", " << cq.IsEmpty() << ") ";

    NoHeadLinkQueue<int> nhlq;
    cout << "\n"
         << "\n"
         << "Test of No Head Pointer Link Queue: \n"
         << "Enqueue ";
    for (int i = 0; i != numOfElem; i++)
    {
        nhlq.Enqueue(elem[i]);
        cout << elem[i] << " ";
    }
    cout << "\n"
         << "And dequeue: the first element of the tuple is the dequeue element ,and the second indicate whether it is empty"
         << "\n";
    for (int i = 0; i != numOfElem; i++)
        cout << "(" << nhlq.Dequeue() << ", " << nhlq.IsEmpty() << ") ";

    cout << "\n"
         << "\n"
         << "Now we test the decimal converter: ";
    int num = 12314;
    int n = 8;
    cout << "Convert " << num << " To " << n << " Of system is: ";
    DecimalSys2OtherSys(num, 2);
    cout << "\n";

    system("pause");
}
