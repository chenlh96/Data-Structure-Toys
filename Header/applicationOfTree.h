#ifndef APPLICATIONOFTREE_H
#define APPLICATIONOFTREE_H
#include "stackNQueue.h"
#include <iostream>
#include <string>
using namespace std;

struct exprNode
{
    char chr;
    exprNode *lExpr, *rExpr;
};

class BinaryExpressionTree
{
  private:
    exprNode *root;
    void Release(exprNode *node);
    int GetPirorLev(char s);
    void InOrder(exprNode *node);
    void PreOrder(exprNode *node);
    void PostOrder(exprNode *node);

  public:
    BinaryExpressionTree();
    BinaryExpressionTree(string expression);
    ~BinaryExpressionTree() { Release(root); }
    void InOrder() { InOrder(root); }
    void PreOrder() { PreOrder(root); }
    void PostOrder() { PostOrder(root); }
};

int BinaryExpressionTree::GetPirorLev(char s)
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

BinaryExpressionTree::BinaryExpressionTree()
{
    this->root = NULL;
}

BinaryExpressionTree::BinaryExpressionTree(string expression)
{
    LinkStack<exprNode *> nodes;
    LinkStack<char> optr;
    optr.Push('\0');
    for (char c : expression)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')')
        {
            if (GetPirorLev(c) < GetPirorLev(optr.GetTop()) || c == '(')
                optr.Push(c);
            else
            {
                while (GetPirorLev(c) >= GetPirorLev(optr.GetTop()) && optr.GetTop() != '\0' && optr.GetTop() != '(')
                {
                    char op = optr.Pop();
                    exprNode *right = nodes.Pop(), *left = nodes.Pop(), *opNode = new exprNode;
                    opNode->chr = op;
                    opNode->lExpr = left;
                    opNode->rExpr = right;
                    nodes.Push(opNode);
                }
                if (c != ')')
                    optr.Push(c);
                else
                    optr.Pop();
            }
        }
        else
        {
            exprNode *num = new exprNode;
            num->chr = c;
            num->lExpr = num->rExpr = NULL;
            nodes.Push(num);
        }
    }

    while (optr.GetTop() != '\0')
    {
        char op = optr.Pop();
        exprNode *right = nodes.Pop(), *left = nodes.Pop(), *opNode = new exprNode;
        opNode->chr = op;
        opNode->lExpr = left;
        opNode->rExpr = right;
        nodes.Push(opNode);
    }

    exprNode *p = nodes.Pop();
    this->root = p;
}

void BinaryExpressionTree::Release(exprNode *bn)
{
    if (bn != NULL)
    {
        Release(bn->lExpr);
        Release(bn->rExpr);
        delete bn;
    }
}

void BinaryExpressionTree::InOrder(exprNode *bn)
{
    if (bn != NULL)
    {
        InOrder(bn->lExpr);
        cout << bn->chr;
        InOrder(bn->rExpr);
    }
}

void BinaryExpressionTree::PreOrder(exprNode *bn)
{
    if (bn != NULL)
    {
        cout << bn->chr;
        PreOrder(bn->lExpr);
        PreOrder(bn->rExpr);
    }
}

void BinaryExpressionTree::PostOrder(exprNode *bn)
{
    if (bn != NULL)
    {
        PostOrder(bn->lExpr);
        PostOrder(bn->rExpr);
        cout << bn->chr;
    }
}

struct netNode
{
    int attenuationFromParent, maxAttenuationToLeafs;
    bool isSetBoost;
    netNode *lnode, *rnode;
};

class SignalNetBinaryTree
{
  private:
    netNode *root;
    void Release(netNode *node);
    void SetBoost(netNode *node, int tolerance);
    void Preorder(netNode *node);
    void InOrder(netNode *node);
    netNode *Create(netNode *node);

  public:
    SignalNetBinaryTree();
    ~SignalNetBinaryTree() { Release(root); }
    void SetBoost(int tolerance) { SetBoost(root, tolerance); }
    void PrintBoost();
};

