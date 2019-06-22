#ifndef SORT_H
#define SORT_H
#include <iostream>
using namespace std;

inline void PrintArr(int arr[], int n)
{
    for (int i = 0; i != n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void InsertSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;
    for (int i = 1; i != n; i++)
    {
        arr[n] = arr[i];
        int j;
        compare++;
        for (j = i - 1; arr[n] < arr[j]; j--)
        {
            arr[j + 1] = arr[j];
            compare++;
            move++;
        }
        arr[j + 1] = arr[n];

        // PrintArr(arr, n);
    }
}

void ShellSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;

    for (int d = n / 2; d != 0; d /= 2)
    {
        for (int i = d; i != n; i++)
        {
            arr[n] = arr[i];
            int j;
            compare++;

            for (j = i - d; j >= 0 && arr[n] < arr[j]; j -= d)
            {
                arr[j + d] = arr[j];
                compare++;
                move++;
            }
            arr[j + d] = arr[n];
        }
        // PrintArr(arr, n);
    }
}

void BubbleSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;

    int lastBound = n - 1, currBound = 0;
    while (lastBound != currBound)
    {
        currBound = lastBound;
        for (int i = 0; i != currBound; i++)
        {
            compare++;

            if (arr[i] > arr[i + 1])
            {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                lastBound = i;
                move++;
            }
        }
        // PrintArr(arr, n);
    }
}

inline void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int Partition(int arr[], int begin, int end, int &compare, int &move)
{
    int bg = begin, ed = end;
    while (bg < ed)
    {
        compare++;
        while (bg < ed && arr[bg] < arr[ed])
        {
            compare++;
            ed--;
        }
        if (bg < ed)
        {
            swap(arr[bg], arr[ed]);
            move++;
            bg++;
        }
        compare++;
        while (bg < ed && arr[bg] < arr[ed])
        {
            compare++;
            bg++;
        }
        if (bg < ed)
        {
            swap(arr[bg], arr[ed]);
            move++;
            ed--;
        }
    }

    return bg;
}

void QuickSort(int arr[], int first, int end, int &compare, int &move)
{
    if (first < end)
    {
        int pivot = Partition(arr, first, end, compare, move);
        QuickSort(arr, first, pivot - 1, compare, move);
        QuickSort(arr, pivot + 1, end, compare, move);
        // PrintArr(arr, end);
    }
}

void QuickSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;
    QuickSort(arr, 0, n - 1, compare, move);
}

void SelectSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;
    for (int i = 0; i != n; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j != n; j++)
        {
            compare++;
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }

        if (minIdx != i)
        {
            swap(arr[i], arr[minIdx]);
            move++;
        }
        // PrintArr(arr, n);
    }
}

void Sift(int arr[], int key, int bound, int &compare, int &move)
{
    int i = key, j = 2 * i + 1;
    while (j <= bound)
    {
        compare++;
        if (j < bound && arr[j] < arr[j + 1])
            j++;
        if (arr[i] > arr[j])
            break;
        else
        {
            swap(arr[i], arr[j]);
            move++;
            i = j, j = 2 * i;
        }
    }
}

void HeapSort(int arr[], int n, int &compare, int &move)
{
    compare = move = 0;
    for (int i = n / 2 - 1; i != -1; i--)
        Sift(arr, i, n - 1, compare, move);
    for (int i = 0; i != n; i++)
    {
        // PrintArr(arr, n);
        swap(arr[0], arr[n - i - 1]);
        move++;
        Sift(arr, 0, n - i - 2, compare, move);
        // PrintArr(arr, n);
    }
}

void Merge(int arr[], int copy[], int start, int middle, int end)
{
    int i = start, j = middle + 1, k = start;
    while (i < middle && j < end)
    {
        if (arr[i] < arr[j])
            copy[k++] = arr[i++];
        else
            copy[k++] = arr[j++];
    }

    while (i < middle)
        copy[k++] = arr[i++];
    while (j < end)
        copy[k++] = arr[j++];
}

