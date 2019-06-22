#include "Header/search.h"

// 1. 顺序查找的实现：实验书p231页
// 2. 折半查找的实现：实验书p232页
// 3. 散列查找的实现：实验书p234页

// 4. 设计顺序查找算法，将哨兵设在下标的高端：课本p217, 5(1)
// 5. 编写算法求给定结点在二叉排序树中所在的层数：课本p217, 5(2)
// 6. 编写算法，在二叉排序树上找出任意两个不同结点的最近公共祖先：课本p217, 5(3)
// 7. 设计算法判定一棵二叉树是否为二叉排序树：课本p217, 5(4)
// 8. 在用线性探测解决冲突的散列表中，设计算法实现闭散列表的删除操作：课本p217, 5(5)
// 9. 二叉排序树的查找性能：实验书p235

int main()
{
    cout << "Begin to test the sequential and binary search.\n";
    const int numOfRecords = 10;
    int record[numOfRecords] = {63, 55, 90, 42, 58, 70, 10, 45, 67, 83};

    int record_seq[numOfRecords], record_bin[numOfRecords] = {7, 13, 21, 22, 39, 45, 61, 82, 87, 92};
    for (int i = 1; i != numOfRecords + 1; i++)
        record_seq[i] = record[i - 1];

    cout << "The record that uesd to test the seq search: ";
    for (int i = 1; i != numOfRecords + 1; i++)
        cout << record_seq[i] << " ";
    cout << "\n"
         << "The record that uesd to test the binary search: ";
    for (int i = 0; i != numOfRecords; i++)
        cout << record_bin[i] << " ";

    const int numOfSearchIdx = 4;
    int searchIdx[numOfSearchIdx] = {4, 6, 9, 3}, count = 0, index;

    cout << "\n"
         << "Sequential locate count Binary locate count\n";

    for (int i = 0; i != numOfSearchIdx; i++)
    {
        index = SeqSearch(record_seq, numOfRecords, record_seq[searchIdx[i]], count);
        cout << record_seq[searchIdx[i]] << "    " << index << "     " << count << "    ";
        index = BinarySearch(record_bin, numOfRecords, record_bin[searchIdx[i]], count);
        cout << record_bin[searchIdx[i]] << "    " << index << "     " << count << "    \n";
    }

    //--------------------------------------------------------------------------------------------------------

    cout << "Begin to test the hash search: \n";

    const int numOfKeys = 9, lenOfHashTable = 11;
    int key[numOfKeys] = {47, 7, 29, 11, 16, 92, 22, 8, 3}, hashTable[lenOfHashTable];
    for (int i = 0; i != lenOfHashTable; i++)
        hashTable[i] = 0;

    cout << "The keys has: ";
    for (int i = 0; i != numOfKeys; i++)
        cout << key[i] << " ";

    CreateHashTable_OA(hashTable, lenOfHashTable, key, numOfKeys);

    cout << "\n"
         << "The table is: ";
    for (int i = 0; i != lenOfHashTable; i++)
        cout << hashTable[i] << " ";

    int count1 = 0, index1, totalCount = 0;

    cout << "\n"
         << "Begin to search the key in the hash table: \n";

    for (int i = 0; i != numOfKeys; i++)
    {
        cout << "Search key " << key[i];
        index1 = HashSearch_OA_mod(hashTable, lenOfHashTable, key[i], count1);
        cout << "  Index: " << index1 << " counts: " << count1 << "\n";
        totalCount += count1;
    }
    cout << "The ASL of open adresstre is: " << totalCount << "\n";

    cout << "Begin to construct the chain hash table: \n";
    chainNode *hashTable1[lenOfHashTable];
    for (int i = 0; i != lenOfHashTable; i++)
        hashTable1[i] = NULL;

    CreateHashTable_Chain(hashTable1, lenOfHashTable, key, numOfKeys);

    cout << "\n"
         << "Begin to search the key in the hash table: \n";
    totalCount = 0;
    for (int i = 0; i != numOfKeys; i++)
    {
        cout << "Search key " << key[i];
        index1 = HashSearch_Chain(hashTable1, lenOfHashTable, key[i], count1)->key;
        cout << "  key: " << index1 << " counts: " << count1 << "\n";
        totalCount += count1;
    }
    cout << "The ASL of open adresstre is: " << totalCount << "\n";

    //===============================================================================================================

    cout << "Begin to test the sentinel search which we set the sentinel in higher index.\n"
         << "still use the following set: ";
    for (int i = 0; i != numOfRecords; i++)
        cout << record[i] << " ";

    cout << "\n"
         << "reocrd index count\n";
    for (int i = 0; i != numOfSearchIdx; i++)
    {
        index = SeqSearchHighSentinel(record, numOfRecords, record[searchIdx[i]], count);
        cout << record[searchIdx[i]] << "    " << index << "     " << count << "    \n";
    }

    //===============================================================================================================

    cout << "Begin to test some required algorithm implement in binary sort tree.\n";

    const int numOfRecords2 = 8;
    int record2[numOfRecords2] = {62, 55, 90, 42, 58, 70, 24, 82}, record2copy[numOfRecords2];
    bool isRandomOrder = false;

    cout << "The records has: ";
    for (int i = 0; i != numOfRecords2; i++)
    {
        cout << record2[i] << " ";
        record2copy[i] = record2[i];
    }

    cout << "\n"
         << "Construct a binary sort tree and select the record by ascending order \n";
    binarySortTree bstSample(record2, numOfRecords2, isRandomOrder);

    const int numOfSearchIdx2 = 4;
    int searchIdx2[numOfSearchIdx2] = {4, 6, 2, 5}, count2 = 0;

    cout << "Get the level of the following records: \n";
    for (int i = 0; i != numOfSearchIdx2 / 2; i++)
        cout << "Records: " << record2[searchIdx2[i]] << " Level: " << bstSample.GetLevel(record2[searchIdx2[i]]) << "\n";

    int searchIdx2_pair[numOfSearchIdx2][2] = {{0, 1}, {5, 4}, {3, 6}, {7, 1}};

    cout << "Get the common ancstor of the following pair records: \n";
    for (int i = 0; i != numOfSearchIdx2; i++)
        cout << "Records pair: " << record2[searchIdx2_pair[i][0]] << " " << record2[searchIdx2_pair[i][1]]
             << " Commom ancestor: " << bstSample.GetCommonAncestor(record2[searchIdx2_pair[i][0]], record2[searchIdx2_pair[i][1]])->data << "\n";

    cout << "Test if a tree is binary sort tree\n";
    cout << bstSample.IsBinarySortTree() << "\n";

    cout << "Begin to analysis the time behavior.\n"
         << "Construct a binary sort tree and select the record by random order \n";
    binarySortTree bstSample1(record2copy, numOfRecords2, !isRandomOrder);

    cout << "Begin search for the element in both tree.\n"
         << "record ascending random\n";
    for (int i = 0; i != numOfSearchIdx2; i++)
    {
        cout << record2[searchIdx2[i]] << "   ";
        bstSample.Search(record2[searchIdx2[i]], count2);
        cout << count2 << "   ";
        bstSample1.Search(record2[searchIdx2[i]], count2);
        cout << count2 << "   \n";
    }
    cout << "For each record, the compare counts using the random generate bst is: \n";
    int max = INT16_MIN, min = INT16_MAX, mean = 0;
    for (int i = 0; i != numOfRecords2; i++)
    {
        bstSample1.Search(record2[i], count2);
        if (count2 > max)
            max = count2;
        else if (count2 < min)
            min = count2;
        mean += count2;
        cout << count2 << " ";
    }
    cout << "\n"
         << "The best condition is: " << min << " The wost condition is: " << max << " And the mean condition is: " << mean / numOfRecords2 << "\n";

    //=====================================================================================================================

    cout << "Begin to test the delete algorothm of hash search.\n";

    const int numOfSearchIdx1 = 4;
    int searchIdx1[numOfSearchIdx1] = {4, 6, 2, 8};

    for (int i = 0; i != numOfSearchIdx1; i++)
    {
        cout << "Delete key " << key[searchIdx1[i]] << " ";
        DeleteKey(hashTable, lenOfHashTable, key[searchIdx1[i]]);
        cout << "Hash table is: ";
        for (int j = 0; j != lenOfHashTable; j++)
            cout << hashTable[j] << " ";
        cout << "\n";
    }

    cout << "\n";
    system("pause");
}