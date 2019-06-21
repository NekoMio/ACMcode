#include <cstdio>
#include <stdint.h>
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
const int MAXN = 200000, BASE = 76543;
const int32_t MOD = 1e9 + 7;
struct Hash_Table
{
    struct edge
    {
        int Id, next;
        int Sum;
    }v[MAXN];
    int first[BASE + 2], p;
    Hash_Table()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
    void clear()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
    int &operator[](int a)
    {
        int H = a % BASE;
        for (int i = first[H]; i != -1; i = v[i].next)
        {
            if (v[i].Id == a)
                return v[i].Sum;
        }
        v[p].Id = a;
        v[p].next = first[H];
        first[H] = p++;
        return v[first[H]].Sum = 0;
    }
}f[2];
int a[20][20], ans[20][20];
int DP(char n, char m)
{
    f[0].clear();
    f[0][0] = 1;
    int now = 0;
    // int Ans = 0;
    register int32_t k = 0, i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            now ^= 1;
            f[now].clear();
            for (k = 0; k < f[now ^ 1].p; k++)
            {
                int S = f[now ^ 1].v[k].Id;
                int Sum = f[now ^ 1].v[k].Sum;
                char L = (S >> (j - 1)) & 1, U = (S >> j) & 1;
                if (a[i][j])
                {
                    if (L == 0 && U == 0)
                        f[now][S] = (f[now][S] + Sum) % MOD;
                    continue;
                }
                else if (L == 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    f[now][nxt] = (f[now][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U == 1)
                {
                    int nxt = S ^ (1 << j);
                    f[now][nxt] = (f[now][nxt] + Sum) % MOD;
                }
                else if (L != 1 && U != 1)
                {
                    int nxt = S ^ (1 << (j - 1));
                    if (i != n)
                        f[now][nxt] = (f[now][nxt] + Sum) % MOD;
                    nxt = S ^ (1 << j);
                    if (j != m) 
                        f[now][nxt] = (f[now][nxt] + Sum) % MOD;
                    f[now][S] = (f[now][S] + Sum) % MOD;
                }
                // if (S == 0)
                //     Ans += Sum;
            }
            for (k = 0; k < f[now].p; k++)
                printf ("%d %d\n", f[now].v[k].Id, f[now].v[k].Sum);
        }
        for (k = 0; k < f[now].p; k++)
            f[now].v[k].Id <<= 1;
    }
    return f[now][0];
}
int main()
{

    char n = read(), m = read();
    register int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            a[i][j] = read();
    DP(n, m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (a[i][j] == 0)
            {
                a[i][j] = 1;
                ans[i][j] = DP(n, m);
                a[i][j] = 0;
            }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            printf ("%d%c", ans[i][j], " \n"[j == m]);
    // while (1);
}
