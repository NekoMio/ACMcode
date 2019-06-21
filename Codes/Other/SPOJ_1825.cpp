#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 200005;
bool tp[MAXN];
struct edge
{
    int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
bool vis[MAXN];
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].v = c;
    v[p].next = first[a];
    first[a] = p++;
}

int size[MAXN], Max[MAXN], root, sum;
void Get_root(int rt, int fa)
{
    size[rt] = 1, Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END]) continue;
        Get_root(v[i].END, rt);
        size[rt] += size[v[i].END];
        Max[rt] = max(Max[rt], size[v[i].END]);
    }
    Max[rt] = max(Max[rt], sum - Max[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
int Maxdp, dep[MAXN], dis[MAXN];
void Get_dis(int rt, int fa)
{
    dep[rt] = dep[fa] + tp[rt];
    Maxdp = max(Maxdp, dep[rt]);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!vis[v[i].END] && v[i].END != fa)
        {
            dis[v[i].END] = dis[rt] + v[i].v;
            Get_dis(v[i].END, rt);
        }
    }
}

int tmp[MAXN], Mx[MAXN];
void Update(int rt, int fa)
{
    tmp[dep[rt]] = max(tmp[dep[rt]], dis[rt]);
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (v[i].END != fa && !vis[v[i].END])
            Update(v[i].END, rt);
}
vector<pair<int, int> > st;
int K, ans;
void Solve(int rt)
{
    vis[rt] = 1; st.clear();
    if (tp[rt]) K--;
    for (int i = first[rt]; i != -1; i = v[i].next)
        if (!vis[v[i].END])
        {
            Maxdp = 0;
            dis[v[i].END] = v[i].v;
            Get_dis(v[i].END, 0);
            st.push_back(make_pair(Maxdp, v[i].END));
        }
    sort(st.begin(), st.end());
    for (int i = 0; i < st.size(); i++)
    {
        Update(st[i].second, rt);
        int now = 0;
        if (i != 0)
        {
            for (int j = st[i].first; j >= 0; j--)
            {
                while (now + j < K && now <= st[i - 1].first)
                    now++, Mx[now] = max(Mx[now - 1], Mx[now]);
                if (now + j <= K) ans = max(ans, Mx[now] + tmp[j]);
            }
        }
        if (i != st.size() - 1)
            for (int j = 0; j <= st[i].first; j++)
                Mx[j] = max(Mx[j], tmp[j]), tmp[j] = 0;
        else
        {
            for (int j = 0; j <= st[i].first; j++)
            {
                if (j <= K) ans = max(ans, max(tmp[j], Mx[j]));
                tmp[j] = Mx[j] = 0;
            }
        }
    }
    if (tp[rt]) K++;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END]) continue;
        root = 0;
        sum = size[v[i].END];
        Get_root(v[i].END, 0);
        Solve(root);
    }
}

int main()
{
    memset (first, -1, sizeof (first));
    int n = read(); K = read(); int m = read();
    for (int i = 1; i <= m; i++) tp[read()] = 1;
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
        add(b, a, c);
    }
    Max[0] = sum = n;
    Get_root(1, 0);
    Solve(root);
    printf ("%d", ans);
}
