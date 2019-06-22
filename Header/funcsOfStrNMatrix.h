#ifndef FUNCSOFSTRNMATRIX_H
#define FUNCSOFSTRNMATRIX_H
#include <iostream>
using namespace std;

int strlen(char *s)
{
    char *p = s;
    int len = 0;
    while (*p != '\0')
    {
        p++;
        len++;
    }
    return len;
}

char *strcat(char *destination, char *src)
{
    char *d = destination, *s = src;
    while (*(d++) != '\0')
        ;
    while (*s != '\0')
        *d++ = *s++;
    *d = '\0';
    return destination;
}

int strcmp(char *str1, char *str2)
{
    char *s1 = str1, *s2 = str2;
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 > *s2)
            return 1;
        else if (*s1 < *s2)
            return -1;
        else
        {
            s1++;
            s2++;
        }
    }
    if (*s1 == '\0' && *s2 == '\0')
        return 0;
    else if (*s1 != '\0')
        return 1;
    else
        return -1;
}

int bf(char s[], char t[])
{
    int i = 0, j = 0;

    while (s[i] != '\0' && t[j] != '\0')
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }

    if (t[j] == '\0')
    {
        return i - j + 1;
    }
    return -1;
}

void calnext(int *next, char t[])
{
    // calculate the next array
    int k = -1;
    // int i = 0;
    next[0] = k;

    for (int i = 1; t[i] != '\0'; i++)
    {
        while (k > -1 && t[i - 1] != t[k])
            k = next[k];

        next[i] = ++k;
    }
}

int kmp(char s[], char t[], int tlen)
{
    int next[tlen];
    calnext(next, t);

    int i = 0, j = 0;

    while (s[i] != '\0' && t[j] != '\0')
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
            if (j == -1)
            {
                i++;
                j++;
            }
        }
    }

    if (t[j] == '\0')
        return i - j + 1;

    return -1;
}

const int matSize = 6;

void compressFixSizeMatrix(int srcMat[matSize][matSize], int compMat[], int size = (matSize + 1) * matSize / 2)
{
    for (int i = 0; i != matSize; i++)
        for (int j = 0; j != i + 1; j++)
            compMat[i * (i + 1) / 2 + j] = srcMat[i][j];
}

int countWords(char *text)
{
    char *pos = text;
    int isBlank = *pos == ' ' ? 1 : 0;
    int count = isBlank ? -1 : 0;
    while (*pos != '\0')
    {
        if (*pos == ' ')
            isBlank = 1;
        else
        {
            if (isBlank == 1)
            {
                isBlank = 0;
                count++;
            }
        }
        pos++;
    }
    return count;
}

const int maxMagicSize = 100;

void oddMagicSquare(int n)
{
    int square[maxMagicSize][maxMagicSize], i = 0, j = n / 2;
    for (int l = 0; l != n; l++)
        for (int m = 0; m != n; m++)
            square[l][m] = 0;
    square[i][j] = 1;
    for (int k = 2; k != n * n + 1; k++)
    {
        if (square[(i - 1 + n) % n][(j - 1 + n) % n] == 0)
        {
            i = (i - 1 + n) % n;
            j = (j - 1 + n) % n;
        }
        else
            i = (i + 1) % n;
        square[i][j] = k;
    }
    for (int l = 0; l != n; l++)
    {
        for (int m = 0; m != n; m++)
            cout << square[l][m] << " ";
        cout << "\n";
    }
}

const int maxStrLength = 100;

int kApproxiMatch(char *str1, char *str2, int k)
{
    int len1 = strlen(str1), len2 = strlen(str2);
    int diff[maxStrLength][maxStrLength];

    for (int j = 0; j != len2; j++)
        diff[0][j] = 0;
    for (int i = 0; i != len1; i++)
        diff[i][0] = i;
    for (int j = 1; j != len2; j++)
    {
        for (int i = 1; i != len1; i++)
        {
            int extra = str1[i] == str2[j] ? 0 : 1;
            diff[i][j] = diff[i - 1][j - 1] + extra;
            if (diff[i][j] > diff[i - 1][j] + 1)
                diff[i][j] = diff[i - 1][j] + 1;
            if (diff[i][j] > diff[i][j - 1] + 1)
                diff[i][j] = diff[i][j - 1] + 1;
        }
        // if (diff[len1][j] <= k)
        //     return j;
    }
    return diff[len1 - 1][len2 - 1];
}

const int maxSize = 50;

void rollMatrix(int rollMat[maxSize][maxSize], int size)
{
    int len = size;
    int n = 1, i = 0, j = 0;
    int move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int l = 0; l != size; l++)
        for (int m = 0; m != size; m++)
            rollMat[l][m] = 0;

    while (len != 0 && len != 1)
    {
        for (int k = 0; k != 4; k++)
        {
            for (int l = 0; l != len - 1; l++)
            {
                rollMat[i][j] = n++;
                i += move[k][0];
                j += move[k][1];
            }
        }
        i++;
        j++;
        len -= 2;
    }
    if (len == 1)
        rollMat[i][j] = n;
}

int FindPattern(char *mainString, char *pattern)
{
    char *ms = mainString, *pat = pattern;
    while (*ms != '\0' && *pat != '\0')
    {
        if (*ms == *pat)
            pat++;
        ms++;
    }
    if (*pat == '\0')
        return 1;
    else
        return 0;
}

int CommonSubstring(char *mainStr1, char *mainStr2, char *pattern)
{
    return FindPattern(mainStr1, pattern) && FindPattern(mainStr2, pattern);
}

#endif // !"FUNCSOFSTRNMATRIX_H"
