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
const int MAXN = 200000, BASE = 76543, INF = 0x7fffffff;
struct Hash_Table
{
    struct edge
    {
        int Id, next;
        long long Max;
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
    long long &operator[](int x)
    {
        int H = x % BASE;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].Id == x)
                return v[i].Max;
        v[p].Id = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].Max = -INF;
    }
}f[2];

int Get(int S, int x)
{
    S >>= 2 * (x - 1);
    return S & 3;
}

int Change(int S, int x, int t)
{
    int tmp = S >> 2 * (x - 1);
    S -= tmp << 2 * (x - 1);
    tmp >>= 2;
    S += tmp << 2 * x;
    S += t << 2 * (x - 1);
    return S;
}

int n, m;
int map[1000][10];

int Find(int S, int x, int dat)
{
    int now = dat;
    while (x >= 1 && x <= m + 1)
    {
        x += now;
        int t = Get(S, x);
        if (t == 1) dat++;
        else if (t == 2) dat--;
        if (dat == 0) return x;
    }
}

long long DP()
{
    f[0][0] = 0;
    int o = 0;
    long long ans = -INF;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            o ^= 1;
            f[o].clear();
            for (int k = 0; k < f[o ^ 1].p; k++)
            {
                int S = f[o ^ 1].v[k].Id;
                long long Max = f[o ^ 1].v[k].Max;
                int L = Get(S, j), U = Get(S, j + 1);
                if (!L && !U)
                {
                    f[o][S] = max(f[o][S], Max);
                    if (i != n && j != m)
                    {
                        int t = Change(S, j, 1);
                        t = Change(t, j + 1, 2);
                        f[o][t] = max(f[o][t], Max + map[i][j]);
                    }
                }
                else if (L && !U)
                {
                    if (i != n)
                        f[o][S] = max(f[o][S], Max + map[i][j]);
                    if (j != m)
                    {
                        int t = Change(S, j, 0);
                        t = Change(t, j + 1, L);
                        f[o][t] = max(f[o][t], Max + map[i][j]);
                    }
                }
                else if (!L && U)
                {
                    if (j != m)
                        f[o][S] = max(f[o][S], Max + map[i][j]);
                    if (i != n)
                    {
                        int t = Change(S, j, U);
                        t = Change(t, j + 1, 0);
                        f[o][t] = max(f[o][t], Max + map[i][j]);
                    }
                }
                else if (L == 1 && U == 1)
                {
                    int t = Change(S, Find(S, j + 1, 1), 1);
                    t = Change(t, j + 1, 0);
                    t = Change(t, j, 0);
                    f[o][t] = max(f[o][t], Max + map[i][j]);
                }
                else if (L == 2 && U == 2)
                {
                    int t = Change(S, Find(S, j, -1), 2);
                    t = Change(t, j + 1, 0);
                    t = Change(t, j, 0);
                    f[o][t] = max(f[o][t], Max + map[i][j]);
                }
                else if (L == 2 && U == 1)
                {
                    int t = Change(S, j + 1, 0);
                    t = Change(t, j, 0);
                    f[o][t] = max(f[o][t], Max + map[i][j]);
                }
                else if (L == 1 && U == 2)
                {
                    int t = Change(S, j, 0);
                    t = Change(t, j + 1, 0);
                    if (!t)
                        ans = max(ans, Max + map[i][j]);
                }
            }
        }
        for (int k = 0; k < f[o].p; k++)
            f[o].v[k].Id <<= 2;
    }
    return ans;
}


int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            map[i][j] = read();
    printf ("%lld", DP());
}