#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
const int MAXN = 205;
const int INF = 0x3f3f3f3f;
int a[MAXN], b[MAXN], c[MAXN], cnt[MAXN];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int S, END, next, cap, v;
}v[MAXN * 100];
int first[MAXN], p;
void add(int a, int b, int c, int f)
{
    v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c, first[a] = p++;
    v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v =-c, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E)
{
    memset (dis, 0x80, sizeof (dis));
    memset (pre, -1, sizeof (pre));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = 1;
    queue<int> Q;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (v[i].cap == 0) continue;
            if (dis[v[i].END] < dis[k] + v[i].v)
            {
                pre[v[i].END] = i;
                dis[v[i].END] = dis[k] + v[i].v;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != 0x8080808080808080;
}
int Max_Profit(int S, int T)
{
    int ans = 0, flow, Sum = 0;
    while (Spfa(S, T))
    {
        flow = INF;
        long long cost = 0;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
        {
            v[i].cap -= flow, v[i ^ 1].cap += flow;
            cost += v[i].v;
        }
        if (Sum + dis[T] * flow < 0) return ans + Sum / -cost;
        else ans += flow, Sum += flow * cost;
    }
    return ans;
}
signed main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    for (int i = 1; i <= n; i++) c[i] = read();
    int T = n + 1;
    for (int i = 1; i <= n; i++)
    {
        int x = a[i];
        for (int j = 2; j * j <= x; j++)
            while (x % j == 0)
                x /= j, cnt[i]++;
        if ((cnt[i] += (x > 1)) & 1) add(0, i, 0, b[i]);
        else add(i, T, 0, b[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] & 1)
        for (int j = 1; j <= n; j++) if (!(cnt[j] & 1))
        {
            if (a[i] % a[j] == 0 && cnt[i] == cnt[j] + 1) add(i, j, c[i] * c[j], INF);
            if (a[j] % a[i] == 0 && cnt[j] == cnt[i] + 1) add(i, j, c[i] * c[j], INF);
        }
    }
    cout << Max_Profit(0, T) << endl;
}