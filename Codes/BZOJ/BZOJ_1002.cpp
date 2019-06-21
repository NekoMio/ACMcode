#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 10000;
struct BigNum
{
    int a[50];
    int len;
    BigNum(const char *s = "")
    {
        long long sum = 0, su = 1;
        int n = strlen(s);
        memset (a, 0, sizeof (a));
        len = 0;
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
    BigNum operator * (const int &b) const
    {
        BigNum ans;
        ans.len = len;
        int y = 0;
        for (int i = 1; i <= ans.len; i++)
        {
            ans.a[i] = a[i] * b + y;
            y = ans.a[i] / base;
            ans.a[i] %= base;
        }
        while(y)
		{
			ans.a[++ans.len] = y % base;
			y /= base;
        }
        return ans;
    }
    void print()
    {
        printf ("%d", a[len]);
        for (int i = len - 1; i >= 1; i--)
            printf ("%04d", a[i]);
    }
}f[3];
int main()
{
    f[1] = BigNum("1"), f[2] = BigNum("5");
    int n;
    scanf ("%d", &n);
    for (int i = 3; i <= n; i++)
    {
        f[i % 3] = f[(i - 1 + 3) % 3] * 3 - f[(i - 2 + 3) % 3];
        f[i % 3].a[1] += 2;
    }
    f[n % 3].print();
}