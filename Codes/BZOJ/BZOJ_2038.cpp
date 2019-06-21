#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 50005;
int a[MAXN], in[MAXN];
struct Query_data
{
    int l, r, id;
    bool operator < (const Query_data &b) const 
    {
        return in[l] == in[b.l] ? r > b.r : in[l] < in[b.l];
    }
    bool operator > (const Query_data &b) const 
    {
        return id < b.id;
    }
}Q[MAXN];
int Sum[MAXN];
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
long long Z, M;
void Update(int i, int c)
{
    Z -= 1ll * Sum[a[i]] * (Sum[a[i]] - 1) / 2;
    Sum[a[i]] += c;
    Z += 1ll * Sum[a[i]] * (Sum[a[i]] - 1) / 2;
}
const int block = 200;
long long ans[MAXN];
bool cmp(const Query_data &a, const Query_data &b)
{
    return a > b;
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        in[i] = i / block + 1;
    }
    for (int i = 1; i <= m; i++)
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
    sort(Q + 1, Q + m + 1);
    for (int i = 1; i <= n; i++)
        Update(i, 1);
    int l = 1, r = n;
    for (int i = 1; i <= m; i++)
    {
        while (l < Q[i].l) {Update(l, -1), l++;}
        while (l > Q[i].l) {l--, Update(l, 1);}
        while (r > Q[i].r) {Update(r, -1), r--;}
        while (r < Q[i].r) {r++, Update(r, 1);}
        ans[Q[i].id] = Z;
    }
    sort(Q + 1, Q + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        if (ans[i] == 0) printf ("0/1\n");
        else
        {
            long long G = gcd(ans[i], M = 1ll * (Q[i].r - Q[i].l + 1) * (Q[i].r - Q[i].l) / 2);
            printf ("%lld/%lld\n", ans[i] / G, M / G);
        }
    }
    // while (1);
}