#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 5e5 + 5;
int a[MAXN];
struct data
{
    int i, l, r, t;
    data(int b = 0, int c = 0, int d = 0, int e = 0) 
    {
        i = b, l = c, r = d, t = e;
    }
    bool operator < (const data &b) const 
    {
        return a[t] - a[i - 1] < a[b.t] - a[b.i - 1]; 
    }
};
int bin[20], Log[MAXN];
int n, K, R, L;
int Max[MAXN][20];
long long ans = 0;
int Query(int l, int r)
{
    if (l == r) return l;
    int t = Log[r - l + 1];
    int t1 = Max[l][t], t2 = Max[r - bin[t] + 1][t];
    return a[t1] > a[t2] ? t1 : t2;
}
void Solve()
{
    priority_queue<data> Q;
    for (int i = 1; i <= n; i++)
    {
        if (i + L - 1 <= n)
        {
            int t = min(n, i + R - 1);
            Q.push(data(i, i + L - 1, t, Query(i + L - 1, t)));
        }
    }
    for (int i = 1; i <= K; i++)
    {
        data t = Q.top(); Q.pop();
        ans += a[t.t] - a[t.i - 1];
        if (t.t - 1 >= t.l) Q.push(data(t.i, t.l, t.t - 1, Query(t.l, t.t - 1)));
        if (t.t + 1 <= t.r) Q.push(data(t.i, t.t + 1, t.r, Query(t.t + 1, t.r)));
    }
}
int main()
{
    bin[0] = 1;
    for (int i = 1; i < 20; i++) bin[i] = bin[i - 1] << 1;
    n = read(), K = read(), L = read(), R = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    Log[0] = -1;
    for (int i = 1; i <= n; i++) Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i <= n; i++) Max[i][0] = i; 
    for (int j = 1; j <= 18; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i + bin[j] - 1 <= n)
            {
                int t1 = Max[i][j - 1], t2 = Max[i + bin[j - 1]][j - 1];
                Max[i][j] = a[t1] > a[t2] ? t1 : t2;
            }
            else break;
        }
    }
    Solve();
    printf ("%lld\n", ans);
    // while (1);
}