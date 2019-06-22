#ifndef List_H
#define List_H
#include <iostream>
using namespace std;
const int MaxSize = 10000;

//==============================================

class IntSeqList
{
public:
  IntSeqList();
  IntSeqList(int arr[], int n);
  ~IntSeqList();
  void Insert(int i, int x);
  int Delete(int i);
  int Locate(int x);
  void PrintList();
  int Length();

private:
  int data[MaxSize];
  int length;
};

// --------------------------------------------
// Implement of the Sequencial List
IntSeqList::IntSeqList()
{
    length = 0;
}

IntSeqList::IntSeqList(int arr[], int n)
{
    if (n > MaxSize)
        throw "Illeagal Parameter: n";

    for (int i = 0; i < n; i++)
    {
        data[i] = arr[i];
    }

    length = n;
}

IntSeqList::~IntSeqList()
{
}

void IntSeqList::Insert(int i, int x)
{
    if (length > MaxSize)
        throw "length greater then upper bound";
    if (i < 1 || i > length + 1)
        throw "arr out of bound exception";
    for (int j = length; j >= i; j--)
    {
        data[j] = data[j - 1];
    }
    data[i - 1] = x;
    length++;
}

int IntSeqList::Delete(int i)
{
    if (length == 0)
        throw "length less then 0: -1";
    if (i < 1 || i > length)
        throw "arr out of bound exception";
    int x = data[i - 1];
    for (int j = i; j < length; j++)
    {
        data[j - 1] = data[j];
    }
    data[i - 1] = x;
    length--;
    return x;
}

int IntSeqList::Locate(int x)
{
    for (int i = 0; i < length; i++)
    {
        if (data[i] == x)
            return i;
    }

    return -1;
}

void IntSeqList::PrintList()
{
    for (int i = 0; i < length; i++)
    {
        cout << data[i] << " ";
    }
}

int IntSeqList::Length()
{
    return length;
}
//--------------------------------------------------------

//==============================================

//==============================================

template <class DataType>
class SeqList
{
public:
  SeqList();
  SeqList(DataType arr[], int n);
  SeqList(SeqList &list);
  ~SeqList()
  {
  }
  void Insert(int i, DataType x);
  void Add(DataType x);
  DataType Delete(int i);
  int LocateFirst(DataType x);
  void PrintList();
  int Length();
  DataType Get(int i);
  DataType &operator[](int i);

  template <class T>
  friend void Union(SeqList<T> &List1, SeqList<T> &List2);
  template <class T>
  friend void Intersect(SeqList<T> &List1, SeqList<T> &List2);

private:
  DataType arr[MaxSize];
  int length;
};

template <class DataType>
SeqList<DataType>::SeqList()
{
  this->length = 0;
}

template <class DataType>
SeqList<DataType>::SeqList(DataType arr[], int n)
{
  if (n > MaxSize)
  {
    throw "OutOfMemoryException";
  }
  this->length = n;
  for (int i = 0; i != this->length; i++)
  {
    this->arr[i] = arr[i];
  }
}

template <class DataType>
SeqList<DataType>::SeqList(SeqList &list)
{
  this->length = list.length;
  for (int i = 0; i != this->length; i++)
  {
    this->arr[i] = list.arr[i];
  }
}

template <class DataType>
void SeqList<DataType>::Insert(int i, DataType x)
{
  if (this->length > MaxSize)
    throw "OutOfMemoryException";
  if (i < 0 || i > length - 1)
    throw "OutOfBoundException";

  for (int j = this->length; j > i; j--)
  {
    this->arr[j] = this->arr[j - 1];
  }
  this->arr[i] = x;
  this->length++;
}

template <class DataType>
void SeqList<DataType>::Add(DataType x)
{
  if (this->length >= MaxSize)
    throw "OutOfMemoryException";

  this->arr[this->length] = x;
  this->length++;
}

template <class DataType>
DataType SeqList<DataType>::Delete(int i)
{
  if (length == 0)
    throw "EmptyException";
  if (i < 0 || i > length - 1)
    throw "OutOfBoundException";

  DataType x = this->arr[i];

  for (int j = i; j < length; j++)
  {
    this->arr[j] = this->arr[j + 1];
  }
  // Delete(this->arr[length - 1]);
  this->length--;

  return x;
}

