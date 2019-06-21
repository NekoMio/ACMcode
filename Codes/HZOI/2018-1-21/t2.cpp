#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 5e5 + 5;
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
    long long ans;
    int last, cnt;
    int a[MAXN << 1][26], Max[MAXN << 1], fa[MAXN << 1];
    int size[MAXN << 1];
    SAM()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        size[np] = 1;
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
                fa[q] = fa[np] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    void Build()
    {
        memset (first, -1, sizeof (first));
        for (int i = 2; i <= cnt; i++)
            add(fa[i], i);
    }
    void DFS(int rt, int fa)
    {
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            DFS(v[i].END, rt);
            size[rt] += size[v[i].END];
        }
        Max[rt] -= Max[fa];
        ans -= 1ll * size[rt] * (size[rt] - 1) * Max[rt];
    }
    long long Query(int n)
    {
        ans = 1ll * n * (n - 1) * (n + 1) / 2;
        for (int i = first[1]; i != -1; i = v[i].next)
            DFS(v[i].END, 1);
        return ans;
    }
}sam;
char s[MAXN];
int main()
{
    scanf ("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) 
        sam.extend(s[i] - 'a');
    sam.Build();
    printf ("%lld\n", sam.Query(n));
}