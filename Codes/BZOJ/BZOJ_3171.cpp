#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
struct edge
{
    int S, END, next, cap, v;
}v[MAXN * 100];
int first[MAXN], p;
void add(int a, int b, int f, int c)
{
    v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c, first[a] = p++;
    v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v =-c, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E)
{
    memset (pre, -1, sizeof (pre));
    memset (dis, 0x3f, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[S] = 0;
    vis[S] = 1;
    queue<int> Q;
    Q.push(S);
    while (!Q.empty())
    {
        int k = Q.front(); Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            if (v[i].cap == 0) continue;
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    Q.push(v[i].END);
                    vis[v[i].END] = 1;
                }
            }
        }
    }
    return dis[E] != 0x3f3f3f3f;
}
int Max_Profit(int S, int T)
{
    int ans = 0, flow;
    int cnt = 0;
    while (Spfa(S, T))
    {
        flow = INF;
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            flow = min(flow, v[i].cap);
        for (int i = pre[T]; i != -1; i = pre[v[i].S])
            v[i].cap -= flow, v[i ^ 1].cap += flow;
        ans += dis[T] * flow;
    }
    return ans;
}
char s[20][20];
int dx[4] = {-1,0,1,0},
    dy[4] = {0,1,0,-1};
int Trans(char c)
{
    switch (c)
    {
        case 'U':
            return 0;
        case 'R':
            return 1;
        case 'D':
            return 2;
        case 'L':
            return 3;
        default:
            return -1;
    }
}
int n, m;
void Update(int &a, int &b, int c)
{
    a += dx[c];
    b += dy[c];
    if (a == 0) a = n;
    if (a == n + 1) a = 1;
    if (b == 0) b = m;
    if (b == m + 1) b = 1;
}
int ID(int a, int b, int s)
{
    if (s == 0) return (a - 1) * m + b;
    else return (a - 1) * m + b + n * m + 1;
}
int main()
{
    memset (first, -1, sizeof (first));
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i] + 1;
    int T = 605;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++) s[i][j] = Trans(s[i][j]);
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k <= 3; k++)
            {
                int ni, nj;
                Update(ni = i, nj = j, k);
                // cerr << ni << " " << nj << " " << (k == s[i][j]) << '\n';
                // cerr << ID(i, j, 0) << ' ' << ID(ni, nj, 1) << '\n';
                if (k == s[i][j])
                    add(ID(i, j, 0), ID(ni, nj, 1), 1, 0);
                else
                    add(ID(i, j, 0), ID(ni, nj, 1), 1, 1);
            }
            add(0, ID(i, j, 0), 1, 0);
            add(ID(i, j, 1), T, 1, 0);
        }
    }
    cout << Max_Profit(0, T) << endl;
    // while (1);
}