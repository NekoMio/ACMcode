#include <cmath>
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
const int MAXN = 300005;
struct SAM
{
    struct edge
    {
        int END, next;
    }v[MAXN << 1];
    int first[MAXN << 1], p;
    void add(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    int a[MAXN << 1][26], fa[MAXN << 1], Max[MAXN << 1], Num[MAXN << 1];
    int f[MAXN << 1][20];
    int cnt, last;
    SAM()
    {
        // Max[0] = -1;
        p = 0;
        memset (first, -1, sizeof (first));
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        Num[np] = 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof (a[nq]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    int extQueryend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof (a[nq]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
        return np;
    }
    void build()
    {
        for (int i = 2; i <= cnt; i++)
            add(fa[i], i);
    }
    void dfs(int rt)
    {
        f[rt][0] = fa[rt];
        for (int i = 1; i <= 19; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            dfs(v[i].END);
            if (rt != 1) Num[rt] += Num[v[i].END];
        }
    }
    int Query(int pos, int len)
    {
        int now = pos;
        for (int i = 19; i >= 0; i--)
            if (Max[f[now][i]] >= len)
                now = f[now][i];
        return Num[now];
    }
}sam;
char s[MAXN];
int l[MAXN], r[MAXN];
int t[350][350];
int Sl[MAXN], in[MAXN], block;
long long ans[MAXN];
char w[MAXN + 1000];
int pos[MAXN];
int n, m, k, q;
long long Calc(int id)
{
    long long ans = 0;
    for (int i = 0; i < k; i++)
    {
        int now = 1;
        for (int j = i; j < k; j++)
        {
            now = sam.a[now][w[Sl[id] + j] - 'a'];
            ans = ans + 1ll * sam.Num[now] * t[i][j];
        }
    }
    return ans;
}
struct Query_data
{
    int l, r;
    int id;
    bool operator < (const Query_data &a) const 
    {
        return in[l] == in[a.l] ? r < a.r : in[l] < in[a.l];
    }
}Q[MAXN];
int main()
{
    n = read(), m = read(), q = read(), k = read();
    scanf ("%s", s + 1);
    for (int i = 1; i <= n; i++)
        sam.extend(s[i] - 'a');
    for (int i = 1; i <= m; i++)
        l[i] = read(), r[i] = read();
    if (k < 320)
    {
        sam.build();
        sam.dfs(1);
        block = sqrt(m);
        for (int i = 1; i <= m; i++) in[i] = (i - 1) / block + 1;
        for (int i = 1; i <= q; i++)
        {
            Sl[i] = Sl[i - 1] + k;
            scanf ("%s", w + Sl[i]);
            Q[i].l = read() + 1, Q[i].r = read() + 1;
            Q[i].id = i;
        }
        sort(Q + 1, Q + q + 1);
        int L = 1, R = m;
        for (int i = 1; i <= m; i++) t[l[i]][r[i]]++;
        for (int i = 1; i <= q; i++)
        {
            while (L < Q[i].l) {t[l[L]][r[L]]--, L++;}
            while (L > Q[i].l) {L--, t[l[L]][r[L]]++;}
            while (R > Q[i].r) {t[l[R]][r[R]]--, R--;}
            while (R < Q[i].r) {R++, t[l[R]][r[R]]++;}
            ans[Q[i].id] = Calc(Q[i].id);
        }
        for (int i = 1; i <= q; i++)
            printf ("%lld\n", ans[i]);
    }
    else
    {
        for (int i = 1; i <= q; i++)
        {
            scanf ("%s", w);
            Q[i].l = read() + 1, Q[i].r = read() + 1;
            Sl[i] = Sl[i - 1] + k;
            sam.last = 1;
            for (int j = 0; j < k; j++) pos[j + Sl[i]] = sam.extQueryend(w[j] - 'a');
        }
        sam.build();
        sam.dfs(1);
        for (int i = 1; i <= q; i++)
        {
            long long ans = 0;
            for (int j = Q[i].l; j <= Q[i].r; j++)
                ans += sam.Query(pos[r[j] + Sl[i]], r[j] - l[j] + 1);
            printf ("%lld\n", ans);
        }
    }
}