#ifndef APPLICATIONOFLIST_H
#define APPLICATIONOFLIST_H
#include "List.h"
using namespace std;

const float epsilon = 1e-06;

template <class T>
void Union(SeqList<T> &List1, SeqList<T> &List2)
{
  int *tmp = new int[List2.length];
  for (int i = 0; i != List2.length; i++)
  {
    tmp[i] = 0;
    if (List1.LocateFirst(List2[i]) == -1)
    {
      tmp[i] = 1;
    }
  }

  for (int i = 0; i != List2.length; i++)
  {
    if (tmp[i] == 1)
    {
      List1.Add(List2[i]);
    }
  }

  delete[] tmp;
}

template <class T>
void Intersect(SeqList<T> &List1, SeqList<T> &List2)
{
  int i = 0;
  while (i != List1.length)
  {
    if (List2.LocateFirst(List1[i]) != -1)
    {
      List1.Delete(i);
    }
    i++;
  }
}

template <class T>
bool Subset(LinkList<T> &ll, LinkList<T> &rl)
{
  Node<T> *r = ll.first->Next;
  while (r->Next != NULL)
  {
    if (rl.Locate(r->Data) == -1)
      return false;
    r = r->Next;
  }

  return true;
}

template <class T>
bool IsEqual(LinkList<T> &ll, LinkList<T> &rl)
{
  return Subset<T>(ll, rl) && Subset<T>(rl, ll);
}

template <class T>
void Intersect(LinkList<T> &ll, LinkList<T> &rl)
{
  Node<T> *r = ll.first->Next;
  T x;
  int count = 0;
  while (count != ll.length)
  {
    x = r->Data;
    r = r->Next;
    if (rl.Locate(x) == -1)
      ll.Delete(count);
    else
      count++;
  }
}

template <class T>
void Union(LinkList<T> &ll, LinkList<T> &rl)
{
  Node<T> *r = rl.first;
  while (r->Next != NULL)
  {
    r = r->Next;
    if (ll.Locate(r->Data) == -1)
      ll.Add(r->Data);
  }
}

template <class T>
void Different(LinkList<T> &ll, LinkList<T> &rl)
{
  if (!Subset(rl, ll))
    throw "the right list is not the subset of the left list";

  Node<T> *r = rl.first->Next;
  while (r != NULL)
  {
    ll.Delete(ll.Locate(r->Data));
    r = r->Next;
  }
}

void SimplifyJosephRing(int arr[], int n, int m)
{
  int idx = -1;
  for (int len = n; len > 0; len--)
  {
    int i = 0;
    while (i != m)
    {
      idx = (idx + 1) % n;
      if (arr[idx] != 0)
        i++;
    }

    cout << arr[idx] << " ";
    arr[idx] = 0;
  }
}

void JosephRing(int arr[], int n, int m)
{
  NoHeadCyclicList<int> ring(arr, n);
  Node<int> *current = ring.first, *del = NULL;
  while (current->Next != ring.first)
    current = current->Next;

  int count = 0;
  while (current->Next != current)
  {
    if (count == m - 1)
    {
      del = current->Next;
      cout << del->Data << " ";
      current->Next = del->Next;
      delete del;
      count = 0;
    }
    else
    {
      current = current->Next;
      count++;
    }
  }
  cout << current->Data << " ";
  delete current;
  ring.first = NULL;
}

struct PolyItem
{
  int poly;
  float coefficient;
};

ostream &operator<<(ostream &os, const PolyItem &item)
{
  if (item.coefficient > 0)
    cout << "+" << item.coefficient << "x^" << item.poly;
  else
    cout << item.coefficient << "x^" << item.poly;
  return os;
}

const int maxItemSize = 100;

inline void GetPolyList(int ploy[], float coef[], int len, PolyItem item[])
{
  for (int i = 0; i != len; i++)
  {
    item[i].poly = ploy[i];
    item[i].coefficient = coef[i];
  }
}

void Polynomial(int apoly[], float acoef[], int alen, int bpoly[], float bcoef[], int blen)
{
  PolyItem item[maxItemSize];
  GetPolyList(apoly, acoef, alen, item);
  LinkList<PolyItem> polya(item, alen);
  GetPolyList(bpoly, bcoef, blen, item);
  LinkList<PolyItem> polyb(item, blen);

  cout << "f_a(x) = ";
  polya.PrintList();
  cout << "f_b(x) = ";
  polyb.PrintList();

  Node<PolyItem> *body = polya.first, *curr = polyb.first->Next, *add;

  while (body->Next != NULL && curr != NULL)
  {
    if (body->Next->Data.poly > curr->Data.poly)
    {
      add = new Node<PolyItem>;
      add->Data.poly = curr->Data.poly;
      add->Data.coefficient = curr->Data.coefficient;
      add->Next = body->Next;
      body->Next = add;
      curr = curr->Next;
    }
    else if (body->Next->Data.poly == curr->Data.poly)
    {
      if (body->Next->Data.coefficient + curr->Data.coefficient > epsilon)
      {
        PolyItem plusItem;
        plusItem.poly = body->Next->Data.poly;
        plusItem.coefficient = body->Next->Data.coefficient + curr->Data.coefficient;
        body->Next->Data = plusItem;
      }
      else
      {
        add = body->Next;
        body->Next = body->Next->Next;
        delete add;
        body = body->Next;
      }
      curr = curr->Next;
    }
    else
    {
      body = body->Next;
    }
  }

  while (curr != NULL)
  {
    body->Next = curr;
    body = body->Next;
    curr = curr->Next;
  }

  cout << "After adding f_b(x) to f_a(x), f_a(x) = ";
  polya.PrintList();
}

#endif // !APPLICATIONOFLIST_H