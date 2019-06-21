#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 2e5 + 5;
struct edge
{
	int S, END, next;
}v[MAXN << 1], e[MAXN << 1], ve[MAXN << 1];
int first[MAXN], p, firste[MAXN], pp, firstve[MAXN], ppp;
void Add(int a, int b)
{
	e[pp].END = b;
	e[pp].next = firste[a];
	firste[a] = pp++;
	// printf ("%d %d\n", a, b);
}
void add2(int a, int b)
{
	ve[ppp].END = b;
	ve[ppp].next = firstve[a];
	firstve[a] = ppp++;
}
int dfn[MAXN], low[MAXN], Index, PT;
bool iscut[MAXN];
vector<int> vc[MAXN];
stack<int> St;
bool Vis[MAXN];
int Color[MAXN];
void tarjan(int rt, int fa)
{
    dfn[rt] = low[rt] = ++Index;
    int S = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
	    if (!dfn[v[i].END])
	    {
	    	St.push(i);
	    	S++;
	        tarjan(v[i].END, rt);
	        low[rt] = min(low[rt], low[v[i].END]);
	        if (low[v[i].END] >= dfn[rt])
			{
				iscut[rt] = 1;
				PT++;
				int x;
				while (1)
				{
					x = St.top(), St.pop();
					if (Color[v[x].S] != PT)
					{
						Color[v[x].S] = PT;
						vc[PT].push_back(v[x].S);
					}
					if (Color[v[x].END] != PT)
					{
						Color[v[x].END] = PT;
						vc[PT].push_back(v[x].END);
					}
					if (v[i].END == v[x].END && rt == v[x].S) break;
					
				}
			}
	    }
	    else if (dfn[v[i].END] < dfn[rt] && rt != fa)
	    {
	    	St.push(i);
	        low[rt] = min(low[rt], dfn[v[i].END]);
    	}
    }
    if (fa < 0 && S == 1) iscut[rt] = 0;
}
int a[MAXN];
void add(int a, int b)
{
	v[p].S = a;
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int s;
int n, m;
int f[MAXN][20], len[MAXN][20], S[MAXN], dep[MAXN];
int ID[MAXN], IDCol[MAXN], Id, L[MAXN], R[MAXN], cnt;
void DFS1(int rt, int fa)
{
	L[rt] = ++cnt;
	f[rt][0] = fa;
	len[rt][0] = S[rt];
	for (int i = 1; i <= 19; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
	for (int i = 1; i <= 19; i++) len[rt][i] = len[rt][i - 1] + len[f[rt][i - 1]][i - 1];
	for (int i = firste[rt]; i != -1; i = e[i].next)
	{
		if (e[i].END == fa) continue;
		dep[e[i].END] = dep[rt] + 1;
		DFS1(e[i].END, rt);
	}
	R[rt] = cnt;
}
int LCA(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    for (int i = 19; i >= 0; i--)
        if (d & (1 << i))
            d -= (1 << i), x = f[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int Calc(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    int ans = 0;
    for (int i = 20; i >= 0; i--)
        if (d & (1 << i))
        {
            d -= (1 << i);
    		ans += len[x][i];
    		x = f[x][i];
    	}
   	return ans;
}
int st[MAXN], top, vis[MAXN], Q;
bool cmp(const int &a, const int &b)
{
    return L[a] < L[b];
}
#define In(a, b) (L[b] <= L[a] && R[a] <= R[b])
int DFS2(int rt, int fa)
{
	int ans = 0;
	if (fa) ans += Calc(rt, fa);
	for (int i = firstve[rt]; i != -1; i = ve[i].next)
	{
		if (ve[i].END == fa) continue;
		ans += DFS2(ve[i].END, rt);
	}
	return ans;
}
int Query(int len)
{
	int k = len;
	Q++;
	sort (a + 1, a + len + 1, cmp);
	for (int i = 1; i <= len; i++) vis[a[i]] = Q + 1;
    for (int i = 1; i < k; i++)
    {
        int lca = LCA(a[i], a[i + 1]);
        if (vis[lca] != Q + 1)
            a[++len] = lca, vis[lca] = Q + 1;
    }
    sort(a + 1, a + len + 1, cmp);
    int root = a[1];
    st[top = 1] = a[1];
    for (int i = 2; i <= len; i++)
    {
        while (top && !In(a[i], st[top])) top--;
        st[++top] = a[i];
        add2(st[top - 1], st[top]);
    }
    int ans = DFS2(root, 0) + S[root];
    for (int i = 1; i <= len; i++)
		firstve[a[i]] = -1;
   	return ans;
}
int c[MAXN];
int main()
{
	freopen ("test/01", "r", stdin);
	int T = read();
	while (T--)
	{
		memset (first, -1, sizeof (first)), p = 0;
		memset (firste, -1, sizeof (firste)), pp = 0;
		memset (firstve, -1, sizeof (firstve)), ppp = 0;
		memset (dfn, 0, sizeof (dfn));
		memset (low, 0, sizeof (low));
		memset (S, 0, sizeof (S));
		memset (ID, 0, sizeof (ID));
		memset (IDCol, 0, sizeof (IDCol));
		for (int i = 1; i <= PT; i++) vc[i].clear(); 
		memset (Color, 0, sizeof (Color)), PT = 0;
		memset (iscut, 0, sizeof (iscut));
		
		while (!St.empty()) St.pop();
		Index = 0, Id = 0, cnt = 0;
		n = read(), m = read();
		for (int i = 1; i <= m; i++)
		{
			int a = read(), b = read();
			add(a, b);
			add(b, a);
		}
		tarjan(1, -1);
		// fprintf (stderr, "---------");
		// for (int i = 1; i <= PT; i++)
		// {
		//	for (auto x : vc[i])
		//	printf ("%d ", x);
		//	printf ("\n");
		//}
		for (int i = 1; i <= n; i++) if (iscut[i]) ID[i] = ++Id, S[Id] = 1;
		for (int i = 1; i <= PT; i++)
		{
			IDCol[i] = ++Id;
			for (int j = 0; j < vc[i].size(); j++)
			{
				if (iscut[vc[i][j]])
				{
					Add(ID[vc[i][j]], Id);
					Add(Id, ID[vc[i][j]]);
				}
			}
		}
		DFS1(1, 0);
		// fprintf (stderr, "------");
		int q = read();
		// fprintf (stderr, "--%d\n", q);
		while (q--)
		{
			s = read();
			int tp = 0;
			for (int i = 1; i <= s; i++)
			{
				c[i] = read();
				if (iscut[c[i]]) a[i] = ID[c[i]], tp++;
				else a[i] = IDCol[Color[c[i]]];
			}
			sort(a + 1, a + s + 1);
			int Len = unique(a + 1, a + s + 1) - a - 1;
			printf ("%d\n", Query(Len) - tp);
			// fprintf (stderr, "%d\n", Q);
		}
	}
}
