#include "Header\ApplicationOfStackNQueue.h"
using namespace std;

// 设计实验：实验书p192
// 1.   火车车厢重排问题

// 综合实验：实验书p194
// 2. 表达式求值：中缀表达式求值，参考殷人昆第3章的课件
// 3. 中缀表达式转为后缀表达式：中缀表达式求值，参考殷人昆第3章的课件
// 4. 后缀表达式求值：课本p73

int main()
{
    const int numOfElem = 9;
    int elem[numOfElem] = {5, 8, 1, 7, 4, 2, 9, 6, 3};
    int elem1[numOfElem] = {3, 6, 2, 7, 4, 9, 1, 8, 5};
    cout << "Now we begin to test the coach reset probklem: \n"
         << "Before reset all of the coach, we first show the former order of the coach number: \n";
    for (int i = 0; i != 9; i++)
        cout << elem[i] << " ";
    cout << "\n"
         << "And we set the number of the buffer rails is: " << numOfElem << "\n"
         << "Now we see the process of reset coaches: \n";
    ResetCoaches(elem, 9, 3);
    cout << "It showes this coaches can be sorted. \n"
         << "\n"
         << "we begin test another train, before sorting the coach using buffer rails(queue): the order is: \n"
         << "And also we set the number of the buffer rails is: " << numOfElem << "\n";

    for (int i = 0; i != 9; i++)
        cout << elem1[i] << " ";
    cout << "Now we see the result: \n";
    ResetCoaches(elem1, 9, 3);
    cout << "It showes this coaches can be sorted. \n";

    char *expression = "2*8*(5+9*7+5/7)%5";
    char *exprRPN = new char;
    Nifix2RPN(exprRPN, expression);
    cout << "\n"
         << "We have a expression that all the number is between 1 and 9 and the expression is: " << expression << "(nifix Type)\n"
         << "Using the nifix expression, the result is: " << CalNifixExpression(expression) << "\n"
         << "Now we transfer this nifix to RPN: " << exprRPN << "\n"
         << "And using the RPN, the result is: " << CalRPN(exprRPN) << "\n"
         << "The results using the two types of the expression is: " << (CalNifixExpression(expression) == CalRPN(exprRPN) ? "True" : "false") << "\n";

    system("pause");
}