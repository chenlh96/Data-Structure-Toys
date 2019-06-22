#include "Header/tree.h"
using namespace std;

// 验证实验
// 1 二叉树的实现：实验书p207页
// 2 树的实现：实验书p210页

// 设计实验：
// 3. 求二叉树中叶子结点的个数：实验书p214
// 4. 求二叉树的结点个数：实验书p80
// 5. 求二叉树的深度：实验书p80-81
// 6. 输出二叉树的后序遍历序列的逆序：实验书p81
// 7. 以二叉链表为存储结构，编写算法求二叉树中结点x的双亲：实验书p81

int main()
{
    cout << "Please input the data to create the binary tree: \n";
    BinaryTree test;
    cout << "\nPreorder the tree\n";
    test.PreOrder();
    cout << "\nInorder the tree\n";
    test.InOrder();
    cout << "\nPostorder the tree\n";
    test.PostOrder();
    cout << "Test some function about the binary tree: \n"
         << "The depth of this tree is: " << test.Depth() << "\n"
         << "The number of the leafs using no recursion algorithm is: " << test.CountLeafsNoRecursive() << "\n"
         << "The total number of nodes is: " << test.Count() << "\n"
         << "The parent of node 4 is: " << test.Parent(4)->data << "\n";

    cout << "Please input the data to create the tree: \n";
    tree test1;
    cout << "\n"
         << "Preorder the tree\n";
    test1.PreOrder();
    cout << "\n"
         << "Postorder the tree\n";
    test1.PostOrder();

    system("pause");
}