#include "Header/applicationOfSort.h"
#include "Header/sort.h"
#include "stdlib.h"
#include "time.h"
using namespace std;

int num4Select[100];

void RandomGenerateArr(int arr[], int n)
{
    for (int i = 0; i != 100; i++)
        num4Select[i] = i + 1;
    int bound = 99;
    for (int i = 0; i != n; i++)
    {
        srand(time(NULL));
        int idx = rand() % (bound + 2) - 1;
        arr[i] = num4Select[idx];
        if (idx != bound)
        {
            int tmp = num4Select[bound];
            num4Select[bound] = num4Select[idx];
            num4Select[idx] = tmp;
        }
        bound--;
    }
}

void AscendingInsertSort(int arr[], int n)
{
    for (int i = 0; i != n; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j != n; j++)
        {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }

        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
        // PrintArr(arr, n);
    }
}
void DecendingInsertSort(int arr[], int n)
{
    for (int i = 0; i != n; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j != n; j++)
        {
            if (arr[j] > arr[minIdx])
                minIdx = j;
        }

        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
        // PrintArr(arr, n);
    }
}

int main()
{
    const int n = 10;
    int arr[n], compare = 0, move = 0;
    RandomGenerateArr(arr, n);

    cout << "Test arrar: \n";
    PrintArr(arr, n);

    cout << "\n\n"
         << "Insert sort : \n ";
    PrintArr(arr, n);
    InsertSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    InsertSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    InsertSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Shell sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    ShellSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    ShellSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    ShellSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Bubble sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    BubbleSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    BubbleSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    BubbleSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Quick sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    QuickSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    QuickSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    QuickSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Select sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    SelectSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    SelectSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    SelectSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Heap sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    HeapSort(arr, n, compare, move);
    cout << "random: compare: " << compare << " move: " << move << "\n";

    AscendingInsertSort(arr, n);
    PrintArr(arr, n);
    HeapSort(arr, n, compare, move);
    cout << "Ascend: compare: " << compare << " move: " << move << "\n";

    DecendingInsertSort(arr, n);
    PrintArr(arr, n);
    HeapSort(arr, n, compare, move);
    cout << "Decending: compare: " << compare << " move: " << move << "\n";

    cout << "\n\n"
         << "Bidirectional bullle sort: \n";
    RandomGenerateArr(arr, n);
    PrintArr(arr, n);
    BidirectionalBubbleSort(arr, n);

    cout << "\n\n"
         << "Link list insert sort: \n";

    RandomGenerateArr(arr, n);
    simplifyLinkList arrList(arr, n);
    arrList.PrintList();
    cout << "\n";
    arrList.InsertSort();

    cout << "\n\n"
         << "LPT algorithm: \n";

    RandomGenerateArr(arr, n * 2);
    cout << "Job time: ";
    PrintArr(arr, n * 2);
    cout << "Machine number: " << 5
         << " LPT result: " << LPT(arr, n, 5) << "\n";

    system("pause");
}