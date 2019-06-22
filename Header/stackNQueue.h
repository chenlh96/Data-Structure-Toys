#ifndef STACKNQUEUE_H
#define STACKNQUEUE_H
#include <iostream>
using namespace std;

const int StackSize = 100;

template <class DataType>
class SeqStack
{
  public:
    SeqStack();
    ~SeqStack() {}
    void Push(DataType x);
    DataType Pop();
    DataType GetTop();
    int Empty();

  private:
    DataType data[StackSize];
    int top;
};

template <class DataType>
SeqStack<DataType>::SeqStack()
{
    top = -1;
}

template <class DataType>
void SeqStack<DataType>::Push(DataType x)
{
    if (top == StackSize - 1)
        throw "up";

    data[++top] = x;
}

template <class DataType>
DataType SeqStack<DataType>::Pop()
{
    if (top == -1)
        throw "down";

    return data[top--];
}

template <class DataType>
DataType SeqStack<DataType>::GetTop()
{
    if (top == -1)
        return -1;

    return data[top];
}

template <class DataType>
int SeqStack<DataType>::Empty()
{
    return top == -1 ? 1 : 0;
}

template <class DataType>
class DualStack
{
    DualStack();
    void Push(int i, DataType x);
    DataType Pop(int i);

  private:
    DataType data[StackSize];
    int top1, top2;
};

template <class DataType>
DualStack<DataType>::DualStack()
{
    top1 = -1;
    top2 = StackSize;
}

template <class DataType>
void DualStack<DataType>::Push(int i, DataType x)
{
    if (top1 == top2 - 1)
        throw "up";

    if (i == 1)
    {
        data[++top1] = x;
    }
    else if (i == 2)
    {
        data[--top2] = x;
    }
}

template <class DataType>
DataType DualStack<DataType>::Pop(int i)
{
    DataType x;
    if (i == 1)
    {
        if (top1 == -1)
            throw "down";
        x = data[top1--];
    }
    else if (i == 2)
    {
        if (top2 == StackSize)
            throw "down";
        x = data[top2++];
    }

    return x;
}

template <class DataType>
struct StackNode
{
    DataType data;
    StackNode<DataType> *next;
};

template <class DataType>
class LinkStack
{
  public:
    LinkStack();
    ~LinkStack();
    void Push(DataType x);
    DataType Pop();
    DataType GetTop();
    bool IsEmpty();
    void Print();

  private:
    StackNode<DataType> *top;
};

template <class DataType>
LinkStack<DataType>::LinkStack()
{
    this->top = new StackNode<DataType>;
    this->top->next = NULL;
}

template <class DataType>
LinkStack<DataType>::~LinkStack()
{
    StackNode<DataType> *p = this->top;
    while (this->top != NULL)
    {
        this->top = this->top->next;
        delete p;
        p = this->top;
    }
}

template <class DataType>
void LinkStack<DataType>::Push(DataType x)
{
    StackNode<DataType> *p = new StackNode<DataType>;
    p->data = x;
    p->next = this->top;
    this->top = p;
}

template <class DataType>
bool LinkStack<DataType>::IsEmpty()
{
    return this->top->next == NULL;
}

template <class DataType>
DataType LinkStack<DataType>::Pop()
{
    if (this->top->next == NULL)
        throw "Empty Stack";

    StackNode<DataType> *tmp = this->top;
    DataType x = tmp->data;
    this->top = this->top->next;
    delete tmp;
    return x;
}

template <class DataType>
DataType LinkStack<DataType>::GetTop()
{
    if (this->top->next == NULL)
        throw "Empty Stack";

    return this->top->data;
}

