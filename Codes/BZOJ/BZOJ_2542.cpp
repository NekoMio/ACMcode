#include <queue>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 100005;
struct edge
{
    int S, END, next, cap;
    double v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int f, double c)
{
    v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = f, v[p].v = c, first[a] = p++;
    v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].v = 1.0 / c, first[b] = p++;
}
double dis[5005];
int pre[5005];
bool vis[5005];
bool Spfa(int S, int E)
{
    // memset (dis, 0, sizeof (dis));
    fill(dis, dis + 5005, -1.0);
    memset (pre, -1, sizeof (pre));
    memset (vis, 0, sizeof (vis));
    queue<int> Q;
    Q.push(S);
    vis[S] = 1;
    dis[S] = 1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (!v[i].cap) continue;
            if (dis[k] * v[i].v - dis[v[i].END] > 1e-7)
            {
                dis[v[i].END] = dis[k] * v[i].v;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != -1.0;
}
int K;
double Max_Profit(int S, int T)
{
    double ans = 1;
    int flow;
    int t = 0;
    while (Spfa(S, T))
    {
        flow = INF;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans *= pow(dis[T], flow);
        t += flow;
    }
    if (t != K) return 0;
    else return ans;
}
double AS[305];
int main()
{
    // freopen ("agent2.in", "r", stdin);
    // freopen ("agent.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    memset (first, -1, sizeof (first));
    cin >> n >> K;
    if (n == 0 && K == 0) return cout << "1.0000" << endl, 0;
    for (int i = 1; i <= n; i++)
        cin >> AS[i];
    int x = 0;
    int S = n + 2, t = n + 1;
    add(0, S, K, 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        add(S, i, x, AS[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        if (x == 1)
            add(i, t, INF, 1);
    }
    int a, b;
    double y;
    while (cin >> a >> b)
    {
        if (a == -1 && b == -1) break;
        cin >> y >> x;
        add(a, b, x, y);
        add(b, a, x, y);
    }
    double ans = Max_Profit(0, t);
    if (ans < 1e-12) cout << "0.0000" << endl;
    else
    {
        stringstream ss, ss2;
        ss << showpoint;
        ss << setprecision(5);
        ss << ans << endl;
        ss >> ans;
        ss2 << showpoint << fixed << setprecision(17) << ans;
        string s;
        s = ss2.str();
        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            char u = s[i];
            if (u == '.')
            {
                cout << u; 
                continue;
            }
            if (cnt != 0 || u != '0') cnt++;
            if (cnt == 5)
            {
                if (i != s.size() - 2 && s[i + 1] >= '5') u++;
                cout << u;
                break;
            }
            else
                cout << u;
        }
    }
    // while (1);
}