SignalNetBinaryTree::SignalNetBinaryTree()
{
    this->root = new netNode;
    this->root->attenuationFromParent = 0;
    this->root->isSetBoost = false;
    cout << "The root has been set, input start form the left child of root: \n";
    this->root->lnode = Create(this->root->lnode);
    this->root->rnode = Create(this->root->rnode);
}

netNode *SignalNetBinaryTree::Create(netNode *node)
{
    cout << "Input the attenuation From Parent: ";
    int data;
    cin >> data;
    if (data == -1)
        return NULL;
    else
    {
        node = new netNode;
        node->attenuationFromParent = data;
        node->isSetBoost = false;
        node->maxAttenuationToLeafs = 0;
        node->lnode = Create(node->lnode);
        node->rnode = Create(node->rnode);
    }
    return node;
}

void SignalNetBinaryTree::Release(netNode *bn)
{
    if (bn != NULL)
    {
        Release(bn->lnode);
        Release(bn->rnode);
        delete bn;
    }
}

void SignalNetBinaryTree::SetBoost(netNode *node, int tolerance)
{
    if (node != NULL)
    {
        SetBoost(node->lnode, tolerance);
        SetBoost(node->rnode, tolerance);
        if (node == this->root)
        {
            this->root->isSetBoost = false;
            return;
        }
        if (node->lnode == NULL && node->rnode == NULL)
        {
            node->maxAttenuationToLeafs = 0;
            node->isSetBoost = false;
        }
        else
        {
            node->maxAttenuationToLeafs = 0;
            if (node->lnode != NULL)
            {
                if (node->lnode->maxAttenuationToLeafs + node->lnode->attenuationFromParent > tolerance)
                    node->lnode->isSetBoost = true;
                else
                    node->maxAttenuationToLeafs = node->lnode->maxAttenuationToLeafs +
                                                  node->lnode->attenuationFromParent;
            }

            if (node->rnode != NULL)
            {
                if (node->rnode->maxAttenuationToLeafs + node->rnode->attenuationFromParent > tolerance)
                    node->rnode->isSetBoost = true;
                else
                {
                    if (node->maxAttenuationToLeafs < node->rnode->maxAttenuationToLeafs +
                                                          node->rnode->attenuationFromParent)
                        node->maxAttenuationToLeafs = node->rnode->maxAttenuationToLeafs +
                                                      node->rnode->attenuationFromParent;
                }
            }
        }
    }
}

void SignalNetBinaryTree::PrintBoost()
{
    Preorder(root);
    cout << "\n";
    InOrder(root);
}

void SignalNetBinaryTree::Preorder(netNode *node)
{
    if (node != NULL)
    {
        cout << (node->isSetBoost ? "Y" : "N") << " ";
        Preorder(node->lnode);
        Preorder(node->rnode);
    }
}
void SignalNetBinaryTree::InOrder(netNode *node)
{
    if (node != NULL)
    {
        InOrder(node->lnode);
        cout << (node->isSetBoost ? "Y" : "N") << " ";
        InOrder(node->rnode);
    }
}

struct huffmanNode
{
    int weight, lchild, rchild, parent;
};

void GetMax(huffmanNode huff[], int max[], int n)
{
    max[0] = max[1] = -1;
    for (int i = 0; i != n; i++)
    {
        if (huff[i].weight > max[0])
        {
            max[1] = max[0];
            max[0] = huff[i].weight;
        }
        else if (huff[i].weight > max[1])
        {
            max[1] = huff[i].weight;
        }
    }
}

void CreateHuffmanTree(huffmanNode huff[], int weight[], int n)
{
    for (int i = 0; i != 2 * n - 1; i++)
    {
        if (i < n)
            huff[i].weight = weight[i];
        else
            huff[i].weight = 0;
        huff[i].parent = -1;
        huff[i].lchild = huff[i].rchild = -1;
    }
    int max[2];
    for (int i = n; i != 2 * n - 1; i++)
    {
        GetMax(huff, max, i);
        huff[max[0]].parent = i;
        huff[max[1]].parent = i;
        huff[i].weight = huff[max[0]].weight + huff[max[1]].weight;
        huff[i].lchild = max[0];
        huff[i].lchild = max[1];
    }
}

#endif // !APPLICATIONOFTREE_H