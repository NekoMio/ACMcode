#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
    int next, END, v;
}v[300005 << 1];
int first[300005], p;
void add(int a, int b, int c)
{
    v[p].next = first[a];
    v[p].END = b;
    v[p].v = c;
    first[a] = p++;
}
int s, n;
int Max_len, P;
int f[300005], dis[300005];
void dfs(int rt, int fa, int len)
{
    f[rt] = fa;
    dis[rt] = len;
    if(len > Max_len) P = rt, Max_len = len;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if(v[i].END == fa) continue;
        dfs(v[i].END, rt, len + v[i].v);
    }
}
bool vis[300005];
int st[300005], top;
queue<int> Q;
int L, R;
bool Judge(int mid)
{
    int l = 1, r = top;
    while (st[1] - st[l + 1] <= mid && l <= top) l++;
    while (st[r - 1] <= mid && r >= 1) r--;
    return st[l] - st[r] <= s;
}
int main()
{
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &s);
    int a, b, c;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b ,c);
        add(b, a, c);
    }
    dfs(1, 0, 0);
    L = P;
    P = 0, Max_len = 0;
    dfs(L, 0, 0);
    R = P;
    for (int i = R; i != f[L]; i = f[i])
    {
        st[++top] = dis[i], Q.push(i), vis[i] = 1;
    }
    memset(dis, 0x3f, sizeof(dis));
    for (int i = R; i != f[L]; i = f[i]) dis[i] = 0;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
            if(dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
    }
    int l = 0,  r = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) if (l < dis[i]) l = dis[i];
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d", ans);
}