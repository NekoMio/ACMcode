#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 50005;
struct edge
{
	int END, next, S;
}v[N << 1];
int first[N], p;
int head[N], n, m, q;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].S = a;
	first[a] = p++;
}
int f[(N << 1) + 200][20]; 
queue<int> Q;
vector<int> In[N];
int du[N], dep[N];
int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 19; i >= 0; i--)
		if (d & (1 << i))
			d -= (1 << i), a = f[a][i];
	if (a == b) return a;
	for (int i = 19; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int main()
{
//	freopen("attack.in", "r", stdin);
//	freopen("attack.out", "w", stdout);
	n = read(), m = read(), q = read();
	memset (first, -1, sizeof (first));
	memset (head, -1, sizeof (head));
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		a = read(), b = read();
		In[b].push_back(a);
		add(a, b);
		du[b]++;
	}
	Q.push(1);
	dep[1] = 1;
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			du[v[i].END]--;
			if (du[v[i].END] == 0) Q.push(v[i].END);
		}
		if (k != 1)
		{
			int lca = 0;
			for (int i = 0; i < In[k].size(); i++)
			{
				if (lca == 0) lca = In[k][i];
				else lca = LCA(lca, In[k][i]);
			}
			f[k][0] = lca;
			dep[k] = dep[lca] + 1;
			for (int i = 1; i <= 19; i++)
				f[k][i] = f[f[k][i - 1]][i - 1];
		}
	}
	while (q--)
	{
		int k = read();
		int lca = read();
		for (int i = 2; i <= k; i++)
			lca = LCA(read(), lca);
		printf ("%d\n", dep[lca]);
	}
}
