#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 200000, BASE = 76543;
struct Hash_Table
{
    struct edge
    {
        int Id, next;
        long long Sum;
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
    long long &operator[](int a)
    {
        int H = a % BASE;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].Id == a)
                return v[i].Sum;
        v[p].Id = a;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].Sum = 0;
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
int map[15][15];

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

int cnt;

long long DP()
{
    f[0][0] = 1;
    int o = 0;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            o ^= 1;
            f[o].clear();
            bool flag = 0;
            for (int k = 0; k < f[o ^ 1].p; k++)
            {
                int S = f[o ^ 1].v[k].Id;
                long long Num = f[o ^ 1].v[k].Sum;
                int L = Get(S, j), U = Get(S, j + 1);
                if (!map[i][j])
                {
                    if (!L && !U)
                    {
                        if (i != n && j != m)
                        {
                            int t = Change(S, j, 1);
                            f[o][Change(t, j + 1, 2)] += Num;
                        }
                    }
                    else if (L && !U)
                    {
                        if (i != n)
                            f[o][S] += Num;
                        if (j != m)
                        {
                            int t = Change(S, j, 0);
                            f[o][Change(t, j + 1, L)] += Num;
                        }
                    }
                    else if (!L && U)
                    {
                        if (j != m)
                            f[o][S] += Num;
                        if (i != n)
                        {
                            int t = Change(S, j + 1, 0);
                            f[o][Change(t, j, U)] += Num;
                        }
                    }
                    else if (L == 1 && U == 1)
                    {
                        int t = Change(S, Find(S, j + 1, 1), 1);
                        t = Change(t, j + 1, 0);
                        f[o][Change(t, j, 0)] += Num;
                    }
                    else if (L == 2 && U == 2)
                    {
                        int t = Change(S, Find(S, j, -1), 2);
                        t = Change(t, j + 1, 0);
                        f[o][Change(t, j, 0)] += Num;
                    }
                    else if (L == 2 && U == 1)
                    {
                        int t = Change(S, j + 1, 0);
                        f[o][Change(t, j, 0)] += Num;
                    }
                    else if (L == 1 && U == 2)
                    {
                        int t = Change(S, j + 1, 0);
                        t = Change(t, j, 0);
                        if (cnt == (n - i) * m + m - j && !t)
                            ans += Num;
                    }
                }
                else if (map[i][j] == 1)
                {
                    if (L && !U)
                    {
                        if (j != m)
                        {
                            int t = Change(S, j + 1, L);
                            f[o][Change(t, j, 0)] += Num;
                        }
                    }
                }
                else if (map[i][j] == 2)
                {
                    if (!L && U)
                    {
                        if (i != n)
                        {
                            int t = Change(S, j + 1, 0);
                            f[o][Change(t, j, U)] += Num;
                        }
                    }
                }
                else if (map[i][j] == 3)
                {
                    if (!flag) cnt--, flag = 1;
                    if (!L && !U) f[o][S] += Num;
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
    scanf ("%d%d", &n, &m);
    char c[15];
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", c + 1);
        for (int j = 1; j <= m; j++)
        {
            if (c[j] == '-') map[i][j] = 1;
            else if (c[j] == '|') map[i][j] = 2;
            else if (c[j] == '#') map[i][j] = 3, cnt++;
        }
    }
    printf ("%lld\n", DP());
    // while (1);
}