template <class DataType>
int SeqList<DataType>::LocateFirst(DataType x)
{
  for (int i = 0; i < this->length; i++)
  {
    if (this->arr[i] == x)
    {
      return i;
    }
  }

  return -1;
}

template <class DataType>
void SeqList<DataType>::PrintList()
{
  for (int i = 0; i != this->length; i++)
  {
    cout << this->arr[i] << " ";
  }

  cout << "\n";
}

template <class DataType>
int SeqList<DataType>::Length()
{
  return this->length;
}

template <class DataType>
DataType SeqList<DataType>::Get(int i)
{
  return this->arr[i];
}

template <class DataType>
DataType &SeqList<DataType>::operator[](int i)
{
  return arr[i];
}

//==============================================

//==============================================
template <class DataType>
class Node
{
public:
  DataType Data;
  Node<DataType> *Next;
};

template <class DataType>
class LinkList
{
public:
  LinkList();
  LinkList(DataType arr[], int n);
  LinkList(const LinkList<DataType> &ll);
  LinkList<DataType> &operator=(const LinkList<DataType> &ll);
  ~LinkList();
  int Locate(DataType x);
  void Insert(int i, DataType x);
  void Add(DataType x);
  DataType Get(int i);
  DataType Delete(int i);
  void PrintList();
  int Length();
  bool IsIncrease();
  void Reverse();
  DataType Get(int i) const;

  template <class T>
  friend bool Subset(LinkList<T> &ll, LinkList<T> &rl);
  template <class T>
  friend bool IsEqual(LinkList<T> &ll, LinkList<T> &rl);
  template <class T>
  friend void Intersect(LinkList<T> &ll, LinkList<T> &rl);
  template <class T>
  friend void Union(LinkList<T> &ll, LinkList<T> &rl);
  template <class T>
  friend void Different(LinkList<T> &ll, LinkList<T> &rl);
  friend void Polynomial(int apoly[], float acoef[], int alen, int bpoly[], float bcoef[], int blen);

private:
  Node<DataType> *first;
  int length;
};

template <class DataType>
LinkList<DataType>::LinkList()
{
  this->first = new Node<DataType>;
  first->Next = NULL;
}

template <class DataType>
LinkList<DataType>::LinkList(DataType arr[], int n)
{
  Node<DataType> *r, *s;
  this->first = new Node<DataType>;
  r = this->first;

  for (int i = 0; i < n; i++)
  {
    s = new Node<DataType>;
    s->Data = arr[i];
    r->Next = s;
    r = s;
  }
  this->length = n;
  r->Next = NULL;
}

template <class DataType>
LinkList<DataType>::LinkList(const LinkList<DataType> &ll)
{
  this->first = new Node<DataType>;
  this->length = ll.length;
  Node<DataType> *r, *s, *q;
  r = this->first;
  s = ll.first->Next;

  while (s != NULL)
  {
    q = new Node<DataType>;
    q->Data = s->Data;
    r->Next = q;
    r = q;
    s = s->Next;
  }

  r->Next = NULL;
}

template <class DataType>
LinkList<DataType> &LinkList<DataType>::operator=(const LinkList<DataType> &ll)
{
  return *LinkList(ll);
}

template <class DataType>
LinkList<DataType>::~LinkList()
{
  Node<DataType> *q = NULL;
  while (first != NULL)
  {
    q = this->first;
    this->first = first->Next;
    delete q;
  }
}

template <class DataType>
void LinkList<DataType>::Insert(int i, DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;
  int count = -1;
  while (p->Next != NULL && count != i - 1)
  {
    p = p->Next;
    count++;
  }

  if (p->Next == NULL)
    throw "illegal postion";
  else
  {
    s = new Node<DataType>;
    s->Data = x;
    s->Next = p->Next;
    p->Next = s;
  }
  this->length++;
}

template <class DataType>
void LinkList<DataType>::Add(DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;
  while (p->Next != NULL)
    p = p->Next;

  s = new Node<DataType>;
  s->Data = x;
  s->Next = NULL;
  p->Next = s;

  this->length++;
}

template <class DataType>
DataType LinkList<DataType>::Get(int i)
{
  Node<DataType> *p = first;
  int count = -1;
  while (p != NULL && count != i)
  {
    p = p->Next;
    count++;
  }
  if (p == NULL || p->Next == NULL)
    throw "illegal postion";
  return p->Data;
}

