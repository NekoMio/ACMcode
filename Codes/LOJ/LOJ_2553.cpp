#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
inline void gmax(long long &x, long long y) { if (x < y) x = y; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 366667;
const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Tree
{
	struct edge
	{
		int END, next, v;
	}v[MAXN << 1];
	int first[MAXN], p;
	Tree()
	{
		memset(first, -1, sizeof (first));
		p = 0;
	}
	int len[MAXN];
	long long dep[MAXN];
	void add(int a, int b, int c)
	{
		v[p].END = b;
		v[p].next = first[a];
		v[p].v = c;
		first[a] = p++;
	}
	long long d[22][MAXN], *dis;
	int id[MAXN], vc[MAXN << 1], Index;
	void DFS(int rt, int fa)
	{
		for (int i = first[rt]; i != -1; i = v[i].next)
		{
			if (v[i].END == fa) continue;
			dep[v[i].END] = dep[rt] + v[i].v;
			DFS(v[i].END, rt);
		}
	}
	int Max[MAXN], fa[MAXN], size[MAXN];
	
	void Init(int n)
	{
		Sum = size[0] = n;
		root = 0;
		DFS(1, 0);
		Solve(1, 0);
	}
}T1, T2;
int a[MAXN];
int main()
{
	// freopen ("wronganswer.in", "r", stdin);
	// freopen ("wronganswer.out", "w", stdout);
	n = read();
	for (int i = 1; i < n; i++)
	{
		int a = read(), b = read(), c = read();
		T1.add(a, b, c);
		T1.add(b, a, c);
	} 
	T1.Init(n);
	for (int i = 1; i < n; i++)
	{
		int a = read(), b = read(), c = read();
		T2.add(a, b, c);
		T2.add(b, a, c);
	}
	printf ("%lld\n", ans);
}

