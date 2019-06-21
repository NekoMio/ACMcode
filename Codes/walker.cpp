#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MOD = 45989;
struct Marmix
{
    long long a[205][205];
    int n, m;
    Marmix(int x = 0, int y = 0)
    {
        memset(a, 0, sizeof(a));
        n = x, m = y;
    }
    Marmix operator*(const Marmix &a)
    {
        if (a.n != m)
        {
            printf("ERROR\n");
            system("pause");
            exit(0);
        }
        Marmix ans(n, a.m);
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= a.m; i++)
            {
                for (int j = 1; j <= a.n; j++)
                {
                    ans.a[k][i] += (this->a[k][j]) * a.a[j][i];
                    //ans.a[k][i] = ans.a[k][i] % MOD;
                }
                ans.a[k][i] = ans.a[k][i] % MOD;
            }
        }
        return ans;
    }
};
struct edge
{
    int END, next, START;
} v[600];
int first[25], p;
void add(int a, int b)
{
    v[p].START = a;
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
#define LL long long
using namespace std;
int n, m;
Marmix pow_mod(Marmix a, LL b)
{
    Marmix ans(p, p);
    for (int i = 1; i <= p; i++)
        ans.a[i][i] = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
int main()
{
    memset(first, -1, sizeof(first));
    // freopen("walker.in", "r", stdin);
    // freopen("walker.out", "w", stdout);
    int A, B;
    long long t;
    scanf("%d%d%lld%d%d", &n, &m, &t, &A, &B);
    int s, e;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e);
        add(e, s);
    }
    Marmix a(p, p);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (v[i].END == v[j].START && (i^1)!=j)
                a.a[i + 1][j + 1] = 1;
        }
    }
    Marmix T(1, p);
    for (int i = first[A]; i != -1; i = v[i].next)
    {
        T.a[1][i + 1] = 1;
    }
    //for(int i=1;i<=n;i++)a.a[i][i]+=1;
    a = pow_mod(a, t - 1);
    Marmix ans;
    ans = T * a;
    LL sum = 0;
    for (int i = 0; i < p; i++)
    {
        if (v[i].END == B)
            sum += ans.a[1][i + 1];
    }
    printf("%lld\n", sum % MOD);
    //while (1)
    ;
}
