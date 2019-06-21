#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int base = 10000;
struct BigNum
{
    int a[30];
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
    BigNum operator / (const int &b) const 
	{
		BigNum ans;
		ans.len = len;
		int y = 0;
		for (int i = len; i >= 1; i--)
		{
			ans.a[i] = (y + a[i]) / b;
			y = (y + a[i]) % b * base;
		}
		while(!ans.a[ans.len] && ans.len > 1)
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
    bool Judge()
    {
        return a[1] & 1;
    }
    void print()
    {
        printf ("%d", a[len]);
        for (int i = len - 1; i >= 1; i--)
            printf ("%04d", a[i]);
    }
}A, B;
int cnt;
bool Do(BigNum &a, BigNum &b)
{
    if (!a.Judge() && !b.Judge()) {a = a / 2; b = b / 2; cnt++; return 1;}
    if (!a.Judge()) {a = a / 2; return 1;}
    if (!b.Judge()) {b = b / 2; return 1;}
    return 0;
}
char s[105];
int main()
{
    freopen("king.in", "r", stdin);
    freopen("king.out", "w", stdout);
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        cnt = 0;
        scanf ("%s", s);
        A = BigNum(s);
        scanf ("%s", s);
        B = BigNum(s);
        while (A != B)
        {
            while (Do(A, B));
            if (A == B) break;
            if (A < B) swap(A, B);
            A = A - B;
        }
        int tmp1 = cnt / 10, tmp2 = cnt % 10, p = 1 << 10;
        while (tmp1--) A = A * p;
        while (tmp2--) A = A * 2;
        if (A.len == 1 && A.a[1] == 1) printf ("Yes\n");
        else printf ("No\n");
    }
}