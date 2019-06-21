#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 20110520;
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
    long long &operator[](int x)
    {
        int H = x % BASE;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].Id == x)
                return v[i].Sum;
        v[p].Id = x;
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


int map[105][105];
int n, m, cnt;

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
                if (map[i][j])
                {
                    if (!flag) cnt--, flag = 1;
                    if (!L && !U)
                        f[o][S] = (f[o][S] + Num) % MOD;
                    continue;
                }
                if (!L && !U)
                {
                    if (i != n)
                    {
                        int t = Change(S, j, 1);
                        f[o][t] = (f[o][t] + Num) % MOD;
                    }
                    if (j != m)
                    {
                        int t = Change(S, j + 1, 1);
                        f[o][t] = (f[o][t] + Num) % MOD;
                    }
                    if (i != n && j != m)
                    {
                        int t = Change(S, j, 2);
                        t = Change(t, j + 1, 2);
                        f[o][t] = (f[o][t] + Num) % MOD;
                    }
                }
                else if (!L && U)
                {
                    if (U == 1)
                    {
                        if (i != n)
                        {
                            int t = Change(S, j, U);
                            t = Change(t, j + 1, 0);
                            f[o][t] = (f[o][t] + Num) % MOD; 
                        }
                        if (j != m)
                        {
                            int t = Change(S, j + 1, 2);
                            f[o][t] = (f[o][t] + Num) % MOD;
                        }
                    }
                    if (U == 2)
                    {
                        if (i != n)
                        {
                            int t = Change(S, j, U);
                            t = Change(t, j + 1, 0);
                            f[o][t] = (f[o][t] + Num) % MOD; 
                        }
                        int t = Change(S, j + 1, 0);
                        if (!t && (n - i) * m + m - j == cnt)
                            ans = (ans + Num) % MOD;
                        f[o][t] = (f[o][t] + Num) % MOD;
                    }
                }
                else if (L && !U)
                {
                    if (L == 1)
                    {
                        if (i != n)
                        {
                            int t = Change(S, j, 2);
                            f[o][t] = (f[o][t] + Num) % MOD;
                        }
                        if (j != m)
                        {
                            int t = Change(S, j + 1, L);
                            t = Change(t, j, 0);
                            f[o][t] = (f[o][t] + Num) % MOD;
                        }
                    }
                    else if (L == 2)
                    {
                        if (j != m)
                        {
                            int t = Change(S, j + 1, L);
                            t = Change(t, j, 0);
                            f[o][t] = (f[o][t] + Num) % MOD;
                        }
                        int t = Change(S, j, 0);
                        if (!t && (n - i) * m + m - j == cnt) 
                            ans = (ans + Num) % MOD;
                        f[o][t] = (f[o][t] + Num) % MOD;
                    }
                }
                else if (L == 1 && U == 1)
                {
                    int t = Change(S, j + 1, 0);
                    t = Change(t, j, 0);
                    f[o][t] = (f[o][t] + Num) % MOD;
                    if (!t && (n - i) * m + m - j == cnt)
                        ans = (ans + Num) % MOD;
                }
            }
            // printf ("%d: ", f[o].p);
            // for (int k = 0; k < f[o].p; k++)
            //     printf ("%d ", f[o].v[k].Id);
            // printf ("\n");
        }
        for (int k = 0; k < f[o].p; k++)
            f[o].v[k].Id <<= 2;
    }
    return ans;
}

int main()
{
    scanf ("%d%d", &n, &m);
    char c[105];
    if (n < m)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf ("%s", c + 1);
            for (int j = 1; j <= m; j++)
                cnt += map[j][i] = c[j] == '*';
        }
        swap(n, m);
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            scanf ("%s", c + 1);
            for (int j = 1; j <= m; j++)
                cnt += map[i][j] = c[j] == '*';
        }
    }
    printf ("%lld", DP());
    // while (1);
}