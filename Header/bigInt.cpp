#include "bigInt.h"
using namespace std;

BigInt::BigInt()
{
    this->len = 1;
    this->number[0] = 0;
    this->sign = 1;
}

BigInt::BigInt(int n)
{
    int num = n;
    int i = 0;
    do
    {
        this->number[i++] = num % 10;
        num /= 10;
    } while (num % 10 != 0);
    this->len = i;
    this->sign = n >= 0 ? 1 : 0;
}

BigInt::BigInt(int arr[], int n, int sign = 1)
{
    this->len = n;
    this->sign = sign;
    for (int i = 0; i != n; i++)
        number[i] = arr[i];
}

BigInt &BigInt::operator=(int n)
{
    int num = n;
    int i = 0;
    do
    {
        this->number[i++] = num % 10;
        num /= 10;
    } while (num % 10 != 0);
    this->len = i;
    this->sign = n >= 0 ? 1 : 0;

    return *this;
}

bool operator==(const BigInt &lbi, const BigInt &rbi)
{
    if (lbi.len != rbi.len || lbi.sign != rbi.sign)
    {
        return false;
    }
    else
    {
        int length = lbi.len;
        for (int i = 0; i != length; i++)
        {
            if (lbi.number[i] != rbi.number[i])
                return false;
        }

        return true;
    }
}
bool operator<(const BigInt &lbi, const BigInt &rbi)
{
    if (lbi.sign != rbi.sign)
    {
        return lbi.sign == 1 ? false : true;
    }
    else
    {
        bool isAbsLess = false;
        if (lbi.len != rbi.len)
        {
            isAbsLess = lbi.len < rbi.len ? true : false;
        }
        else
        {
            for (int i = (lbi.len) - 1; i != -1; i--)
            {
                if (rbi.number[i] != lbi.number[i])
                {
                    if (lbi.number[i] < rbi.number[i])
                        isAbsLess = true;
                    else if (lbi.number[i] > rbi.number[i])
                        isAbsLess = false;
                    break;
                }
            }
        }

        return lbi.sign == 1 ? isAbsLess : !isAbsLess;
    }
}
bool operator<=(const BigInt &lbi, const BigInt &rbi)
{
    return lbi == rbi || lbi < rbi;
}
bool operator!=(const BigInt &lbi, const BigInt &rbi)
{
    return !(lbi == rbi);
}
bool operator>(const BigInt &lbi, const BigInt &rbi)
{
    return !(lbi <= rbi);
}
bool operator>=(const BigInt &lbi, const BigInt &rbi)
{
    return !(lbi < rbi);
}

bool operator&&(const BigInt &lbi, const BigInt &rbi)
{
    return !(lbi.len == 1 && lbi.number[0] == 0) && !(rbi.len == 1 && rbi.number[0] == 0);
}
bool operator||(const BigInt &lbi, const BigInt &rbi)
{
    return !(lbi.len == 1 && lbi.number[0] == 0) || !(rbi.len == 1 && rbi.number[0] == 0);
}

bool BigInt::operator!() const
{
    return this->len == 1 && this->number[0] == 0;
}

BigInt BigInt::abs() const
{
    BigInt absi(*this);
    absi.sign = 1;
    return absi;
}

inline void BigInt::AbsPlus(const BigInt &bi, int plusNum[], int &length)
{
    int l = this->len > bi.len ? this->len : bi.len;
    int s = this->len <= bi.len ? this->len : bi.len;
    // int plusNum[IntSize];
    for (int i = 0; i != l; i++)
    {
        if (i < s)
            plusNum[i] += this->number[i] + bi.number[i];

        if (plusNum[i] >= 10)
        {
            plusNum[i + 1] = plusNum[i] / 10;
            plusNum[i] %= 10;
        }
    }

    length = plusNum[l] == 0 ? l : (l + 1);
}

inline void BigInt::AbsMinus(const BigInt &bi, int minusNum[], int &length)
{
    int right;
    for (int i = 0; i != this->len; i++)
    {
        right = i < bi.len ? bi.number[i] : 0;
        if (this->number[i] >= right)
        {
            minusNum[i] = this->number[i] - right;
        }
        else
        {
            minusNum[i] = this->number[i] - right + 10;
            minusNum[i + 1]--;
        }
    }

    for (int i = this->len - 1; i != -1; i--)
    {
        if (minusNum[i] > 0)
        {
            length = i + 1;
            break;
        }
    }
}

BigInt BigInt::operator-() const
{
    BigInt minus(*this);
    minus.sign = this->sign == 1 ? -1 : 1;
    return minus;
}

BigInt &BigInt::operator++()
{
    int i = 0;
    this->number[i]++;
    while (this->number[i] >= 10 && i != this->len)
    {
        this->number[i] %= 10;
        this->number[i + 1]++;
        i++;
    }
    if (this->number[this->len] != 0)
        this->len++;

    return *this;
}
BigInt BigInt::operator++(int)
{
    BigInt ret = *this;
    int i = 0;
    this->number[i]++;
    while (this->number[i] >= 10 && i != this->len)
    {
        this->number[i] %= 10;
        this->number[i + 1]++;
        i++;
    }
    if (this->number[this->len] != 0)
        this->len++;

    return ret;
}

BigInt &BigInt::operator--()
{
    int i = 0;
    this->number[i]--;
    while (this->number[i] < 0 && i != this->len)
    {
        this->number[i] += 10;
        this->number[i + 1]--;
        i++;
    }
    if (this->number[this->len - 1] == 0)
        this->len--;

    return *this;
}
BigInt BigInt::operator--(int)
{
    BigInt ret = *this;
    int i = 0;
    this->number[i]--;
    while (this->number[i] < 0 && i != this->len)
    {
        this->number[i] += 10;
        this->number[i + 1]--;
        i++;
    }
    if (this->number[this->len - 1] == 0)
        this->len--;

    return ret;
}

