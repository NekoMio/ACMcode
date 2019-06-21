#include <cstdio>
#include <cstring>
#include <algorithm>
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

int Get(int x, int j)
{
    x >>= 2 * (j - 1);
    x &= 3;
    return x;
}

int Change(int x, int j, int t)
{
    int tmp = x >> 2 * (j - 1);
    x -= tmp << (j - 1) * 2;
    tmp >>= 2;
    x += tmp << 2 * j;
    x += t << 2 * (j - 1);
    return x;
}

int n, m;

int Find(int S, int j, int dat)
{
    int now = dat;
    while (j >= 1 && j <= m + 1)
    {
        j += now;
        int t = Get(S, j);
        if (t == 1) dat++;
        else if (t == 2) dat--;
        if (dat == 0)
            return j;
    }
}

int cnt = 0;

int map[15][15];

long long DP()
{
    long long ans = 0;
    f[0][0] = 1;
    int o = 0;
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
                    if (!L && !U) f[o][S] = Num;
                    continue;
                }
                if (!L && !U)
                {
                    if (i != n && j != m)
                    {
                        int t = Change(S, j, 1);
                        f[o][Change(t, j + 1, 2)] += Num;
                    }
                }
                else if (!L && U)
                {
                    if (j != m)
                        f[o][S] += Num;
                    if (i != n)
                    {
                        int t = Change(S, j, U);
                        f[o][Change(t, j + 1, 0)] += Num;
                    }
                }
                else if (L && !U)
                {
                    if (i != n)
                        f[o][S] += Num;
                    if (j != m)
                    {
                        int t = Change(S, j + 1, L);
                        f[o][Change(t, j, 0)] += Num;
                    }
                }
                else if (L == 1 && U == 1)
                {
                    int t = Change(S, Find(S, j + 1, 1), 1);
                    t = Change(t, j, 0);
                    t = Change(t, j + 1, 0);
                    f[o][t] += Num;
                }
                else if (L == 2 && U == 2)
                {
                    // printf ("%d\n", Find(S, j, -1));
                    int t = Change(S, Find(S, j, -1), 2);
                    t = Change(t, j, 0);
                    t = Change(t, j + 1, 0);
                    f[o][t] += Num;
                }
                else if (L == 2 && U == 1)
                {
                    int t = Change(S, j, 0);
                    f[o][Change(t, j + 1, 0)] += Num;
                }
                else if (L == 1 && U == 2)
                {
                    int t = Change(S, j, 0);
                    t = Change(t, j + 1, 0);
                    if ((n - i) * m + m - j == cnt && t == 0) 
                        ans += Num;
                }
            }
            // printf ("%d: ", f[o].p);
            // for (int k = 0; k < f[o].p; k++)
            //     printf ("%d: %d ", f[o].v[k].Id, f[o].v[k].Sum);
            // printf ("\n");
        }
        for (int j = 0; j < f[o].p; j++)
            f[o].v[j].Id <<= 2;
    }
    return ans;
}


char c[20];

int main()
{
    // freopen ("formula1.in", "r", stdin);
    // freopen ("formula1.out", "w", stdout);
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", c + 1);
        for (int j = 1; j <= m; j++)
        {
            cnt += map[i][j] = c[j] == '*';
        }
    }
    printf ("%lld\n", DP());
    // while (1);
}