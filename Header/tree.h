#ifndef TREE_H
#define TREE_H
#include "stackNQueue.h"
#include <iostream>
using namespace std;

struct BinaryNode
{
    int data;
    BinaryNode *lchild, *rchild;
};

class BinaryTree
{
  public:
    BinaryTree() { root = Create(root); }
    ~BinaryTree() { Release(root); }
    void PreOrder() { PreOrder(root); }
    void InOrder() { InOrder(root); }
    void PostOrder() { PostOrder(root); }
    void ReversePostOrder() { ReversePostOrder(root); }
    int CountLeafsNoRecursive();
    int Count();
    int Depth();
    BinaryNode *Parent(int x) { return Parent(root, x); }

  private:
    BinaryNode *root;
    BinaryNode *Create(BinaryNode *bn);
    void Release(BinaryNode *bn);
    void PreOrder(BinaryNode *bn);
    void InOrder(BinaryNode *bn);
    void PostOrder(BinaryNode *bn);
    void ReversePostOrder(BinaryNode *bn);
    BinaryNode *Parent(BinaryNode *bn, int x);
};

BinaryNode *BinaryTree::Create(BinaryNode *bn)
{
    int d;
    cout << "Input an integer as data: ";
    cin >> d;
    if (d == -1)
        return NULL;
    else
    {
        bn = new BinaryNode;
        bn->data = d;
        bn->lchild = Create(bn->lchild);
        bn->rchild = Create(bn->rchild);
    }
    return bn;
}

void BinaryTree::Release(BinaryNode *bn)
{
    if (bn != NULL)
    {
        Release(bn->lchild);
        Release(bn->rchild);
        delete bn;
    }
}

void BinaryTree::PreOrder(BinaryNode *bn)
{
    if (bn == NULL)
        return;

    else
    {
        cout << bn->data << " ";
        PreOrder(bn->lchild);
        PreOrder(bn->rchild);
    }
}

void BinaryTree::InOrder(BinaryNode *bn)
{
    if (bn == NULL)
        return;

    else
    {
        InOrder(bn->lchild);
        cout << bn->data << " ";
        InOrder(bn->rchild);
    }
}

void BinaryTree::PostOrder(BinaryNode *bn)
{
    if (bn == NULL)
        return;

    else
    {
        PostOrder(bn->lchild);
        PostOrder(bn->rchild);
        cout << bn->data << " ";
    }
}

void BinaryTree::ReversePostOrder(BinaryNode *bn)
{
    if (bn != NULL)
    {
        cout << bn->data << " ";
        PostOrder(bn->rchild);
        PostOrder(bn->lchild);
    }
}

int BinaryTree::CountLeafsNoRecursive()
{
    LinkStack<BinaryNode> path;
    int count = 0;
    BinaryNode *nodeptr = root, node;
    while (nodeptr != NULL || !path.IsEmpty())
    {
        while (nodeptr != NULL)
        {
            if (nodeptr->lchild == NULL && nodeptr->rchild == NULL)
                count++;
            path.Push(*nodeptr);
            nodeptr = nodeptr->lchild;
        }
        if (!path.IsEmpty())
        {
            node = path.Pop();
            nodeptr = &node;
            nodeptr = nodeptr->rchild;
        }
    }

    return count;
}

int BinaryTree::Count()
{
    LinkStack<BinaryNode> path;
    int count = 0;
    BinaryNode *nodeptr = root, node;
    while (nodeptr != NULL || !path.IsEmpty())
    {
        while (nodeptr != NULL)
        {
            path.Push(*nodeptr);
            count++;
            nodeptr = nodeptr->lchild;
        }
        if (!path.IsEmpty())
        {
            node = path.Pop();
            nodeptr = &node;
            nodeptr = nodeptr->rchild;
        }
    }

    return count;
}

int BinaryTree::Depth()
{
    if (root == NULL)
        return 0;
    LinkQueue<BinaryNode *> sib;
    sib.Enqueue(root);
    int dep = 0, size = 1, currentSize;
    while (!sib.IsEmpty())
    {
        dep++;
        currentSize = size;
        size = 0;
        while (currentSize != 0)
        {
            BinaryNode *curr = sib.Dequeue();
            currentSize--;
            if (curr->lchild != NULL)
            {
                sib.Enqueue(curr->lchild);
                size++;
            }
            if (curr->rchild != NULL)
            {
                sib.Enqueue(curr->rchild);
                size++;
            }
        }
    }

    return dep;
}