template <class DataType>
DataType LinkList<DataType>::Delete(int i)
{
  Node<DataType> *p = first, *q = NULL;
  int count = -1;
  while (p != NULL && count != i - 1)
  {
    p = p->Next;
    count++;
  }
  DataType x;
  if (p == NULL || p->Next == NULL)
    throw "illegal postion";
  else
  {
    q = p->Next;
    x = q->Data;
    p->Next = q->Next;
    delete q;
  }
  this->length--;
  return x;
}

template <class DataType>
int LinkList<DataType>::Locate(DataType x)
{
  Node<DataType> *p = first->Next;
  int count = 0;
  while (p != NULL)
  {
    if (p->Data == x)
      return count;
    p = p->Next;
    count++;
  }
  return -1;
}

template <class DataType>
void LinkList<DataType>::PrintList()
{
  Node<DataType> *p = first->Next;
  while (p != NULL)
  {
    cout << p->Data << " ";
    p = p->Next;
  }
  cout << "\n";
}

template <class DataType>
int LinkList<DataType>::Length() { return length; }

template <class DataType>
bool LinkList<DataType>::IsIncrease()
{
  Node<DataType> *p = first;
  while (p->Next->Next != NULL)
  {
    p = p->Next;
    if (p->Data > p->Next->Data)
      return false;
  }

  return true;
}

template <class DataType>
void LinkList<DataType>::Reverse()
{
  Node<DataType> pre = NULL, p = first->Next, after;

  while (p != NULL)
  {
    after = p->Next;
    p->Next = pre;
    pre = p;
    p = after;
  }

  this->first = pre;
}

template <class DataType>
DataType LinkList<DataType>::Get(int i) const
{
  Node<DataType> *p = this->first;
  int count = -1;
  while (count != i)
  {
    p = p->Next;
    count++;
  }
  DataType x = p->Data;
  return x;
}

//==============================================

//==============================================

template <class DataType>
class CyclicList
{
public:
  CyclicList();
  CyclicList(DataType arr[], int n);
  CyclicList(const CyclicList<DataType> &ll);
  CyclicList<DataType> &operator=(const CyclicList<DataType> &ll);
  ~CyclicList();
  int Locate(DataType x);
  void Insert(int i, DataType x);
  void Add(DataType x);
  DataType Delete(int i);
  void PrintList();
  int Length();

private:
  Node<DataType> *first;
  int length;
};

template <class DataType>
CyclicList<DataType>::CyclicList()
{
  this->first = new Node<DataType>;
  this->first->Next = this->first;
  this->length = 0;
}

template <class DataType>
CyclicList<DataType>::CyclicList(DataType arr[], int n)
{
  Node<DataType> *r, *s;
  this->first = new Node<DataType>;
  r = this->first;

  for (int i = 0; i < n; i++)
  {
    s = new Node<DataType>;
    s->Data = arr[i];
    r->Next = s;
    r = s;
  }
  this->length = n;
  r->Next = first;
}

template <class DataType>
CyclicList<DataType>::CyclicList(const CyclicList<DataType> &ll)
{
  this->first = new Node<DataType>;
  this->length = ll.length;
  Node<DataType> *r, *s, *q;
  r = this->first;
  s = ll.first->Next;

  while (s != ll.first)
  {
    q = new Node<DataType>;
    q->Data = s->Data;
    r->Next = q;
    r = q;
    s = s->Next;
  }

  r->Next = first;
}

template <class DataType>
CyclicList<DataType> &CyclicList<DataType>::operator=(const CyclicList<DataType> &ll)
{
  return *CyclicList(ll);
}

template <class DataType>
CyclicList<DataType>::~CyclicList()
{
  Node<DataType> *q = NULL;
  while (first != NULL)
  {
    q = this->first;
    this->first = this->first->Next;
    delete q;
  }
}

template <class DataType>
void CyclicList<DataType>::Insert(int i, DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;
  int count = -1;
  while (p->Next != this->first && count != i - 1)
  {
    p = p->Next;
    count++;
  }

  if (p->Next == this->first)
    throw "illegal postion";
  else
  {
    s = new Node<DataType>;
    s->Data = x;
    s->Next = p->Next;
    p->Next = s;
  }
  this->length++;
}

template <class DataType>
void CyclicList<DataType>::Add(DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;
  while (p->Next != this->first)
    p = p->Next;

  s = new Node<DataType>;
  s->Data = x;
  s->Next = this->first;
  p->Next = s;

  this->length++;
}

