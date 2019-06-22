#ifndef SEARCH_H
#define SEARCH_H
#include "stdlib.h"
#include "time.h"
#include "tree.h"
using namespace std;

int SeqSearch(int arr[], int n, int searchElem, int &compareCount)
{
    int i = n;
    arr[0] = searchElem;
    compareCount = 0;
    while (++compareCount && arr[i--] != searchElem)
        ;
    return i;
}

int SeqSearchHighSentinel(int arr[], int n, int searchElem, int &compareCount)
{
    int i = 0;
    arr[n] = searchElem;
    compareCount = 0;
    while (++compareCount && arr[i++] != searchElem)
        ;
    return i - 1;
}

int BinarySearch(int arr[], int n, int searchElem, int &compareCount)
{
    int low = 0, high = n - 1, mid;
    compareCount = 0;
    while (low <= high)
    {
        compareCount++;
        mid = (low + high) / 2;
        if (searchElem < arr[mid])
            high = mid - 1;
        else if (searchElem > arr[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

class binarySortTree
{
  private:
    BinaryNode *root;
    void Insert(BinaryNode *&root, BinaryNode *node);
    void Delete(BinaryNode *root, BinaryNode *node);
    int GetLevel(BinaryNode *root, int elem);
    BinaryNode *Search(BinaryNode *root, int elem, int &searchCount);
    BinaryNode *GetCommonAncestor(BinaryNode *root, int elem1, int elem2);
    bool IsBinarySortTree(BinaryNode *node, int prevElem);
    void Release(BinaryNode *node);

  public:
    binarySortTree(/* args */);
    binarySortTree(int arr[], int n, bool isRandomInsert);
    binarySortTree(const binarySortTree &bst);
    void Insert(int elem);
    void Delete(int elem);
    int GetLevel(int elem);
    BinaryNode *Search(int elem, int &searchCount);
    BinaryNode *GetCommonAncestor(int elem1, int elem2);
    bool IsBinarySortTree();
    ~binarySortTree() { Release(root); }
};

binarySortTree::binarySortTree(/* args */)
{
    root = NULL;
}

binarySortTree::binarySortTree(int arr[], int n, bool isRandomInsert)
{
    root = NULL;
    for (int i = 0; i != n; i++)
    {
        if (isRandomInsert)
        {
            if (i < n - 1)
            {
                srand((unsigned)time(NULL));
                int rd = (rand() % (n - i)) - 1, tmp;
                Insert(arr[rd]);
                if (rd != n - 1 - i)
                {
                    tmp = arr[rd];
                    arr[rd] = arr[n - i - 1];
                    arr[n - 1 - i] = arr[rd];
                }
            }
            else
                Insert(arr[0]);
        }
        else
            Insert(arr[i]);
    }
}

void binarySortTree::Insert(int elem)
{
    BinaryNode *elemNode = new BinaryNode;
    elemNode->data = elem;
    elemNode->lchild = elemNode->rchild = NULL;
    Insert(root, elemNode);
}

void binarySortTree::Insert(BinaryNode *&root, BinaryNode *node)
{
    if (root == NULL)
        root = node;
    else if (root->data > node->data)
        Insert(root->lchild, node);
    else
        Insert(root->rchild, node);
}

void binarySortTree::Release(BinaryNode *node)
{
    if (node != NULL)
    {
        Release(node->lchild);
        Release(node->rchild);
        delete node;
    }
}

void binarySortTree::Delete(int elem)
{
    BinaryNode *parent = NULL, *del = root;

    while (del != NULL && del->data != elem)
    {
        if (parent == NULL)
            parent = root;
        else
            parent = del;
        if (del->data < elem)
            del = del->rchild;
        else if (del->data > elem)
            del = del->lchild;
    }

    if (del != NULL)
        Delete(parent, del);
}

void binarySortTree::Delete(BinaryNode *parent, BinaryNode *del)
{
    if (del->lchild == NULL && del->rchild == NULL)
    {
        if (parent->lchild == del)
            parent->lchild = NULL;
        else
            parent->rchild = NULL;
        delete del;
    }
    else if (del->rchild == NULL)
    {
        if (parent->lchild == del)
            parent->lchild = del->lchild;
        else
            parent->rchild = del->lchild;
        delete del;
    }
    else if (del->lchild == NULL)
    {
        if (parent->lchild == del)
            parent->lchild = del->rchild;
        else
            parent->rchild = del->rchild;
        delete del;
    }
    else
    {
        BinaryNode *parentCopy = del, *delCopy = del->rchild;
        while (delCopy->lchild != NULL)
        {
            parentCopy = delCopy;
            delCopy = delCopy->lchild;
        }
        del->data = delCopy->data;
        if (parent->lchild == del)
        {
            if (parentCopy == del)
                parentCopy->rchild = delCopy->rchild;
            else
                parentCopy->lchild = delCopy->rchild;
        }
        else
        {
            if (parentCopy == del)
                parentCopy->lchild = delCopy->rchild;
            else
                parentCopy->rchild = delCopy->rchild;
        }
        delete delCopy;
    }
}

BinaryNode *binarySortTree::Search(int elem, int &searchCount)
{
    searchCount = 0;
    return Search(root, elem, searchCount);
}

int binarySortTree::GetLevel(int elem)
{
    return GetLevel(root, elem);
}

int binarySortTree::GetLevel(BinaryNode *root, int elem)
{
    if (root == NULL)
        return 0;
    else
    {
        if (elem < root->data)
            return GetLevel(root->lchild, elem) + 1;
        else if (elem > root->data)
            return GetLevel(root->rchild, elem) + 1;
        else
            return 1;
    }
}

BinaryNode *binarySortTree::Search(BinaryNode *root, int elem, int &searchCount)
{
    if (root == NULL)
        return NULL;
    else
    {
        searchCount++;
        if (root->data == elem)
            return root;
        else if (root->data > elem)
            return Search(root->lchild, elem, searchCount);
        else
            return Search(root->rchild, elem, searchCount);
    }
}

BinaryNode *binarySortTree::GetCommonAncestor(int elem1, int elem2)
{
    return GetCommonAncestor(root, elem1, elem2);
}

BinaryNode *binarySortTree::GetCommonAncestor(BinaryNode *node, int elem1, int elem2)
{
    if (node == NULL)
        return NULL;
    else if (elem1 == node->data || elem2 == node->data)
        return node;
    else if (elem1 < node->data && elem2 > node->data)
        return node;
    else if (elem1 < node->data && elem2 < node->data)
        return GetCommonAncestor(node->lchild, elem1, elem2);
    else
        return GetCommonAncestor(node->rchild, elem1, elem2);
}

bool binarySortTree::IsBinarySortTree()
{
    return IsBinarySortTree(root, INT16_MIN);
}

bool binarySortTree::IsBinarySortTree(BinaryNode *node, int prevElem)
{
    if (node == NULL)
        return true;
    else
    {
        bool isBSTLeft = IsBinarySortTree(node->lchild, prevElem);
        if (!isBSTLeft || prevElem > node->data)
            return false;
        prevElem = node->data;
        return IsBinarySortTree(node->rchild, prevElem);
    }
}

int HashSearch_OA_mod(int hashTable[], int mod, int key, int &compareCount)
{
    // the mod number is the length of the key array default
    int j = key % mod;
    compareCount = 1;
    if (hashTable[j] == key)
        return j;
    else if (hashTable[j] == 0)
    {
        hashTable[j] = key;
        return -1;
    }
    int i = (j + 1) % mod;
    while (hashTable[i] != 0 && i != j)
    {
        compareCount++;
        if (hashTable[i] == key)
            return i;
        else
            i = (i + 1) % mod;
    }

    if (i == j)
        throw "OutOfBoundException";
    hashTable[i] = key;
    return -1;
}

void DeleteKey(int hashTable[], int mod, int key)
{
    int j = key % mod, i = 0;
    if (hashTable[j] != key)
    {
        i = (j + 1) % mod;
        while (hashTable[i] != 0 && i != j)
        {
            if (hashTable[i] == key)
                break;
            else
                i = (i + 1) % mod;
        }

        if (i == j)
            throw "No fit key";
        else
            hashTable[i] = -1;
    }
    else
        hashTable[j] = -1;
}

void CreateHashTable_OA(int hashTable[], int lenOfHashTable, int key[], int lenOfKey)
{
    int tmp = 0;
    for (int i = 0; i != lenOfKey; i++)
        HashSearch_OA_mod(hashTable, lenOfHashTable, key[i], tmp);
}

struct chainNode
{
    int key;
    chainNode *next;
};

chainNode *HashSearch_Chain(chainNode *hashTable[], int mod, int key, int &compareCount)
{
    // the mod number is the length of the key array default
    int j = key % mod;
    compareCount = 0;
    chainNode *pos = hashTable[j];

    while (pos != NULL && pos->key != key)
    {
        pos = pos->next;
        compareCount++;
    }
    if (pos != NULL && pos->key == key)
    {
        compareCount++;
        return pos;
    }
    else
    {
        chainNode *n = new chainNode;
        n->key = key;
        n->next = hashTable[j];
        hashTable[j] = n;
        return NULL;
    }
}

void CreateHashTable_Chain(chainNode *hashTable[], int lenOfHashTable, int key[], int lenOfKey)
{
    int tmp = 0;
    for (int i = 0; i != lenOfKey; i++)
        HashSearch_Chain(hashTable, lenOfHashTable, key[i], tmp);
}

#endif // !SEARCH_H
