#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void gmin(int &a, int b)
{
    if (b < a) a = b;
}
struct Matrix
{
    int a[305][305];
    int n;
    Matrix(int x = 0)
    {
        memset (a, 0x3f, sizeof (a));
        n = x;
    }
    void mul(Matrix &ans, const Matrix &b)
    {
        memset (ans.a, 0x3f, sizeof (ans.a));
        ans.n = n;
        register int i, j, k;
        for (i = 1; i <= n; ++i)
        {
            for (k = 1; k <= n; k++)
            {
                if (a[i][k] == 0x3f3f3f3f) continue;
                for (j = 1; j <= n; ++j)
                    gmin(ans.a[i][j], a[i][k] + b.a[k][j]);
            }
        }
    }
}A[10], B;
int n, m;
bool Judge(const Matrix &c)
{
    register int i;
    for (i = 1; i <= n; ++i) if (c.a[i][i] < 0) return 1;
    return 0;
}
int main()
{
    register int i;
    n = read(), m = read();
    static Matrix C(n);
    for (i = 1; i <= n; ++i) A[0].a[i][i] = C.a[i][i] = 0;
    A[0].n = n;
    for (i = 1; i <= m; ++i)
    {
        int a = read(), b = read(), c = read();
        A[0].a[a][b] = c;
    }
    for (i = 1; i <= 8; ++i)
        A[i - 1].mul(A[i], A[i - 1]);
    int ans = 0;
    for (i = 8; i >= 0; i--)
    {
        C.mul(B, A[i]);
        if (!Judge(B))
        {
            ans |= (1 << i);
            C = B;
        }
    }
    if (ans + 1 == 512) printf ("0\n");
    else printf ("%d\n", ans + 1);
    // while (1);
}