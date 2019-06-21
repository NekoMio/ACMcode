#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
struct edge
{
    int S, END, next, cap, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int f, int c)
{
    v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].v = c, v[p].cap = f, first[a] = p++;
    v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].v =-c, v[p].cap = 0, first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E)
{
    memset (dis, 0x3f, sizeof (dis));
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
            if (!v[i].cap) continue;
            if (dis[v[i].END] > dis[k] + v[i].v)
            {
                dis[v[i].END] = dis[k] + v[i].v;
                pre[v[i].END] = i;
                if (!vis[v[i].END])
                {
                    vis[v[i].END] = 1;
                    Q.push(v[i].END);
                }
            }
        }
    }
    return dis[E] != 0x3f3f3f3f;
}
int Min_Profit(int S, int T)
{
    int ans = 0, flow;
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
map<int, set<int> > X;
map<int, int> sb;
int S[MAXN];
int id[MAXN][2], Index;
int main()
{
    int n = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i <= n; i++)
    {
        int a = read(), b = read();
        if (!id[a][0]) id[a][0] = ++Index;
        if (!id[b][1]) id[b][1] = ++Index;
        X[a].insert(b);
        S[a]++;
        sb[b]++;
    }
    int s = ++Index, T = ++Index;
    for (map<int, set<int> >::iterator it = X.begin(); it != X.end(); it++)
    {
        add(s, id[it->first][0], S[it->first], 0);
        for (map<int, int>::iterator j = sb.begin(); j != sb.end(); j++)
        {
            if (!it->second.count(j->first))
                add(id[it->first][0], id[j->first][1], 1, 0);
            else 
                add(id[it->first][0], id[j->first][1], 1, 1);
        }
    }
    for (map<int, int>::iterator it = sb.begin(); it != sb.end(); it++)
        add(id[it->first][1], T, it->second, 0);
    int SS = ++Index;
    add(SS, s, n, 0);
    printf ("%d\n", Min_Profit(SS, T));
}