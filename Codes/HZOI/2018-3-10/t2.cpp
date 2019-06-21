#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 6e4 + 5;
struct edge
{
    int END, next;
}V[MAXN << 2];
int first[MAXN], p;
void add(int a, int b)
{
    V[p].END = b;
    V[p].next = first[a];
    first[a] = p++;
}
int Rank[MAXN], Color[MAXN], dis[2][MAXN];
bool vis[MAXN];
void Spfa(int op, int s)
{
    // memset (dis[op], 0x3f, sizeof (dis[op]));
    queue<int> Q;
    Q.push(s);
    dis[op][s] = 0;
    vis[s] = 1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        vis[k] = 0;
        for (int i = first[k]; i != -1; i = V[i].next)
        {
            if (dis[op][V[i].END] > dis[op][k] + 1)
            {
                dis[op][V[i].END] = dis[op][k] + 1;
                if (!vis[V[i].END])
                {
                    vis[V[i].END] = 1;
                    Q.push(V[i].END);
                }
            }
        }
    }
}
struct data
{
    int a, b, id;
};
int ans[MAXN << 1];
void Divide(vector<int> u, vector<pair<int, int> > v, vector<data> q)
{
    if (u.size() == 3)
    {
        for (int i = 0; i < q.size(); i++)
            if (q[i].a == q[i].b)
                ans[q[i].id] = 0;
            else
                ans[q[i].id] = 1;
        return;
    }
    // memset (first, -1, sizeof (first)); 
    for (int i = 0; i < u.size() - 1; i++)
        first[u[i]] = first[u[i + 1]] = -1;
    p = 0;
    for (int i = 0; i < u.size() - 1; i++)
    {
        add(u[i], u[i + 1]);
        add(u[i + 1], u[i]);
    }
    add(u[u.size() - 1], u[0]);
    add(u[0], u[u.size() - 1]);
    for (int i = 0; i < v.size(); i++)
    {
        add(v[i].first, v[i].second);
        add(v[i].second, v[i].first);
    }
    int Min = 0x3f3f3f3f, id = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int tmp = max(abs(Rank[v[i].first] - Rank[v[i].second]), (int)u.size() - abs(Rank[v[i].first] - Rank[v[i].second]));
        if (tmp < Min)
        {
            tmp = Min;
            id = i;
        }
    }
    int l = Rank[v[id].first] - 1, r = Rank[v[id].second] - 1;
    if (l > r) swap(l, r);
    for (int i = 0; i < u.size(); i++)
        if (i < l || i > r)
            Color[u[i]] = 0;
        else Color[u[i]] = 1;
    Spfa(0, v[id].first);
    Spfa(1, v[id].second);
    for (int i = 0; i < q.size(); i++)
        if (Color[q[i].a] != Color[q[i].b])
        {
            ans[q[i].id] = (dis[0][q[i].a] + dis[0][q[i].b]);
            ans[q[i].id] = min(ans[q[i].id], dis[1][q[i].a] + dis[1][q[i].b]);
            ans[q[i].id] = min(ans[q[i].id], dis[0][q[i].a] + dis[1][q[i].b] + 1);
            ans[q[i].id] = min(ans[q[i].id], dis[1][q[i].a] + dis[0][q[i].b] + 1);
        }
    for (int i = 0; i < u.size(); i++)
        dis[0][u[i]] = dis[1][u[i]] = 0x3f3f3f3f;
    vector<data> q1, q2;
    for (int i = 0; i < q.size(); i++)
        if (Color[q[i].a] == Color[q[i].b])
            if (Color[q[i].a] == 1)
                q2.push_back(q[i]);
            else
                q1.push_back(q[i]);
    vector<pair<int, int> > v1, v2;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == id) continue;
        if (Color[v[i].first] == Color[v[i].second])
        {
            if (Color[v[i].first] == 1)
                v2.push_back(v[i]);
            else
                v1.push_back(v[i]);
        }
        else if (v[i].first == u[l] || v[i].first == u[r])
        {
            if (Color[v[i].second] == 1)
                v2.push_back(v[i]);
            else
                v1.push_back(v[i]);
        }
        else if (v[i].second == u[l] || v[i].second == u[r])
        {
            if (Color[v[i].first] == 1)
                v2.push_back(v[i]);
            else
                v1.push_back(v[i]);
        }
    }
    vector<int> u1;
    int cnt = 0;
    for (int i = 0; i < u.size(); i++)
    {
        if (i == l || i == r)
        {
            Rank[u[i]] = ++cnt;
            u1.push_back(u[i]);
            continue;
        }
        if (Color[u[i]] == 0)
        {
            Rank[u[i]] = ++cnt;
            u1.push_back(u[i]);
        }
    }
    // for (auto x : u1) printf ("%d\n", x);
    Divide(u1, v1, q1);
    u1.clear();
    for (int i = 0; i < u.size(); i++)
        if (i < l || i > r)
            Color[u[i]] = 0;
        else Color[u[i]] = 1;
    cnt = 0;
    for (int i = 0; i < u.size(); i++)
    {
        if (i == l || i == r)
        {
            Rank[u[i]] = ++cnt;
            u1.push_back(u[i]);
            continue;
        }
        if (Color[u[i]] == 1)
        {
            Rank[u[i]] = ++cnt;
            u1.push_back(u[i]);
        }
    }
    Divide(u1, v2, q2);
}
vector<int> u;
vector<pair<int,int> > v;
vector<data> q;
int main()
{
    // freopen ("drive14.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    memset (dis, 0x3f, sizeof (dis));
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n - 3; i++)
    {
        int a = read(), b = read();
        v.push_back(pair<int, int>(a, b));
    }
    int m = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        q.push_back((data){a, b, i});
    }
    for (int i = 1; i <= n; i++)
    {
        u.push_back(i);
        Rank[i] = i;
    }
    Divide(u, v, q);
    for (int i = 1; i <= m; i++)
        printf ("%d\n", ans[i]);
    // while (1);
}