template <class DataType>
DataType CyclicList<DataType>::Delete(int i)
{
  Node<DataType> *p = this->first, *q = NULL;
  int count = -1;
  while (p->Next != this->first && count != i - 1)
  {
    p = p->Next;
    count++;
  }
  DataType x;
  if (p->Next == this->first)
    throw "illegal postion";
  else
  {
    q = p->Next;
    x = q->Data;
    p->Next = q->Next;
    delete q;
  }
  this->length--;
  return x;
}

template <class DataType>
int CyclicList<DataType>::Locate(DataType x)
{
  Node<DataType> *p = this->first->Next;
  int count = 0;
  while (p != this->first)
  {
    if (p->Data == x)
      return count;
    p = p->Next;
    count++;
  }
  return -1;
}

template <class DataType>
void CyclicList<DataType>::PrintList()
{
  Node<DataType> *p = this->first->Next;
  while (p != this->first)
  {
    cout << p->Data << " ";
    p = p->Next;
  }
  cout << "\n";
}

template <class DataType>
int CyclicList<DataType>::Length() { return length; }

//==============================================

//==============================================

template <class DataType>
class NoHeadLinkList
{
public:
  NoHeadLinkList();
  NoHeadLinkList(DataType arr[], int n);
  NoHeadLinkList(const NoHeadLinkList<DataType> &ll);
  NoHeadLinkList<DataType> &operator=(const NoHeadLinkList<DataType> &ll);
  ~NoHeadLinkList();
  int Locate(DataType x);
  void Insert(int i, DataType x);
  void Add(DataType x);
  DataType Delete(int i);
  void PrintList();
  int Length();

private:
  Node<DataType> *first;
  int length;
};

template <class DataType>
NoHeadLinkList<DataType>::NoHeadLinkList()
{
  this->first = NULL;
  this->length = 0;
}

template <class DataType>
NoHeadLinkList<DataType>::NoHeadLinkList(DataType arr[], int n)
{
  Node<DataType> *r, *s;
  this->first = new Node<DataType>;
  r = this->first;

  for (int i = 0; i < n; i++)
  {
    s = new Node<DataType>;
    s->Data = arr[i];
    r->Next = s;
    r = s;
  }
  this->length = n;
  r->Next = NULL;

  s = this->first;
  this->first = this->first->Next;
  delete s;
}

template <class DataType>
NoHeadLinkList<DataType>::NoHeadLinkList(const NoHeadLinkList<DataType> &ll)
{
  this->first = new Node<DataType>;
  Node<DataType> *r, *s, *q;
  r = this->first;
  s = ll.first;

  while (s != NULL)
  {
    q = new Node<DataType>;
    q->Data = s->Data;
    r->Next = q;
    r = q;
    s = s->Next;
  }

  this->length = ll.length;
  r->Next = NULL;
  q = this->first;
  this->first = this->first->Next;
  delete q;
}

template <class DataType>
NoHeadLinkList<DataType> &NoHeadLinkList<DataType>::operator=(const NoHeadLinkList<DataType> &ll)
{
  return *NoHeadLinkList(ll);
}

template <class DataType>
NoHeadLinkList<DataType>::~NoHeadLinkList()
{
  Node<DataType> *q = NULL;
  while (first != NULL)
  {
    q = this->first;
    this->first = first->Next;
    delete q;
  }
}

template <class DataType>
void NoHeadLinkList<DataType>::Insert(int i, DataType x)
{
  Node<DataType> *s = NULL;

  if (i == 0)
  {
    s = new Node<DataType>;
    s->Data = x;
    s->Next = first;
    first = s;
  }
  else
  {
    Node<DataType> *p = this->first;
    int count = 0;
    while (p->Next != NULL && count != i - 1)
    {
      p = p->Next;
      count++;
    }

    if (p->Next == NULL)
      throw "illegal postion";
    else
    {
      s = new Node<DataType>;
      s->Data = x;
      s->Next = p->Next;
      p->Next = s;
    }
  }

  this->length++;
}

template <class DataType>
void NoHeadLinkList<DataType>::Add(DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;
  while (p->Next != NULL)
    p = p->Next;

  s = new Node<DataType>;
  s->Data = x;
  s->Next = NULL;
  p->Next = s;

  this->length++;
}