BinaryNode *BinaryTree::Parent(BinaryNode *bn, int x)
{
    LinkQueue<BinaryNode *> sib;
    sib.Enqueue(root);
    if (root->data == x)
        return NULL;
    int size = 1, currentSize;
    while (!sib.IsEmpty())
    {
        currentSize = size;
        size = 0;
        while (currentSize != 0)
        {
            BinaryNode *curr = sib.Dequeue();
            if ((curr->lchild != NULL && curr->lchild->data == x) ||
                (curr->rchild != NULL && curr->rchild->data == x))
                return curr;
            currentSize--;
            if (curr->lchild != NULL)
            {
                sib.Enqueue(curr->lchild);
                size++;
            }
            if (curr->rchild != NULL)
            {
                sib.Enqueue(curr->rchild);
                size++;
            }
        }
    }

    return NULL;
}

struct TreeNode
{
    int data;
    TreeNode *firstChild, *rightSib;
};

struct QueueTreeNode
{
    TreeNode *data;
    QueueTreeNode *next;
};

class tree
{
  private:
    TreeNode *root;
    void PreOrder(TreeNode *tn);
    void PostOrder(TreeNode *tn);
    void Release(TreeNode *tn);

  public:
    tree(/* args */);
    ~tree() { Release(root); }
    void PreOrder() { PreOrder(root); }
    void PostOrder() { PostOrder(root); }
};

tree::tree(/* args */)
{
    int parentNum = -1, childNum = -1;
    QueueTreeNode *front = new QueueTreeNode, *rear = front, *head = NULL, *curr = NULL; // *del = front;
    cout << "Please input the num of the root: ";
    cin >> parentNum;
    curr = new QueueTreeNode;
    curr->data = new TreeNode;
    curr->data->data = parentNum;
    curr->data->firstChild = NULL;
    curr->data->rightSib = NULL;
    curr->next = NULL;
    rear->next = curr;
    rear = curr;
    root = curr->data;

    cout << "Enter a two-tuple with the first element is the parent number and the second element si the child number. The two element must be seperated by a blank."
         << "\n";
    cin >> parentNum >> childNum;
    while (parentNum != -1 && childNum != -1)
    {
        curr = new QueueTreeNode;
        curr->data = new TreeNode;
        curr->data->data = childNum;
        curr->data->firstChild = NULL;
        curr->data->rightSib = NULL;
        curr->next = NULL;
        rear->next = curr;
        rear = curr;

        while (front != rear)
        {
            while (front->next->data->data != parentNum)
                front = front->next;
            head = front->next;

            if (head->data->firstChild == NULL)
                head->data->firstChild = curr->data;
            else
            {

                if (head->data->firstChild->rightSib == NULL)
                    head->data->firstChild->rightSib = curr->data;
                else
                {
                    TreeNode *right = head->data->firstChild->rightSib;
                    while (right->rightSib != NULL)
                        right = right->rightSib;
                    right->rightSib = curr->data;
                }
            }
            break;
        }
        cin >> parentNum >> childNum;
    }
    // delete curr;
    // delete head;
    // while (del != NULL)
    // {
    //     curr = del;
    //     del = del->next;
    //     delete curr;
    // }
}

void tree::Release(TreeNode *tn)
{
    if (tn == NULL)
        return;
    else
    {
        Release(tn->firstChild);
        Release(tn->rightSib);
        delete tn;
    }
}

void tree::PreOrder(TreeNode *tn)
{
    if (tn == NULL)
        return;

    else
    {
        cout << tn->data << " ";
        PreOrder(tn->firstChild);
        PreOrder(tn->rightSib);
    }
}

void tree::PostOrder(TreeNode *tn)
{
    if (tn == NULL)
        return;

    else
    {
        PostOrder(tn->firstChild);
        PostOrder(tn->rightSib);
        cout << tn->data << " ";
    }
}

#endif // !TREE_H