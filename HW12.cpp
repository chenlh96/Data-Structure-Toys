#include "Header/applicationOfTree.h"

int main()
{
    string expr = "3+2*5-1";
    cout << "The expression is: " << expr << "\n"
         << "Use this expression to construct a binary expression tree: \n";
    BinaryExpressionTree biExprTree(expr);
    cout << "InOrder: ";
    biExprTree.InOrder();
    cout << "\n"
         << "PreOrder: ";
    biExprTree.PreOrder();
    cout << "\n"
         << "PostOrder: ";
    biExprTree.PostOrder();

    string expr1 = "(3+2)*5-1";
    cout << "\n"
         << "The expression is: " << expr1 << "\n"
         << "Use this expression to construct a binary expression tree: \n";
    BinaryExpressionTree biExprTree1(expr1);
    cout << "InOrder: ";
    biExprTree1.InOrder();
    cout << "\n"
         << "PreOrder: ";
    biExprTree1.PreOrder();
    cout << "\n"
         << "PostOrder: ";
    biExprTree1.PostOrder();

    cout << "\n";
    system("pause");
}