void MergePass(int arr[], int copy[], int n, int step)
{
    int i = 0;
    while (i < n - 2 * step)
    {
        Merge(arr, copy, i, i + step, i + 2 * step);
        i += 2 * step;
    }
    if (i < n - step)
        Merge(arr, copy, i, i + step, n);
    else
    {
        for (int j = i; j != n; j++)
            copy[j] = arr[j];
    }
}

void MergeSort(int arrOri[], int arrCopy[], int n)
{
    int step = 1;
    while (step < n)
    {
        MergePass(arrOri, arrCopy, n, step);
        step *= 2;
        MergePass(arrCopy, arrOri, n, step);
        step *= 2;
    }
}

struct linkNode
{
    int elem;
    linkNode *next;
};

class simplifyLinkList
{
  private:
    linkNode *head;

  public:
    simplifyLinkList(/* args */);
    simplifyLinkList(int arr[], int n);
    simplifyLinkList(const simplifyLinkList &copy);
    void PrintList();
    ~simplifyLinkList();
    void InsertSort();
};

simplifyLinkList::simplifyLinkList(/* args */)
{
    head = NULL;
}
simplifyLinkList::simplifyLinkList(const simplifyLinkList &copy)
{
    head = new linkNode;
    head->next = NULL;
    linkNode *curr, *pcopy = copy.head->next, *p = head;

    while (pcopy != NULL)
    {
        curr = new linkNode;
        curr->elem = pcopy->elem;
        curr->next = NULL;
        p->next = curr;
        p = p->next;
        pcopy = pcopy->next;
    }
}
simplifyLinkList::simplifyLinkList(int arr[], int n)
{
    head = new linkNode;
    head->next = NULL;
    linkNode *curr, *p = head;

    for (int i = 0; i != n; i++)
    {
        curr = new linkNode;
        curr->elem = arr[i];
        curr->next = NULL;
        p->next = curr;
        p = p->next;
    }
}

simplifyLinkList::~simplifyLinkList()
{
    linkNode *del;
    while (head != NULL)
    {
        del = head;
        head = head->next;
        delete del;
    }
}

void simplifyLinkList::InsertSort()
{
    linkNode *orderPrePtr = head, *orderPtr = head->next,
             *disorderPtr = orderPtr->next, *disorderPrePtr = orderPtr;
    bool isExchage = false;
    while (disorderPtr != NULL)
    {
        while (!isExchage)
        {
            while (orderPtr->elem < disorderPtr->elem)
            {
                orderPrePtr = orderPtr;
                orderPtr = orderPtr->next;
            }

            if (orderPtr != disorderPtr)
            {
                linkNode *tmp = disorderPtr->next;
                disorderPrePtr->next = disorderPtr->next;
                disorderPtr->next = orderPtr;
                orderPrePtr->next = disorderPtr;
                disorderPtr = tmp;
                isExchage = true;
            }
            else
            {
                disorderPrePtr = disorderPtr;
                disorderPtr = disorderPtr->next;
                isExchage = true;
            }
        }
        orderPrePtr = head;
        orderPtr = head->next;
        isExchage = false;
    }
    PrintList();
}

void simplifyLinkList::PrintList()
{
    linkNode *printNode = head->next;
    while (printNode != NULL)
    {
        cout << printNode->elem << " ";
        printNode = printNode->next;
    }
}

void BidirectionalBubbleSort(int arr[], int n)
{
    int flag = 1, i = 0;
    while (flag == 1)
    {
        flag = 0;
        for (int j = i; j != n - i - 2; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                flag = 1;
            }
        }
        for (int j = n - i - 1; j != i; j--)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(arr[j], arr[j - 1]);
                flag = 1;
            }
        }
        i++;
        PrintArr(arr, n);
    }
}
#endif // !SORT_H