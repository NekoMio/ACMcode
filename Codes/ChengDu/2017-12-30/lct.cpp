#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

struct data
{
	int L, R;
}blo[MAXN];

struct edge
{
	int END, next;
}v[MAXN << 1];
int first[MAXN], p;
int L[MAXN], R[MAXN], Color[MAXN];
bool vis[MAXN];
int S, E, Max;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
char s[MAXN];

void dfs(int rt, int fa, int dis)
{
	vis[rt] = 1;
	if (dis > Max) { Max = dis, S = rt; }
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt, dis + 1);
	}
}
void DFS(int rt, int fa, int dis)
{
	if (dis > Max) { Max = dis, E = rt; }
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS(v[i].END, rt, dis + 1);
	}
}

int Sum[MAXN], size[MAXN];

void DFS1(int rt, int fa)
{
	Sum[rt] = 0;
	size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS1(v[i].END, rt);
		Sum[rt] += Sum[v[i].END] + size[v[i].END];
		size[rt] += size[v[i].END]; 
	}
}
int ans = 0;
void DFS2(int rt, int fa, int dis)
{
	ans = ans + dis + Sum[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS2(v[i].END, rt, dis - size[v[i].END] + size[1] - size[v[i].END]);
	}
}

int main()
{
	freopen ("lct.in", "r", stdin);
	freopen ("lct.out", "w", stdout);
	memset (first, -1, sizeof(first));
	int n = read(), m = read();
	scanf ("%s", s + 1);
	for (int i = 1; i <= n; i++) Color[i] = s[i] == 'B';
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			S = 0, E = 0;
			Max = 0;
			dfs(i, 0, 0);
			Max = 0;
			DFS(S, 0, 0);
			blo[++cnt].L = S, blo[cnt].R = E;
		}
	}
	for (int i = 2; i <= cnt; i++)
	{
		add(blo[i].L, blo[i - 1].R);
		add(blo[i - 1].R, blo[i].L);
	}
	DFS1(1, 0);
	DFS2(1, 0, 0);
	printf ("%d\n-1\n", ans);
}
