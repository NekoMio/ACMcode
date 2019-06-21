#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
const long long base = 10000000000000000ll;
struct bignumber
{
    long long a[3];
    bignumber()
    {
        memset(a, 0, sizeof(a));
    }
    bignumber(unsigned long long s)
    {
        *this = s;
    }
    bignumber operator=(const unsigned long long s)
    {
        a[1] = s % base;
        a[2] = s / base;
        return *this;
    }
    bignumber operator+(const bignumber &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] += s.a[1];
        int k = a[1] / base;
        a[1] %= base;
        a[2] += s.a[2] + k;
        return ans;
    }
    bignumber operator+(const long long &s)
    {
        bignumber S = (unsigned long long)s;
        return *this + S;
    }
    bignumber operator+(const int &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] += s;
        int k = a[1] / base;
        a[1] %= base;
        a[2] += k;
        return ans;
    }
    bignumber operator*(const int &s)
    {
        bignumber ans;
        ans = *this;
        ans.a[1] *= s;
        int k = a[1] / base;
        a[1] %= base;
        ans.a[2] *= s;
        ans.a[2] += k;
        return ans;
    }
    bool operator==(const bignumber &s) const
    {
        return a[1] == s.a[1] && a[2] == s.a[2];
    }
    bool operator<(const bignumber &s) const
    {
        return a[2] < s.a[2] ? 1 : a[1] < s.a[1];
    }
    bool operator>(const bignumber &s) const
    {
        return a[2] > s.a[2] ? 1 : a[1] > s.a[1];
    }
    bignumber operator-(const bignumber &s)
    {
        bignumber ans;
        if (*this == s)
            return ans;
        ans = *this;
        if (ans.a[1] < s.a[1])
            ans.a[1] += base, ans.a[2] -= 1;
        ans.a[1] -= s.a[1];
        ans.a[2] -= s.a[2];
        return ans;
    }
    bignumber operator-(const long long &s)
    {
        bignumber S = (unsigned long long)s;
        return *this - S;
    }
} f[19];
void Init()
{
    f[1] = 9;
    f[2] = 180;
    f[3] = 2700;
    f[4] = 36000;
    f[5] = 450000;
    f[6] = 5400000;
    f[7] = 63000000;
    f[8] = 720000000;
    f[9] = 8100000000ull;
    f[10] = 90000000000ull;
    f[11] = 990000000000ull;
    f[12] = 10800000000000ull;
    f[13] = 117000000000000ull;
    f[14] = 1260000000000000ull;
    f[15] = 13500000000000000ull;
    f[16] = 144000000000000000ull;
    f[17] = 1530000000000000000ull;
    f[18] = 16200000000000000000ull;
}
void print(bignumber a)
{
    if (a.a[2] != 0)
    {
        printf("%lld", a.a[2]);
        printf("%016lld", a.a[1]);
    }
    else
    {
        printf("%lld", a.a[1]);
    }
}
int main()
{
    Init();
    //print(f[18]);
    string a, b;
    bignumber ans1, ans2;
    cin >> a >> b;
    int t = 0;
    for (int j = 0, i = a.size(); i >= 2; j++, i--)
    {
        if (a[j] == '0')
            continue;
        ans1 = ans1 + f[i - 1] * (a[j] - '0') + (long long)pow(10, i - 1) * (a[j] - '0' - 1) + (long long)(a[j] - '0') * (long long)pow(10, i - 1) * t;
        t++;
    }
    ans1 = ans1 + (t + 1) * (int)(a[a.size() - 1] - '0');
    if (a[a.size() - 1] != '0')
        ans1 = ans1 - 1;
    t = 0;
    for (int j = 0, i = b.size(); i >= 2; j++, i--)
    {
        if (b[j] == '0')
            continue;
        ans2 = ans2 + f[i - 1] * (b[j] - '0') + (long long)pow(10, i - 1) * (b[j] - '0' - 1) + (long long)(b[j] - '0') * (long long)pow(10, i - 1) * t;
        t++;
    }
    ans2 = ans2 + (t + 1) * (int)(b[b.size() - 1] - '0');
    for (int i = 0; i < b.size() - 1; i++)
        if (b[i] != '0')
            ans2 = ans2 + 1;

    print(ans2 - ans1);
    //while (1)
    ;
}