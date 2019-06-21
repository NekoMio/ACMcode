#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct edge
{
    int END, next, v;
}v[20005];
int first[10005], p;
int rt = 0, size, Min, ans;
int s[10005], t, dep[10005], K;
bool flag[10005];
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
void Get_root(int x, int fa)
{
    s[x] = 1;
    int now = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa && !flag[v[i].END])
        {
            Get_root(v[i].END, x);
            s[x] += s[v[i].END];
            now = max(now, s[v[i].END]);
        }
    }
    now = max(now, size - s[x]);
    if (now <= Min) Min = now, rt = x;
}
void Get_Dep(int x, int Dep, int fa)
{
    dep[++t] = Dep;
    s[x] = 1;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa && !flag[v[i].END])
        {
            Get_Dep(v[i].END, Dep + v[i].v, x);
            s[x] += s[v[i].END];
        }
    }
}
int calc(int x, int init)
{
    t = 0;
    Get_Dep(x, init, 0);
    sort(dep + 1, dep + t + 1);
    int ret = 0;
    for (int l = 1, r = t; l < r; )
        if (dep[l] + dep[r] <= K) ret += r - l++;
        else r--;
    return ret;
}
void Work(int x)
{
    ans += calc(x, 0);
    flag[x] = 1;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (!flag[v[i].END])
        {
            ans -= calc(v[i].END, v[i].v);
            Min = size = s[v[i].END];
            Get_root(v[i].END, rt = 0);
            Work(rt);
        }
    }
}
int main()
{
    int n;
    while (scanf("%d%d", &n, &K))
    {
        if (n == 0 && K == 0) break;
        memset(first, -1, sizeof(first));
        memset(flag, 0, sizeof(flag));
        p = 0;
        int a, b, c;
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
            add(b, a, c);
        }
        Min = size = n;
        Get_root(1, rt = 0);
        ans = 0;
        Work(rt);
        printf("%d\n", ans);
    }
}
/*
5 4
1 2 3
1 3 1
1 4 2
3 5 1
*/