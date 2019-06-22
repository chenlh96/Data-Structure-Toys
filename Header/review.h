#include <ctime>
#include <iostream>
#include <time.h>
using namespace std;

template <typename ElemType>
double MySort(ElemType arr[], int n)
{
    time_t start, end;

    time(&start);
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[idx])
                idx = j;
        }

        if (i != idx)
        {
            ElemType tmp = arr[idx];
            arr[idx] = arr[i];
            arr[i] = tmp;
        }
    }
    time(&end);

    return difftime(end, start);
}

template <class DataType>
inline void convert(DataType arr[], int begin, int end)
{
    int b = begin, e = end;
    while (true)
    {
        int tmp = arr[b];
        arr[b] = arr[e];
        arr[e] = tmp;

        b++;
        e--;

        if (b >= e)
            break;
    }
}

template <class DataType>
void rotate(DataType arr[], int n, int k)
{
    convert<DataType>(arr, 0, k - 1);
    convert<DataType>(arr, k, n - 1);
    convert<DataType>(arr, 0, n - 1);
}

void LeftOddRightEven(int arr[], int n)
{
    int begin = 0, end = n - 1;
    while (true)
    {
        while (arr[begin] % 2 != 0)
            begin++;

        while (arr[end] % 2 == 0)
            end--;

        if (begin >= end)
            break;

        int tmp = arr[begin];
        arr[begin] = arr[end];
        arr[end] = tmp;
    }
}

class Point
{
  public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(Point &&p) : x(p.x), y(p.y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    Point &operator=(const Point &p)
    {
        if (this != &p)
        {
            this->x = p.GetX();
            this->y = p.GetY();
        }
        return *this;
    }
    ~Point() {}

    void move(int newx, int newy)
    {
        this->x = newx;
        this->y = newy;
    }
    int GetX() const { return x; }
    int GetY() const { return y; }

    friend ostream &operator<<(ostream &os, const Point &);
    friend istream &operator>>(istream &is, Point &);
    friend Point operator+(const Point &, const Point &);
    friend Point operator*(const Point &, int);
    friend bool operator<(const Point &, const Point &);
    friend bool operator>(const Point &, const Point &);

  private:
    int x, y;
};

ostream &operator<<(ostream &os, const Point &p)
{
    os << "The coordinates of this point is: (" << p.x << ", " << p.y << ")";
    return os;
}

istream &operator>>(istream &is, Point &p)
{
    cout << "please input the x then y: "
         << "\n";
    is >> p.x >> p.y;
    return is;
}

Point operator+(const Point &p1, const Point &p2)
{
    return Point(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

Point operator*(const Point &p, int multiplier)
{
    return Point(p.GetX() * multiplier, p.GetY() * multiplier);
}
bool operator<(const Point &p1, const Point &p2)
{
    return p1.x < p2.x;
}
bool operator>(const Point &p1, const Point &p2)
{
    return p1.x > p2.x;
}
