#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN = 20005;

struct edge
{
	int END, next;
	int v;
}v[MAXN << 1]; 
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int size[MAXN], Max[MAXN], ans, sum, t[3], d[MAXN];
bool vis[MAXN];
int root;
void Get_root(int rt, int fa)
{
	size[rt] = 1, Max[rt] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (!vis[v[i].END] && v[i].END != fa)
		{
			Get_root(v[i].END, rt);
			size[rt] += size[v[i].END];
			Max[rt] = max(Max[rt], size[v[i].END]);
		}
	}
	Max[rt] = max(Max[rt], sum - size[rt]);
	if (Max[rt] < Max[root]) root = rt;
}

void dfs(int rt, int fa)
{
	t[d[rt]]++;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (!vis[v[i].END] && v[i].END != fa)
		{
			d[v[i].END] = (d[rt] + v[i].v) % 3;
			dfs(v[i].END, rt);
		}
	}
}

int Calc(int rt, int x)
{
	t[0] = t[1] = t[2] = 0;
	d[rt] = x;
	dfs(rt, 0);
	return t[1] * t[2] * 2 + t[0] * t[0];
}

void Solve(int rt)
{
	ans += Calc(rt, 0);
	vis[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (!vis[v[i].END])
		{
			ans -= Calc(v[i].END, v[i].v);
			root = 0, sum = size[v[i].END];
			Get_root(v[i].END, 0);
			Solve(root);
		}
	}
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	memset (first, -1, sizeof (first));
	int n = read();
	int a, b, c;
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read(), c = read() % 3;
		add(a, b, c);
		add(b, a, c);
	}
	Max[0] = sum = n;
	Get_root(1, 0);
	Solve(root);
	int G = gcd(ans, n * n);
	printf ("%d/%d\n", ans / G, n * n / G);
}