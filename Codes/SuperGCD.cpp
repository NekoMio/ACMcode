#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long base = 1000000000000000000;
struct BigNum
{
    long long a[1505];
    int len;
    BigNum(const char *s = "")
    {
        long long sum = 0, su = 1;
        int n = strlen(s);
        for (int j = n - 1; j >= 0; j--)
        {
            sum += (s[j] - '0') * su;
            su *= 10;
            if (su == base)
            {
                a[++len] = sum;
                sum = 0, su = 1;
            }
        }
        if (sum != 0 || len == 0)
            a[++len] = sum;
    }
    BigNum operator-(const BigNum &b) const
    {
        BigNum ans = *this;
        int m = max(len, b.len);
        for (int i = 1; i <= m; i++)
        {
            if (ans.a[i] < b.a[i])
                ans.a[i + 1] -= 1, ans.a[i] += base;
            ans.a[i] -= b.a[i];
        }
        while (ans.len > 1 && ans.a[ans.len] == 0)
            ans.len--;
        return ans;
    }
    bool operator<(const BigNum &b) const
    {
        if (b.len > len)
            return 1;
        if (len > b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] < b.a[i])
                return 1;
            else if (a[i] > b.a[i])
                return 0;
        return 0;
    }
    bool operator==(const BigNum &b) const
    {
        if (len != b.len)
            return 0;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 0;
        return 1;
    }
    bool operator!=(const BigNum &b) const
    {
        if (len != b.len)
            return 1;
        for (int i = len; i >= 1; i--)
            if (a[i] != b.a[i])
                return 1;
        return 0;
    }
};
int main()
{
    static char s[10010];
    scanf("%s", s);
    static BigNum a(s);
    scanf("%s", s);
    static BigNum b(s);
    while (a != b)
    {
        if (b < a)
            a = a - b;
        else
            b = b - a;
    }
    printf("%lld", a.a[a.len]);
    for (int i = a.len - 1; i >= 1; i--)
        printf("%018lld", a.a[i]);
}