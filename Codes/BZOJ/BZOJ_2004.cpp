#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 30031;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Matrix
{
    int a[150][150];
    int n, m;
    Matrix(int x = 0, int y = 0)
    {
        memset(a, 0, sizeof (a));
        n = x, m = y;
    }
    const int *operator[](const int &b) const
    {
        return a[b];
    }
    int *operator[](const int &b)
    {
        return a[b];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans(n, b.m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == 0) continue;
                for (int k = 1; k <= b.m; k++)
                    ans[i][k] += a[i][j] * b[j][k] % MOD;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= b.m; j++)
                ans[i][j] %= MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans(n, n), a = *this;
        for (int i = 1; i <= n; i++)
            ans[i][i] = 1;
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
};
int mp[(1 << 10) + 1], Id[(1 << 10) + 1];
int n, k, p;
bool OK(int x)
{
    if (!(x & 1)) return 0;
    int t = 0;
    for (int i = 0; i < p; i++)
        if (x & (1 << i))
            t++;
    return t == k;
}
int F[2][(1 << 10) + 1];
int main()
{
    n = read(), k = read(), p = read();
    int N = (1 << p) - 1;
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        if (OK(i))
            mp[++cnt] = i, Id[i] = cnt;
    static Matrix T(cnt, cnt);
    for (int i = 1; i <= cnt; i++)
    {
        int x = mp[i] >> 1;
         for (int j = 0; j < p; j++)
        {
            if ((1 << j) & x) continue;
            if (!Id[x | (1 << j)]) continue;
            T[i][Id[x | (1 << j)]] = 1;
        }
    }
    int s = 0;
    for (int i = 0; i < k; i++) s |= (1 << i);
    static Matrix A(1, cnt);
    A[1][Id[s]] = 1;
    A = A * (T ^ (n - k));
    printf ("%d\n", A[1][Id[s]]);
}