BigInt operator+(const BigInt &lbi, const BigInt &rbi)
{
    BigInt plus;
    if (lbi.sign == rbi.sign)
    {
        lbi.abs().AbsPlus(rbi.abs(), plus.number, plus.len);
        plus.sign = lbi.sign == 1 ? 1 : -1;
    }
    else
    {
        if (lbi.abs() <= rbi.abs())
        {
            rbi.abs().AbsMinus(lbi.abs(), plus.number, plus.len);
            plus.sign = lbi.sign == 1 ? -1 : 1;
        }
        else
        {
            lbi.abs().AbsMinus(rbi.abs(), plus.number, plus.len);
            plus.sign = lbi.sign == 1 ? 1 : -1;
        }
    }

    return plus;
}
BigInt operator-(const BigInt &lbi, const BigInt &rbi)
{
    BigInt revRbi(rbi);
    revRbi.sign = rbi.sign == 1 ? -1 : 1;
    return lbi + revRbi;
}
BigInt operator*(const BigInt &lbi, const BigInt &rbi)
{
    BigInt multiply;
    multiply.len = lbi.len + rbi.len;
    multiply.sign = lbi.sign * rbi.sign;
    for (int i = 0; i != multiply.len; i++)
        multiply.number[i] = 0;
    for (int i = 0; i != multiply.len - 1; i++)
    {
        for (int j = 0; j != i + 1; j++)
        {
            if (i - j < rbi.len && j < lbi.len)
                multiply.number[i] += lbi.number[j] * rbi.number[i - j];
        }
        if (multiply.number[i] >= 10)
        {
            multiply.number[i + 1] += multiply.number[i] / 10;
            multiply.number[i] %= 10;
        }
    }
    if (multiply.number[multiply.len - 1] == 0)
        multiply.len--;
    return multiply;
}

BigInt operator/(const BigInt &lbi, const BigInt &rbi)
{
    BigInt divide;
    int divideNum[IntSize];
    for (int i = 0; i != lbi.len; i++)
        divideNum[i] = lbi.number[i];

    if (lbi.abs() < rbi.abs())
    {
        return divide;
    }
    else
    {
        divide.len = lbi.len - rbi.len + 1;
        divide.sign = lbi.sign * rbi.sign;
        int start = lbi.len - 1;

        for (int i = 0; i != divide.len; i++)
        {
            int j = 0, end = lbi.len - rbi.len - i;
            bool isLess;
            do
            {
                isLess = false;
                while (divideNum[start] == 0)
                    start--;
                if (start - end + 1 != rbi.len)
                {
                    isLess = start - end >= rbi.len ? false : true;
                }
                else
                {
                    for (int k = start; k != end - 1; k--)
                    {
                        if (divideNum[k] != rbi.number[k - start + rbi.len - 1])
                        {
                            if (divideNum[k] < rbi.number[k - divide.len + 1])
                                isLess = true;
                            break;
                        }
                    }
                }
                if (!isLess)
                {
                    for (int k = end; k != start + 1; k++) // k != end + rbi.len
                    {
                        int right = k - end >= rbi.len ? 0 : rbi.number[k - end];
                        int extra = divideNum[k] >= right ? 0 : 1;
                        divideNum[k] = divideNum[k] - right + extra * 10;
                        if (extra)
                            divideNum[k + 1]--;
                    }
                    j++;
                }

            } while (!isLess);
            divide.number[divide.len - 1 - i] = j;
        }
    }

    while (divide.number[divide.len - 1] == 0)
        divide.len--;

    return divide;
}

BigInt operator%(const BigInt &lbi, const BigInt &rbi)
{
    BigInt mod;
    int modNum[IntSize];
    for (int i = 0; i != lbi.len; i++)
        modNum[i] = lbi.number[i];

    if (lbi.abs() < rbi.abs())
    {
        mod = BigInt(lbi);
        mod.sign = lbi.sign * rbi.sign;
        return mod;
    }
    else
    {
        mod.len = lbi.len - rbi.len + 1;
        mod.sign = lbi.sign * rbi.sign;
        int start = lbi.len - 1;

        for (int i = 0; i != mod.len; i++)
        {
            int j = 0, end = lbi.len - rbi.len - i;
            bool isLess;
            do
            {
                isLess = false;
                while (modNum[start] == 0)
                    start--;
                if (start - end + 1 != rbi.len)
                {
                    isLess = start - end >= rbi.len ? false : true;
                }
                else
                {
                    for (int k = start; k != end - 1; k--)
                    {
                        if (modNum[k] != rbi.number[k - start + rbi.len - 1])
                        {
                            if (modNum[k] < rbi.number[k - mod.len + 1])
                                isLess = true;
                            break;
                        }
                    }
                }
                if (!isLess)
                {
                    for (int k = end; k != start + 1; k++) // k != end + rbi.len
                    {
                        int right = k - end >= rbi.len ? 0 : rbi.number[k - end];
                        int extra = modNum[k] >= right ? 0 : 1;
                        modNum[k] = modNum[k] - right + extra * 10;
                        if (extra)
                            modNum[k + 1]--;
                    }
                    j++;
                }

            } while (!isLess);
        }
    }

    while (modNum[mod.len - 1] == 0)
        mod.len--;
    for (int i = 0; i != mod.len; i++)
        mod.number[i] = modNum[i];

    return mod;
}

ostream &operator<<(ostream &os, const BigInt &bi)
{
    if (bi.sign != 1)
        cout << "-";
    for (int i = bi.len - 1; i != -1; i--)
        cout << bi.number[i];
    return os;
}

    // istream &operator>>(istream &is, const BigInt &bi);