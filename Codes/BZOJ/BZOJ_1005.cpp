#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int BASE = 10000;
const int MAXN = 1005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct BigNum
{
    int a[5005];
    int len;
    BigNum()
    {
        memset (a, 0, sizeof (a));
        len = 0;
    }
    BigNum(int x)
    {
        memset (a, 0, sizeof (a));
        a[1] = x;
        len = 1;
    }
    BigNum operator * (const int &b) const 
    {
        BigNum ans;
        ans.len = len;
        int y = 0;
        for (int i = 1; i <= len; i++)
        {
            ans.a[i] = a[i] * b + y;
            y = ans.a[i] / BASE;
            ans.a[i] %= BASE;
        }
        while (y)
        {
            ans.a[++ans.len] = y % BASE;
            y /= BASE;
        }
        return ans;
    }
    BigNum operator / (const int &b) const 
    {
        BigNum ans;
        ans.len = len;
        int y = 0;
        for (int i = len; i; i--)
        {
            ans.a[i] = (y + a[i]) / b;
            y = (y + a[i]) % b * BASE;
        }
        while (!ans.a[ans.len] && ans.len > 1)
            ans.len--;
        return ans;
    }
    void print()
    {
        printf("%d", a[len]);
        for (int i = len - 1; i >= 1; i--)
            printf ("%04d", a[i]);
    }
};
int D[MAXN];
int main()
{
    int n = read();
    int Sum = 0, Sum2 = 0;
    bool flag = 0;
    for (int i = 1; i <= n; i++)
    {
        D[i] = read();
        if (D[i] != -1) Sum += D[i], Sum2 += D[i] - 1;
        else flag = 1;
        if (D[i] == 0 && n > 1) return printf ("0\n"), 0;
    }
    if (!flag && Sum != 2 * n - 2) return printf ("0\n"), 0;
    static BigNum ans(1);
    for (int i = n - Sum2 - 1; i <= n - 2; i++) 
        ans = ans * i;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (D[i] != -1)
        {
            for (int j = 2; j <= D[i] - 1; j++)
                ans = ans / j;
            cnt++;
        }   
    }
    for (int i = 1; i <= n - Sum2 - 2; i++)
        ans = ans * (n - cnt);
    ans.print();
    // while (1);
}