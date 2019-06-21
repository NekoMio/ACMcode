#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
struct edge
{
    int END, next;
}v[105];
int first[15], p;
struct func
{
    void operator ()(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
}add;
#define lowbit(_) ((_)&(-_))
struct func2
{
    int operator ()(int x)
    {
        int ans = 0;
        while (x) ans += (x & 1), x >>= 1;
        return ans;
    }
}Get_Num;
int cnt[(1 << 10) + 1];
long long C[55][55];
double f[(1 << 10) + 1][50];
double g[(1 << 10) + 1][50];
signed main()
{
    int n, m, a, b;
    scanf ("%lld%lld", &n, &m);
    memset (first, -1, sizeof (first));
    for (int i = 1; i <= m; i++)
    {
        scanf ("%lld%lld", &a, &b);
        add(a, b);
        add(b, a);
    }
    int N = (1 << n) - 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= n; j++)
            if (i & (1 << (j - 1)))
                for (int k = first[j]; k != -1; k = v[k].next)
                    if (i & (1 << (v[k].END - 1)))
                        cnt[i]++;
        cnt[i] /= 2;
    }
    C[0][0] = 1;
    for (int i = 1; i <= 50; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 1; i <= N; i++)
    {
        if (Get_Num(i) == 1)
        {
            g[i][0] = 1;
            continue;
        }
        int j = lowbit(i);
        for (int S = (i - 1) & i; S; S = (S - 1) & i)
        {
            if (j & S)
                for (int l = 0; l <= cnt[S]; l++)
                    for (int k = 0; k <= cnt[S ^ i]; k++)
                        f[i][l + k] += g[S][l] * C[cnt[i ^ S]][k];
        }
        for (j = 0; j <= cnt[i]; j++) g[i][j] = C[cnt[i]][j] - f[i][j];
    }
    double H = 0;
    for (int i = 0; i <= m; i++) H += f[N][i] / C[cnt[N]][i];
    printf ("%.6lf", H / (m + 1));
}