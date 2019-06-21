// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
const int MAXN = 300005;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct data
{
    int v, cnt;
    data(int c = 0, int cn = 0)
    {
        v = c, cnt = cn;
    }
    bool operator < (const data &a) const
    {
        return cnt == a.cnt ? v < a.v : cnt < a.cnt;
    }
};
vector<data> Add[MAXN], rm[MAXN];
set<data> st[MAXN];
long long ans;
int C[MAXN], Ad[MAXN];
bool died;
void dfs(int rt, int fa)
{
    set<data>::iterator it;
    for (int i = 0; i < Add[rt].size(); i++)
        st[rt].insert(Add[rt][i]);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa) continue;
        dfs(v[i].END, rt);
        if (died) return;
        if (st[v[i].END].size() > st[rt].size())
            swap(st[v[i].END], st[rt]), swap(Ad[v[i].END], Ad[rt]);
        for (it = st[v[i].END].begin(); it != st[v[i].END].end(); it++)
            st[rt].insert(data(it->v, C[it->v] = it->cnt - Ad[v[i].END] + Ad[rt]));
    }
    for (int i = 0; i < rm[rt].size(); i++)
        st[rt].erase(data(rm[rt][i].v, C[rm[rt][i].v]));
    if (rt == 1) return;
    if (st[rt].empty()) {died = 1; return;}
    ans += st[rt].begin()->cnt - Ad[rt];
    Ad[rt] += st[rt].begin()->cnt - Ad[rt];
}
signed main()
{
    int n = read(), m = read(), a, b, c;
    memset (first, -1, sizeof (first));
    for (int i = 1; i < n; i++)
    {
        a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read(), c = read();
        Add[a].push_back(data(i, c));
        rm[b].push_back(data(i, c));
        C[i] = c;
    }
    dfs(1, 0);
    if (died) printf ("-1");
    else printf ("%lld", ans);
}