template <class DataType>
DataType NoHeadLinkList<DataType>::Delete(int i)
{
  Node<DataType> *q = NULL;
  DataType x;

  if (i == 0)
  {
    q = first;
    x = first->Data;
    first = first->Next;
    delete q;
  }
  else
  {
    Node<DataType> *p = this->first;
    int count = 0;
    while (p != NULL && count != i - 1)
    {
      p = p->Next;
      count++;
    }
    if (p == NULL || p->Next == NULL)
      throw "illegal postion";
    else
    {
      q = p->Next;
      x = q->Data;
      p->Next = q->Next;
      delete q;
    }
    this->length--;
  }
  return x;
}

template <class DataType>
int NoHeadLinkList<DataType>::Locate(DataType x)
{
  Node<DataType> *p = first;
  int count = 0;
  while (p != NULL)
  {
    if (p->Data == x)
      return count;
    p = p->Next;
    count++;
  }
  return -1;
}

template <class DataType>
void NoHeadLinkList<DataType>::PrintList()
{
  Node<DataType> *p = first;
  while (p != NULL)
  {
    cout << p->Data << " ";
    p = p->Next;
  }
  cout << "\n";
}

template <class DataType>
int NoHeadLinkList<DataType>::Length() { return length; }
//==============================================

//==============================================

template <class DataType>
class NoHeadCyclicList
{
public:
  NoHeadCyclicList();
  NoHeadCyclicList(DataType arr[], int n);
  // NoHeadCyclicList(const NoHeadCyclicList<DataType> &ll);
  // NoHeadCyclicList<DataType> &operator=(const NoHeadCyclicList<DataType> &ll);
  ~NoHeadCyclicList();
  int Locate(DataType x);
  void Insert(int i, DataType x);
  // void Add(DataType x);
  DataType Delete(int i);
  void PrintList();
  int Length();

  friend void JosephRing(int arr[], int n, int m);

private:
  Node<DataType> *first;
  int length;
};

template <class DataType>
NoHeadCyclicList<DataType>::NoHeadCyclicList()
{
  this->first = NULL;
  this->length = 0;
}

template <class DataType>
NoHeadCyclicList<DataType>::NoHeadCyclicList(DataType arr[], int n)
{
  Node<DataType> *r, *s;
  this->first = new Node<DataType>;
  r = this->first;

  for (int i = 0; i < n; i++)
  {
    s = new Node<DataType>;
    s->Data = arr[i];
    r->Next = s;
    r = s;
  }
  this->length = n;

  s = this->first;
  this->first = this->first->Next;
  delete s;

  r->Next = this->first;
}

template <class DataType>
NoHeadCyclicList<DataType>::~NoHeadCyclicList()
{
  Node<DataType> *q = NULL;
  while (first != NULL)
  {
    q = this->first;
    this->first = first->Next;
    delete q;
  }
}

template <class DataType>
void NoHeadCyclicList<DataType>::Insert(int i, DataType x)
{
  Node<DataType> *p = this->first, *s = NULL;

  if (i == 0)
  {
    while (p->Next != this->first)
      p = p->Next;

    s = new Node<DataType>;
    s->Data = x;
    s->Next = first;
    first = s;
    p->Next = this->first;
  }
  else
  {
    p = p->Next;
    int count = 1;
    while (p != this->first && count != i - 1)
    {
      p = p->Next;
      count++;
    }

    if (p == this->first && count != 1)
      throw "illegal postion";
    else
    {
      s = new Node<DataType>;
      s->Data = x;
      s->Next = p->Next;
      p->Next = s;
    }
  }

  this->length++;
}

template <class DataType>
DataType NoHeadCyclicList<DataType>::Delete(int i)
{
  Node<DataType> *p = this->first, *q = NULL;
  DataType x;

  if (i == 0)
  {
    while (p->Next != this->first)
      p = p->Next;

    q = this->first;
    x = this->first->Data;
    this->first = this->first->Next;
    p->Next = this->first;
    delete q;
  }
  else
  {
    p = p->Next;
    int count = 1;
    while (p != this->first && count != i - 1)
    {
      p = p->Next;
      count++;
    }
    if ((p != this->first && count != i - 1) || p->Next == this->first)
      throw "illegal postion";
    else
    {
      q = p->Next;
      x = q->Data;
      p->Next = q->Next;
      delete q;
    }
    this->length--;
  }
  return x;
}

