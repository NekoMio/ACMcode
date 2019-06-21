#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
const int INF = 0x7fffffff;
int a[MAXN], in[MAXN], l[MAXN], r[MAXN];
int Min[1000], Change[MAXN];
int Block_Change[1000], Block_Add[1000];
queue<int> Q[1000];
void Add(int L, int R, int x)
{
    if (in[L] == in[R])
    {
        for (int i = l[in[L]]; i <= r[in[R]]; i++)
            a[i] += Block_Add[in[L]];
        Block_Add[in[L]] = 0;
        while (!Q[in[L]].empty())
        {
            int k = Q[in[L]].front();
            Q[in[L]].pop();
            for (int i = l[in[L]]; i <= r[in[R]]; i++)
                if (k > a[i])
                    a[i] = k, Change[i]++;
        }
        for (int i = L; i <= R; i++)
            a[i] += x, Change[i]++;
        Min[in[L]] = INF;
        for (int i = l[in[L]]; i <= r[in[L]]; i++)
            Min[in[L]] = min(Min[in[L]], a[i]);
        return;
    }
    for (int i = l[in[L]]; i <= r[in[L]]; i++)
        a[i] += Block_Add[in[L]];
    Block_Add[in[L]] = 0;
    while (!Q[in[L]].empty())
    {
        int k = Q[in[L]].front();
        Q[in[L]].pop();
        for (int i = l[in[L]]; i <= r[in[L]]; i++)
            if (k > a[i])
                a[i] = k, Change[i]++;
    }
    for (int i = L; i <= r[in[L]]; i++)
        a[i] += x, Change[i]++;
    Min[in[L]] = INF;
    for (int i = l[in[L]]; i <= r[in[L]]; i++)
        Min[in[L]] = min(Min[in[L]], a[i]);
    for (int i = l[in[R]]; i <= r[in[R]]; i++)
        a[i] += Block_Add[in[R]];
    Block_Add[in[R]] = 0;
    while (!Q[in[R]].empty())
    {
        int k = Q[in[R]].front();
        Q[in[R]].pop();
        for (int i = l[in[R]]; i <= r[in[R]]; i++)
            if (k > a[i])
                a[i] = k, Change[i]++;
    }
    for (int i = l[in[R]]; i <= R; i++)
        a[i] += x, Change[i]++;
    Min[in[R]] = INF;
    for (int i = l[in[R]]; i <= r[in[R]]; i++)
        Min[in[R]] = min(Min[in[R]], a[i]);
    for (int i = in[L] + 1; i < in[R]; i++)
    {
        int t = Q[i].size();
        for (int j = 1; j <= t; j++)
        {
            int k = Q[i].front() + x;
            Q[i].pop();
            Q[i].push(k);
        }
        Block_Change[i]++;
        Block_Add[i] += x;
        Min[i] += x;
    }
}
void Max(int L, int R, int x)
{
    if (in[L] == in[R])
    {
        for (int i = l[in[L]]; i <= r[in[R]]; i++)
            a[i] += Block_Add[in[L]];
        Block_Add[in[L]] = 0;
        while (!Q[in[L]].empty())
        {
            int k = Q[in[L]].front();
            Q[in[L]].pop();
            for (int i = l[in[L]]; i <= r[in[R]]; i++)
                if (k > a[i])
                    a[i] = k, Change[i]++;
        }
        for (int i = L; i <= R; i++)
            if (x > a[i])
                a[i] = x, Change[i]++;
        Min[in[L]] = INF;
        for (int i = l[in[L]]; i <= r[in[L]]; i++)
            Min[in[L]] = min(Min[in[L]], a[i]);
        return;
    }
    for (int i = l[in[L]]; i <= r[in[L]]; i++)
        a[i] += Block_Add[in[L]];
    Block_Add[in[L]] = 0;
    while (!Q[in[L]].empty())
    {
        int k = Q[in[L]].front();
        Q[in[L]].pop();
        for (int i = l[in[L]]; i <= r[in[L]]; i++)
            if (k > a[i])
                a[i] = k, Change[i]++;
    }
    for (int i = L; i <= r[in[L]]; i++)
        if (x > a[i])
            a[i] = x, Change[i]++;
    Min[in[L]] = INF;
    for (int i = l[in[L]]; i <= r[in[L]]; i++)
        Min[in[L]] = min(Min[in[L]], a[i]);
    for (int i = l[in[R]]; i <= r[in[R]]; i++)
        a[i] += Block_Add[in[R]];
    Block_Add[in[R]] = 0;
    while (!Q[in[R]].empty())
    {
        int k = Q[in[R]].front();
        Q[in[R]].pop();
        for (int i = l[in[R]]; i <= r[in[R]]; i++)
            if (k > a[i])
                a[i] = k, Change[i]++;
    }
    for (int i = l[in[R]]; i <= R; i++)
        if (x > a[i])
            a[i] = x, Change[i]++;
    Min[in[R]] = INF;
    for (int i = l[in[R]]; i <= r[in[R]]; i++)
        Min[in[R]] = min(Min[in[R]], a[i]);
    for (int i = in[L] + 1; i < in[R]; i++)
    {
        if (x > Min[i])
        {
            Q[i].push(x);
            Min[i] = x;
        }
    }
}
int Query(int x)
{
    for (int i = l[in[x]]; i <= r[in[x]]; i++)
        a[i] += Block_Add[in[x]];
    Block_Add[in[x]] = 0;
    while (!Q[in[x]].empty())
    {
        int k = Q[in[x]].front();
        Q[in[x]].pop();
        for (int i = l[in[x]]; i <= r[in[x]]; i++)
            if (k > a[i])
                a[i] = k, Change[i]++;
    }
    return a[x];
}
int main()
{
    // memset (Min, 0x3f, sizeof (Min));
    int n = read();
    if (n <= 10000)
    {
        for (int i = 1; i <= n; i++)
            a[i] = read();
        int m = read();
        char s[5];
        while (m--)
        {
            scanf ("%s", s);
            if (s[0] == 'A')
            {
                int L = read(), R = read(), x = read();
                if (x == 0) continue;
                for (int i = L; i <= R; i++)
                    a[i] += x, Change[i]++;
            }
            else if (s[0] == 'M')
            {
                int L = read(), R = read(), x = read();
                for (int i = L; i <= R; i++)
                {
                    if (x > a[i])
                        a[i] = x, Change[i]++;
                }
            }
            else
            {
                int x = read();
                printf ("%d %d\n", a[x], Change[x]);
            }
        }
    }
    else
    {
        int block = sqrt(n);
        for (int i = 1; i <= n; i++)
        {
            a[i] = read();
            in[i] = (i - 1) / block + 1;
        }
        for (int i = 1; i <= in[n]; i++)
        {
            l[i] = block * (i - 1) + 1;
            r[i] = min(l[i] + block - 1, n);
            Min[i] = INF;
            for (int j = l[i]; j <= r[i]; j++)
                Min[i] = min(Min[i], a[j]);
        }
        int m = read();
        char s[5];
        while (m--)
        {
            scanf ("%s", s);
            if (s[0] == 'A')
            {
                int L = read(), R = read(), x = read();
                if (x == 0) continue;
                Add(L, R, x);
            }
            else if (s[0] == 'M')
            {
                int L = read(), R = read(), x = read();
                Max(L, R, x);
            }
            else
            {
                int x = read();
                int ans = Query(x);
                printf ("%d %d\n", ans, Change[x] + Block_Change[in[x]]);
            }
        }
    }
    // while (1);
}