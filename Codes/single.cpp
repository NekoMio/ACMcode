#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct edge
{
	int END, next;
} v[200005];
int first[100005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int Sum[100005], c[100005];
int a[100005];
int b[100005];
void dfs1(int rt, int fa, int Dep)
{
	Sum[rt] = a[rt];
	b[1] += Dep * a[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		dfs1(v[i].END, rt, Dep + 1);
		Sum[rt] += Sum[v[i].END];
	}
}
void Get_b(int rt, int fa)
{
	if (rt != 1)
		b[rt] = b[fa] + Sum[1] - 2 * Sum[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_b(v[i].END, rt);
	}
}
int Get_Sum(int rt, int fa)
{
	if (rt != 1)
		Sum[rt] = (b[fa] - b[rt] + Sum[1]) / 2;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_Sum(v[i].END, rt);
	}
}
int Get_a(int rt, int fa)
{
	a[rt] = Sum[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_a(v[i].END, rt);
		a[rt] -= Sum[v[i].END];
	}
}
int Get_c(int rt, int fa)
{
	if (rt != 1)
		c[rt] = b[rt] - b[fa];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa)
			continue;
		Get_c(v[i].END, rt);
	}
}
int n;
void worka()
{
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dfs1(1, 0, 0);
	Get_b(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", b[i]);
	printf("\n");
}
void workb()
{
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	Get_c(1, 0);
	long long All = 0;
	for (int i = 2; i <= n; i++)
		All += c[i];
	Sum[1] = (All + 2 * b[1]) / (n - 1);
	Get_Sum(1, 0);
	Get_a(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
int main()
{
	//freopen("single.in","r",stdin);
	//freopen("single.out","w",stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(Sum, 0, sizeof(Sum));
		memset(first, -1, sizeof(first));
		memset(c, 0, sizeof(c));
		p = 0;
		int s, e;
		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			scanf("%d%d", &s, &e);
			add(s, e);
			add(e, s);
		}
		int t;
		scanf("%d", &t);
		if (t)
			workb();
		else
			worka();
	}
	return 0;
}