template <class DataType>
int NoHeadCyclicList<DataType>::Locate(DataType x)
{
  Node<DataType> *p = this->first;
  int count = 0;
  if (p->Data == x)
    return count;

  p = p->Next;
  while (p != this->first)
  {
    count++;
    if (p->Data == x)
      return count;
    p = p->Next;
  }
  return -1;
}

template <class DataType>
void NoHeadCyclicList<DataType>::PrintList()
{
  Node<DataType> *p = first;
  cout << p->Data << " ";
  p = p->Next;
  while (p != this->first)
  {
    cout << p->Data << " ";
    p = p->Next;
  }
  cout << "\n";
}

template <class DataType>
int NoHeadCyclicList<DataType>::Length() { return length; }

template <class DataType>
struct DualNode
{
  DataType data;
  DualNode<DataType> *next;
  DualNode<DataType> *prev;
};

template <class DataType>
class DualLinkList
{
public:
  DualLinkList();
  DualLinkList(DataType arr[], int n);
  DualLinkList(const DualLinkList<DataType> &);
  DualLinkList &operator=(const DualLinkList<DataType> &) = default;
  ~DualLinkList();

  void Insert(int i, DataType x);
  DataType Delete(int i);
  int Locate(DataType x);
  void PrintList();
  int Length();

private:
  DualNode<DataType> *first;
};

template <class DataType>
DualLinkList<DataType>::DualLinkList()
{
  this->first = new DualNode<DataType>;
  DualNode<DataType> r = NULL;
  this->first->next = r;
  r->prev = this->first;
}

template <class DataType>
DualLinkList<DataType>::DualLinkList(DataType arr[], int n)
{
  this->first = new DualNode<DataType>;
  DualNode<DataType> *pre = this->first, *curr = NULL;

  for (int i = 0; i != n; i++)
  {
    curr = new DualNode<DataType>;
    curr->data = arr[i];
    pre->next = curr;
    curr->prev = pre;
    pre = curr;
  }
  this->first->prev = NULL;
  curr->next = NULL;
}

template <class DataType>
DualLinkList<DataType>::DualLinkList(const DualLinkList<DataType> &dual)
{
  this->first = new DualNode<DataType>;
  DualNode<DataType> *ori = this->first, *copy = dual.first, *next;

  while (copy->next != NULL)
  {
    copy = copy->next;
    next = new DualNode<DataType>;
    next->data = copy->data;
    ori->next = next;
    next->prev = ori;
    ori = next;
  }
  this->first->prev = ori->next = NULL;
}

template <class DataType>
DualLinkList<DataType>::~DualLinkList()
{
  DualNode<DataType> *del = NULL;
  while (first != NULL)
  {
    del = first;
    first = first->next;
    delete del;
  }
}

template <class DataType>
void DualLinkList<DataType>::Insert(int i, DataType x)
{
  DualNode<DataType> *curr = this->first;
  int idx = -1;
  while (idx != i - 1 && curr != NULL)
  {
    curr = curr->next;
    idx++;
  }

  if (curr == NULL || curr->next == NULL)
    throw "Illegal Position";

  DualNode<DataType> *p = new DualNode<DataType>;
  p->data = x;
  p->next = curr->next;
  p->prev = curr;
  curr->next->prev = p;
  curr->next = p;
}

template <class DataType>
DataType DualLinkList<DataType>::Delete(int i)
{
  DualNode<DataType> *curr = this->first;
  int idx = -1;
  while (idx != i - 1 && curr != NULL)
  {
    curr = curr->next;
    idx++;
  }

  if (curr == NULL || curr->next == NULL)
    throw "Illegal Position";

  DualNode<DataType> *p = curr->next;
  DataType x = p->data;
  curr->next = p->next;
  curr->next->prev = curr;
  delete p;
  return x;
}

template <class DataType>
int DualLinkList<DataType>::Locate(DataType x)
{
  int idx = -1;
  DualNode<DataType> *p = this->first;
  while (p->next != NULL)
  {
    p = p->next;
    idx++;
    if (p->data == x)
      return idx;
  }

  return -1;
}

template <class DataType>
int DualLinkList<DataType>::Length()
{
  int count = 0;
  DualNode<DataType> *p = this->first;
  while (p->next != NULL)
  {
    p = p->next;
    count++;
  }
  return count;
}

