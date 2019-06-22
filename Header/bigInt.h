#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
using namespace std;

const int IntSize = 1000;

class BigInt
{
  public:
    BigInt();
    BigInt(int[], int, int);
    BigInt(int);
    // BigInt(const char *);
    BigInt(BigInt &&) = default;
    BigInt(const BigInt &) = default;
    BigInt &operator=(BigInt &&) = default;
    BigInt &operator=(const BigInt &) = default;
    BigInt &operator=(int);
    // BigInt &operator=(const char *);

    ~BigInt() {}

    friend bool operator==(const BigInt &lbi, const BigInt &rbi);
    friend bool operator<(const BigInt &lbi, const BigInt &rbi);
    friend bool operator>(const BigInt &lbi, const BigInt &rbi);
    friend bool operator!=(const BigInt &lbi, const BigInt &rbi);
    friend bool operator<=(const BigInt &lbi, const BigInt &rbi);
    friend bool operator>=(const BigInt &lbi, const BigInt &rbi);

    friend bool operator&&(const BigInt &lbi, const BigInt &rbi);
    friend bool operator||(const BigInt &lbi, const BigInt &rbi);
    bool operator!() const;

    BigInt abs() const;
    BigInt &operator++();
    BigInt &operator--();
    BigInt operator++(int);
    BigInt operator--(int);
    BigInt operator-() const;
    friend BigInt operator+(const BigInt &lbi, const BigInt &rbi);
    friend BigInt operator-(const BigInt &lbi, const BigInt &rbi);
    friend BigInt operator*(const BigInt &lbi, const BigInt &rbi);
    friend BigInt operator/(const BigInt &lbi, const BigInt &rbi);
    friend BigInt operator%(const BigInt &lbi, const BigInt &rbi);

    friend ostream &operator<<(ostream &os, const BigInt &);
    // friend istream &operator>>(istream &is, const BigInt &);

  private:
    inline void AbsPlus(const BigInt &bi, int plusNum[], int &length);
    inline void AbsMinus(const BigInt &bi, int minusNum[], int &length);
    int number[IntSize];
    int len, sign;
};

#endif // !BIGINT_H
