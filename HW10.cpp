#include "Header/FuncsOfStrNMatrix.h"
#include <iostream>
using namespace std;

//  1. 串操作的实现：实验书p197页
// 	实验目的
//      （1）掌握串的顺序存储结构
//      （2）验证顺序串及其基本操作的实现
//      （3）掌握字符串的操作特点
// 	实验内容
//      （1）定义一个包含串的长度、拼接、比较大小等基本操作的头文件函数原型
//      （2）实现串的求长芭、拼接、比较大小等基本操作。
// 2. 对称矩阵的压缩存储：实验书p199页
// 	 实验目的
//      （1）掌握对称矩阵的压缩存储方法
//      （2）验证称矩阵的压缩存储的寻址方法
// 	实验内容
//      （1）建立一个n×n的对称矩阵A
//      （2）将对称矩阵用一维数组SA存储
//      （3）在数组SA中实现对矩阵A的任意元素进行存取操作

// 3. 实现BF算法
// 4. 实现KMP算法
// 5. 求公共子串：课本p96,5(1)
// 6. 统计文本中单词的个数: 实验书p200
// 7. 幻方:  实验书p200

// 8. 近似串匹配
// 9. 数字旋转方阵

int main()
{
    const int len = 5;
    char test[len + 1] = {'a', 'b', 'a', 'b', 'c', '\0'};
    cout << "The char array \"test\" is: " << test << " The length of the char array \'test\' is: " << strlen(test) << "\n";
    char test1[len + 4] = {'a', 'b', 'a', 'b', 'c', 'e', 'e', '5', '\0'};
    cout << "The char array \"test1\" is: " << test1 << " The length of the char array \'test\' is: " << strlen(test1) << "\n";
    cout << "Compare the two char. The result is: test1 " << (strcmp(test1, test) == 1 ? ">" : "<") << " test\n";
    strcat(test1, test);
    cout << "Cat the two char. The result is: " << test1 << "\n";

    int mat[6][6] = {
        {1, 3, 4, 5, 6, 78},
        {3, 6, 7, 85, 67, 7},
        {4, 7, 4, 2, 34, 5},
        {5, 85, 2, 45, 64, 3},
        {6, 67, 34, 64, 2, 7},
        {78, 7, 5, 3, 7, 8}};
    // int size = (6 * (6 + 1)) / 2;
    cout << "the original matrix is: \n";
    for (int l = 0; l != matSize; l++)
    {
        for (int m = 0; m != matSize; m++)
            cout << mat[l][m] << " ";
        cout << "\n";
    }
    int compMat[(matSize + 1) * matSize / 2];
    compressFixSizeMatrix(mat, compMat);
    cout << "Try get the element from the compress matrix(5 times): \n";
    int i, j;
    for (int l = 0; l != 5; l++)
    {
        cout << "Input the row col index: ";
        cin >> i >> j;
        cout << "the element: " << (i >= j ? compMat[i * (i + 1) / 2 + j] : compMat[j * (j + 1) / 2 + i]) << "\n";
    }

    char *str = "sympathatic", *sub1 = "path", *sub2 = "pathh", *sub3 = "pdsaf";
    cout << "Now we test the bf and the kmp algorithm,\n"
         << "The main string is: " << str << "and we are looking for the following 3 substring in the main string: \n"
         << sub1 << " " << sub2 << " and " << sub3 << "\n"
         << "The result is: " << bf(str, sub1) << " " << bf(str, sub2) << " and " << bf(str, sub3) << "\n"
         << "And what about the kmp algorithm? the result is: \n"
         << kmp(str, sub1, 4) << " " << kmp(str, sub2, 5) << " and " << kmp(str, sub3, 5) << "\n";

    char *common1 = "world health organization", *common2 = "who is the best", *pat = "who";
    cout << "We also use the word: \"" << common1 << "\" and \"" << common2 << "\" to find the pattern: " << pat << "\n"
         << "and the result is: " << CommonSubstring(common1, common2, pat) << "\n";

    char *text = "GitHub is a development platform inspired by the way you work. From open source to business, you can host and review code, manage projects, and build software alongside millions of other developers.";
    cout << "The text we use to test is: \n"
         << text << "\n"
         << "total count of words is: " << countWords(text) << "\n";

    cout << "The test for the odd magic square: a 3 dim odd magic square is: \n";
    oddMagicSquare(3);
    cout << "A 7 dim odd magic square is: \n";
    oddMagicSquare(7);

    char *word1 = "spontaneous", *word2 = "simultaneous";
    cout << "we use the following 2 words to test the k approcimate match function: " << word1 << " " << word2 << "\n"
         << "The result is: " << kApproxiMatch(word1, word2, 6) << "\n";

    int roll[maxSize][maxSize];
    cout << "Test for the rolling matrix: we set the dimension of the matrix is 8 and the result is: \n";
    rollMatrix(roll, 8);
    for (int i = 0; i != 8; i++)
    {
        for (int j = 0; j != 8; j++)
            cout << roll[i][j] << " ";
        cout << "\n";
    }
    cout << "Test for the rolling matrix: we set the dimension of the matrix is 10 and the result is: \n";
    rollMatrix(roll, 10);
    for (int i = 0; i != 10; i++)
    {
        for (int j = 0; j != 10; j++)
            cout << roll[i][j] << " ";
        cout << "\n";
    }
    system("pause");
}