template <class DataType>
void DualLinkList<DataType>::PrintList()
{
  DualNode<DataType> *p = this->first;
  while (p->next != NULL)
  {
    p = p->next;
    cout << p->data << " ";
  }
  // while (p->prev != NULL)
  // {
  //   cout << p->data << " ";
  //   p = p->prev;
  // }
  cout << "\n";
}

template <class DataType>
class CyclyicDualLinkList
{
public:
  CyclyicDualLinkList();
  CyclyicDualLinkList(DataType arr[], int n);
  CyclyicDualLinkList(const CyclyicDualLinkList<DataType> &);
  CyclyicDualLinkList &operator=(const CyclyicDualLinkList<DataType> &) = default;
  ~CyclyicDualLinkList();

  void Insert(int i, DataType x);
  DataType Delete(int i);
  int Locate(DataType x);
  void PrintList();
  int Length();

private:
  DualNode<DataType> *first;
};

template <class DataType>
CyclyicDualLinkList<DataType>::CyclyicDualLinkList()
{
  this->first = new DualNode<DataType>;
  this->first->next = this->first;
  this->first->prev = this->first;
}

template <class DataType>
CyclyicDualLinkList<DataType>::CyclyicDualLinkList(DataType arr[], int n)
{
  this->first = new DualNode<DataType>;
  DualNode<DataType> *pre = this->first, *curr = NULL;

  for (int i = 0; i != n; i++)
  {
    curr = new DualNode<DataType>;
    curr->data = arr[i];
    pre->next = curr;
    curr->prev = pre;
    pre = curr;
  }
  curr->next = this->first;
  this->first->prev = curr;
}

template <class DataType>
CyclyicDualLinkList<DataType>::CyclyicDualLinkList(const CyclyicDualLinkList<DataType> &cdl)
{
  this->first = new DualNode<DataType>;
  DualNode<DataType> *pre = this->first, *curr = NULL, *copy = cdl.first;

  while (copy->next != cdl.first)
  {
    copy = copy->next;
    curr = new DualNode<DataType>;
    curr->data = copy->data;
    pre->next = curr;
    curr->prev = pre;
    pre = curr;
  }

  curr->next = this->first;
  this->first->prev = curr;
}

template <class DataType>
CyclyicDualLinkList<DataType>::~CyclyicDualLinkList()
{
  DualNode<DataType> *del = NULL;
  while (first != NULL)
  {
    del = first;
    first = first->next;
    delete del;
  }
}

template <class DataType>
void CyclyicDualLinkList<DataType>::Insert(int i, DataType x)
{
  DualNode<DataType> *curr = this->first;
  int idx = -1;
  while (idx != i - 1 && curr->next != this->first)
  {
    curr = curr->next;
    idx++;
  }

  if (curr->next == this->first)
    throw "Illegal Position";

  DualNode<DataType> *p = new DualNode<DataType>;
  p->data = x;
  p->next = curr->next;
  p->prev = curr;
  curr->next->prev = p;
  curr->next = p;
}

template <class DataType>
DataType CyclyicDualLinkList<DataType>::Delete(int i)
{
  DualNode<DataType> *curr = this->first;
  int idx = -1;
  while (idx != i - 1 && curr->next != this->first)
  {
    curr = curr->next;
    idx++;
  }

  if (curr->next == this->first)
    throw "Illegal Position";

  DualNode<DataType> *p = curr->next;
  DataType x = p->data;
  curr->next = p->next;
  curr->next->prev = curr;
  return x;
}

template <class DataType>
int CyclyicDualLinkList<DataType>::Locate(DataType x)
{
  int idx = -1;
  DualNode<DataType> *p = this->first;
  while (p->next != this->first)
  {
    p = p->next;
    idx++;
    if (p->data == x)
      return idx;
  }

  return -1;
}

template <class DataType>
int CyclyicDualLinkList<DataType>::Length()
{
  int count = -1;
  DualNode<DataType> *p = this->first;
  while (p->next != this->first)
  {
    p = p->next;
    count++;
  }
  return count;
}

template <class DataType>
void CyclyicDualLinkList<DataType>::PrintList()
{
  DualNode<DataType> *p = this->first;
  while (p->next != this->first)
  {
    p = p->next;
    cout << p->data << " ";
  }
  cout << "\n";
}

#endif