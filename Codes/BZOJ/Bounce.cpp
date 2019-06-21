#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, k[200005], block;
int in[200005], next[200005], times[200005], l[200005];
int main()
{
    //freopen("1.in","r",stdin);
    //scanf("%d", &n);
    n = read();
    block = sqrt(n);
    for (int i = 0; i < n; i++)
    {
        k[i] = read();
        //scanf("%d", k + i);
        in[i] = i / block + 1;
        l[i] = (in[i] - 1) * block;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (i + k[i] > n)
        {
            times[i] = 1;
            next[i] = n;
        }
        else if (in[i] == in[i + k[i]])
        {
            times[i] = times[i + k[i]] + 1;
            next[i] = next[i + k[i]];
        }
        else
        {
            times[i] = 1;
            next[i] = i + k[i];
        }
    }
    //scanf("%d", &m);
    m = read();
    int op, s;
    while (m--)
    {
        //scanf("%d", &op);
        op = read();
        if (op == 1)
        {
            //scanf("%d", &s);
            s = read();
            int ans = 0;
            for (int i = s; i < n; i = next[i])
            {
                ans += times[i];
            }
            printf("%d\n", ans);
        }
        else
        {
            //scanf("%d%d", &s, &c);
            //k[s] = c;
            s = read();
            k[s] = read();
            for (int i = s; i >= l[s]; i--)
            {
                if (i + k[i] > n)
                {
                    times[i] = 1;
                    next[i] = i + k[i];
                }
                if (in[i] == in[i + k[i]])
                {
                    times[i] = times[i + k[i]] + 1;
                    next[i] = next[i + k[i]];
                }
                else
                {
                    times[i] = 1;
                    next[i] = i + k[i];
                }
            }
        }
    }
    //printf("%lf", (double)clock() / CLOCKS_PER_SEC);
}