template <class DataType>
void LinkStack<DataType>::Print()
{
    StackNode<DataType> *curr = this->top;
    while (curr->next != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "\n";
}

template <class DataType>
class NoHeadLinkStack
{
  public:
    NoHeadLinkStack();
    ~NoHeadLinkStack();
    void Push(DataType x);
    DataType Pop();
    bool IsEmpty();
    void Print();

  private:
    StackNode<DataType> *top;
};

template <class DataType>
NoHeadLinkStack<DataType>::NoHeadLinkStack()
{
    this->top = NULL;
}

template <class DataType>
NoHeadLinkStack<DataType>::~NoHeadLinkStack()
{
    StackNode<DataType> *p = this->top;
    while (this->top != NULL)
    {
        this->top = this->top->next;
        delete p;
        p = this->top;
    }
}

template <class DataType>
void NoHeadLinkStack<DataType>::Push(DataType x)
{
    if (this->top == NULL)
    {
        this->top = new StackNode<DataType>;
        this->top->data = x;
        this->top->next = NULL;
    }
    else
    {
        StackNode<DataType> *p = new StackNode<DataType>;
        p->data = x;
        p->next = this->top;
        this->top = p;
    }
}

template <class DataType>
DataType NoHeadLinkStack<DataType>::Pop()
{
    if (this->IsEmpty())
        throw "Empty Set";
    StackNode<DataType> *p = this->top;
    this->top = this->top->next;
    DataType ret = p->data;
    delete p;
    return ret;
}

template <class DataType>
bool NoHeadLinkStack<DataType>::IsEmpty()
{
    return this->top == NULL;
}

template <class DataType>
void NoHeadLinkStack<DataType>::Print()
{
    StackNode<DataType> *curr = this->top;
    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "\n";
}

template <class DataType>
class LinkQueue
{
  public:
    LinkQueue();
    LinkQueue(const LinkQueue<DataType> &);
    ~LinkQueue();
    void Enqueue(DataType x);
    DataType Dequeue();
    DataType GetFront();
    DataType GetRear();
    int IsEmpty();
    void Print();

  private:
    StackNode<DataType> *front, *rear;
};

template <class DataType>
LinkQueue<DataType>::LinkQueue()
{
    StackNode<DataType> *init = new StackNode<DataType>;
    init->next = NULL;
    this->front = this->rear = init;
}

template <class DataType>
LinkQueue<DataType>::LinkQueue(const LinkQueue<DataType> &lq)
{
    this->front = new StackNode<DataType>;
    StackNode<DataType> *ori = lq.front, *copy = this->front, *curr = NULL;
    while (ori->next == NULL)
    {
        ori = ori->next;
        curr = new StackNode<DataType>;
        curr->data = ori->data;
        copy->next = curr;
        copy = curr;
    }
    this->rear = copy;
}

template <class DataType>
LinkQueue<DataType>::~LinkQueue()
{
    StackNode<DataType> *del = this->front;
    while (this->front != NULL)
    {
        this->front = this->front->next;
        delete del;
        del = this->front;
    }
    this->rear = NULL;
}

template <class DataType>
void LinkQueue<DataType>::Enqueue(DataType x)
{
    StackNode<DataType> *p = new StackNode<DataType>;
    p->data = x;
    p->next = NULL;
    this->rear->next = p;
    this->rear = p;
}

template <class DataType>
DataType LinkQueue<DataType>::Dequeue()
{
    StackNode<DataType> *ret = this->front->next;
    DataType x = ret->data;
    this->front->next = this->front->next->next;
    if (this->front->next == NULL)
        this->rear = this->front;
    delete ret;
    return x;
}

template <class DataType>
DataType LinkQueue<DataType>::GetFront()
{
    return this->front->next->data;
}

template <class DataType>
DataType LinkQueue<DataType>::GetRear()
{
    return this->rear->data;
}

template <class DataType>
int LinkQueue<DataType>::IsEmpty() { return this->front == this->rear; }

template <class DataType>
void LinkQueue<DataType>::Print()
{
    StackNode<DataType> *curr = this->front;
    while (curr != this->rear)
    {
        curr = curr->next;
        cout << curr->data << " ";
    }
    cout << "\n";
}

template <class DataType>
class NoHeadLinkQueue
{
  public:
    NoHeadLinkQueue();
    ~NoHeadLinkQueue();
    void Enqueue(DataType x);
    DataType Dequeue();
    bool IsEmpty();
    void Print();

  private:
    StackNode<DataType> *front, *rear;
};

template <class DataType>
NoHeadLinkQueue<DataType>::NoHeadLinkQueue()
{
    this->front = NULL;
    this->rear = this->front;
}

template <class DataType>
NoHeadLinkQueue<DataType>::~NoHeadLinkQueue()
{
    StackNode<DataType> *del = this->front;
    while (this->front != NULL)
    {
        this->front = this->front->next;
        delete del;
        del = this->front;
    }
    this->rear = NULL;
}

template <class DataType>
void NoHeadLinkQueue<DataType>::Enqueue(DataType x)
{
    if (this->front == NULL && this->rear == NULL)
    {
        this->front = new StackNode<DataType>;
        this->front->data = x;
        this->front->next = NULL;
        this->rear = this->front;
    }
    else
    {
        StackNode<DataType> *p = new StackNode<DataType>;
        p->data = x;
        p->next = NULL;
        this->rear->next = p;
        this->rear = p;
    }
}

template <class DataType>
DataType NoHeadLinkQueue<DataType>::Dequeue()
{
    StackNode<DataType> *ret;
    DataType x;
    if (this->front == this->rear)
    {
        ret = this->front;
        x = ret->data;
        delete ret;
        this->front = this->rear = NULL;
    }
    else
    {
        ret = this->front;
        x = ret->data;
        this->front = this->front->next;
        delete ret;
    }
    return x;
}

template <class DataType>
bool NoHeadLinkQueue<DataType>::IsEmpty()
{
    return this->front == NULL && this->rear == NULL;
}

template <class DataType>
void NoHeadLinkQueue<DataType>::Print()
{
    StackNode<DataType> *curr = this->front;
    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "\n";
}

const int QueueSize = 10;

template <class DataType>
class CirQueue
{
  public:
    CirQueue();
    ~CirQueue() {}
    void Enqueue(DataType x);
    DataType Dequeue();
    bool IsEmpty() { return front == rear; }
    void Print();

  private:
    DataType data[QueueSize];
    int front, rear;
};

template <class DataType>
CirQueue<DataType>::CirQueue()
{
    front = rear = QueueSize - 1;
}

template <class DataType>
void CirQueue<DataType>::Enqueue(DataType x)
{
    if ((rear + 1) % QueueSize == front)
        throw "up";

    rear = (rear + 1) % QueueSize;
    data[rear] = x;
}

template <class DataType>
DataType CirQueue<DataType>::Dequeue()
{
    if (front == rear)
        throw "down";

    DataType x = data[front];
    front = (front + 1) % QueueSize;
    return x;
}
#endif // !STACKNQUEUE_H

