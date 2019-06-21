#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    long long END, next, v;
} v[5005];
long long first[2505], p;
void add(long long a, long long b, long long c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
long long a[2505][2505];
long long b[2505][2505];
long long minn[2505], head[2505];
bool intree[2505];
void dfs(long long s, long long x, long long fa, long long dis)
{
    b[s][x] = dis;
    for (long long i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs(s, v[i].END, x, dis + v[i].v);
        }
    }
}
int main()
{
    //memset(first, -1, sizeof(first));
    freopen("treas.in", "r", stdin);
    freopen("treas.out", "w", stdout);
    long long T;
    scanf("%lld", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        memset(head, 0, sizeof(head));
        p = 0;
        long long n;
        scanf("%lld", &n);
        for (long long i = 1; i <= n; i++)
        {
            for (long long j = 1; j <= n; j++)
            {
                scanf("%lld", &a[i][j]);
            }
        }
        if (n == 1)
        {
            printf("Yes\n1\n");
            continue;
        }
        memset(minn, 0x3f, sizeof(minn));
        memset(intree, 0, sizeof(intree));
        minn[1] = 0;
        for (long long i = 1; i <= n; i++)
        {
            long long k = 0;
            for (long long j = 1; j <= n; j++)
            {
                if (!intree[j] && (minn[j] < minn[k]))
                {
                    k = j;
                }
            }
            intree[k] = 1;
            // add(i, k, minn[k]);
            // add(k, i, minn[k]);
            for (long long j = 1; j <= n; j++)
            {
                if (!intree[j] && j != k && (a[k][j] < minn[j]))
                {
                    minn[j] = a[k][j];
                    head[j] = k;
                }
            }
        }
        for (long long i = 2; i <= n; i++)
        {
            add(i, head[i], minn[i]);
            add(head[i], i, minn[i]);
        }
        for (long long i = 1; i <= n; i++)
        {
            dfs(i, i, 0, 0);
        }
        bool flag = 0;
        for (long long i = 1; i <= n; i++)
        {
            for (long long j = 1; j <= n; j++)
            {
                if (a[i][j] != b[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
        {
            printf("No\n");
            continue;
        }
        else
        {
            printf("Yes\n");
            double ans = 0;
            long long d = 0;
            for (long long i = 1; i <= n; i++)
            {
                long long sum = 0, t = 0;
                for (long long j = first[i]; j != -1; j = v[j].next)
                {
                    sum += v[j].v;
                    t++;
                }
                if (ans < (double)sum / t)
                {
                    ans = (double)sum / t;
                    d = i;
                }
            }
            printf("%lld\n", d);
        }
    }
    // while (1)
    ;
}