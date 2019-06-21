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
inline void gmin(int &a, int b) { if (a > b) a = b; }
const int MAXN = 100005;
struct data
{
    int v, l;
    data(int _v = 0, int _l = 0) : v(_v), l(_l) {}
    bool operator < (const data &a) const 
    {
        return l < a.l;
    }
}a[MAXN];
int F[105][128];
int Min[MAXN];
int main()
{
    // freopen ("D.3.0.in", "r", stdin);
    // freopen ("D.out", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i].v = read(), a[i].l = read();
    // int q = read();
    if (m <= 100)
    {
        int q = read();
        memset (F, 0x3f, sizeof (F));
        F[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 128; j++)
            {
                for (int k = 1; k <= a[i].l; k++)
                    gmin(F[i][j | k], F[i - 1][j] + a[i].v);
                gmin(F[i][j], F[i - 1][j]);
            }
        while (q--)
        {
            int c = read();
            printf ("%d\n", F[n][c] == 0x3f3f3f3f ? -1 : F[n][c]);
        }
    }
    else
    {
        sort(a + 1, a + n + 1);
        Min[n + 1] = -1;
        Min[n] = a[n].v;
        for (int i = n - 1; i >= 1; i--)
            Min[i] = min(Min[i + 1], a[i].v);
        int q = read();
        while (q--)
        {
            int c = read();
            int t = lower_bound(a + 1, a + n + 1, data(0, c)) - a;
            printf ("%d\n", Min[t]);
            // if (q % 10000 == 0) 
            //     fprintf (stderr, "-------------%d\n", q);
        }
    }
}