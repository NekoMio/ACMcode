#include <bits/stdc++.h>
using namespace std;
const int MAXM = 2005;
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
int A[MAXM], B[MAXM], C[MAXM], D[MAXM];
int du[MAXN];
int n, m;
int tot;
struct edge
{
    int END, next, cap;
}v[100005];
int first[MAXN], p;
void add(int a, int b, int f)
{
    v[p].END = b, v[p].cap = f, v[p].next = first[a], first[a] = p++;
    v[p].END = a, v[p].cap = 0, v[p].next = first[b], first[b] = p++;
}
int dis[MAXN];
bool vis[MAXN];
bool BFS(int S, int E)
{
    queue<int> Q;
    memset (vis, 0, sizeof (vis));
    memset (dis, -1, sizeof (dis));
    vis[S] = 1;
    dis[S] = 0;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!vis[v[i].END] && v[i].cap > 0)
            {
                vis[v[i].END] = 1;
                dis[v[i].END] = dis[k] + 1;
                Q.push(v[i].END);
            }
        }
    }
    return vis[E];
}
int DFS(int S, int E, int a)
{
    if (S == E || a == 0) return a;
    int flow = 0, f;
    for (int i = first[S]; i != -1; i = v[i].next)
    {
        if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
        {
            a -= f;
            flow += f;
            v[i].cap -= f;
            v[i ^ 1].cap += f;
            if (a == 0) break;
        }
    }
    if (!flow) dis[S] = -1;
    return flow;
}
int Dinic(int S, int E)
{
    int ans = 0;
    while (BFS(S, E))
    {
        ans += DFS(S, E, INF);
    }
    return ans;
}
bool Judge()
{
    for (int i = 1; i <= n; i++)
        if (du[i] % 2 != 0) return 1;
        else tot += abs(du[i]) / 2;
    return 0;
}
bool Judge(int mid)
{
    memset (first, -1, sizeof (first));
    p = 0;
    int S = 0, T = n + 1;
    for (int i = 1; i <= m; i++)
        if (C[i] > mid) return 0;
        else if (D[i] <= mid) add(A[i], B[i], 1);
    for (int i = 1; i <= n; i++)
    {
        if (du[i] > 0) add(S, i, du[i] / 2);
        if (du[i] < 0) add(i, T, -du[i] / 2);
    }
    if (Dinic(S, T) == tot / 2) return 1;
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        if (C[i] > D[i])
            swap(A[i], B[i]), swap(C[i], D[i]);
        du[A[i]]++, du[B[i]]--;
    }
    if (Judge()) return cout << "NIE" << endl, 0;
    int l = 0, r = 0x3f3f3f3f, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (Judge(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf ("%d\n", ans);
}