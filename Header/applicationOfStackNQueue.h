#ifndef APPLICATIONOFSTACKNQUEUE_H
#define APPLICATIONOFSTACKNQUEUE_H
#include "StackNQueue.h"
#include <string.h>

void DecimalSys2OtherSys(int dec, int n)
{
    SeqStack<int> converter;
    while (dec != 0)
    {
        converter.Push(dec % n);
        dec /= n;
    }
    bool outputZero = true;
    while (!converter.Empty())
    {
        if (converter.GetTop() != 0)
            outputZero = false;
        if (!outputZero)
            cout << converter.Pop();
    }
}

const int MaxNumOfRails = 100;

inline void Scan(LinkQueue<int> bufferRails[], int numOfRails, int &output)
{
    bool reScan = true;
    while (reScan)
    {
        reScan = false;
        for (int j = 0; j != numOfRails; j++)
        {
            while (!bufferRails[j].IsEmpty() && bufferRails[j].GetFront() == output)
            {
                cout << "Output buffer rail " << j << " head coach: " << bufferRails[j].Dequeue()
                     << "\n";
                output++;
                reScan = true;
            }
        }
    }
}

void ResetCoaches(int coaches[], int numOfCoaches, int numOfRails)
{
    LinkQueue<int> bufferRails[MaxNumOfRails];
    int output = 1, currCoachNum;
    bool hasOutput;
    for (int i = 0; i != numOfCoaches; i++)
    {
        hasOutput = false;
        currCoachNum = coaches[i];
        if (currCoachNum == output)
        {
            cout << "Output in-rail coach: " << output++ << "\n";
            hasOutput = true;
        }
        Scan(bufferRails, numOfRails, output);

        if (!hasOutput)
        {
            int maxIdx = -1;
            for (int j = 0; j != numOfRails; j++)
            {
                if (bufferRails[j].IsEmpty() || currCoachNum > bufferRails[j].GetRear())
                    maxIdx = j;
            }
            if (maxIdx != -1)
            {
                cout << "Enqueue coach " << currCoachNum << " in buffer rail " << maxIdx << "\n";
                bufferRails[maxIdx].Enqueue(currCoachNum);
            }
            else
            {
                cout << "\n"
                     << "Until this step these coaches cannot reset.";
                break;
            }
        }
    }

    Scan(bufferRails, numOfRails, output);
}

inline int GetPirorLev(char s)
{
    if (s == '/' || s == '*' || s == '%')
        return 1;
    else if (s == '+' || s == '-')
        return 2;
    else if (s == ')' || s == '(')
        return 3;
    else if (s == '\0')
        return 4;
    return -1;
}

inline int Operate(int left, int right, char s)
{
    switch (s)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    case '%':
        return left % right;
    default:
        throw "Invalid Operation";
    }
}

int CalNifixExpression(const char *s)
{
    LinkStack<char> optr;
    optr.Push('\0');
    LinkStack<int> opnd;

    while (*s != '\0' || optr.GetTop() != '\0')
    {
        if (*s == '\0')
        {
            char op = optr.Pop();
            int right = opnd.Pop(), left = opnd.Pop();
            opnd.Push(Operate(left, right, op));
        }
        else
        {
            if (*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == '%' || *s == '(' || *s == ')')
            {
                if (GetPirorLev(*s) < GetPirorLev(optr.GetTop()) || *s == '(')
                {
                    optr.Push(*s);
                }
                else
                {
                    while (GetPirorLev(*s) >= GetPirorLev(optr.GetTop()) &&
                           optr.GetTop() != '\0' && optr.GetTop() != '(')
                    {
                        char op = optr.Pop();
                        int right = opnd.Pop(), left = opnd.Pop();
                        opnd.Push(Operate(left, right, op));
                    }
                    if (*s != ')')
                        optr.Push(*s);
                    else
                        optr.Pop();
                }
            }
            else
            {
                opnd.Push(*s - '0');
            }
            s++;
        }
    }

    return opnd.GetTop();
}

