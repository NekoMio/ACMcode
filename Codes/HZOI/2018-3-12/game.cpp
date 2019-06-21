/* WildRage */
// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 7005;
int b[2][MAXN], k[2], n;
int f[2][MAXN];
int vis[2][MAXN], use[2][MAXN];
int Next(int pos, int a)
{
    int t = pos + a;
    if (t > n) t %= n;
    if (t == 0) t = n;
    // if (t == 1 && a == 2022) printf ("233333\n");
    return t;
}
int T;
int DP(int op, int pos)
{ 
    if (f[op][pos] != -1) return f[op][pos];
    if (pos == 1) return f[op][pos] = 0;
    if (vis[op][pos] == T) return 3;
    vis[op][pos] = T;
    bool flag = 0;
    for (int i = 1; i <= k[op]; i++)
    {
        int tmp = DP(op ^ 1, Next(pos, b[op][i]));
        if (tmp == 0) 
            return vis[op][pos] = 0, use[op][pos] = 1, f[op][pos] = 1;
        if (tmp == 2) use[op][pos] = 1, f[op][pos] = 2;
        if (tmp == 3) flag = 1;
    }
    // vis[op][pos] = 0
    if (!flag)
    {
        if (f[op][pos] == -1) use[op][pos] = 1, f[op][pos] = 0;
        return f[op][pos];
    }
    return 3;
}
int main()
{
    // freopen ("game4.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    n = read();
    k[0] = read(); for (int i = 1; i <= k[0]; i++) b[0][i] = read();
    k[1] = read(); for (int i = 1; i <= k[1]; i++) b[1][i] = read();
    memset (f, -1, sizeof (f));
    for (int i = 2; i <= n; i++)
    {
        T++;
        // memset (f, -1, sizeof (f));
        int tmp = DP(0, i);
        // printf ("%d\n", f[0][4979]);
        if (tmp == 0) printf ("Lose%c", " \n"[i == n]);
        if (tmp == 1) printf ("Win%c", " \n"[i == n]);
        if (tmp == 2) printf ("Loop%c", " \n"[i == n]);
        if (tmp == 3) printf ("Loop%c", " \n"[i == n]);
        if (tmp == 3)
        {
            for (int i = 1; i <= n; i++)
            {
                if (vis[0][i] == T && !use[0][i])
                    use[0][i] = 1, f[0][i] = 2;
                if (vis[1][i] == T && !use[1][i])
                    use[1][i] = 1, f[1][i] = 2;
            }   
        }
    }
    // printf ("\n");
    // memset (f, -1, sizeof (f));
    for (int i = 2; i <= n; i++)
    {
        T++;
        // memset (f, -1, sizeof (f));
        int tmp = DP(1, i);
        if (tmp == 0) printf ("Lose%c", " \n"[i == n]);
        if (tmp == 1) printf ("Win%c", " \n"[i == n]);
        if (tmp == 2) printf ("Loop%c", " \n"[i == n]);
        if (tmp == 3) printf ("Loop%c", " \n"[i == n]);
        if (tmp == 3)
        {
            for (int i = 1; i <= n; i++)
            {
                if (vis[0][i] == T && !use[0][i])
                    use[0][i] = 1, f[0][i] = 2;
                if (vis[1][i] == T && !use[1][i])
                    use[1][i] = 1, f[1][i] = 2;
            }   
        }
    }
    // printf ("\n");
    // while (1);
}