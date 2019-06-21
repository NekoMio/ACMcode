#include <cstdio>
#include <cstring>
using namespace std;
#define LL unsigned long long
const int N = 300010, M = 15000010, L = 20000010;
const LL P = 23333333, p = 1000007, mod = 998244353;
int head[P], next[L], cnt[L], E, Next[N], Pre[N], a[N];
LL w[L], Pow[60];
int n, m;
char str[L];
void Insert(LL x, int y)
{
    LL now = x % P;
    bool flag = 0;
    for (int i = head[now]; i; i = next[i])
        if (w[i] == x)
        {
            cnt[i] += y;
            flag = 1;
            break;
        }
    if (!flag)
    {
        next[++E] = head[now];
        head[now] = E;
        cnt[E] = 1;
        w[E] = x;
    }
}
int Query(LL x)
{
    LL now = x % P;
    for (int i = head[now]; i; i = next[i])
        if (w[i] == x)
            return cnt[i];
    return 0;
}
void Change(int x, int y)
{
    int now = x;
    for (int k = 1; k <= 50; k++)
    {
        int ret = now;
        LL Hash = a[now];
        for (int j = 1; j <= k; j++)
        {
            ret = Next[ret];
            Hash = Hash * p + a[ret];
        }
        for (int l = k + 1; l <= 50; l++)
        {
            Insert(Hash, y);
            ret = Next[ret];
            if (!ret)
                break;
            Hash = Hash * p + a[ret];
        }
        now = Pre[now];
        if (!now)
            break;
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Insert(a[i], 1);
    }
    Pow[0] = 1;
    for (int i = 1; i <= 50; i++)
    {
        Pow[i] = Pow[i - 1] * p;
    }
    int op;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d", &x, &y);
            Next[x] = y;
            Pre[y] = x;
            Change(x, 1);
        }
        else if (op == 2)
        {
            scanf("%d", &x);
            Change(x, -1);
            Pre[Next[x]] = 0, Next[x] = 0;
        }
        else
        {
            scanf("%s", str + 1);
            scanf("%d", &x);
            LL ret = 0;
            for (int i = 1; i <= x; i++)
                ret = ret * p + str[i] - '0';
            LL ans = Query(ret);
            LL len = strlen(str + 1);
            for (int i = x + 1; i <= len; i++)
            {
                ret = ret - (str[i - x] - '0') * Pow[x - 1];
                ret = ret * p + (str[i] - '0');
                ans = ans * Query(ret) % mod;
            }
            printf("%lld\n", ans);
        }
    }
}