void Nifix2RPN(char *dest, char *src)
{
    char *dtn = dest;
    LinkStack<char> optr;
    optr.Push('\0');

    while (*src != '\0')
    {
        if (*src == '+' || *src == '-' || *src == '*' || *src == '/' ||
            *src == '%' || *src == '(' || *src == ')')
        {
            if (GetPirorLev(*src) < GetPirorLev(optr.GetTop()) || *src == '(')
                optr.Push(*src);
            else
            {
                if (*src != ')')
                {
                    while (GetPirorLev(*src) >= GetPirorLev(optr.GetTop()) &&
                           optr.GetTop() != '\0')
                        *dtn++ = optr.Pop();
                    optr.Push(*src);
                }
                else
                {
                    while (optr.GetTop() != '(')
                        *dtn++ = optr.Pop();
                    optr.Pop();
                }
            }
        }
        else
            *dtn++ = *src;
        src++;
    }
    while (optr.GetTop() != '\0')
        *dtn++ = optr.Pop();

    *dtn = '\0';
}

int CalRPN(const char *src)
{
    LinkStack<int> cal;
    while (*src != '\0')
    {
        if (*src == '+' || *src == '-' || *src == '*' || *src == '/' || *src == '%')
        {
            int right = cal.Pop(), left = cal.Pop();
            cal.Push(Operate(left, right, *src));
        }
        else
        {
            cal.Push(*src - '0');
        }
        src++;
    }
    return cal.GetTop();
}

struct coordinate
{
    int x, y, prevdir;
    int nextdir[4];
};

bool operator==(const coordinate &l, const coordinate &r)
{
    return l.x == r.x && l.y == r.y;
}

bool operator!=(const coordinate &l, const coordinate &r)
{
    return !(l == r);
}

void InitCoordinate(coordinate &c, int arr[2], int dir)
{
    c.x = arr[0];
    c.y = arr[1];
    c.prevdir = dir;
    for (int i = 0; i != 4; i++)
        c.nextdir[i] = 0;
}

void ChangeCoordinate(coordinate &c, int arr[2], int dir)
{
    c.x += arr[0];
    c.y += arr[1];
    c.prevdir = dir;
    for (int i = 0; i != 4; i++)
        c.nextdir[i] = 0;
    if (dir <= 2)
        c.nextdir[dir + 2] = 1;
    else
        c.nextdir[dir - 2] = 1;
}

void MazeRunner(int maze[8][10], int start[2], int goal[2])
{
    int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    LinkStack<coordinate> path;
    coordinate startCoor, endCoor;
    InitCoordinate(startCoor, start, -1);
    InitCoordinate(endCoor, goal, -1);
    path.Push(startCoor);

    while (!path.IsEmpty() && path.GetTop() != endCoor)
    {
        coordinate curr = path.Pop();
        cout << "(" << curr.x << ", " << curr.y << "):  ";
        for (int i = 0; i != 4; i++)
        {
            cout << "try (" << curr.x + direction[i][0] << ", " << curr.y + direction[i][1] << "): ";

            if (maze[curr.x + direction[i][0]][curr.y + direction[i][1]] == 0 && curr.nextdir[i] != 1)
            {
                cout << " OK;\n";
                curr.nextdir[i] = 1;
                path.Push(curr);
                ChangeCoordinate(curr, direction[i], i);
                path.Push(curr);
                break;
            }
            cout << " not OK; ";
        }
        cout << "\n";
    }
    cout << "\n";
    if (!path.IsEmpty())
    {
        while (!path.IsEmpty())
        {
            coordinate pos = path.Pop();
            cout << "(" << pos.x << ", " << pos.y << ") -> ";
        }
        cout << "success";
    }
    else
        cout << "No path";
}

#endif // !APPLICATIONOFSTACKNQUEUE_H